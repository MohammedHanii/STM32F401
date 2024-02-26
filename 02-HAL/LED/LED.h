/*
 * LED.h
 *
 *  Created on: Feb 25, 2024
 *      Author: Mohammed Hani
 */

#ifndef LED_H_
#define LED_H_

#include "STD_TYPES.h"
#include "LED_config.h"
#include "GPIO.h"

typedef struct
{
    u32 Port;
    u32 Pin;
    u8 Connection;
    u8 DefaultState;
}LED_cfg_t;

typedef enum
{
    LED_OK,
	LED_enuInvalidPortNum,
	LED_enuInvalidPinNum,
	LED_enuInvalidMode,
	LED_enuNullPtr,
    LED_NOK
} LED_ErrorStatus_t;

#define 	LED_ON       1
#define 	LED_OFF      0

#define LED_CONNECTION_FORWARD  0
#define LED_CONNECTION_REVERSE  1

void LED_Init(void);

void LED_SetLEDState (u32 LED_Name , u32 LED_State);


#endif /* LED_H_ */
