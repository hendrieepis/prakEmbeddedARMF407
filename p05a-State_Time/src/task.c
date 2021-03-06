/*
 * task.c
 *
 *  Created on: Apr 10, 2016
 *      Author: hendri
 */
#include "task.h"
#include "stm32f4xx.h"
#include "device.h"
#include "uart.h"

//Private constant-----------------------
#define LAMA_MERAH	5
#define LAMA_KUNING	2
#define LAMA_HIJAU	4

#define MerahON   HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_SET)
#define MerahOFF  HAL_GPIO_WritePin(bar0_GPIO_Port,bar0_Pin,GPIO_PIN_RESET)

#define KuningON  HAL_GPIO_WritePin(bar1_GPIO_Port,bar1_Pin,GPIO_PIN_SET)
#define KuningOFF HAL_GPIO_WritePin(bar1_GPIO_Port,bar1_Pin,GPIO_PIN_RESET)

#define HijauON	   HAL_GPIO_WritePin(bar2_GPIO_Port,bar2_Pin,GPIO_PIN_SET)
#define HijauOFF  HAL_GPIO_WritePin(bar2_GPIO_Port,bar2_Pin,GPIO_PIN_RESET)

//Private variable-----------------------
enum state {merah, kuning, hijau } stateku;
unsigned int Time_in_state=0;

/* -------------------------------------- *
	Traffic_Light_Init()
	Set kondisi pertama ke merah
-* -------------------------------------- */

void Task_Init(void){
	stateku=merah;
}

void Task_Run(void){

	//	USARTPutStr("."); //current state
		switch(stateku)
		{
			case merah:
		        {

					MerahON;
					KuningOFF;
					HijauOFF;
					printf("Merah ON \n\r");
		        	if (++Time_in_state==LAMA_MERAH)
		        	{
		        		stateku=kuning;
		        		Time_in_state=0;
		        	}

		        	break;
		        }

			case kuning:
		        {

		        	MerahOFF;
		        	KuningON;
		        	HijauOFF;
		        	printf("Kuning ON \n\r");
		        	if (++Time_in_state==LAMA_KUNING)
		        	{
		        		stateku=hijau;
		        		Time_in_state=0;
		        	}

		        	break;
		        }

			case hijau:
		        {
	                MerahOFF;
	                KuningOFF;
	                HijauON;
	                printf("Hijau ON \n\r");
		        	if (++Time_in_state==LAMA_HIJAU)
		        	{
		        		stateku=merah;
		        		Time_in_state=0;
		        	}

		        	break;
		        }
		}

}

