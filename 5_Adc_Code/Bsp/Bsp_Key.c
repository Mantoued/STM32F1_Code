#include "Bsp_Key.h"

void Bsp_Key_Gpio_Init(void)
{
	GPIO_InitTypeDef key_Gpio;
	RCC_APB2PeriphClockCmd(KEY_UP_CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(KEY_K1_K2_K3_CLOCK, ENABLE);
	
	GPIO_StructInit(&key_Gpio);
	key_Gpio.GPIO_Pin = KEY_UP_PIN;
	key_Gpio.GPIO_Mode = GPIO_Mode_IPD;					//下拉输入
	key_Gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(KEY_UP_PORT, &key_Gpio);
	
	key_Gpio.GPIO_Pin = KEY_K1_K2_K3_PIN;
	key_Gpio.GPIO_Mode = GPIO_Mode_IPU;					//上拉输入
	GPIO_Init(KEY_K1_K2_K3_PORT, &key_Gpio);
}



