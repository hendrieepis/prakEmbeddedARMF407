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

void task1_update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(bar0_GPIO_Port,bar0_Pin);
}

void task2_update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(bar1_GPIO_Port,bar1_Pin);
}


void task3_update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(bar2_GPIO_Port,bar2_Pin);
}


void task4_update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(bar3_GPIO_Port,bar3_Pin);
}



