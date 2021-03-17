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

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	while(1){
		/* User code here      -----------------------------------------------*/

        counterShow();
        if(sensorDetected()){
        	CounterUpdate();
        }
        if(resetDetected()){
            CounterZero();
        }
	}
}

