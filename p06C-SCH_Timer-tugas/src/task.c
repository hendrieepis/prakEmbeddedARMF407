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
#include "counter.h"
#include "sensor.h"
unsigned char bouncing=0xFF;
void Task_Init(void){

}
void Task_Run(void){
}


void task1_update(void)
{
	if (sensorDetected())
		CounterUpdate();
	if (resetDetected())
		CounterZero();
	counterShow();
}

void task2_update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(led1_GPIO_Port,led1_Pin);
}

void task3_update(void)
{
	//dummy running task
	printf("ok lah \n\r");
}
