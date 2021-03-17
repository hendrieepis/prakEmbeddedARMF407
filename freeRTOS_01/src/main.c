#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "hardwareinit.h"
#include "uart.h"
#include "task.h"
#include "seos.h"


int main(void)
{
	Task_Init();
	HAL_Init();
	SystemClock_Config();
	GPIOInitConfiguration();
	UartInitConfiguration();
	seos_Init(2);

	while(1){
	}
}



