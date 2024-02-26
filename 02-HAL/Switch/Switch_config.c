/*
 * Switch_config.c
 *
 *  Created on: Feb 25, 2024
 *      Author: Mohammed Hani
 */

#include "Switch.h"
#include "Switch_config.h"

const Switch_cfg_t SWITCHEs[_Switch_Num] =
{
	[Switch_1] =
	{
		.Port 		  = GPIO_PORTA,
		.Pin  		  = GPIO_PIN0,
		.State		  = GPIO_INPUT_PULL_UP,
	},
	[Switch_2] =
	{
		.Port 		  = GPIO_PORTA,
		.Pin  		  = GPIO_PIN1,
		.State		  = GPIO_INPUT_PULL_UP,
	},

};


