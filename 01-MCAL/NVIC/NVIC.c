/*
 * NVIC.c
 *
 *  Created on: Mar 13, 2024
 *      Author: Mohammed Hani
 */

#include "NVIC.h"

typedef struct
{
    u32 NVIC_ISER[8];
    u32 Reserved[24];
    u32 NVIC_ICER[8];
    u32 Reserved1[24];
    u32 NVIC_ISPR[8];
    u32 Reserved2[24];
    u32 NVIC_ICPR[8];
    u32 Reserved3[24];
    u32 NVIC_IABR[8];
    u32 Reserved4[56];
    u32 NVIC_IPR[59];
    u32 Reserved5[643];
    u32 NVIC_STIR;
} NVIC_PERI_T;

#define 	NVIC  			 ((NVIC_PERI_T*)(0xE000E100))
#define 	AIRCR 			 (*(volatile u32*)0xE000ED0C)
#define 	NVIC_VECTKEY	 0x05FA0000
#define 	MAX_IRQ_NUMBER	 84
#define 	GROUPS_BASE      (0x05FA0300)


NVIC_ErrorStatus_t NVIC_IRQControl(u8 Copy_IRQn, u32 Copy_Status)
{
    NVIC_ErrorStatus_t Local_ErrorStatus = NVIC_OK;
    if(Copy_IRQn > MAX_IRQ_NUMBER)
    {
    	Local_ErrorStatus = NVIC_InvalidIRQ;
    }
    else if (Copy_Status != SET_PENDING && Copy_Status != CLR_PENDING)
    {
        Local_ErrorStatus = NVIC_InvalidStatus;
    }
    else
        {
            if (Copy_Status == IRQ_ENABLE)
            {
                NVIC->NVIC_ISER[Copy_IRQn / 32] = (1 << (Copy_IRQn % 32));
            }
            else
            {
                NVIC->NVIC_ICER[Copy_IRQn / 32] = (1 << (Copy_IRQn % 32));
            }
        }

     return Local_ErrorStatus;

}
NVIC_ErrorStatus_t NVIC_IRQPendingControl(u8 Copy_IRQn, u32 Copy_Status)
{
    NVIC_ErrorStatus_t Local_ErrorStatus = NVIC_OK;
    if(Copy_IRQn > MAX_IRQ_NUMBER)
    {
    	Local_ErrorStatus = NVIC_InvalidIRQ;
    }
    else if (Copy_Status != SET_PENDING && Copy_Status != CLR_PENDING)
    {
        Local_ErrorStatus = NVIC_InvalidStatus;
    }
    else
        {
    	if (Copy_Status == SET_PENDING)
    	        {
    	            NVIC->NVIC_ISPR[Copy_IRQn / 32] = (1 << (Copy_IRQn % 32));
    	        }
    	        else
    	        {
    	            NVIC->NVIC_ICPR[Copy_IRQn / 32] = (1 << (Copy_IRQn % 32));
    	        }
        }
    return Local_ErrorStatus;
}
NVIC_ErrorStatus_t NVIC_GetActive(u8 Copy_IRQn, u32 *Add_Status)
{
    NVIC_ErrorStatus_t Local_ErrorStatus = NVIC_OK;

    if (Copy_IRQn > MAX_IRQ_NUMBER)
    {
        Local_ErrorStatus = NVIC_InvalidIRQ;
    }
    else if (!Add_Status)
    {
        Local_ErrorStatus = NVIC_NullPtr;
    }
    else
    {
        u16 Local_RegisterNumber = Copy_IRQn / 32;
        u16 Local_BitPosition = Copy_IRQn % 32;
        u32 Local_TempIABR = (NVIC->NVIC_IABR[Local_RegisterNumber]);
        *Add_Status = (Local_TempIABR & (1 << Local_BitPosition)) >> Local_BitPosition;
    }

    return Local_ErrorStatus;

}
NVIC_ErrorStatus_t NVIC_GenerateSwINT(u8 Copy_IRQn)
{
    NVIC_ErrorStatus_t Local_ErrorStatus = NVIC_OK;

    if (Copy_IRQn > MAX_IRQ_NUMBER)
    {
        Local_ErrorStatus = NVIC_InvalidIRQ;
    }
    else
    {
        u32 Local_TempSTIR = NVIC->NVIC_STIR;
        Local_TempSTIR |= Copy_IRQn;
        NVIC->NVIC_STIR = Local_TempSTIR;
    }
     return Local_ErrorStatus;

}
void NVIC_SetIRQPriority(u8 Copy_IRQn, u32 Copy_Preemtion, u32 Copy_SubGroupPriorty, u32 Copy_GroupName)
{
    u16 Local_BitIndex = ((Copy_IRQn % 4) * 8) + 4;
    u16 Loc_PriortyValue = Copy_SubGroupPriorty | (Copy_Preemtion << ((Copy_GroupName - GROUPS_BASE) >> 8));
    u32 Loc_TempIpr = NVIC->NVIC_IPR[Copy_IRQn / 4];

    Loc_TempIpr &= ~(0xF << Local_BitIndex);
    Loc_TempIpr |= Loc_PriortyValue << Local_BitIndex;
    NVIC->NVIC_IPR[Copy_IRQn / 4] = Loc_TempIpr;
    AIRCR = Copy_GroupName;

}


