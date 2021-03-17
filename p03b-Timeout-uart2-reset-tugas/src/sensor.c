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
	uint32_t  Timeout_loop=0;
	uint32_t  Timeout_value=0x7FFFFF;
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)==GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(!HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)) {
			while((!HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin))&& (Timeout_loop++<=Timeout_value));
			if (Timeout_loop>=Timeout_value)
			{
				HAL_GPIO_WritePin(buzzer_GPIO_Port,buzzer_Pin,GPIO_PIN_SET);
				HAL_Delay(1000);
				HAL_GPIO_WritePin(buzzer_GPIO_Port,buzzer_Pin,GPIO_PIN_RESET);
				HAL_Delay(1000);
				printf("Err:001-btn1 error \n\r");
			} else
			{
				//				  CLR(buzzer);
				FlagDetect=1;
			}
		}
	}
	return FlagDetect;
}

uint8_t resetDetected(void){
	uint32_t  Timeout_loop=0;
	uint32_t  Timeout_value=0x7FFFFF;
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(pbRight_GPIO_Port,pbRight_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(pbRight_GPIO_Port,pbRight_Pin)== GPIO_PIN_RESET) {
			while((HAL_GPIO_ReadPin(pbRight_GPIO_Port,pbRight_Pin)== GPIO_PIN_RESET)&& (Timeout_loop++<=Timeout_value));
			if (Timeout_loop>=Timeout_value)
			{
				HAL_GPIO_WritePin(buzzer_GPIO_Port,buzzer_Pin,GPIO_PIN_SET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(buzzer_GPIO_Port,buzzer_Pin,GPIO_PIN_RESET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(buzzer_GPIO_Port,buzzer_Pin,GPIO_PIN_SET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(buzzer_GPIO_Port,buzzer_Pin,GPIO_PIN_RESET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(buzzer_GPIO_Port,buzzer_Pin,GPIO_PIN_SET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(buzzer_GPIO_Port,buzzer_Pin,GPIO_PIN_RESET);
				HAL_Delay(100);
				printf("Err:002-btn2 error \n\r");
			} else
			{
				//				  CLR(buzzer);
				FlagDetect=1;
			}

		}
	}
	return FlagDetect;
}
