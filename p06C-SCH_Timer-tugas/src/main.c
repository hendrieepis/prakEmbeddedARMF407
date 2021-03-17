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

/* Private variables ---------------------------------------------------------*/
//UART_HandleTypeDef huart2;

// task1 object counting
// task2 blinky setiap 400ms
// task3 kirim informasi ke uart setiap 2 dtk sekali kata "hello"

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	SCH_init(1);
	uint16_t periode=2;
	uint16_t delay=0;
	/* Set up the scheduler */
	SCH_Add_Task(task1_update, delay, periode);
	SCH_Add_Task(task2_update, delay, 400);
	SCH_Add_Task(task3_update, delay, 1000);
	/* Start the scheduler */
	SCH_Start();

	while(1) {
		SCH_Dispatch_Tasks();
	}
	return 0;
}
