#include "main.h"

#define MAIN_DELAY_1MS 			(0X1FFF)
void delayms(uint32_t _xms)
{
	uint32_t times = MAIN_DELAY_1MS;
	while(_xms--)
	{
		times = MAIN_DELAY_1MS;
		while(times --);
	}
}

int main(void)
{
	Bsp_All_Init();
	while(1)
	{
		App_Tim_Service_Running();

		if (App_Tim_Get_Flag(TIM_100MS_SET))
			App_Gpio_Led_Running();
	}
	return 0;
}

