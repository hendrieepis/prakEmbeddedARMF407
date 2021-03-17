
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
#include "counter.h"
#include "sensor.h"
#include "hardwareinit.h"
#include <stdbool.h>
uint32_t  currentMilist;
uint32_t  previusMilist1;
uint32_t  previusMilist2;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();

	while(1){
		//task 1
		currentMilist=HAL_GetTick();
		if(currentMilist-previusMilist1 > 200) {
			HAL_GPIO_TogglePin(led0_GPIO_Port,led0_Pin);
			previusMilist1=currentMilist;
		}

		if (HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)==GPIO_PIN_RESET) {
			HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_SET);
			previusMilist2=currentMilist;
		}
		else if(currentMilist-previusMilist2 >= 2000) {
			HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
		}

	}
}





