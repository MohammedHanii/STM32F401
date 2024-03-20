/*
 * Schedular.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Mohammed Hani
 */

#include "Schedular.h"

static volatile u32 Pending_ticks ;
extern const Runnable_t RunnableList [_RUN_NUM];

#define 	TICK_TIME_MS   	10

static void Sched (void);
static void Tickcbf (void);


void Sched_Init (void)
{

	STK_SetConfig(STK_PROCESSOR_CLOCK_EN_INT);
	STK_SetTimeMS (TICK_TIME_MS);
	STK_SetCallBack (Tickcbf);
}

void Sched_Start (void)
{


	STK_Strat ();
	while (1)
	{
		if (Pending_ticks)
		{
			Pending_ticks -- ;
			Sched ();
		}

	}

}


void Sched (void)
{

	u32 idx;
	static u32 Timestamp =0 ;

	for(idx=0 ; idx < _RUN_NUM; idx ++)
	{

		if((RunnableList[idx].CBF) &&(Timestamp % RunnableList[idx].PeriodicityMS ==0))
		{

			RunnableList[idx].CBF();
		}
	}

	Timestamp += TICK_TIME_MS;
}


static void Tickcbf (void)
{
	Pending_ticks ++ ;
}

