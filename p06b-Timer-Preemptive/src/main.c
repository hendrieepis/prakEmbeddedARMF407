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
    hSCH_init(1);
    hSCH_Add_Task(LED_Flash0_Update, 0, 1000,0);
    hSCH_Add_Task(LED_Flash1_Update, 200, 1000,0);
    hSCH_Add_Task(LED_Flash2_Update, 400, 1000,1);
    /* Start the scheduler */
    hSCH_Start();
    while (1)
    {
        hSCH_Dispatch_Tasks();
    }
	return 0;
}
