#include <sch.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
#include "task.h"
TIM_HandleTypeDef TIM_Handle;

void TIM4_IRQHandler(void)
{
	if (__HAL_TIM_GET_FLAG(&TIM_Handle, TIM_FLAG_UPDATE) != RESET)      //In case other interrupts are also running
	{
		if (__HAL_TIM_GET_ITSTATUS(&TIM_Handle, TIM_IT_UPDATE) != RESET)
		{
			__HAL_TIM_CLEAR_FLAG(&TIM_Handle, TIM_FLAG_UPDATE);
			/*put your code here */
			HAL_GPIO_TogglePin(led0_GPIO_Port,led0_Pin);
			hSCH_Update();
		}
	}
}

void hSCH_init(uint32_t Periode){
/*	sampling is not equal to freq.
 *  PB1 Timer clock = 84MHz
 *	Prescaller = 42000
 *	Tick=42000/84Mhz=0.5ms
 *	if interval timer 1ms
 *	then interval timer= periode*tick
 *	Periode= IntervalTimer/Tick
 *	Periode= 1ms/0.5ms
 *	Periode=2
 */
	__TIM4_CLK_ENABLE();
	TIM_Handle.Init.Prescaler = 42000-1;
	TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Handle.Init.Period = (2*Periode)-1;
	TIM_Handle.Instance = TIM4;   //Same timer whose clocks we enabled
	HAL_TIM_Base_Init(&TIM_Handle);     // Init timer
//	HAL_TIM_Base_Start_IT(&TIM_Handle); // start timer interrupts
	HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
}

void hSCH_Start(void){
	HAL_TIM_Base_Start_IT(&TIM_Handle); // start timer interrupts
}

void hSCH_Dispatch_Tasks(void)
{
    uint8_t Index;
// Dispatches (runs) the next task (if one is ready)
    for (Index = 0; Index < hSCH_MAX_TASKS; Index++)
    {
// Only dispatching co-operative tasks
        if ((hSCH_tasks_G[Index].Co_op) && (hSCH_tasks_G[Index].RunMe > 0))
        {
            (*hSCH_tasks_G[Index].pTask)(); // Run the task
            hSCH_tasks_G[Index].RunMe -= 1; // Reset / reduce RunMe flag
// Periodic tasks will automatically run again
// - if this is a �one shot� task, remove it from the array
            if (hSCH_tasks_G[Index].Period == 0)
            {
// Faster than call to delete task
                hSCH_tasks_G[Index].pTask = 0;
            }
        }
    }
// Report system status
    hSCH_Report_Status();
// The scheduler enters idle mode at this point
//    sleep_mode();
}



uint8_t hSCH_Delete_Task(uint8_t Task_index)
{
	uint8_t Return_code;
    if (hSCH_tasks_G[Task_index].pTask == 0)
    {
// No task at this location...
//
// Set the global error variable
        Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
// ...also return an error code
        Return_code = RETURN_ERROR;
    }
    else
    {
        Return_code = RETURN_NORMAL;
    }
    hSCH_tasks_G[Task_index].pTask = 0;
    hSCH_tasks_G[Task_index].Delay = 0;
    hSCH_tasks_G[Task_index].Period = 0;
    hSCH_tasks_G[Task_index].RunMe = 0;
    return Return_code; // return status
}

void hSCH_Update(void)
{
	uint8_t Index;
// NOTE: calculations are in *TICKS* (not milliseconds)
    for (Index = 0; Index < hSCH_MAX_TASKS; Index++)
    {
// Check if there is a task at this location
        if (hSCH_tasks_G[Index].pTask)
        {
            if (hSCH_tasks_G[Index].Delay == 0)
            {
// The task is due to run
//
                if (hSCH_tasks_G[Index].Co_op)
                {
// If it is a co-operative task, increment the RunMe flag
                    hSCH_tasks_G[Index].RunMe += 1;
                }
                else
                {
// If it is a pre-emptive task, run it IMMEDIATELY
                    (*hSCH_tasks_G[Index].pTask)(); // Run the task
                    hSCH_tasks_G[Index].RunMe -= 1; // Reset / reduce RunMe flag
// Periodic tasks will automatically run again
// - if this is a �one shot� task, remove it from the array
                    if (hSCH_tasks_G[Index].Period == 0)
                    {
                        hSCH_tasks_G[Index].pTask = 0;
                    }
                }
                if (hSCH_tasks_G[Index].Period)
                {
// Schedule regular tasks to run again
                    hSCH_tasks_G[Index].Delay = hSCH_tasks_G[Index].Period;
                }
            }
            else
            {
// Not yet ready to run: just decrement the delay
                hSCH_tasks_G[Index].Delay -= 1;
            }
        }
    }
}


void hSCH_Report_Status(void)
{
#ifdef SCH_REPORT_ERRORS
// ONLY APPLIES IF WE ARE REPORTING ERRORS
// Check for a new error code
    if (Error_code_G != Last_error_code_G)
    {
// Negative logic on LEDs assumed
        Error_port = 255 - Error_code_G;
        Last_error_code_G = Error_code_G;
        if (Error_code_G != 0)
        {
            Error_tick_count_G = 60000;
        }
        else
        {
            Error_tick_count_G = 0;
        }
    }
    else
    {
        if (Error_tick_count_G != 0)
        {
            if (--Error_tick_count_G == 0)
            {
                Error_code_G = 0; // Reset error code
            }
        }
    }
#endif

}


uint8_t hSCH_Add_Task(void (* pFunction)(),uint16_t DELAY,uint16_t PERIOD,uint8_t Co_op)
{
	uint8_t  Index = 0;
// First find a gap in the array (if there is one)
    while ((hSCH_tasks_G[Index].pTask != 0) && (Index < hSCH_MAX_TASKS))
    {
        Index++;
    }
// Have we reached the end of the list?
    if (Index == hSCH_MAX_TASKS)
    {
// Task list is full
//
// Set the global error variable
        Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
// Also return an error code
        return hSCH_MAX_TASKS;
    }
// If we�re here, there is a space in the task array
    hSCH_tasks_G[Index].pTask = pFunction;
    hSCH_tasks_G[Index].Delay = DELAY;
    hSCH_tasks_G[Index].Period = PERIOD;
    hSCH_tasks_G[Index].Co_op = Co_op;
    hSCH_tasks_G[Index].RunMe = 0;
    return Index; // return position of task (to allow later deletion)
}
