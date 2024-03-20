/*
 * SYSTICK.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Mohammed Hani
 */

#include "SYSTICK.h"

typedef struct
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;

}STK_Reg_t;


#define 	STK_BASE_ADDRESS  	0xE000E010
#define 	STK_START_STOP    	0x00000001
#define 	STK_SRC           	0x00000004
#define 	STK_Clear_Mode    	0xFFFFFFF9
#define 	LOW_RELOAD_VAL    		0x00000001
#define 	HIGH_RELOAD_VAL   		0x00FFFFFF
#define 	CLK_Frequency_IN_MHZ 	16000000


volatile STK_Reg_t *const STK = (volatile STK_Reg_t*) STK_BASE_ADDRESS;



STK_ERRORSTATE_t  STK_Strat (void)
{

	STK_ERRORSTATE_t Local_ReturnError = STK_OK;

	u32 Local_ret= STK->STK_CTRL;

	/*set Start*/
	Local_ret |= STK_START_STOP ;

	STK->STK_CTRL =Local_ret;

	return Local_ReturnError;
}


STK_ERRORSTATE_t  STK_Stop (void)
{

	STK_ERRORSTATE_t Local_ReturnError = STK_OK;

	u32 Local_ret= STK->STK_CTRL;

	/*set Start*/
	Local_ret &=  ~(STK_START_STOP) ;

	STK->STK_CTRL =Local_ret;

	return Local_ReturnError;
}


STK_ERRORSTATE_t  STK_SetTimeMS (u32 timeMS)
{

	STK_ERRORSTATE_t 	Local_ReturnError= STK_OK ;

	/*calculate the Mp frequency */

	u32 Local_Mp_freq = ((STK ->STK_CTRL)&(STK_SRC)) ? CLK_Frequency_IN_MHZ : CLK_Frequency_IN_MHZ/ 8;

	/*calculate the Reload value */

	u32 Reload_value = (timeMS *Local_Mp_freq /1000) - 1 ;

	/*check if it exceds the bounderies */
	if ((timeMS <LOW_RELOAD_VAL) ||(timeMS > HIGH_RELOAD_VAL)){
		Local_ReturnError = STK_NOK ;
	}
	else {
		/*set The preload value*/
		STK->STK_LOAD =Reload_value;

		/*clear the current*/
		STK->STK_VAL = 0;
	}
	return Local_ReturnError;
}

STK_ERRORSTATE_t  STK_SetConfig (u32 Mode)
{

	STK_ERRORSTATE_t Local_ReturnError= STK_OK;

	u32 Local_ret = STK->STK_CTRL;

	if (Mode != STK_PROCESSOR_CLOCK_NO_INT &&
			Mode != STK_PROCESSOR_CLOCK_EN_INT &&
			Mode != STK_AHB_8_EN_INT &&
			Mode != STK_AHB_8_NO_INT)
	{
		Local_ReturnError= STK_WrongMode;
	}
	else {
		Local_ret &= STK_Clear_Mode ;
		Local_ret |= Mode;

		STK->STK_CTRL =Local_ret;

	}
   return Local_ReturnError;
}



STK_ERRORSTATE_t  STK_SetCallBack (STK_CBF_t CBF)
{

	STK_ERRORSTATE_t Local_ReturnError= STK_OK;

	if (CBF != NULL)
	{
		/*CallBack function when STK generates interrupts*/
	}
	else
	{
		Local_ReturnError= STK_NULLPTR;
	}

	return Local_ReturnError;
}



