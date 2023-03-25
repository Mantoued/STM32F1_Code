#include "App_Gpio.h"

void App_Gpio_Led_Running(void)
{
	uint8_t led_status = 0;
	
	led_status = Mid_Gpio_Led_RW_Status(E_USER_READ, 0);
	if (0 == led_status) led_status = 0xFE;
	else led_status <<= 1;
	
	Mid_Gpio_Led_RW_Status(E_USER_WRITE, led_status);
}

