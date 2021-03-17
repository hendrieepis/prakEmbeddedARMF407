#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_tim.h"

#define   APB1_TIMERFREQ 84000000
#define   PWM_fREQUENCY 10000 // dalam Hz
#define   TIM_PULSE_CH1_Prosen 75
#define   TIM_PULSE_CH2_Prosen 50
#define   TIM_PERIOD        APB1_TIMERFREQ / (PWM_fREQUENCY -1)
#define   TIM_PULSE_CH1    ((TIM_PERIOD + 1) * TIM_PULSE_CH1_Prosen) / 100 - 1
#define   TIM_PULSE_CH2    ((TIM_PERIOD + 1) * TIM_PULSE_CH2_Prosen) / 100 - 1
#define   TIM_PRESCALER    0     // APB1 prescaler

GPIO_InitTypeDef GPIO_InitStructure;
TIM_HandleTypeDef TimHandle;
TIM_OC_InitTypeDef PWMConfig;

static void MX_GPIO_Init(void);
static void MX_TIM_Init(void);
void SystemClock_Config(void);

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_TIM_Init();
	__HAL_TIM_SetCompare(&TimHandle, TIM_CHANNEL_1, TIM_PULSE_CH1);
	while(1)
	{
	}
}

void MX_GPIO_Init(void){
	__GPIOD_CLK_ENABLE();
	GPIO_InitStructure.Pin = GPIO_PIN_12 | GPIO_PIN_13;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Alternate = GPIO_AF2_TIM4;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void MX_TIM_Init(void){
	__TIM4_CLK_ENABLE();
	TimHandle.Instance = TIM4;
	TimHandle.Init.Period = TIM_PERIOD;
	TimHandle.Init.Prescaler =TIM_PRESCALER;
	TimHandle.Init.ClockDivision = 0;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_TIM_PWM_Init(&TimHandle);

	PWMConfig.Pulse = TIM_PULSE_CH1;
	PWMConfig.OCMode = TIM_OCMODE_PWM1;
	PWMConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
	PWMConfig.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	PWMConfig.OCIdleState = TIM_OCIDLESTATE_SET;
	PWMConfig.OCNIdleState= TIM_OCNIDLESTATE_RESET;
	PWMConfig.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&TimHandle,&PWMConfig,TIM_CHANNEL_1);

	PWMConfig.Pulse = TIM_PULSE_CH2;
	PWMConfig.OCMode = TIM_OCMODE_PWM1;
	PWMConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
	PWMConfig.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	PWMConfig.OCIdleState = TIM_OCIDLESTATE_SET;
	PWMConfig.OCNIdleState= TIM_OCNIDLESTATE_RESET;
	PWMConfig.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&TimHandle,&PWMConfig,TIM_CHANNEL_2);

	HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2);
}

/** System Clock Configuration
 */
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
