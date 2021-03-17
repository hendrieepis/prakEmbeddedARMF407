
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
uint32_t onTime1 = 100;           // milliseconds of on-time
uint32_t offTime1 = 1000;          // milliseconds of off-time

uint32_t onTime2 = 1000;           // milliseconds of on-time
uint32_t offTime2 = 100;          // milliseconds of off-time

bool ledState1 = false;
bool ledState2 = false;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	while(1){
		currentMilist=HAL_GetTick();
		if((ledState1==HIGH)&&(currentMilist-previousMilist1 > onTime1)) {
			previousMilist1=currentMilist;
			ledState1=LOW;
			HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,ledState1);
		} else if ((ledState1==LOW)&&(currentMilist-previousMilist1 > offTime1)) {
			previousMilist1=currentMilist;
			ledState1=HIGH;
			HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,ledState1);
		}

		if((ledState2==HIGH)&&(currentMilist-previousMilist2 > onTime2)) {
			previousMilist2=currentMilist;
			ledState2=LOW;
			HAL_GPIO_WritePin(led0_GPIO_Port,led1_Pin,ledState2);
		} else if ((ledState2==LOW)&&(currentMilist-previousMilist2 > offTime2)) {
			previousMilist2=currentMilist;
			ledState2=HIGH;
			HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,ledState2);
		}


	}
}





