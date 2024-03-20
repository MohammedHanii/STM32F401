/*
 * Schedular.h
 *
 *  Created on: Mar 20, 2024
 *      Author: Mohammed Hani
 */

#ifndef SCHEDULAR_H_
#define SCHEDULAR_H_

#include "STD_TYPES.h"
#include "RunnableList_Cfg.h"
#include "SYSTICK.h"

typedef void (*Runnable_CBF_t)(void);

typedef struct
{
	char*Name;
	u32 PeriodicityMS;
	u32 Priority;
	u32 DelayMS;
	Runnable_CBF_t CBF;

}Runnable_t;


void Sched_Init  (void);

void Sched_start (void);


#endif /* SCHEDULAR_H_ */
