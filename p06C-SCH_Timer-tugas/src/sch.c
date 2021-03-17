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
			SCH_update();
		}
	}
}

void SCH_init(uint32_t Periode){
	// init timer
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

void SCH_Start(void){
	HAL_TIM_Base_Start_IT(&TIM_Handle); // start timer interrupts
}

uint8_t SCH_Add_Task(void (* pFunction)(),uint16_t DELAY,uint16_t PERIOD)
{
	uint8_t Index = 0;
	/* First find a gap in the array (if there is one) */
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)){
		Index++;
	}
	/* Have we reached the end of the list? */
	if (Index == SCH_MAX_TASKS){
		/* Task list is full
    -> set the global error variable */
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		/* Also return an error code */
		return SCH_MAX_TASKS;
	}
	/* If we're here, there is a space in the task array */
	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].Delay = DELAY + 1;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe = 0;
	return Index; /* return pos. of task (to allow deletion) */
}


void SCH_Dispatch_Tasks(void)
{
	uint8_t Index;
	/* Dispatches (runs) the next task (if one is ready) */
	for (Index = 0; Index < SCH_MAX_TASKS; Index++){
		if (SCH_tasks_G[Index].RunMe > 0){
			(*SCH_tasks_G[Index].pTask)(); /* Run the task */
			SCH_tasks_G[Index].RunMe --; /* Reduce RunMe count */
			/* Periodic tasks will automatically run again
      - if this is a 'one shot' task, delete it */
			if (SCH_tasks_G[Index].Period == 0){
				SCH_Delete_Task(Index);
			}
		}
	}
	/* Report system status */
	//SCH_Report_Status();
	/* The scheduler enters idle mode at this point */
//	sleep_mode();
}


uint8_t SCH_Delete_Task(const uint8_t TASK_INDEX)
{
	unsigned char Return_code;
	if (SCH_tasks_G[TASK_INDEX].pTask == 0){
		/* No task at this location...
    -> set the global error variable */
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		/* ...also return an error code */
		Return_code = RETURN_ERROR;
	}
	else {
		Return_code = RETURN_NORMAL;
	}
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	return Return_code; /* return status */
}

void SCH_update(void)
{
	uint8_t Index;
	/* NOTE: calculations are in *TICKS* (not milliseconds) */
	for (Index = 0; Index < SCH_MAX_TASKS; Index++){
		/* Check if there is a task at this location */
		if (SCH_tasks_G[Index].pTask){
			if (--SCH_tasks_G[Index].Delay == 0){
				/* The task is due to run */
				SCH_tasks_G[Index].RunMe++; /* Inc. 'RunMe' flag */
				if (SCH_tasks_G[Index].Period){
					/* Schedule regular tasks to run again */
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			}
		}
	}
}


/*--------------------------------------------------------*/
void SCH_Report_Status(void)
{
#ifdef SCH_REPORT_ERRORS
	/* ONLY APPLIES IF WE ARE REPORTING ERRORS */
	/* Check for a new error code */
	if (Error_code_G != Last_error_code_G)
	{
		/* Negative logic on LEDs assumed */
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
				Error_code_G = 0; /* Reset error code */
			}
		}
	}
#endif
}
