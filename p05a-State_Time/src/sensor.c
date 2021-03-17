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
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		detectedFLag=1;
	}
	return detectedFLag;
}

uint8_t resetDetected(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(pbRight_GPIO_Port,pbRight_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		detectedFLag=1;
	}
	return detectedFLag;
}

