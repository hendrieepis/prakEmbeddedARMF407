
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
uint32_t OnTime = 100;           // milliseconds of on-time
uint32_t OffTime = 1000;          // milliseconds of off-time
bool ledState = false;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	while(1){
		currentMilist=HAL_GetTick();
		if((ledState==HIGH)&&(currentMilist-previousMilist > OnTime)) {
			ledState=LOW;
			previousMilist=currentMilist;
			HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,ledState);
		} if((ledState==LOW)&&(currentMilist-previousMilist > OffTime)) {
			ledState=HIGH;
			previousMilist=currentMilist;
			HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,ledState);
		}
	}
}





