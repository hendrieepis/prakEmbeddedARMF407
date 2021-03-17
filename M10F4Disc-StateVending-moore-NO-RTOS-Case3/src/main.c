/*Desain vending mesin yang mempunyai minuman 1000. mesin menerima masukan berupa uang 500 dan 1000.
transaksi diproses dengan menekan tombol proses. Transaksi yang belum diproses masih
dapat
dibatalkan dengan menekan tombol batal*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
#include "counter.h"
#include "sensor.h"
#include "hardwareinit.h"
#include "uart.h"
#include <stdbool.h>

#define ON 1
#define OFF 0
#define Outdrop(status) ((status==OFF) ? HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_RESET))
#define Out500(status) ((status==OFF) ? HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_RESET))
#define Out1000(status) ((status==OFF) ? HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_RESET))
#define Sound(status) ((status==ON)? HAL_GPIO_WritePin(buzzer_GPIO_Port,buzzer_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(buzzer_GPIO_Port,bar0_Pin,buzzer_Pin))

typedef enum{St0,St1,St2,St3,St4,St5,St6,St7,St8, Stdrop} state_t;
state_t presentState;
state_t nextState;

void dropCandy();
void dropKoin();

int datain;
int C500,C1000=0;


int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	presentState=St0;
	printf("\n\r");
	printf("vending machine 1.2 \n\r");
	printf("St0\n\r");
	while(1)
	{
		switch (presentState) {
		case St0:
			if(Coin500Detected()) {
				nextState=St1;
				printf("St1\n\r");
			}
			if (Coin1000Detected()){
				nextState=St2;
				printf("St2\n\r");
			}
			break;
		case St1:
			if(Coin500Detected()) {
				nextState=St2;
				printf("St2\n\r");
			}
			if (Coin1000Detected()){
				nextState=St3;
				printf("St3: kembali 500\n\r");
			}
			if (returnDetected()){
				nextState=St7;
				printf("St7\n\r");
				printf("batal\n\r");
			}
			break;
		case St2:
			if(Coin500Detected()) {
				nextState=St3;
				printf("St3: kembali 500\n\r");
			}
			if (Coin1000Detected()){
				nextState=St6;
				printf("St6: kembali 1000 \n\r");
			}
			if (returnDetected()){
				nextState=St8;
				printf("St8\n\r");
				printf("batal 1000\n\r");
			}
			if (prosesDetected()) {
				nextState= Stdrop;
				printf("Stdrop\n\r");
			}
			break;

		case St3:
			nextState=St4;
			printf("St4\n\r");
			Out500(ON);
			HAL_Delay(1000);
			Out500(OFF);
			break;

		case St4:
			if(Coin500Detected()) {
				nextState=St3;
				printf("St3: kembali 500\n\r");
			}
			if (Coin1000Detected()){
				nextState=St6;
				printf("St6: kembali 1000 \n\r");
			}
			if (returnDetected()){
				nextState=St8;
				printf("St8\n\r");
				printf("batal 1000\n\r");
			}
			if (prosesDetected()) {
				nextState= Stdrop;
				printf("Stdrop\n\r");
			}
			break;

		case St6:
			nextState=St5;
			printf("St5\n\r");
			Out1000(ON);
			HAL_Delay(1000);
			Out1000(OFF);
			break;

		case St5:
			if(Coin500Detected()) {
				nextState=St3;
				printf("St3: kembali 500\n\r");
			}
			if (Coin1000Detected()){
				nextState=St6;
				printf("St6: kembali 1000\n\r");
			}
			if (returnDetected()){
				nextState=St8;
				printf("St8\n\r");
				printf("batal 1000\n\r");
			}
			if (prosesDetected()) {
				nextState= Stdrop;
				printf("permen keluar\n\r");
			}
			break;
		case Stdrop:
			nextState=St0;
			printf("St0\n\r");
			Outdrop(ON);
			HAL_Delay(1000);
			Outdrop(OFF);
			break;
		case St7:
			nextState=St0;
			printf("St0\n\r");
			Out500(ON);
			HAL_Delay(1000);
			Out500(OFF);
			break;
		case St8:
			nextState=St0;
			printf("St0\n\r");
			Out1000(ON);
			HAL_Delay(1000);
			Out1000(OFF);
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
	HAL_GPIO_WritePin(bar3_GPIO_Port,bar3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(bar4_GPIO_Port,bar4_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(bar5_GPIO_Port,bar5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(bar6_GPIO_Port,bar6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(bar7_GPIO_Port,bar7_Pin,GPIO_PIN_RESET);
	HAL_Delay(100);
	printf("permen keluar\n\r");
}

void dropKoin(){
	for (int i=0;i<5;i++) {
		HAL_GPIO_WritePin(bar7_GPIO_Port,bar7_Pin,GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(bar7_GPIO_Port,bar7_Pin,GPIO_PIN_RESET);
		HAL_Delay(100);
	}
}
