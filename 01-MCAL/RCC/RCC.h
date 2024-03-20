/*
 * RCC.h
 *
 *  Created on: Feb 5, 2024
 *      Author: Mohammed Hani
 */

#ifndef RCC_H_
#define RCC_H_
#include "STD_TYPES.h"

/*************************NEW TYPES*************************/
typedef enum
{
  HSI,
  HSE
}RCC_enuPLLSRC_t;

typedef struct
{
  RCC_enuPLLSRC_t   RCC_PLLSCR;
  u32  RCC_PLL_M;
  u32  RCC_PLL_N;
  u32  RCC_PLL_P;
  u32  RCC_PLL_Q;
}RCC_structCLKPLL_t;

/*************************REGISTERS*************************/
#define 		RCC_CR                  *((volatile u32*)0x40023800)
#define 		RCC_PLLCFGR             *((volatile u32*)0x40023804)
#define 		RCC_CFGR                *((volatile u32*)0x40023808)
#define 		RCC_CIR                 *((volatile u32*)0x4002380C)
#define 		RCC_AHB1RSTR            *((volatile u32*)0x40023810)
#define 		RCC_AHB2RSTR            *((volatile u32*)0x40023814)
#define 		RCC_APB1RSTR            *((volatile u32*)0x40023820)
#define 		RCC_APB2RSTR            *((volatile u32*)0x40023824)
#define 		RCC_AHB1ENR             *((volatile u32*)0x40023830)
#define 		RCC_AHB2ENR             *((volatile u32*)0x40023834)
#define 		RCC_APB1ENR             *((volatile u32*)0x40023840)
#define 		RCC_APB2ENR             *((volatile u32*)0x40023844)
#define 		RCC_AHB1LPENR           *((volatile u32*)0x40023850)
#define 		RCC_AHB2LPENR           *((volatile u32*)0x40023854)
#define 		RCC_APB1LPENR           *((volatile u32*)0x40023860)
#define 		RCC_APB2LPENR           *((volatile u32*)0x40023864)
#define 		RCC_BDCR                *((volatile u32*)0x40023870)
#define 		RCC_CSR                 *((volatile u32*)0x40023874)
#define 		RCC_SSCGR               *((volatile u32*)0x40023880)
#define 		RCC_PLLI2SCFGR          *((volatile u32*)0x40023884)
#define 		RCC_DCKCFGR             *((volatile u32*)0x4002388C)

/*************************CLOCKS*************************/
#define 		RCC_HSI                 0
#define 		RCC_HSE                 1
#define 		RCC_PLL                 2

/*************************CLOCK STATUS*************************/
#define			CLOCK_STATUS_OFF						0
#define			CLOCK_STATUS_ON							1

/*************************MASKS*************************/
#define			MASK_HSI_ON				0x00000001
#define			MASK_HSI_READY			0x00000002
#define			MASK_HSE_ON  			0x00010000
#define         MASK_HSE_READY 			0x00020000
#define			MASK_PLL_ON				0x01000000
#define         MASK_PLL_READY			0x02000000
#define 		MASK_SW                 0x00000003
#define 		MASK_GET_SWS            0x0000000C
#define			MASK_SWS_HSI 			0x00000000
#define 		MASK_SWS_HSE 			0x00000004
#define			MASK_SWS_PLL 			0x00000008

#define 		MASK_SET_HSI            0x00000001
#define 		MASK_SET_HSE            0x00010000
#define 		MASK_SET_PLL            0x01000000

#define 		MASK_PPL_M           	0x0000003F
#define 		MASK_PPL_N           	0x00007FC0
#define 		MASK_PPL_P           	0x00030000
#define 		MASK_PPL_Q           	0x0F000000
#define 		MASK_PPL_SRC         	0x00400000
#define 		MASK_SET_PRE_AHB        0x000000F0
#define 		MASK_SET_PRE_APB1       0x00001C00
#define 		MASK_SET_PRE_APB2       0x0000E000

#define 		SHIFT_AHB                4
#define 		SHIFT_APB1               10
#define 		SHIFT_APB2               13

#define 		SHIFT_PLL_M              0
#define 		SHIFT_PLL_N              6
#define 		SHIFT_PLL_P              16
#define 		SHIFT_PLL_Q              24
#define 		SHIFT_PLL_SRC            22

/*************************AHB PRESCALERS*************************/
#define 		AHB_NO_CLOCK_FACTOR          0b0000
#define 		AHB_CLOCK_DIVIDED_BY_2       0b1000
#define 		AHB_CLOCK_DIVIDED_BY_4       0b1001
#define 		AHB_CLOCK_DIVIDED_BY_8       0b1010
#define 		AHB_CLOCK_DIVIDED_BY_16      0b1011
#define 		AHB_CLOCK_DIVIDED_BY_64      0b1100
#define 		AHB_CLOCK_DIVIDED_BY_128     0b1101
#define	 		AHB_CLOCK_DIVIDED_BY_256     0b1110
#define 		AHB_CLOCK_DIVIDED_BY_512     0b1111

/*************************APB1 PRESCALERS*************************/
#define 		APB1_NO_CLOCK_FACTOR          0b000
#define 		APB1_CLOCK_DIVIDED_BY_2       0b100
#define 		APB1_CLOCK_DIVIDED_BY_4       0b101
#define 		APB1_CLOCK_DIVIDED_BY_8       0b110
#define 		APB1_CLOCK_DIVIDED_BY_16      0b111

/*************************APB2 PRESCALERS*************************/
#define 		APB2_NO_CLOCK_FACTOR                           0b000
#define 		APB2_CLOCK_DIVIDED_BY_2                        0b100
#define 		APB2_CLOCK_DIVIDED_BY_4                        0b101
#define 		APB2_CLOCK_DIVIDED_BY_8                        0b110
#define 		APB2_CLOCK_DIVIDED_BY_16                       0b111

/*************************PERIPHERALS DEFINES*************************/
/*************************AHB1*************************/
#define 		GPIOA_RCC                       0
#define 		GPIOB_RCC                       1
#define 		GPIOC_RCC                       2
#define 		GPIOD_RCC                       3
#define 		GPIOE_RCC                       4
#define 		GPIOH_RCC                       7
#define 		CRC_RCC                         12
#define 		DMA1_RCC                        21
#define 		DMA2_RCC                        22

/*************************AHB2*************************/
#define 		OTGFS_RCC 						7

/*************************APB1*************************/
#define 		TIM2_RCC                        0
#define 		TIM3_RCC                        1
#define 		TIM4_RCC                        2
#define 		TIM5_RCC                        3
#define 		WWDG_RCC                        11
#define 		SPI2_RCC                        14
#define 		SPI3_RCC                        15
#define 		USART2_RCC                      17
#define 		I2C1_RCC                        21
#define 		I2C2_RCC                        22
#define 		I2C3_RCC                        23
#define 		PWR_RCC                         28

/*************************APB2*************************/
#define 		TIM1_RCC                        0
#define 		USART1_RCC                      4
#define 		USART6_RCC                      5
#define 		ADC1_RCC                        8
#define 		SDIO_RCC                        11
#define 		SPI1_RCC                        12
#define 		SPI4_RCC                        13
#define 		SYSCFG_RCC                      14
#define 		TIM9_RCC                        16
#define 		TIM10_RCC                       17
#define 		TIM11_RCC                       18


#define 		AHB1_BUS                        0
#define 		AHB2_BUS                        1
#define 		APB1_BUS                        2
#define 		APB2_BUS                        3


/*************************FUNCTION PROTOTYPES*************************/
void RCC_SelectClk(u8 Copy_SysClk);

void RCC_ConrolClk(u8 Copy_SysClk, u8 ClkStatus);

void RCC_ConfigPLL(RCC_structCLKPLL_t Copy_structPLLCongif);

void RCC_EnablePeripheral(u32 Copy_PeripheralBus, u32 Copy_Peripheral);

void RCC_DisablePeripheral(u32 Copy_PeripheralBus, u32 Copy_Peripheral);

void RCC_ControlPrescalerAHB(u32 Copy_AHBPrescaler);

void RCC_ControlPrescalerAPB1(u32 Copy_APB1Prescaler);

void RCC_ControlPrescalerAPB2(u32 Copy_APB2Prescaler);




#endif /* RCC_H_ */
