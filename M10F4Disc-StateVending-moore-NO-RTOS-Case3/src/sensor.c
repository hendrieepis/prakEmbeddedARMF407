#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
#include "sensor.h"
uint8_t Coin500Detected(void){
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(40);
		if(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}

uint8_t Coin1000Detected(void){
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(pbRight_GPIO_Port,pbRight_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(40);
		if(HAL_GPIO_ReadPin(pbRight_GPIO_Port,pbRight_Pin)== GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(pbRight_GPIO_Port,pbRight_Pin)== GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}

uint8_t returnDetected(void){
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(pbCancel_GPIO_Port,pbCancel_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(40);
		if(HAL_GPIO_ReadPin(pbCancel_GPIO_Port,pbCancel_Pin)== GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(pbCancel_GPIO_Port,pbCancel_Pin)== GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}

uint8_t prosesDetected(void){
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(pbOk_GPIO_Port,pbOk_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(40);
		if(HAL_GPIO_ReadPin(pbOk_GPIO_Port,pbOk_Pin)== GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(pbOk_GPIO_Port,pbOk_Pin)== GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
