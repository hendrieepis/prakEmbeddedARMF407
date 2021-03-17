/**
 ******************************************************************************
 * @file    main.c
 * @author  hendri
 * @version V1.0
 * @date    Juni 2016
 * @brief   Default main function.
 ******************************************************************************
 */

#include <sch.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "hardwareinit.h"
#include "task.h"
#include "uart.h"

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	SCH_init(1);
	uint16_t periode=1000;
	uint16_t delay=0;
	/* Prepare for the 'Flash_LED' task */
	//	  TaskInit();
	/* Set up the scheduler */
	SCH_Add_Task(task1_update, delay, periode);
	SCH_Add_Task(task2_update, delay+200, periode);
	SCH_Add_Task(task3_update, delay+400, periode);
	SCH_Add_Task(task4_update, delay+600, periode);
	/* Start the scheduler */
	SCH_Start();

	while(1) {
		SCH_Dispatch_Tasks();
	}
	return 0;
}
