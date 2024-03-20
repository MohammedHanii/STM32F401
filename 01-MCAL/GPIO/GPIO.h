/*
 * GPIO.h
 *
 *  Created on: Feb 18, 2024
 *      Author: Mohammed Hani
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "STD_TYPES.h"

typedef struct
{
	u32  GPIOPort;
	u32  GPIOPin;
	u32  GPIODirection;
	u32  GPIOMode;
	u32  GPIOSpeed;

}GPIOPortConfg_t;

typedef enum
{
	GPIO_OK,
	GPIO_PortError,
	GPIO_PinError,
	GPIO_SpeedError,
	GPIO_ValueError,
	GPIO_WrongConfig,
	GPIO_NullPointer
}GPIOErrorStatus;

#define		GPIO_PORTA		    0
#define		GPIO_PORTB		    1
#define		GPIO_PORTC		    2
#define		GPIO_PORTD          3
#define		GPIO_PORTE		    4
#define		GPIO_PORTH          5

#define 	GPIO_PIN0   		0
#define 	GPIO_PIN1   		1
#define 	GPIO_PIN2   		2
#define 	GPIO_PIN3   		3
#define 	GPIO_PIN4   		4
#define 	GPIO_PIN5   		5
#define 	GPIO_PIN6   		6
#define 	GPIO_PIN7   		7
#define 	GPIO_PIN8   		8
#define 	GPIO_PIN9   		9
#define 	GPIO_PIN10  		10
#define 	GPIO_PIN11  		11
#define 	GPIO_PIN12  		12
#define 	GPIO_PIN13  		13
#define 	GPIO_PIN14  		14
#define 	GPIO_PIN15  		15

#define 	NUMBER_OF_PORTS 	6
#define 	NUMBER_OF_PINS 		15

#define		GPIO_VALUE_SET		1
#define		GPIO_VALUE_RESET	0
/********************************PIN MODES********************************/
#define 	GPIO_INPUT      	0x0
#define 	GPIO_OUTPUT     	0x1
#define 	GPIO_AF_M       	0x2
#define 	GPIO_ANALOG     	0x3
/********************************OUTPUT MODE********************************/
#define GPIO_OUTPUT_PUSHPULL    0x0
#define GPIO_OUTPUT_OPENDRAIN   0x1
/********************************INPUT MODE********************************/
#define GPIO_INPUT_PULL_NO     0x0
#define GPIO_INPUT_PULL_UP     0x1
#define GPIO_INPUT_PULL_DOWN   0x2
/********************************SPEED********************************/
#define GPIO_OUTPUT_SPEED_LOW         0x0
#define GPIO_OUTPUT_SPEED_MEDIUM      0x1
#define GPIO_OUTPUT_SPEED_HIGH        0x2
#define GPIO_OUTPUT_SPEED_VERY_HIGH   0x3

/********************************PROTOTYPES********************************/
GPIOErrorStatus GPIO_Init(GPIOPortConfg_t * Copy_PortConfig);
GPIOErrorStatus GPIO_SetPinValue(u8 Copy_Port, u8 Copy_PinNum, u8 Copy_Value);
GPIOErrorStatus GPIO_GetPinValue(u8 Copy_Port, u8 Copy_PinNum, u8* Add_Value);

#endif /* GPIO_H_ */
