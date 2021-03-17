/*
 * task.c
 *
 *  Created on: Apr 10, 2016
 *      Author: hendri
 */
#include "task.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
unsigned char bouncing=0xFF;
void Task_Init(void){

}
void Task_Run(void){
}


void LED_Flash0_Update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(bar0_GPIO_Port,bar0_Pin);
//	printf("ok \n\r");
}

void LED_Flash1_Update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(bar1_GPIO_Port,bar1_Pin);
}

void LED_Flash2_Update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(bar2_GPIO_Port,bar2_Pin);
}

void LED_Flash3_Update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(bar3_GPIO_Port,bar3_Pin);
}


