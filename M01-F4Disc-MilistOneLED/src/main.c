
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
#include "counter.h"
#include "sensor.h"
#include "hardwareinit.h"
#include <stdbool.h>


#define LOW false
#define HIGH true

UART_HandleTypeDef huart2;
uint32_t currentMilist,previousMilist;
uint32_t interval=500;
bool ledState = false;
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	while(1){
		currentMilist=HAL_GetTick();
		if((currentMilist-previousMilist) > interval) {
			previousMilist=currentMilist;
			if(ledState==LOW) {
				ledState=HIGH;
			} else {
				ledState=LOW;
			}
			HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,ledState);
		}
	}
}





