/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
#include "counter.h"
#include "sensor.h"
#include "hardwareinit.h"
void CWLED(void);
void CCWLED(void);
uint8_t DIR=0;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
    CWLED();
	while(1){
//		/* User code here      -----------------------------------------------*/
		CWLED();
		/* User code here      -----------------------------------------------*/
	}
}

void CWLED(void){
	HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_RESET);
	HAL_Delay(300);

	HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_RESET);
	HAL_Delay(300);

	HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_RESET);
	HAL_Delay(300);

	HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_RESET);
	HAL_Delay(300);
}

void CCWLED(void){
	HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_RESET);
	HAL_Delay(300);

	HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_RESET);
	HAL_Delay(300);

	HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_RESET);
	HAL_Delay(300);

	HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_RESET);
	HAL_Delay(300);
}


