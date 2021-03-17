#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dma.h"


//--------------------------------------------------------------
// Liste aller DAC-Kurvenformen
// (keine Nummer doppelt und von 0 beginnend)
//--------------------------------------------------------------
typedef enum {
  DAC_WAVE_OFF          = 0, // Dauer Lo-Pegel       [Len=1]
  DAC_WAVE1_SINUS       = 1, // Waveform1 (Sinus)    [Len=32]
  DAC_WAVE2_SAWTOOTH   = 2, // Waveform2 (S�gezahn) [Len=17]
  DAC_WAVE3_TRIANGLE     = 3, // Waveform3 (TRIANGLE)  [Len=32]
  DAC_WAVE4_SQUAREWAVE    = 4  // Waveform4 (SQUAREWAVE) [Len=4]
}DAC_DMA_WAVE_NAME_t;


//--------------------------------------------------------------
// Timer Grundeinstellungen
//--------------------------------------------------------------
#define  DAC_DMA_DEF_PERIODE   255  // default periode
#define  DAC_DMA_DEF_PRESCALE   10  // default prescaler


//--------------------------------------------------------------
// Struktur einer DAC-Kurvenform
//--------------------------------------------------------------
typedef struct {
  DAC_DMA_WAVE_NAME_t name;
  const uint16_t *ptr;
  uint16_t wave_len;
}DAC_WAVE_t;


//--------------------------------------------------------------
// Timer Einstellung
// Moegliche Timer fuer den DAC1 Trigger :
//   Timer2, Timer4, Timer5, Timer6, Timer7
//   (Timer8 h�ngt an APB2)
//--------------------------------------------------------------

// einen Timer ausw�hlen
//#define DAC_DMA_T1_TIM2            2
//#define DAC_DMA_T1_TIM4            4
//#define DAC_DMA_T1_TIM5            5
#define DAC_DMA_T1_TIM6            6
//#define DAC_DMA_T1_TIM7            7


#ifdef DAC_DMA_T1_TIM2
  #define DAC_TIM1_TRG            DAC_Trigger_T2_TRGO
  #define DAC_TIM1_CLK            RCC_APB1Periph_TIM2
  #define DAC_TIM1_NAME           TIM2
#elif defined DAC_DMA_T1_TIM4
  #define DAC_TIM1_TRG            DAC_Trigger_T4_TRGO
  #define DAC_TIM1_CLK            RCC_APB1Periph_TIM4
  #define DAC_TIM1_NAME           TIM4
#elif defined DAC_DMA_T1_TIM5
  #define DAC_TIM1_TRG            DAC_Trigger_T5_TRGO
  #define DAC_TIM1_CLK            RCC_APB1Periph_TIM5
  #define DAC_TIM1_NAME           TIM5
#elif defined DAC_DMA_T1_TIM6
  #define DAC_TIM1_TRG            DAC_Trigger_T6_TRGO
  #define DAC_TIM1_CLK            RCC_APB1Periph_TIM6
  #define DAC_TIM1_NAME           TIM6
#elif defined DAC_DMA_T1_TIM7
  #define DAC_TIM1_TRG            DAC_Trigger_T7_TRGO
  #define DAC_TIM1_CLK            RCC_APB1Periph_TIM7
  #define DAC_TIM1_NAME           TIM7
#endif

//--------------------------------------------------------------
// Adressen der DACs
// (siehe Seite 55 vom Referenz Manual)
//--------------------------------------------------------------
#define DAC_BASE_ADR        ((uint32_t)0x40007400)

//--------------------------------------------------------------
// Adressen der Register
// (siehe Seite 325 vom Referenz Manual)
//--------------------------------------------------------------
#define DAC1_REG_DHR_12R1_OFFSET   0x08  // 12bit, rechtsb�ndig
#define DAC2_REG_DHR_12R2_OFFSET   0x14  // 12bit, rechtsb�ndig

#define DAC1_DHR_12R1_ADDRESS    (DAC_BASE_ADR | DAC1_REG_DHR_12R1_OFFSET)
#define DAC2_DHR_12R2_ADDRESS    (DAC_BASE_ADR | DAC2_REG_DHR_12R2_OFFSET)

//--------------------------------------------------------------
// Global function
//--------------------------------------------------------------
void UB_DAC_DMA_Init(void);
void UB_DAC_DMA_SetWaveform1(DAC_DMA_WAVE_NAME_t wave);
void UB_DAC_DMA_SetFrq1(uint16_t vorteiler, uint16_t periode);

//--------------------------------------------------------------
// Global Variable
//--------------------------------------------------------------
DAC_InitTypeDef  DAC_InitStructure;  // MUSS Global sein (BUGFIX)

//--------------------------------------------------------------
// interne Funktionen
//--------------------------------------------------------------
void P_DAC_DMA_InitIO1(void);
void P_DAC_DMA_InitTIM1(void);
void P_DAC_DMA_InitDAC1(void);


//--------------------------------------------------------------
// standard Kurvenform f�r DAC=AUS
//--------------------------------------------------------------
const uint16_t WaveOff[] = {0}; // Dauer Lo-Pegel

//--------------------------------------------------------------
// Kurvenform die Ausgegeben werden soll als Array
// von 12bit Werten (0 bis 4095)
//--------------------------------------------------------------
const uint16_t Wave1[] = { // Sinus
  2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056,
  4095, 4056, 3939, 3750, 3495, 3185, 2831, 2447,
  2047, 1647, 1263,  909,  599,  344,  155,   38,
     0,   38,  155,  344,  599,  909, 1263, 1647
};

//--------------------------------------------------------------
// Kurvenform die Ausgegeben werden soll als Array
// von 12bit Werten (0 bis 4095)
//--------------------------------------------------------------
const uint16_t Wave2[] = { // S�gezahn
     0,  256,  512,  768, 1024, 1280, 1536, 1792,
  2048, 2304, 2560, 2816, 3072, 3328, 3584, 3840,
  4095
};

//--------------------------------------------------------------
// Kurvenform die Ausgegeben werden soll als Array
// von 12bit Werten (0 bis 4095)
//--------------------------------------------------------------
const uint16_t Wave3[] = { // TRIANGLE
     0,  256,  512,  768, 1024, 1280, 1536, 1792,
  2048, 2304, 2560, 2816, 3072, 3328, 3584, 3840,
  4095, 3840, 3584, 3328, 3072, 2816, 2560, 2304,
  2048, 1792, 1536, 1280, 1024,  768,  512,  256
};


//--------------------------------------------------------------
// Kurvenform die Ausgegeben werden soll als Array
// von 12bit Werten (0 bis 4095)
//--------------------------------------------------------------
const uint16_t Wave4[] = { // SQUAREWAVE
     0,  0,  4095,  4095
};


//--------------------------------------------------------------
// Definition aller Kurvenformen
// Reihenfolge wie bei DAC_DMA_WAVE_NAME_t
//--------------------------------------------------------------
const DAC_WAVE_t DAC_WAVE[] = {
  // Name             , Kurve  , L�nge
  {DAC_WAVE_OFF       , WaveOff, 1},
  {DAC_WAVE1_SINUS    , Wave1  , 32},
  {DAC_WAVE2_SAWTOOTH, Wave2  , 17},
  {DAC_WAVE3_TRIANGLE  , Wave3  , 32},
  {DAC_WAVE4_SQUAREWAVE , Wave4  , 4},
};

int  main ( void )
{
	SystemInit();
  //activate settings // Quartz

  // Init the DAC in DMA mode (DAC-1 and DAC-2)
  UB_DAC_DMA_Init ();

  UB_DAC_DMA_SetWaveform1 (DAC_WAVE1_SINUS);

  // make Frq from the sine signal at 1Hz
  // The sine signal is 32 values ​​long
  // F = 84MHz / 300/8750/32 = 1 Hz
  UB_DAC_DMA_SetFrq1 (3,874);
  while (1)
  {
  }
}


void UB_DAC_DMA_Init()
{
    P_DAC_DMA_InitIO1();
    P_DAC_DMA_InitTIM1();
    P_DAC_DMA_InitDAC1();
    UB_DAC_DMA_SetWaveform1(DAC_WAVE_OFF);
}


void UB_DAC_DMA_SetWaveform1(DAC_DMA_WAVE_NAME_t wave)
{
  DMA_InitTypeDef DMA_InitStructure;

  // Clock Enable (DMA)
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

  // DMA init (DMA1, Channel7, Stream5)
  DMA_Cmd(DMA1_Stream5, DISABLE);
  DMA_DeInit(DMA1_Stream5);
  DMA_InitStructure.DMA_Channel = DMA_Channel_7;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)DAC1_DHR_12R1_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)DAC_WAVE[wave].ptr;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = DAC_WAVE[wave].wave_len;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream5, &DMA_InitStructure);

  // DMA enable
  DMA_Cmd(DMA1_Stream5, ENABLE);
  // DMA-DAC enable
  DAC_DMACmd(DAC_Channel_1, ENABLE);
}

//--------------------------------------------------------------
// stellt die Frequenz f�r DAC1 ein
// Grundfrequenz = 2*APB1 (APB1=42MHz) => TIM_CLK=84MHz
// vorteiler : 0 bis 0xFFFF
// periode   : 0 bis 0xFFFF
//
// Ausgangs-Frq = TIM_CLK/(vorteiler+1)/(periode+1)/wave_len
//--------------------------------------------------------------
void UB_DAC_DMA_SetFrq1(uint16_t vorteiler, uint16_t periode)
{
  TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Period = periode;
  TIM_TimeBaseStructure.TIM_Prescaler = vorteiler;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(DAC_TIM1_NAME, &TIM_TimeBaseStructure);
}

void P_DAC_DMA_InitIO1(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  // Clock Enable (GPIO)
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  // Config des DAC-Pins als Analog-Ausgang
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void P_DAC_DMA_InitTIM1(void)
{
  TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;

  // Clock enable (Timer)
  RCC_APB1PeriphClockCmd(DAC_TIM1_CLK, ENABLE);

  // Timer-Config
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Period = DAC_DMA_DEF_PERIODE;
  TIM_TimeBaseStructure.TIM_Prescaler = DAC_DMA_DEF_PRESCALE;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(DAC_TIM1_NAME, &TIM_TimeBaseStructure);

  // Trigger
  TIM_SelectOutputTrigger(DAC_TIM1_NAME, TIM_TRGOSource_Update);

  // Timer enable
  TIM_Cmd(DAC_TIM1_NAME, ENABLE);
}

void P_DAC_DMA_InitDAC1(void)
{
  // Clock Enable (DAC)
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

  // DAC init
  DAC_InitStructure.DAC_Trigger = DAC_TIM1_TRG;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

  // DAC enable
  DAC_Cmd(DAC_Channel_1, ENABLE);
}


