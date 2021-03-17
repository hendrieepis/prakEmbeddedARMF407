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
#define hSCH_MAX_TASKS 3
#define RETURN_NORMAL  0
#define RETURN_ERROR  1
//************************************





// --Global variable here -----------------

typedef  struct
{
/* Pointer to the task (must be a 'void (void)' function) */
  void (* pTask)(void);
  uint16_t Delay;
  uint16_t Period;
  uint8_t RunMe;
  uint8_t Co_op;
} sTask;

uint8_t Error_code_G;
sTask hSCH_tasks_G[hSCH_MAX_TASKS];

// Error codes
//----------------------------------------------------------------------
#define ERROR_SCH_TOO_MANY_TASKS (1)
#define ERROR_SCH_CANNOT_DELETE_TASK (2)

// --Global function here ------------------
void hSCH_init(uint32_t Periode);
uint8_t hSCH_Delete_Task(uint8_t Task_index);
void hSCH_Update(void);
void hSCH_Dispatch_Tasks(void);
uint8_t hSCH_Add_Task(void (* pFunction)(),uint16_t DELAY,uint16_t PERIOD,uint8_t Co_op);
void hSCH_Report_Status(void);
uint8_t hSCH_Delete_Task(uint8_t Task_index);
void hSCH_Start(void);

#endif /* SCH_H_ */
