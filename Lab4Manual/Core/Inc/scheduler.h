///*
// * scheduler.h
// *
// *  Created on: Nov 11, 2022
// *      Author: WELCOME
// */
//
//#ifndef INC_SCHEDULER_H_
//#define INC_SCHEDULER_H_
//
//#include <stdint.h>
//
////typedef struct{
////	void (*pTask)(void);
////	uint32_t 	Delay;
////	uint32_t 	Period;
////	uint8_t 	RunMe;
////
////	uint32_t 	TaskID;
////}sTasks;
////
////#define SCH_MAX_TASKS	40
////
////void SCH_Init(void);
////
////void SCH_Add_Task ( void (*pFunction)() ,
////					uint32_t DELAY,
////					uint32_t PERIOD);
////
////void SCH_Update(void);
////
////void SCH_Dispatch_Tasks(void);
//#define ERROR_SCH_TOO_MANY_TASKS 1
//#define ERROR_SCH_CANNOT_DELETE_TASK 2
//#define RETURN_ERROR 3
//#define RETURN_NORMAL 4
//
//typedef struct{
//	//Pointer to the task (must be a 'void (void)' function)
//	void (*pTask)(void);
//	uint32_t Delay;
//	uint32_t Period;
//	uint8_t RunMe;
//	uint32_t TaskID;
//}sTasks;
//
//// MUST BE ADJUSTED FOR EACH NEW PROJECT
//#define SCH_MAX_TASKS	5
//#define NO_TASK_ID		0
//sTasks SCH_tasks_G[SCH_MAX_TASKS];
//
//void SCH_Init(void);
//
//void SCH_Update(void);
//
//unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD);
//void SCH_Dispatch_Tasks(void);
//
////typedef unsigned char BYTE;
////typedef BYTE* tByte;
//// uint8_t
//unsigned char SCH_Delete_Task(const uint8_t TASK_INDEX);
//
//void SCH_Go_To_Sleep(void);
//void SCH_Report_Status(void);
//void Watchdog_init(void);
//#endif /* INC_SCHEDULER_H_ */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdint.h"

void SCH_Init(void);
void SCH_Update(void);
void SCH_Add_Task(void (*pFunction)(), uint32_t Delay, uint32_t Period);
void SCH_Dispatch_Tasks(void);
void SCH_Delete_Task(uint32_t TASK_INDEX);

#endif /* INC_SCHEDULER_H_ */
