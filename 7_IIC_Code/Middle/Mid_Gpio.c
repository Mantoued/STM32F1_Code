#include "Mid_Gpio.h"


void Mid_Gpio_Led_Ctrl(uint8_t _led, MID_GPIO_LED_OPERATION _opt)
{
	switch (_opt)
	{
	case LED_OFF_OPT:
		MID_GPIO_LED(_led) = LED_OFF_STA;
		break;
	case LED_ON_OPT:
		MID_GPIO_LED(_led) = LED_ON_STA;
		break;
	case LED_TOGGLE_OPT:
		MID_GPIO_LED(_led) = ~MID_GPIO_LED(_led);
		break;
	default:
		
		break;
	}
}

uint8_t Mid_Gpio_Led_RW_Status(USER_READ_WRITE _rw, uint8_t _status)
{
	uint8_t re = 0;
	switch (_rw)
	{
	case E_USER_READ:
		re = GPIOC->ODR & 0xFF;
		break;
	case E_USER_WRITE:
		GPIOC->ODR &= 0xFFFFFF00;
		GPIOC->ODR |= _status;
		break;
	default:
		break;
	}
	
	return re;
}

