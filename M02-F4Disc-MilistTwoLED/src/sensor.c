#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
#include "sensor.h"
uint8_t sensorDetected(void){
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
