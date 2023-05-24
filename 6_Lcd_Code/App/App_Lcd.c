#include "App_Lcd.h"

void App_Lcd_Init(void)
{
	Mid_Lcd_Fill_Rect(0, 0, 320, 480, 0xFFFF);
}

void App_Lcd_Test(void)
{
	Mid_Lcd_Fill_Rect(0, 0, 50, 50, 0xFF);
	Mid_Lcd_Fill_Rect(10, 10, 50, 50, 0xFF00);
	Mid_Lcd_Draw_H_Line(100, 100, 200, 0x0FF0);
	Mid_Lcd_Draw_V_Line(100, 100, 200, 0x0FF0);
}


