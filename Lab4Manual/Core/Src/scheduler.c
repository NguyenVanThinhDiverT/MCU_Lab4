/////*
//// * scheduler.c
//// *
//// *  Created on: Nov 11, 2022
//// *      Author: WELCOME
//// */
////
////#include "scheduler.h"
////
//////sTasks SCH_tasks_G[SCH_MAX_TASKS];
//////uint8_t current_index_task = 0;
//////
//////void SCH_Init(void){
//////	current_index_task = 0;
//////}
//////
//////void SCH_Add_Task ( void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD){
//////	if(current_index_task < SCH_MAX_TASKS){
//////
//////		SCH_tasks_G[current_index_task].pTask = pFunction;
//////		SCH_tasks_G[current_index_task].Delay = DELAY;
//////		SCH_tasks_G[current_index_task].Period =  PERIOD;
//////		SCH_tasks_G[current_index_task].RunMe = 0; // flag
//////
//////		// SCH_tasks_G[current_index_task].TaskID = current_index_task;
//////		// Delete Task (Task ID)
//////
//////		current_index_task++;
//////	}
//////}
//////
//////void SCH_Update(void){
//////	for(int i = 0; i < current_index_task; i++){
//////		if(SCH_tasks_G[i].Delay > 0){
//////			SCH_tasks_G[i].Delay--;
//////		}
//////		else{
//////			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
//////			SCH_tasks_G[i].RunMe += 1;
//////		}
//////	}
//////}
//////void SCH_Dispatch_Tasks(void){
//////	for(int i = 0; i < current_index_task; i++){
//////		if(SCH_tasks_G[i].RunMe > 0){
//////			SCH_tasks_G[i].RunMe--;
//////			(*SCH_tasks_G[i].pTask)();
//////		}
//////	}
//////}
////unsigned char Error_code_G = 0;
////void SCH_Init(void){
////	unsigned char i;
////	for (i = 0; i< SCH_MAX_TASKS; i++){
////		SCH_Delete_Task(i);
////	}
////	Error_code_G=0;
//////	Timer_init();
//////	Watchdog_init();
////}
////
////void SCH_Update(void){
////	unsigned char Index;
////	//NOTE: Caculations are in *TICKS* (not milliseconds)
////	for (Index = 0; Index < SCH_MAX_TASKS; Index++){
////		//Check if there is a task at this location
////		if(SCH_tasks_G[Index].pTask){
////			if(SCH_tasks_G[Index].Delay == 0){
////				//The task is due to run
////				//Inc the 'RunMe' flag
////				SCH_tasks_G[Index].RunMe += 1;
////			if(SCH_tasks_G[Index].Period){
////				//Schedule peridoic tasks to run again
////				SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
////				}
////			}
////			else{
////				SCH_tasks_G[Index].Delay -= 1;
////			}
////		}
////	}
////}
////
////unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD){
////	unsigned char Index = 0;
////	// First find a gap int the array (if there is one)
////	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
////	{
////		Index++;
////	}
////	//Have we reached the end of the list?
////	if (Index == SCH_MAX_TASKS)
////	{
////		//Task list is full
////		//Set the global error variable
////		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
////		// Also return an error code
////		return SCH_MAX_TASKS;
////	}
////	// If we're here, there is a space in the task array
////	SCH_tasks_G[Index].pTask = pFunction;
////	SCH_tasks_G[Index].Delay = DELAY;
////	SCH_tasks_G[Index].Period = PERIOD;
////	SCH_tasks_G[Index].RunMe = 0;
////	// return position of task (to allow later deletion)
////	return Index;
////}
////
////void SCH_Dispatch_Tasks(void){
////	unsigned char Index;
////	//Dispatches (runs) the next task (if one is ready)
////	for(Index = 0; Index < SCH_MAX_TASKS; Index++){
////		if(SCH_tasks_G[Index].RunMe > 0){
////			(*SCH_tasks_G[Index].pTask)();
////			SCH_tasks_G[Index].RunMe -= 1; //Reset /reduce RunMe flag
////			//Periodic tasks will automatically run again
////			//- if this is a 'one shot' task, remove it from the array
////			if(SCH_tasks_G[Index].Period == 0){
////				SCH_Delete_Task(Index);
////			}
////		}
////	}
////	//Report system status
////	SCH_Report_Status();
////	//The scheduler enters idle mode at this point
////	SCH_Go_To_Sleep();
////}
////
////unsigned char SCH_Delete_Task(const uint8_t TASK_INDEX){
////	unsigned char Return_code;
////	if(SCH_tasks_G[TASK_INDEX].pTask == 0){
////		// No task at this location ...
////		//
////		// Set the global error variable
////		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
////
////		// ... also return an error code
////		Return_code = RETURN_ERROR;
////	}
////	else{
////		Return_code = RETURN_NORMAL;
////	}
////	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
////	SCH_tasks_G[TASK_INDEX].Delay = 0;
////	SCH_tasks_G[TASK_INDEX].Period= 0;
////	SCH_tasks_G[TASK_INDEX].RunMe = 0;
////	return Return_code; //return status
////}
////
////void SCH_Go_To_Sleep(void){
////
////}
////
////void SCH_Report_Status(void){
////#ifdef SCH_REPORT_ERRORS
////	// ONLY APPLIES IF WE ARE REPORTING ERRORS
////	// Check for a new error code
////	if(Error_code_G != Last_error_code_G){
////		// Negative logic on LEDs assumed
////		Error_port = 255 - Error_code_G;
////		Last_error_code_G = Error_code_G;
////		if(Error_code_G != 0){
////			Error_tick_count_G = 60000;
////		}
////		else{
////			Error_tick_count_G = 0;
////		}
////	}
////	else{
////		if(Error_tick_count_G != 0){
////			if(--Error_tick_count_G == 0){
////				Error_code_G = 0; // Reset error code
////			}
////		}
////	}
////#endif
////}
////
////
////
#include "scheduler.h"

typedef struct {
  void (*pTask)();
  uint32_t Delay;
  uint32_t Period;
  uint32_t RunMe;
  uint32_t TaskID;
}sTask;

#define SCH_MAX_TASKS 40

sTask SCH_tasks_G[SCH_MAX_TASKS];
uint32_t current_index_task = 0;

void SCH_Init(void) {
  current_index_task = 0;
}

void SCH_Update(void) {
  for(int i = 0; i < current_index_task; i++) {
    if(SCH_tasks_G[i].Delay > 0) {
      SCH_tasks_G[i].Delay--;
    }
    else {
      SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
      SCH_tasks_G[i].RunMe++;
    }
  }
}

void SCH_Add_Task(void (*pFunction)(), uint32_t Delay, uint32_t Period) {
  if(current_index_task < SCH_MAX_TASKS) {
    SCH_tasks_G[current_index_task].pTask = pFunction;
    SCH_tasks_G[current_index_task].Delay = Delay;
    SCH_tasks_G[current_index_task].Period = Period;
    SCH_tasks_G[current_index_task].RunMe = 0;
    SCH_tasks_G[current_index_task].TaskID = current_index_task;

    current_index_task++;
  }
}

void SCH_Dispatch_Tasks(void) {
  for(int i = 0; i < current_index_task; i++) {
    if(SCH_tasks_G[i].RunMe > 0) {
      (*SCH_tasks_G[i].pTask)();
      SCH_tasks_G[i].RunMe--;
      if(SCH_tasks_G[i].Period == 0){
    	  SCH_Delete_Task(i);
      }
    }
  }
}

void SCH_Delete_Task(uint32_t TASK_INDEX)
{

	if (TASK_INDEX >= current_index_task ){ //

			return;
		}else {
			for (int i = TASK_INDEX; i < current_index_task - 1; i++){
				SCH_tasks_G[i].pTask  = SCH_tasks_G[i+1].pTask;
				SCH_tasks_G[i].Period = SCH_tasks_G[i+1].Period;
				SCH_tasks_G[i].RunMe  = SCH_tasks_G[i+1].RunMe;
				SCH_tasks_G[i].Delay  = SCH_tasks_G[i+1].Delay;
			}
			current_index_task--;
		}
}
