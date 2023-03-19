#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__

#include "common.h"

#define LED_GPIO_PINS		(GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7)

/*位绑定定义*/
#define GPIO_ODR_A (GPIOA_BASE+0x0c)
#define GPIO_IDR_A (GPIOA_BASE+0x08)
#define GPIO_ODR_B (GPIOB_BASE+0x0c)
#define GPIO_IDR_B (GPIOB_BASE+0x08)
#define GPIO_ODR_C (GPIOC_BASE+0x0c)
#define GPIO_IDR_C (GPIOC_BASE+0x08)
#define GPIO_ODR_D (GPIOD_BASE+0x0c)
#define GPIO_IDR_D (GPIOD_BASE+0x08)
#define GPIO_ODR_E (GPIOE_BASE+0x0c)
#define GPIO_IDR_E (GPIOE_BASE+0x08)

#define BitBand(Addr,Num)	*((volatile unsigned long *)((Addr & 0xf0000000) + 0x2000000 + ((Addr & 0xfffff) << 5) + (Num << 2)))

#define PAout(n)	BitBand(GPIO_ODR_A,n)
#define PAin(n)		BitBand(GPIO_IDR_A,n)
#define PBout(n) 	BitBand(GPIO_ODR_B,n)
#define PBin(n)		BitBand(GPIO_IDR_B,n)
#define PCout(n) 	BitBand(GPIO_ODR_C,n)
#define PCin(n)		BitBand(GPIO_IDR_C,n)
#define PDout(n) 	BitBand(GPIO_ODR_D,n)
#define PDin(n)		BitBand(GPIO_IDR_D,n)
#define PEout(n) 	BitBand(GPIO_ODR_E,n)
#define PEin(n)		BitBand(GPIO_IDR_E,n)

void Bsp_Gpio_Led_Init(void);

#endif
