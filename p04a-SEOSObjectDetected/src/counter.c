/*
 * counter.c
 *
 *  Created on: Sep 27, 2017
 *      Author: hendri
 */
#include "counter.h"
#include "stdint.h"
#include "device.h"
#include "stm32f4xx.h"
#include "uart.h"

uint8_t count;
void CounterUpdate(void){
	++count;
}
void counterShow(void){
	//Counter Show
	HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,count & (1<<0));
	HAL_GPIO_WritePin(bar1_GPIO_Port,bar1_Pin,count & (1<<1));
	HAL_GPIO_WritePin(bar2_GPIO_Port,bar2_Pin,count & (1<<2));
	HAL_GPIO_WritePin(bar3_GPIO_Port,bar3_Pin,count & (1<<3));
	HAL_GPIO_WritePin(bar4_GPIO_Port,bar4_Pin,count & (1<<4));
	HAL_GPIO_WritePin(bar5_GPIO_Port,bar5_Pin,count & (1<<5));
	HAL_GPIO_WritePin(bar6_GPIO_Port,bar6_Pin,count & (1<<6));
	HAL_GPIO_WritePin(bar7_GPIO_Port,bar7_Pin,count & (1<<7));
}

void CounterZero(void){
	count=0;
}

uint8_t CounterGetValue(void){
	return (count);
}


