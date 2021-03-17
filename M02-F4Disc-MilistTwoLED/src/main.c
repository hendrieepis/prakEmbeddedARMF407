
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
uint32_t currentMilist,previousMilist1,previousMilist2;
uint32_t interval1 = 100;           // milliseconds of on-time
uint32_t interval2 = 1000;          // milliseconds of off-time
bool ledState1 = false;
bool ledState2 = false;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	while(1){
		currentMilist=HAL_GetTick();
		if((currentMilist-previousMilist1) > interval1) {
			previousMilist1=currentMilist;
			if(ledState1==LOW) {
				ledState1=HIGH;
			} else {
				ledState1=LOW;
			}
			HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,ledState1);
		}

		if((currentMilist-previousMilist2) > interval2) {
			previousMilist2=currentMilist;
			if(ledState2==LOW) {
				ledState2=HIGH;
			} else {
				ledState2=LOW;
			}
			HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,ledState2);
		}
	}
}





