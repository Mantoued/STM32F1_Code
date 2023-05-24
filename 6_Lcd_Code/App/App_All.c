#include "App_All.h"

void App_All_Init(void)
{
	App_Gpio_Get_Led_Status();
	App_Key_Data_Init();
	App_Key_Set_Func();
	App_Usart_Init();
	App_Lcd_Init();
	App_Lcd_Test();
}
