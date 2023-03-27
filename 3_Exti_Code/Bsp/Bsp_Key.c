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

void Bsp_Key_NVIC_Config(void)
{
	NVIC_InitTypeDef Key_NVIC;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			// 设置中断优先级分组2
	
	Key_NVIC.NVIC_IRQChannel = EXTI0_IRQn;							//使能按键所在的外部中断通道
	Key_NVIC.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
	Key_NVIC.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0
	Key_NVIC.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&Key_NVIC);  	  													//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	Key_NVIC.NVIC_IRQChannel = EXTI2_IRQn;							//使能按键所在的外部中断通道
	Key_NVIC.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
	Key_NVIC.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
	Key_NVIC.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&Key_NVIC); 

	Key_NVIC.NVIC_IRQChannel = EXTI3_IRQn;							//使能按键所在的外部中断通道
	Key_NVIC.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
	Key_NVIC.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
	Key_NVIC.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&Key_NVIC); 
	
	Key_NVIC.NVIC_IRQChannel = EXTI4_IRQn;							//使能按键所在的外部中断通道
	Key_NVIC.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
	Key_NVIC.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
	Key_NVIC.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&Key_NVIC); 
}

void Bsp_Key_Exti_Init(void)
{
	EXTI_InitTypeDef key_Exti;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	Bsp_Key_Gpio_Init();
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	//PA0配置外部中断
	key_Exti.EXTI_Line = EXTI_Line0;
	key_Exti.EXTI_Mode = EXTI_Mode_Interrupt;
	key_Exti.EXTI_Trigger = EXTI_Trigger_Rising;
	key_Exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&key_Exti);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);	//PE2配置外部中断
	key_Exti.EXTI_Line = EXTI_Line2;
	key_Exti.EXTI_Mode = EXTI_Mode_Interrupt;
	key_Exti.EXTI_Trigger = EXTI_Trigger_Falling;
	key_Exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&key_Exti);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);	//PE3配置外部中断
	key_Exti.EXTI_Line = EXTI_Line3;
	EXTI_Init(&key_Exti);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);	//PE4配置外部中断
	key_Exti.EXTI_Line = EXTI_Line4;
	EXTI_Init(&key_Exti);
	
	Bsp_Key_NVIC_Config();
}



