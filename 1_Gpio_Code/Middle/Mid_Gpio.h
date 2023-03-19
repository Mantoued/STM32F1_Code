#ifndef __MID_GPIO_H__
#define __MID_GPIO_H__

#include "Bsp_Gpio.h"

typedef enum {
	LED_ON_STA = 0,
	LED_OFF_STA,
}MID_GPIO_LED_STATUS;

typedef enum {
	LED_OFF_OPT = 0,
	LED_ON_OPT,
	LED_TOGGLE_OPT,
}MID_GPIO_LED_OPERATION;

#define MID_GPIO_LED(n) 				(PCout(n))

void Mid_Gpio_Led_Ctrl(uint8_t _led, MID_GPIO_LED_OPERATION _opt);
uint8_t Mid_Gpio_Led_RW_Status(USER_READ_WRITE _rw, uint8_t _status);

#endif
