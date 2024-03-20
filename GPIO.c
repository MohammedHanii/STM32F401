/*
 * GPIO.c
 *
 *  Created on: Feb 18, 2024
 *      Author: Mohammed Hani
 */

#include "GPIO.h"

typedef struct
{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIOReg_t;

#define 	MASK_LSB			0x1
#define		MASK_LS2B			0x3

#define 	GPIOA_BASE_ADDRESS 	((volatile GPIOReg_t* const) 0x40020000)
#define 	GPIOB_BASE_ADDRESS 	((volatile GPIOReg_t* const) 0x40020400)
#define 	GPIOC_BASE_ADDRESS 	((volatile GPIOReg_t* const) 0x40020800)
#define 	GPIOD_BASE_ADDRESS 	((volatile GPIOReg_t* const) 0x40020C00)
#define 	GPIOE_BASE_ADDRESS 	((volatile GPIOReg_t* const) 0x40021000)
#define 	GPIOH_BASE_ADDRESS 	((volatile GPIOReg_t* const) 0x40021C00)


volatile GPIOReg_t * const GPIO[NUMBER_OF_PORTS] =
{
		GPIOA_BASE_ADDRESS,
		GPIOB_BASE_ADDRESS ,
		GPIOC_BASE_ADDRESS,
		GPIOD_BASE_ADDRESS,
		GPIOE_BASE_ADDRESS,
		GPIOH_BASE_ADDRESS
};

GPIOErrorStatus GPIO_Init(GPIOPortConfg_t * Copy_PortConfig)
{
	GPIOErrorStatus ReturnError = GPIO_OK;
	u32 Local_TempConfig 	= GPIO[Copy_PortConfig -> GPIOPort] -> MODER;
	u32 Local_PinMode 		= Copy_PortConfig -> GPIOMode;
	u32 Local_PinDirection  = Copy_PortConfig -> GPIODirection;
	u32 Local_PinSpeed 		= Copy_PortConfig -> GPIOSpeed;
	u32 Local_PinNumber 	= Copy_PortConfig -> GPIOPin;

	if(Copy_PortConfig -> GPIOPort > NUMBER_OF_PORTS)
		{
			ReturnError = GPIO_PortError;
		}
		else if(Copy_PortConfig -> GPIOPin > NUMBER_OF_PINS)
		{
			ReturnError = GPIO_PinError;
		}
		else if(Copy_PortConfig -> GPIOMode > GPIO_ANALOG)
		{
				ReturnError = GPIO_WrongConfig;
		}
		else if(Copy_PortConfig -> GPIOSpeed > GPIO_OUTPUT_SPEED_VERY_HIGH)
		{
			ReturnError = GPIO_SpeedError;
		}
	else
	{
		//MODE REGISTER(MODER)
		Local_TempConfig &= ~(MASK_LS2B << (Local_PinNumber*2));
		Local_TempConfig |= Local_PinDirection << (Local_PinNumber*2);
		GPIO[Copy_PortConfig -> GPIOPort] -> MODER = Local_TempConfig;

		// O/P TYPE REGISTER(OTYPER)
		if(Copy_PortConfig -> GPIODirection == GPIO_OUTPUT)
		{
			Local_TempConfig &= ~(MASK_LSB <<Local_PinNumber);
			Local_TempConfig |= Local_PinMode << Local_PinNumber;
			GPIO[Copy_PortConfig -> GPIOPort] -> OTYPER = Local_TempConfig;
		}
		else
		{
			//PULL-UP , PULL-DOWN REGISTER(PUPDR)
			Local_TempConfig &= ~(MASK_LS2B << (Local_PinNumber*2));
			Local_TempConfig |= (Local_PinMode << (Local_PinNumber*2));
			GPIO[Copy_PortConfig -> GPIOPort] -> PUPDR = Local_TempConfig;
		}

		// OUTPUT SPEED REGISTER(OSPEEDR)
		Local_TempConfig &= ~(MASK_LS2B << (Local_PinNumber*2));
		Local_TempConfig |= (Local_PinSpeed << (Local_PinNumber*2));
		GPIO[Copy_PortConfig -> GPIOPort] -> OSPEEDR = Local_TempConfig;

	}
	return ReturnError;
}
GPIOErrorStatus GPIO_SetPinValue(u8 Copy_Port, u8 Copy_PinNum, u8 Copy_Value)
{
	GPIOErrorStatus ReturnError = GPIO_OK;
	if(Copy_Port > NUMBER_OF_PORTS)
	{
		ReturnError = GPIO_PortError;
	}
	else if(Copy_PinNum > NUMBER_OF_PINS)
	{
		ReturnError = GPIO_PinError;
	}
	else if((Copy_Value != GPIO_VALUE_SET) && (Copy_Value != GPIO_VALUE_RESET))
	{
			ReturnError = GPIO_ValueError;
	}
	else
	{
		if(Copy_Value == GPIO_VALUE_SET)
		{
			GPIO[Copy_Port] -> BSRR |= 1 << (Copy_PinNum);
		}
		else
		{
			GPIO[Copy_Port] -> BSRR |= 1 << (Copy_PinNum + 16);
		}
	}

	return ReturnError;
}
GPIOErrorStatus GPIO_GetPinValue(u8 Copy_Port, u8 Copy_PinNum, u8* Add_Value)
{
	GPIOErrorStatus ReturnError = GPIO_OK;
	u32 Local_Reg;
		if(Copy_Port > NUMBER_OF_PORTS)
		{
			ReturnError = GPIO_PortError;
		}
		else if(Copy_PinNum > NUMBER_OF_PINS)
		{
			ReturnError = GPIO_PinError;
		}
		else if(Add_Value == NULL)
		{
				ReturnError = GPIO_NullPointer;
		}
		else
		{
			Local_Reg = GPIO[Copy_Port] -> IDR;
			*Add_Value = (Local_Reg & (1 << Copy_PinNum)) >> Copy_PinNum;
		}
		return ReturnError;
}
