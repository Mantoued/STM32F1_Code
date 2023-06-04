#include "Bsp_Tim.h"

void Bsp_Tim_SysTick_Init(void)
{
	SysTick_Config(SystemCoreClock / 1000);
}
