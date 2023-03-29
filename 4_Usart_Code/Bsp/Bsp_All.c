#include "Bsp_All.h"

void Bsp_All_Init(void)
{
	Bsp_Gpio_Led_Init();
	Bsp_Tim_SysTick_Init();
	Bsp_Key_Gpio_Init();
	Bsp_Usart_Config();
}
