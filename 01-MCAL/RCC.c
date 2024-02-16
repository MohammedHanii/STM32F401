/*
 * RCC.c
 *
 *  Created on: Feb 5, 2024
 *      Author: Mohammed Hani
 */

#include "STD_TYPES.h"
#include "RCC.h"

void RCC_SelectClk(u8 Copy_SysClk)
{
	u32 Local_CFGR_REG;
	u32 Local_TimeOut = 0;

		switch(Copy_SysClk)
		{
			case RCC_HSI:
				if((RCC_CR & MASK_HSI_ON) == MASK_HSI_ON)
				{
					if((RCC_CR & MASK_HSI_READY) == MASK_HSI_READY)
					{
						Local_CFGR_REG = RCC_CFGR;
						Local_CFGR_REG &= ~MASK_SW;
						Local_CFGR_REG |= (RCC_HSI<<0);
						RCC_CFGR = Local_CFGR_REG;
						while( ((RCC_CFGR & MASK_GET_SWS) != MASK_SWS_HSI) && (Local_TimeOut<500))
						{
							Local_TimeOut++;
						}
					}
				}
				break;

			case RCC_HSE:
				if((RCC_CR & MASK_HSE_ON) == MASK_HSE_ON)
				{
					if((RCC_CR & MASK_HSE_READY) == MASK_HSE_READY)
					{
						Local_CFGR_REG = RCC_CFGR;
						Local_CFGR_REG &= ~MASK_SW;
						Local_CFGR_REG |= (RCC_HSE<<0);
						RCC_CFGR = Local_CFGR_REG;
						while( ((RCC_CFGR & MASK_GET_SWS) != MASK_SWS_HSE) && (Local_TimeOut<500))
						{
							Local_TimeOut++;
						}
					}
				}
				break;

			case RCC_PLL:
				if((RCC_CR & MASK_PLL_ON) == MASK_PLL_ON)
				{
					if((RCC_CR & MASK_PLL_READY) == MASK_PLL_READY)
					{
						Local_CFGR_REG = RCC_CFGR;
						Local_CFGR_REG &= ~MASK_SW;
						Local_CFGR_REG |= (RCC_PLL<<0);
						RCC_CFGR = Local_CFGR_REG;
						while( ((RCC_CFGR & MASK_GET_SWS) != MASK_SWS_PLL) && (Local_TimeOut<500))
						{
							Local_TimeOut++;
						}
					}
				}
				break;

		}


}

void RCC_ConrolClk(u8 Copy_SysClk, u8 ClkStatus)
{
	u32 Local_TimeOut = 0;

		switch(Copy_SysClk)
		{
			case RCC_HSI:
				if(ClkStatus == CLOCK_STATUS_OFF)
				{
					RCC_CR &= (~MASK_SET_HSI);
				}
				else
				{
					RCC_CR |= (MASK_SET_HSI);
					while( ((RCC_CR & MASK_HSI_READY) == 0) && (Local_TimeOut<500))
					{
						Local_TimeOut++;
					}
				}
				break;

			case RCC_HSE:
				if(ClkStatus == CLOCK_STATUS_OFF)
				{
					RCC_CR &= (~MASK_SET_HSE);
				}
				else
				{
					RCC_CR |= (MASK_SET_HSE);
					while( ((RCC_CR & MASK_HSE_READY) == 0) && (Local_TimeOut<500))
					{
						Local_TimeOut++;
					}
				}
				break;

			case RCC_PLL:
				if(ClkStatus == CLOCK_STATUS_OFF)
				{
					 RCC_CR &= (~MASK_SET_PLL);
				}
				else
				{
					RCC_CR |= (MASK_SET_PLL);
					while( ((RCC_CR & MASK_PLL_READY) == 0) && (Local_TimeOut<500))
					{
						Local_TimeOut++;
					}
				}
				break;
		}


}



void RCC_ConfigPLL(RCC_structCLKPLL_t Copy_structPLLCongif)
{
	  RCC_enuPLLSRC_t Local_PLLSource = Copy_structPLLCongif.RCC_PLLSCR;
	  u32 Local_PLL_M = Copy_structPLLCongif.RCC_PLL_M;
	  u32 Local_PLL_N = Copy_structPLLCongif.RCC_PLL_N;
	  u32 Local_PLL_P = Copy_structPLLCongif.RCC_PLL_P;
	  u32 Local_PLL_Q = Copy_structPLLCongif.RCC_PLL_Q;

	  u32 Local_PLLCFGR_Register;

	  Local_PLLCFGR_Register = RCC_PLLCFGR;
	  Local_PLLCFGR_Register &= ~MASK_PPL_M;
	  Local_PLLCFGR_Register |= (Local_PLL_M<<SHIFT_PLL_M);
	  RCC_PLLCFGR = Local_PLLCFGR_Register;

	  Local_PLLCFGR_Register = RCC_PLLCFGR;
	  Local_PLLCFGR_Register &= ~MASK_PPL_N;
	  Local_PLLCFGR_Register |= (Local_PLL_N<<SHIFT_PLL_N);
	  RCC_PLLCFGR = Local_PLLCFGR_Register;

	  Local_PLLCFGR_Register = RCC_PLLCFGR;
	  Local_PLLCFGR_Register &= ~MASK_PPL_P;
	  Local_PLLCFGR_Register |= (Local_PLL_P<<SHIFT_PLL_P);
	  RCC_PLLCFGR = Local_PLLCFGR_Register;

	  Local_PLLCFGR_Register = RCC_PLLCFGR;
	  Local_PLLCFGR_Register &= ~ MASK_PPL_Q;
	  Local_PLLCFGR_Register |= (Local_PLL_Q<<SHIFT_PLL_Q);
	  RCC_PLLCFGR = Local_PLLCFGR_Register;

	  Local_PLLCFGR_Register = RCC_PLLCFGR;
	  Local_PLLCFGR_Register &= ~MASK_PPL_SRC;
	  Local_PLLCFGR_Register |= (Local_PLLSource<<SHIFT_PLL_SRC);
	  RCC_PLLCFGR = Local_PLLCFGR_Register;
}

void RCC_EnablePeripheral(u32 Copy_PeripheralBus, u32 Copy_Peripheral)
{
	switch(Copy_PeripheralBus)
	{
		case AHB1_BUS:
			RCC_AHB1ENR |= (1<<Copy_Peripheral);
		break;

		case AHB2_BUS:
			RCC_AHB2ENR |= (1<<Copy_Peripheral);
		break;

		case APB1_BUS:
			RCC_APB1ENR |= (1<<Copy_Peripheral);
		break;

		case APB2_BUS:
			RCC_APB2ENR |= (1<<Copy_Peripheral);
		break;

	}
}

void RCC_DisablePeripheral(u32 Copy_PeripheralBus, u32 Copy_Peripheral)
{
	switch(Copy_PeripheralBus)
	{
		case AHB1_BUS:
			RCC_AHB1ENR &= ~(1<<Copy_Peripheral);
		break;

		case AHB2_BUS:
			RCC_AHB2ENR &= ~(1<<Copy_Peripheral);
		break;

		case APB1_BUS:
			RCC_APB1ENR &= ~(1<<Copy_Peripheral);
		break;

		case APB2_BUS:
			RCC_APB2ENR &= ~(1<<Copy_Peripheral);
		break;

	}
}
void RCC_ControlPrescalerAHB(u32 Copy_AHBPrescaler)
{
	u32 Local_CFGGR_REG;
	switch(Copy_AHBPrescaler)
	{
        case AHB_NO_CLOCK_FACTOR:
        	Local_CFGGR_REG  = RCC_CFGR;
        	Local_CFGGR_REG &= ~MASK_SET_PRE_AHB;
        	Local_CFGGR_REG |= (AHB_NO_CLOCK_FACTOR<<SHIFT_AHB);
		  RCC_CFGR = Local_CFGGR_REG;
        break;


        case AHB_CLOCK_DIVIDED_BY_2:
             Local_CFGGR_REG  = RCC_CFGR;
             Local_CFGGR_REG &= ~MASK_SET_PRE_AHB;
             Local_CFGGR_REG |= (AHB_CLOCK_DIVIDED_BY_2<<SHIFT_AHB);
             RCC_CFGR = Local_CFGGR_REG;
        break;


        case AHB_CLOCK_DIVIDED_BY_4:
             Local_CFGGR_REG  = RCC_CFGR;
             Local_CFGGR_REG &= ~MASK_SET_PRE_AHB;
             Local_CFGGR_REG |= (AHB_CLOCK_DIVIDED_BY_4<<SHIFT_AHB);
             RCC_CFGR = Local_CFGGR_REG;
        break;


        case AHB_CLOCK_DIVIDED_BY_8:
             Local_CFGGR_REG  = RCC_CFGR;
             Local_CFGGR_REG &= ~MASK_SET_PRE_AHB;
             Local_CFGGR_REG |= (AHB_CLOCK_DIVIDED_BY_8<<SHIFT_AHB);
             RCC_CFGR = Local_CFGGR_REG;
        break;


        case AHB_CLOCK_DIVIDED_BY_16:
              Local_CFGGR_REG  = RCC_CFGR;
              Local_CFGGR_REG &= ~MASK_SET_PRE_AHB;
              Local_CFGGR_REG |= (AHB_CLOCK_DIVIDED_BY_16<<SHIFT_AHB);
              RCC_CFGR = Local_CFGGR_REG;
        break;


        case AHB_CLOCK_DIVIDED_BY_64:
              Local_CFGGR_REG  = RCC_CFGR;
              Local_CFGGR_REG &= ~MASK_SET_PRE_AHB;
              Local_CFGGR_REG |= (AHB_CLOCK_DIVIDED_BY_64<<SHIFT_AHB);
              RCC_CFGR = Local_CFGGR_REG;
        break;


        case AHB_CLOCK_DIVIDED_BY_128:
              Local_CFGGR_REG  = RCC_CFGR;
              Local_CFGGR_REG &= ~MASK_SET_PRE_AHB;
              Local_CFGGR_REG |= (AHB_CLOCK_DIVIDED_BY_128<<SHIFT_AHB);
              RCC_CFGR = Local_CFGGR_REG;
        break;


        case AHB_CLOCK_DIVIDED_BY_256:
              Local_CFGGR_REG  = RCC_CFGR;
              Local_CFGGR_REG &= ~MASK_SET_PRE_AHB;
              Local_CFGGR_REG |= (AHB_CLOCK_DIVIDED_BY_256<<SHIFT_AHB);
              RCC_CFGR = Local_CFGGR_REG;
        break;


        case AHB_CLOCK_DIVIDED_BY_512:
              Local_CFGGR_REG  = RCC_CFGR;
              Local_CFGGR_REG &= ~MASK_SET_PRE_AHB;
              Local_CFGGR_REG |= (AHB_CLOCK_DIVIDED_BY_512<<SHIFT_AHB);
              RCC_CFGR = Local_CFGGR_REG;
        break;
	}
}

void RCC_ControlPrescalerAPB1(u32 Copy_APB1Prescaler)
{
	u32 Local_CFGGR_REG;
	switch(Copy_APB1Prescaler)
	{
		case APB1_NO_CLOCK_FACTOR:
			Local_CFGGR_REG = RCC_CFGR;
			Local_CFGGR_REG &= ~MASK_SET_PRE_APB1;
			Local_CFGGR_REG |= (APB1_NO_CLOCK_FACTOR<<SHIFT_APB1);
			RCC_CFGR = Local_CFGGR_REG;
		break;

		case APB1_CLOCK_DIVIDED_BY_2:
			Local_CFGGR_REG = RCC_CFGR;
			Local_CFGGR_REG &= ~MASK_SET_PRE_APB1;
			Local_CFGGR_REG |= (APB1_CLOCK_DIVIDED_BY_2<<SHIFT_APB1);
			RCC_CFGR = Local_CFGGR_REG;
		break;

		case APB1_CLOCK_DIVIDED_BY_4:
			Local_CFGGR_REG = RCC_CFGR;
			Local_CFGGR_REG &= ~MASK_SET_PRE_APB1;
			Local_CFGGR_REG |= (APB1_CLOCK_DIVIDED_BY_4<<SHIFT_APB1);
			RCC_CFGR = Local_CFGGR_REG;
		break;

		case APB1_CLOCK_DIVIDED_BY_8:
			Local_CFGGR_REG = RCC_CFGR;
			Local_CFGGR_REG &= ~MASK_SET_PRE_APB1;
			Local_CFGGR_REG |= (APB1_CLOCK_DIVIDED_BY_8<<SHIFT_APB1);
			RCC_CFGR = Local_CFGGR_REG;
		break;

		case APB1_CLOCK_DIVIDED_BY_16:
			Local_CFGGR_REG = RCC_CFGR;
			Local_CFGGR_REG &= ~MASK_SET_PRE_APB1;
			Local_CFGGR_REG |= (APB1_CLOCK_DIVIDED_BY_16<<SHIFT_APB1);
			RCC_CFGR = Local_CFGGR_REG;
		break;
	}
}

void RCC_ControlPrescalerAPB2(u32 Copy_APB1Prescaler)
{
	u32 Local_CFGGR_REG;
	switch(Copy_APB1Prescaler)
	{
		case APB2_NO_CLOCK_FACTOR:
			Local_CFGGR_REG = RCC_CFGR;
			Local_CFGGR_REG &= ~MASK_SET_PRE_APB2;
			Local_CFGGR_REG |= (APB1_NO_CLOCK_FACTOR<<SHIFT_APB2);
			RCC_CFGR = Local_CFGGR_REG;
		break;

		case APB2_CLOCK_DIVIDED_BY_2:
			Local_CFGGR_REG = RCC_CFGR;
			Local_CFGGR_REG &= ~MASK_SET_PRE_APB2;
			Local_CFGGR_REG |= (APB1_CLOCK_DIVIDED_BY_2<<SHIFT_APB2);
			RCC_CFGR = Local_CFGGR_REG;
		break;

		case APB2_CLOCK_DIVIDED_BY_4:
			Local_CFGGR_REG = RCC_CFGR;
			Local_CFGGR_REG &= ~MASK_SET_PRE_APB2;
			Local_CFGGR_REG |= (APB1_CLOCK_DIVIDED_BY_4<<SHIFT_APB2);
			RCC_CFGR = Local_CFGGR_REG;
		break;

		case APB2_CLOCK_DIVIDED_BY_8:
			Local_CFGGR_REG = RCC_CFGR;
			Local_CFGGR_REG &= ~MASK_SET_PRE_APB2;
			Local_CFGGR_REG |= (APB1_CLOCK_DIVIDED_BY_8<<SHIFT_APB2);
			RCC_CFGR = Local_CFGGR_REG;
		break;

		case APB2_CLOCK_DIVIDED_BY_16:
			Local_CFGGR_REG = RCC_CFGR;
			Local_CFGGR_REG &= ~MASK_SET_PRE_APB2;
			Local_CFGGR_REG |= (APB1_CLOCK_DIVIDED_BY_16<<SHIFT_APB2);
			RCC_CFGR = Local_CFGGR_REG;
		break;
	}
}
