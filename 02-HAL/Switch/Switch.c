/*
 * LED.c
 *
 *  Created on: Feb 25, 2024
 *      Author: Mohammed Hani
 */

#include "Switch.h"
#include "GPIO.h"

extern const Switch_cfg_t SWITCHEs[_Switch_Num];

void Switch_Init(void)
{
	u8 Local_Iterator;
	GPIOPinConfg_t Switch_cfg;
	Switch_cfg.GPIODirection = GPIO_INPUT;
	Switch_cfg.GPIOSpeed = GPIO_OUTPUT_SPEED_HIGH;


	for(Local_Iterator = 0; Local_Iterator < _Switch_Num; Local_Iterator++)
	{
		Switch_cfg.GPIOPort = SWITCHEs[Local_Iterator].Port;
		Switch_cfg.GPIOPin =  SWITCHEs[Local_Iterator].Pin;
		Switch_cfg.GPIOMode = SWITCHEs[Local_Iterator].State;
		GPIO_Init(&Switch_cfg);
	}
}

void Switch_GetSwitchState(u32 SwitchName, u32 *Add_SwitchState)
{
    u32 Loc_State;
    u32 Loc_Temp = 0 ;
    GPIO_GetPinValue(SWITCHEs[SwitchName].Port, SWITCHEs[SwitchName].Pin, &Loc_State);
    if(SWITCHEs[SwitchName].State == GPIO_INPUT_PULL_UP)
    {
      Loc_Temp = 1 ;
    }
    else
    {
      Loc_Temp = 0 ;
    }
    *Add_SwitchState = Loc_State ^ Loc_Temp;
}
