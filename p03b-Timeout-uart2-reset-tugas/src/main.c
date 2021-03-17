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
			
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	while(1){
		/* User code here      -----------------------------------------------*/
        counterShow();
        if(sensorDetected()){
        	CounterUpdate();
        	printf ("count:%d \n\r",CounterGetValue());
        }

        if(resetDetected()){
            CounterZero();
        	printf ("count:%d \n\r",CounterGetValue());
        }
		/* User code here      -----------------------------------------------*/
	}
}

