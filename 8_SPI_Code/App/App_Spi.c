#include "App_Spi.h"
#include "App_Lcd.h"

static void App_Flash_Init(void)
{
	uint16_t id = 0;
	Bsp_SPI_Config();
	
	id = Mid_Spi_Flash_Read_Device_ID();
	sprintf(Ascii_Buf, "This is a SPI Test.");
	
	Mid_Lcd_Show_16x16_Ascii(10, 20, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
	sprintf(Ascii_Buf, "The SPI id = 0x%x.", id);
	Mid_Lcd_Show_16x16_Ascii(10, 40, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
	
	sprintf(Ascii_Buf, "This is a Text for save:");
	Mid_Lcd_Show_16x16_Ascii(10, 60, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
	sprintf(Ascii_Buf, "I'm PT, This is my save text.");
	Mid_Lcd_Show_16x16_Ascii(20, 80, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
}

static char SPI_Buf[128];
#define SPI_FLASH_RW_ADDR				(10)
void App_Spi_Test(void)
{
	uint8_t text_len = 0;
	App_Flash_Init();
	
	sprintf(SPI_Buf, "I'm PT, This is my save text.");
	text_len = strlen(SPI_Buf);
	Mid_Flash_Write_Data((uint8_t *)SPI_Buf, SPI_FLASH_RW_ADDR, text_len);
	
	memset(SPI_Buf, 0, sizeof(SPI_Buf));
	sprintf(Ascii_Buf, "Save text writen and text buf cleared.");
	Mid_Lcd_Show_16x16_Ascii(10, 100, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
	
	sprintf(Ascii_Buf, "Save text read...");
	Mid_Lcd_Show_16x16_Ascii(10, 120, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
	
	Mid_Spi_Flash_Read_Data((uint8_t *)SPI_Buf, SPI_FLASH_RW_ADDR,  text_len);
	Mid_Lcd_Show_16x16_Ascii(20, 140, SPI_Buf, strlen(SPI_Buf), APP_WHITE, APP_BLACK);
	
	sprintf(Ascii_Buf, "Test Over.");
	Mid_Lcd_Show_16x16_Ascii(10, 180, Ascii_Buf, strlen(Ascii_Buf), APP_WHITE, APP_BLACK);
}

