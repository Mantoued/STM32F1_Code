#include "Bsp_Gpio.h"

void Bsp_Gpio_Led_Init(void)
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(LED_GPIO_CLOCK, ENABLE);
	
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = LED_GPIO_PINS;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(LED_GPIO_PORT, &gpio);
	
	GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PINS);
	
//	GPIOC->CRL &= 0x00000000;	//PC0~7  �Ĵ�������
//	GPIOC->CRL |= 0x33333333;	//�������
//	GPIOC->ODR |= 0x00FF;			//Ĭ������ߵ�ƽ
}



