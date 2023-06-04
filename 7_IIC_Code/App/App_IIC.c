#include "App_IIC.h"
#include "App_Lcd.h"

#define EEPROM_BYTES_PAGE_SIZE 			(8)
#define EEPROM_ADDR									(0xA0)

char IIC_Buf[128];
void App_IIC_Test(void)
{
	uint8_t text_len = 0;
	sprintf(Ascii_Buf, "This is a EEPROM Test.");
	Mid_Lcd_Show_16x16_Ascii(10, 20, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
	sprintf(Ascii_Buf, "This is a Text for save:");
	Mid_Lcd_Show_16x16_Ascii(10, 40, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
	sprintf(Ascii_Buf, "I'm PT, This is my save text.");
	Mid_Lcd_Show_16x16_Ascii(20, 60, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
	
	sprintf(IIC_Buf, "I'm PT, This is my save text.");
	text_len = strlen(IIC_Buf);
	Mid_IIC_Buffer_Write((uint8_t *)IIC_Buf, 0, EEPROM_ADDR, text_len, EEPROM_BYTES_PAGE_SIZE);
	memset(IIC_Buf, 0, sizeof(IIC_Buf));
	sprintf(Ascii_Buf, "Save text writen and text buf cleared.");
	Mid_Lcd_Show_16x16_Ascii(10, 80, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
	
	sprintf(Ascii_Buf, "Save text read...");
	Mid_Lcd_Show_16x16_Ascii(10, 100, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
	
	Mid_IIC_Buffer_Read((uint8_t *)IIC_Buf, 0, EEPROM_ADDR,  text_len);
	Mid_Lcd_Show_16x16_Ascii(20, 120, IIC_Buf, strlen(IIC_Buf), APP_WHITE, APP_BLACK);
	
	sprintf(Ascii_Buf, "Test Over.");
	Mid_Lcd_Show_16x16_Ascii(10, 140, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
}


