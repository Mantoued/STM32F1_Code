#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "common.h"
#include "Bsp_Gpio.h"

#define KEY_UP_PIN 					(GPIO_Pin_0)
#define KEY_UP_PORT 				(GPIOA)
#define KEY_UP_CLOCK				(RCC_APB2Periph_GPIOA)

#define KEY_K0_UP 					(PAin(0))

#define KEY_K1_K2_K3_PIN		(GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4)
#define KEY_K1_K2_K3_PORT		(GPIOE)
#define KEY_K1_K2_K3_CLOCK	(RCC_APB2Periph_GPIOE)

#define KEY_K1_LEFT 				(PEin(2))
#define KEY_K2_DOWN 				(PEin(3))
#define KEY_K3_RIGHT 				(PEin(4))



void Bsp_Key_Gpio_Init(void);

#endif
