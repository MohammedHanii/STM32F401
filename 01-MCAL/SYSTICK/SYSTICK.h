/*
 * SYSTICK.h
 *
 *  Created on: Mar 20, 2024
 *      Author: Mohammed Hani
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "STD_TYPES.h"

typedef void (*STK_CBF_t)(void);


typedef enum
{
     STK_OK,
	 STK_NOK,
	 STK_NULLPTR,
	 STK_WrongMode
}STK_ERRORSTATE_t;


/*choose AHB/8 bus with no exception request */
#define STK_AHB_8_NO_INT     				0x00000000

/*choose Processor clock (AHB)with no exception request */
#define STK_PROCESSOR_CLOCK_NO_INT 	 	0x00000004

/*choose AHB/8 bus with  exception request */
#define  STK_AHB_8_EN_INT          	 	0x00000002

/*choose Processor clock (AHB)with  exception request */
#define STK_PROCESSOR_CLOCK_EN_INT  		0x00000006


//===============================API's================================//
/*
 * @brief   : Starts the SysTick timer.
 * @param   : None
 * @return  : Error status indicating success or failure.
 * @details : This function starts the SysTick timer to generate interrupts according
 *            to the configured time interval.
 */
STK_ERRORSTATE_t  STK_Strat (void);


/*
 * @brief   : Stops the SysTick timer.
 * @param   : None
 * @return  : Error status indicating success or failure.
 * @details : This function stops the SysTick timer from generating interrupts.
 */
STK_ERRORSTATE_t  STK_Stop (void);

/*
 * @brief   : Sets the time interval for the SysTick timer.
 * @param   : Copy_TimeMs - The time interval in milliseconds.
 * @return  : Error status indicating success or failure.
 * @details : This function sets the time interval for the SysTick timer, which determines
 *            the period between interrupts generated by the timer.
 */
STK_ERRORSTATE_t  STK_SetTimeMS (u32 time);

/*
 * @brief   : Sets the configuration of the SysTick timer.
 * @param   : Copy_Mode - The mode to configure the SysTick timer.
 * @return  : Error status indicating success or failure.
 * @details : This function configures the SysTick timer according to the provided mode.
 */
STK_ERRORSTATE_t  STK_SetConfig (u32 Mode);

/*
 * @brief   : Sets the callback function for the SysTick timer interrupt.
 * @param   : Copy_CallBack - Pointer to the callback function.
 * @return  : Error status indicating success or failure.
 * @details : This function sets the callback function to be called when the SysTick timer
 *            generates an interrupt. The callback function will be executed each time
 *            the timer generates an interrupt.
 */
STK_ERRORSTATE_t  STK_SetCallBack (STK_CBF_t CBF);


#endif /* SYSTICK_H_ */
