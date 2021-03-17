/*
 * seos.h
 *
 *  Created on: Apr 10, 2016
 *      Author: hendri
 */

#ifndef SCH_H_
#define SCH_H_
#include <stdint.h>

// *** edit only in this line below **
#define SCH_MAX_TASKS 4
/* Type definition here ------------------------------------ */
#define RETURN_NORMAL  0
#define RETURN_ERROR  1
//************************************

// --Global variable here -----------------

/* Store in DATA area, if possible, for rapid access
Total memory per task is 7 bytes */

typedef struct
{
  void (* pTask)(void);
  uint16_t Delay;
  uint16_t Period;
  uint8_t RunMe;
} sTask;

uint8_t Error_code_G;
sTask SCH_tasks_G[SCH_MAX_TASKS];

// Error codes
//----------------------------------------------------------------------
#define ERROR_SCH_TOO_MANY_TASKS (1)
#define ERROR_SCH_CANNOT_DELETE_TASK (2)

// --Global function here ------------------

void TIM4_IRQHandler(void);
void SCH_init(uint32_t Periode);
void SCH_Start(void);
uint8_t SCH_Delete_Task(const uint8_t TASK_INDEX);
void SCH_update(void);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Add_Task(void (* pFunction)(),uint16_t DELAY,uint16_t PERIOD);
void SCH_Report_Status(void);
//void SCH_Start(void);

#endif /* SCH_H_ */
