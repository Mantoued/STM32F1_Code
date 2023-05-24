#include "App_Gpio.h"

static LED_CTRL_UNION Led_Status;

void App_Gpio_Waterfall_Light(void)
{
	Led_Status.status = Mid_Gpio_Led_RW_Status(E_USER_READ, 0);
	if (0 == Led_Status.status) Led_Status.status = 0xFE;
	else Led_Status.status <<= 1;
}

void App_Gpio_Led_Ctrl(LED_CTRL_ENUM _mode, uint8_t _status, uint8_t _index)
{
	if (_index >= 8) return;
	
	if (LED_CTRL_STATUS == _mode)
	{
		Led_Status.status = _status;
		return;
	}
	
	_status &= 0x01;
	Led_Status.status &= ~(1 << _index);
	Led_Status.status |= (_status << _index);
}

uint8_t App_Gpio_Get_Led_Status(void)
{
	Led_Status.status = Mid_Gpio_Led_RW_Status(E_USER_READ, 0);
	return Led_Status.status;
}

void App_Gpio_Led_Running(void)
{
	Mid_Gpio_Led_RW_Status(E_USER_WRITE, Led_Status.status);
}

