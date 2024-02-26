/*
 * LED.c
 *
 *  Created on: Feb 26, 2024
 *      Author: Mohammed Hani
 */

/*
 * LED.c
 *
 *  Created on: Feb 25, 2024
 *      Author: Mohammed Hani
 */

#include "LED.h"
#include "GPIO.h"

extern const LED_cfg_t LEDs[_LED_Num];

void LED_Init(void)
{
	u8 Local_Iterator;
	GPIOPinConfg_t LED_cfg;
	LED_cfg.GPIODirection = GPIO_OUTPUT;
	LED_cfg.GPIOSpeed = GPIO_OUTPUT_SPEED_HIGH;
	LED_cfg.GPIOMode = GPIO_OUTPUT_PUSHPULL;


	for(Local_Iterator = 0; Local_Iterator < _LED_Num; Local_Iterator++)
	{
		LED_cfg.GPIOPort = LEDs[Local_Iterator].Port;
		LED_cfg.GPIOPin =  LEDs[Local_Iterator].Pin;
		GPIO_Init(&LED_cfg);
	}
}

void LED_SetLEDState (u32 LED_Name , u32 LED_State)
{
	GPIO_SetPinValue(LEDs[LED_Name].Port ,LEDs[LED_Name].Pin , (LED_State) ^ (LEDs[LED_Name].Connection));

}



