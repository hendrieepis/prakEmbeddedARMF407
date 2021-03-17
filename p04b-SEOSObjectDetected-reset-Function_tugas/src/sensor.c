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
#include "seos.h"
uint32_t mstick;


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


uint8_t sensorDetectedTimeout(void){
// alpha version 0.0.1
	static unsigned char debounce=0xFF;

	unsigned char detectedFLag=0;
	static uint32_t  Timeout_loop=0;
	uint32_t  Timeout_value=0x700;
	if(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET){
		if ((Timeout_loop++<=Timeout_value))
			debounce=(debounce<<1);
		else {
			printf("Err:001-btn errorlo \n\r");
			if ((milist_seos - mstick) >50) {
				HAL_GPIO_TogglePin(led2_GPIO_Port,led2_Pin);
				mstick=milist_seos;
			}
			debounce=0xFF;
		}

	} else {
		debounce= (debounce<<1)|1;
		Timeout_loop=0;
		mstick=milist_seos;
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
