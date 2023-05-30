#include "App_Lcd.h"

char Ascii_Buf[100];

#define APP_BLACK				(0x0000)
#define APP_WHITE				(0xFFFF)
#define APP_BLUE				(0x00FF)
#define APP_YELLOW			(0xFF00)
#define APP_GREEN				(0x0FF0)
void App_Lcd_Init(void)
{
	Mid_Lcd_Fill_Rect(0, 0, 320, 480, APP_BLACK);
	Mid_Lcd_Fill_Rect(0, 0, 320, 20, APP_BLUE);
	Mid_Lcd_Fill_Rect(0, 460, 320, 20, APP_YELLOW);
}

void App_Lcd_Test(void)
{
	sprintf(Ascii_Buf, "System Start.");
	Mid_Lcd_Show_16x16_Ascii(10, 20, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
	sprintf(Ascii_Buf, "LCD OK!");
	Mid_Lcd_Show_16x16_Ascii(10, 40, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
}


