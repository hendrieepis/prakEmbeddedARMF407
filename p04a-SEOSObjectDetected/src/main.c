/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
#include "counter.h"
#include "sensor.h"
#include "hardwareinit.h"
#include "uart.h"
#include "seos.h"
			
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	SCH_init(2);
	while(1){
		/* User code here      -----------------------------------------------*/
		//		HAL_GPIO_TogglePin(led0_GPIO_Port,led0_Pin);
		//		HAL_Delay(1000);
		/* User code here      -----------------------------------------------*/
	}
}

