#include "App_Lcd.h"

char Ascii_Buf[100];

void App_Lcd_Init(void)
{
	Mid_Lcd_Fill_Rect(0, 0, 320, 480, APP_BLACK);
	Mid_Lcd_Fill_Rect(0, 0, 320, 20, APP_BLUE);
	Mid_Lcd_Fill_Rect(0, 460, 320, 20, APP_YELLOW);
}

void App_Lcd_Test(void)
{
//	sprintf(Ascii_Buf, "System Start.");
//	Mid_Lcd_Show_16x16_Ascii(10, 20, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
//	sprintf(Ascii_Buf, "LCD OK!");
//	Mid_Lcd_Show_16x16_Ascii(10, 40, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
}


