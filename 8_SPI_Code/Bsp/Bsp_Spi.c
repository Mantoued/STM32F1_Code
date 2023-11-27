#include "Bsp_Spi.h"


static void _Bsp_SPI_Gpio_Init(void)
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOG, ENABLE);
	
	//PB13 SCK, PB14 MISO, PB15 MOSI
	gpio.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &gpio);
	
	//CS
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOG, &gpio);
	
	SPI2_FLASH_CS(1);
}

void Bsp_SPI_Config(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	
	_Bsp_SPI_Gpio_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
	
	SPI_Cmd(SPI2, ENABLE);
	

}
