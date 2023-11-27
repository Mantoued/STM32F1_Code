#ifndef __APP_LCD_H__
#define __APP_LCD_H__

#include "Mid_Lcd.h"

#define APP_BLACK				(0x0000)
#define APP_WHITE				(0xFFFF)
#define APP_BLUE				(0x00FF)
#define APP_YELLOW			(0xFF00)
#define APP_GREEN				(0x0FF0)

extern char Ascii_Buf[100];
void App_Lcd_Init(void);
void App_Lcd_Test(void);

#endif
