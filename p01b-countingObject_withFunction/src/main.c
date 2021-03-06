
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
			
UART_HandleTypeDef huart2;
uint16_t count;

//  start device.h
//define General IO on Development Board
#define bar0_Pin GPIO_PIN_7
#define bar0_GPIO_Port GPIOD
#define bar1_Pin GPIO_PIN_5
#define bar1_GPIO_Port GPIOB
#define bar2_Pin GPIO_PIN_4
#define bar2_GPIO_Port GPIOB
#define bar3_Pin GPIO_PIN_2
#define bar3_GPIO_Port GPIOE
#define bar5_Pin GPIO_PIN_4
#define bar5_GPIO_Port GPIOE
#define bar4_Pin GPIO_PIN_5
#define bar4_GPIO_Port GPIOE
#define bar7_Pin GPIO_PIN_6
#define bar7_GPIO_Port GPIOE
#define bar6_Pin GPIO_PIN_13
#define bar6_GPIO_Port GPIOC
#define bar9_Pin GPIO_PIN_14
#define bar9_GPIO_Port GPIOC
#define bar8_Pin GPIO_PIN_15

#define bar8_GPIO_Port GPIOC
#define pbUp_Pin GPIO_PIN_4
#define pbUp_GPIO_Port GPIOC
#define pbRight_Pin GPIO_PIN_5
#define pbRight_GPIO_Port GPIOC
#define pbDown_Pin GPIO_PIN_0
#define pbDown_GPIO_Port GPIOB
#define pbLeft_Pin GPIO_PIN_1
#define pbLeft_GPIO_Port GPIOB
#define pbOk_Pin GPIO_PIN_10
#define pbOk_GPIO_Port GPIOE
#define pbCancel_Pin GPIO_PIN_15
#define pbCancel_GPIO_Port GPIOE
#define dipSW3_Pin GPIO_PIN_11
#define dipSW3_GPIO_Port GPIOB
#define dipSW4_Pin GPIO_PIN_12
#define dipSW4_GPIO_Port GPIOB
#define dipSW2_Pin GPIO_PIN_10
#define dipSW2_GPIO_Port GPIOD
#define dipSW1_Pin GPIO_PIN_11
#define dipSW1_GPIO_Port GPIOD
#define buzzer_Pin GPIO_PIN_11
#define buzzer_GPIO_Port GPIOC

//define General IO on STM32F4Discovery BOard
#define led0_Pin GPIO_PIN_12
#define led0_GPIO_Port GPIOD
#define led1_Pin GPIO_PIN_13
#define led1_GPIO_Port GPIOD
#define led2_Pin GPIO_PIN_14
#define led2_GPIO_Port GPIOD
#define led3_Pin GPIO_PIN_15
#define led3_GPIO_Port GPIOD
#define userButton_Pin GPIO_PIN_0
#define userButton_GPIO_Port GPIOA

// hardwareinit.h dan hardwareinit.c
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

//counter.h dan counter.c
void counterShow(void);
void CounterUpdate(void);

// sensor.c dan sensor.h
uint8_t sensorDetected(void);

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	while(1){
        counterShow();
        if(sensorDetected()){
        	CounterUpdate();
        }
	}
}

void CounterUpdate(void){
	++count;
}
void counterShow(void){
	//Counter Show
	HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,count & (1<<0));
	HAL_GPIO_WritePin(bar1_GPIO_Port,bar1_Pin,count & (1<<1));
	HAL_GPIO_WritePin(bar2_GPIO_Port,bar2_Pin,count & (1<<2));
	HAL_GPIO_WritePin(bar3_GPIO_Port,bar3_Pin,count & (1<<3));
	HAL_GPIO_WritePin(bar4_GPIO_Port,bar4_Pin,count & (1<<4));
	HAL_GPIO_WritePin(bar5_GPIO_Port,bar5_Pin,count & (1<<5));
	HAL_GPIO_WritePin(bar6_GPIO_Port,bar6_Pin,count & (1<<6));
	HAL_GPIO_WritePin(bar7_GPIO_Port,bar7_Pin,count & (1<<7));
}

uint8_t sensorDetected(void){
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void MX_GPIO_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOE_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOE, bar3_Pin|bar5_Pin|bar4_Pin|bar7_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOC, bar6_Pin|bar9_Pin|bar8_Pin|buzzer_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOD, led0_Pin|led1_Pin|led2_Pin|led3_Pin
	                          |bar0_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOB, bar2_Pin|bar1_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pins : bar3_Pin bar5_Pin bar4_Pin bar7_Pin */
	  GPIO_InitStruct.Pin = bar3_Pin|bar5_Pin|bar4_Pin|bar7_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	  /*Configure GPIO pins : bar6_Pin bar9_Pin bar8_Pin buzzer_Pin */
	  GPIO_InitStruct.Pin = bar6_Pin|bar9_Pin|bar8_Pin|buzzer_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pin : userButton_Pin */
	  GPIO_InitStruct.Pin = userButton_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(userButton_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : pbUp_Pin pcRight_Pin */
	  GPIO_InitStruct.Pin = pbUp_Pin|pbRight_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pins : pbDown_Pin pbLeft_Pin dipSW3_Pin dipSW4_Pin */
	  GPIO_InitStruct.Pin = pbDown_Pin|pbLeft_Pin|dipSW3_Pin|dipSW4_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*Configure GPIO pins : pbOk_Pin pbCancel_Pin */
	  GPIO_InitStruct.Pin = pbOk_Pin|pbCancel_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	  /*Configure GPIO pins : dipSW2_Pin dipSW1_Pin */
	  GPIO_InitStruct.Pin = dipSW2_Pin|dipSW1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	  /*Configure GPIO pins : led0_Pin led1_Pin led2_Pin led3_Pin
	                           bar0_Pin */
	  GPIO_InitStruct.Pin = led0_Pin|led1_Pin|led2_Pin|led3_Pin
	                          |bar0_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	  /*Configure GPIO pins : bar2_Pin bar1_Pin */
	  GPIO_InitStruct.Pin = bar2_Pin|bar1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
