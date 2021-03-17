/*
 * task.c
 *
 *  Created on: Apr 10, 2016
 *      Author: hendri
 */
#include "task.h"
#include "counter.h"
#include "stm32f4xx.h"
#include "device.h"
#include "sensor.h"

unsigned char bouncing=0xFF;
unsigned char bouncing2=0xFF;
void Task_Init(void){

}

void Task_Run(void){
	if(sensorDetected())
		CounterUpdate();
	if(resetDetected())
		CounterZero();
	counterShow();
}

