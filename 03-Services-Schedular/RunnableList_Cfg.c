/*
 * RunnableList_Cfg.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Mohammed Hani
 */


#include "Schedular.h"
#include "RunnableList_Cfg.h"

const Runnable_t RunnableList[_RUN_NUM]=
{
		[App1]=
		{
				.Name ="ToggleLed1",
				.PeriodicityMS=10,
				.CBF=Runnable_Toggle_Led1,
		},
		[App2]=
		{
				.Name ="ToggleLed2",
				.PeriodicityMS=20,
				.CBF=Runnable_Toggle_Led2,
		}
};

