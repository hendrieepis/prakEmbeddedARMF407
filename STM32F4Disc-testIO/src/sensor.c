/*
 * sensor.c
 *
 *  Created on: Sep 27, 2017
 *      Author: hendri
 */
#include "sensor.h"
#include "stm32f4xx.h"
#include "device.h"
#include "stdint.h"
uint8_t sensorDetected(void){
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(userButton_GPIO_Port,userButton_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(userButton_GPIO_Port,userButton_Pin)== GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(userButton_GPIO_Port,userButton_Pin)== GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
