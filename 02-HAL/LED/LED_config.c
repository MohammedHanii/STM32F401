/*
 * LED_config.c
 *
 *  Created on: Feb 25, 2024
 *      Author: Mohammed Hani
 */

#include "LED.h"
#include "LED_config.h"

const LED_cfg_t LEDs[_LED_Num] =
{
	[LED_Red] =
	{
		.Port 		  = GPIO_PORTA,
		.Pin  		  = GPIO_PIN0,
		.Connection   = LED_CONNECTION_FORWARD,
		.DefaultState = LED_OFF,
	},
	[LED_Green] =
	{
		.Port 		  = GPIO_PORTA,
		.Pin  		  = GPIO_PIN1,
		.Connection   = LED_CONNECTION_FORWARD,
		.DefaultState = LED_OFF,
	},
	[LED_Blue] =
	{
		.Port 		  = GPIO_PORTA,
		.Pin  		  = GPIO_PIN2,
		.Connection   = LED_CONNECTION_FORWARD,
		.DefaultState = LED_OFF,
	},

};


