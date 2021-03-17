/*Desain vending mesin yang mempunyai minuman 1500. mesin menerima masukan berupa uang 500 dan 1000.
mesin tidak mengembalikan kelebihan uang*/
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
#include "counter.h"
#include "sensor.h"
#include "hardwareinit.h"
#include "uart.h"
#include <stdbool.h>
typedef enum{st0,st500,st1000,stopen} state_t;
state_t presentState;
state_t nextState;

void dropCandy();

int datain;
int C500,C1000=0;


int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	presentState=st0;
	printf("\n\r");
	printf("vending machine 1.1 \n\r");
	printf("St0\n\r");
	while(1)
	{
		switch (presentState) {
		case st0:
			HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_SET);
			if(Coin500Detected()) {
				printf("St500\n\r");
				nextState=st500;
			} else if (Coin1000Detected()){
				nextState=st1000;
				printf("St1000\n\r");
			}
			break;
		case st500:
			HAL_GPIO_WritePin(bar1_GPIO_Port,bar1_Pin,GPIO_PIN_SET);
			if(Coin500Detected()) {
				nextState=st1000;
				printf("St1000\n\r");
			} else if (Coin1000Detected()){
				nextState=stopen;
				printf("Stopen\n\r");
			}
			break;
		case st1000:
			HAL_GPIO_WritePin(bar2_GPIO_Port,bar2_Pin,GPIO_PIN_SET);
			if(Coin500Detected()) {
				nextState=stopen;
				printf("Stopen\n\r");
			} else if (Coin1000Detected()){
				nextState=stopen;
				printf("Stopen\n\r");
			}
			break;
		case stopen:
			HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_SET);
			dropCandy();
			nextState=st0;
			printf("St0\n\r");
			break;
		}
		presentState=nextState;
	}
	return 0;
}

void dropCandy(){

	for (int i=0;i<5;i++) {
		HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
		HAL_Delay(100);
	}
	HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(bar1_GPIO_Port,bar1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(bar2_GPIO_Port,bar2_Pin,GPIO_PIN_RESET);
	HAL_Delay(100);
	printf("permen keluar\n\r");
}
