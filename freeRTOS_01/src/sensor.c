#include "sensor.h"
#include "device.h"
#include "stm32f4_discovery.h"
#include <stdint.h>


uint8_t sensorDetected(void){
	uint32_t  Timeout_loop=0;
	uint32_t  Timeout_value=0x7FFFFF;
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(pbOk_GPIO_Port,pbOk_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(pbOk_GPIO_Port,pbOk_Pin)== GPIO_PIN_RESET) {
			while((HAL_GPIO_ReadPin(pbOk_GPIO_Port,pbOk_Pin)== GPIO_PIN_RESET)&& (Timeout_loop++<=Timeout_value));
			if (Timeout_loop>=Timeout_value)
			{
				HAL_GPIO_WritePin(bar9_GPIO_Port,bar9_Pin,GPIO_PIN_SET);
				HAL_Delay(1000);
				HAL_GPIO_WritePin(bar9_GPIO_Port,bar9_Pin,GPIO_PIN_RESET);
				HAL_Delay(1000);
			} else
			{
				//				  CLR(buzzer);
				FlagDetect=1;
			}

		}
	}
	return FlagDetect;
}
