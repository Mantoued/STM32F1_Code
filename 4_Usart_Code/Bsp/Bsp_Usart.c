#include "Bsp_Usart.h"

static void _Bsp_Usart_Gpio_Init(void)
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_9;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_10;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);
}

void Bsp_Usart_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 |RCC_APB2Periph_AFIO, ENABLE);
	_Bsp_Usart_Gpio_Init();
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	
	USART_SendData(USART1, ' ');
	while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
}

