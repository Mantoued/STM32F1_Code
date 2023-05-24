#ifndef __APP_GPIO_H__
#define __APP_GPIO_H__

#include "Mid_Gpio.h"

typedef enum{
	LED_CTRL_STATUS = 0,
	LED_CTRL_BIT,
}LED_CTRL_ENUM;

typedef union {
	uint8_t status;
	struct {
		uint8_t led_0 		:	1;
		uint8_t led_1 		:	1;
		uint8_t led_2 		:	1;
		uint8_t led_3 		:	1;
		uint8_t led_4 		:	1;
		uint8_t led_5 		:	1;
		uint8_t led_6 		:	1;
		uint8_t led_7 		:	1;	
	}mBit;
}LED_CTRL_UNION;

void App_Gpio_Waterfall_Light(void);
uint8_t App_Gpio_Get_Led_Status(void);
void App_Gpio_Led_Ctrl(LED_CTRL_ENUM _mode, uint8_t _status, uint8_t _index);
void App_Gpio_Led_Running(void);

#endif
