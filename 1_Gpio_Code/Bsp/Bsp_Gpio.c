#include "Bsp_Gpio.h"

void Bsp_Gpio_Led_Init(void)
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = LED_GPIO_PINS;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpio);
	
	GPIO_SetBits(GPIOC, LED_GPIO_PINS);
	
//	GPIOC->CRL &= 0x00000000;	//PC0~7  寄存器配置
//	GPIOC->CRL |= 0x33333333;	//推挽输出
//	GPIOC->ODR |= 0x00FF;			//默认输出高电平
}



