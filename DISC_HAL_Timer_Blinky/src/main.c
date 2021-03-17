#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
			
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
void SystemClock_Config(void);

TIM_HandleTypeDef TIM_Handle;
int main(void)
{
	// init HAL and IO
	HAL_Init();
	SystemClock_Config();
	__GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_initStruct;
	GPIO_initStruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_initStruct.Pin=GPIO_PIN_12;
	GPIO_initStruct.Pull=GPIO_NOPULL;
	GPIO_initStruct.Speed=GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOD,&GPIO_initStruct);
	// init timer
	__TIM4_CLK_ENABLE();
	TIM_Handle.Init.Prescaler = 42000;
	TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Handle.Init.Period = 999;
	TIM_Handle.Instance = TIM4;   //Same timer whose clocks we enabled
	HAL_TIM_Base_Init(&TIM_Handle);     // Init timer
	HAL_TIM_Base_Start_IT(&TIM_Handle); // start timer interrupts
	HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
	while(1)
	{
	}
}

void TIM4_IRQHandler(void)
{
	if (__HAL_TIM_GET_FLAG(&TIM_Handle, TIM_FLAG_UPDATE) != RESET)      //In case other interrupts are also running
	{
		if (__HAL_TIM_GET_ITSTATUS(&TIM_Handle, TIM_IT_UPDATE) != RESET)
		{
			__HAL_TIM_CLEAR_FLAG(&TIM_Handle, TIM_FLAG_UPDATE);
			/*put your code here */
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
		}
	}
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
