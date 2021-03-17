
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
#include "counter.h"
#include "sensor.h"
#include "hardwareinit.h"
#include <stdbool.h>
uint32_t  currentMilist;
uint32_t  previousMilist1;
uint32_t  previousMilist2;
uint32_t  previousMilist3;
uint32_t  previousMilist4;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();

	while(1){
		//task 1
		currentMilist=HAL_GetTick();
		if(currentMilist-previousMilist1 > 200) {
			HAL_GPIO_TogglePin(led0_GPIO_Port,led0_Pin);
			previousMilist1=currentMilist;
		}

		//task 2
		currentMilist=HAL_GetTick();
		if(currentMilist-previousMilist2 > 1000) {
			HAL_GPIO_TogglePin(led1_GPIO_Port,led1_Pin);
			previousMilist2=currentMilist;
		}

		// task 3
		if (HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)==GPIO_PIN_RESET) {
			HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_SET);
			previousMilist3=currentMilist;
		}
		else if(currentMilist-previousMilist3 >= 2000) {
			HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_RESET);
		}

		// task 4
		if (HAL_GPIO_ReadPin(pbRight_GPIO_Port,pbRight_Pin)==GPIO_PIN_RESET) {
			HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_SET);
			previousMilist4=currentMilist;
		}
		else if(currentMilist-previousMilist4 >= 1000) {
			HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_RESET);
		}

	}
}





