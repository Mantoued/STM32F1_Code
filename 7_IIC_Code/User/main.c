#include "main.h"
//#include "stm32f10x_conf.h"
int main(void)
{
	Bsp_All_Init();
	App_All_Init();
	while(1)
	{
		App_Tim_Service_Running();

		if (App_Tim_Get_Flag(TIM_40MS_SET))
		{
			App_Key_Running();
			//App_Usart_Recv_And_Send();
		}
		
		if (App_Tim_Get_Flag(TIM_100MS_SET))
		{
			App_Gpio_Led_Running();
		}
		
		if (App_Tim_Get_Flag(TIM_1000MS_SET))
		{
			App_Usart_Send_Adc_Value();
		}
	}
	return 0;
}

