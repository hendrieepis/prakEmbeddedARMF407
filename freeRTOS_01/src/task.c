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
#include "uart.h"
#define doorOpen    HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_SET)
#define doorClose   HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_RESET)
//#define buzzerON   HAL_GPIO_WritePin(bar2_GPIO_Port,bar2_Pin,GPIO_PIN_SET)
//#define buzzerOFF  HAL_GPIO_WritePin(bar2_GPIO_Port,bar2_Pin,GPIO_PIN_RESET)
#define buzzerON   HAL_GPIO_WritePin(buzzer_GPIO_Port,buzzer_Pin,GPIO_PIN_SET)
#define buzzerOFF  HAL_GPIO_WritePin(buzzer_GPIO_Port,buzzer_Pin,GPIO_PIN_RESET)
#define YES 1
#define NO 0
//Private variable-----------------------
enum state {start,startDelay, enterpass, check, open,openDelay, alarm, resetalarm, resetverify} Kondisi;
volatile uint8_t debounce1=0xFF;
volatile uint8_t debounce2=0xFF;
volatile uint8_t debounce3=0xFF;
volatile uint8_t debounce4=0xFF;
volatile uint8_t tombol=0;
volatile uint8_t kombinasi[4]={0,0,0,0};
volatile uint8_t pressed=NO;
volatile uint8_t count=0;
volatile uint8_t fail_count=0;
volatile uint8_t rxBuffer5 = '\000';

volatile uint16_t timeout;

//Private task -----------------------
void Task_Init(void)
{
	timeout=0;
	Kondisi=start;
}

unsigned char Button1_OK(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(pbUp_GPIO_Port,pbUp_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		printf("1-OK \n\r");
		//		print_UART2("1-OK",5);
		detectedFLag=1;
	}
	return detectedFLag;
}

unsigned char Button2_OK(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(pbLeft_GPIO_Port,pbLeft_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		printf("2-OK \n\r");
		//		print_UART2("2-OK",5);
		detectedFLag=1;
	}
	return detectedFLag;
}

unsigned char Button3_OK(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(pbRight_GPIO_Port,pbRight_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		printf("3-OK \n\r");
		//		print_UART2("3-OK",5);
		detectedFLag=1;
	}
	return detectedFLag;
}

unsigned char Button4_OK(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(pbDown_GPIO_Port,pbDown_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		printf("4-OK \n\r");
		//		print_UART2("4-OK",5);
		detectedFLag=1;
	}
	return detectedFLag;
}

void Task_Run(void)
{
	switch(Kondisi)
	{
	case start:
	{
		printf("****     Alarm System   PENS 2012 ***** \n\r");
		Kondisi=startDelay;
		break;
	}
	case startDelay:
	{
		count=0;
		fail_count=0;
		HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_SET);
		if (++timeout > 1000) // dari scheduler sebesar 2ms*1000= 2 detik
		{
			printf("Enter Password  \n\r"); //current state
			HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
			timeout=0;
			Kondisi=enterpass;
		}
		break;
	}
	case enterpass:
	{
		if(Button1_OK())
		{
			tombol=1;
			pressed=YES;
			timeout=0;
		}

		if (Button2_OK())
		{
			tombol=2;
			pressed=YES;
			timeout=0;
		}

		if (Button3_OK())
		{
			tombol=3;
			pressed=YES;
			timeout=0;
		}

		if (Button4_OK())
		{
			tombol=4;
			pressed=YES;
			timeout=0;
		}


		if (pressed==YES)
		{
			//geser karakter
			kombinasi[0]=kombinasi[1];
			kombinasi[1]=kombinasi[2];
			kombinasi[2]=kombinasi[3];
			kombinasi[3]=tombol;
			pressed=NO;
			tombol=0;
			count++;
			//			printf("*"); //current state
		}

		//sudah 4 karakter
		if (count>3) Kondisi=check;

		//jeda memasukkan password lebih dari 3 detik
		if ((++timeout>1500) && (count >0))
		{
			printf("Time Out! \n\r");
			Kondisi=alarm;
			timeout=0;
		}

		break;
	}
	case check:
	{
		if      ((kombinasi[0]==1)&&
				(kombinasi[1]==2)&&
				(kombinasi[2]==3)&&
				(kombinasi[3]==4))
		{
			Kondisi=open;
		}
		else
		{
			if (++fail_count >= 3)
			{
				Kondisi=alarm;
			}
			else
			{
				printf("\n\r Coba lagi \n\r");
				timeout=0;
				count=0;
				Kondisi=enterpass;
			}
		}

		break;
	}

	case open:
	{
		printf("Access Granted \n\r");
		doorOpen;
		Kondisi=openDelay;
		break;
	}
	case openDelay:
	{
		if (++timeout > 1000) // dari scheduler sebesar 2ms*500= 1 detik
		{
			doorClose;
			buzzerOFF;
			Kondisi=start;
			timeout=0;
		}
		break;
	}

	case alarm:
	{
		printf("Access Denied! \n\r");
		buzzerON;
		count=0;
		pressed=NO;
		break;
	}
	}
}


