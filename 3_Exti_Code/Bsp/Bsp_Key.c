#include "Bsp_Key.h"

void Bsp_Key_Gpio_Init(void)
{
	GPIO_InitTypeDef key_Gpio;
	RCC_APB2PeriphClockCmd(KEY_UP_CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(KEY_K1_K2_K3_CLOCK, ENABLE);
	
	GPIO_StructInit(&key_Gpio);
	key_Gpio.GPIO_Pin = KEY_UP_PIN;
	key_Gpio.GPIO_Mode = GPIO_Mode_IPD;					//��������
	key_Gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(KEY_UP_PORT, &key_Gpio);
	
	key_Gpio.GPIO_Pin = KEY_K1_K2_K3_PIN;
	key_Gpio.GPIO_Mode = GPIO_Mode_IPU;					//��������
	GPIO_Init(KEY_K1_K2_K3_PORT, &key_Gpio);
}

void Bsp_Key_NVIC_Config(void)
{
	NVIC_InitTypeDef Key_NVIC;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			// �����ж����ȼ�����2
	
	Key_NVIC.NVIC_IRQChannel = EXTI0_IRQn;							//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	Key_NVIC.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
	Key_NVIC.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0
	Key_NVIC.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&Key_NVIC);  	  													//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	Key_NVIC.NVIC_IRQChannel = EXTI2_IRQn;							//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	Key_NVIC.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
	Key_NVIC.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
	Key_NVIC.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&Key_NVIC); 

	Key_NVIC.NVIC_IRQChannel = EXTI3_IRQn;							//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	Key_NVIC.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
	Key_NVIC.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
	Key_NVIC.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&Key_NVIC); 
	
	Key_NVIC.NVIC_IRQChannel = EXTI4_IRQn;							//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	Key_NVIC.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
	Key_NVIC.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
	Key_NVIC.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&Key_NVIC); 
}

void Bsp_Key_Exti_Init(void)
{
	EXTI_InitTypeDef key_Exti;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	Bsp_Key_Gpio_Init();
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	//PA0�����ⲿ�ж�
	key_Exti.EXTI_Line = EXTI_Line0;
	key_Exti.EXTI_Mode = EXTI_Mode_Interrupt;
	key_Exti.EXTI_Trigger = EXTI_Trigger_Rising;
	key_Exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&key_Exti);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);	//PE2�����ⲿ�ж�
	key_Exti.EXTI_Line = EXTI_Line2;
	key_Exti.EXTI_Mode = EXTI_Mode_Interrupt;
	key_Exti.EXTI_Trigger = EXTI_Trigger_Falling;
	key_Exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&key_Exti);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);	//PE3�����ⲿ�ж�
	key_Exti.EXTI_Line = EXTI_Line3;
	EXTI_Init(&key_Exti);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);	//PE4�����ⲿ�ж�
	key_Exti.EXTI_Line = EXTI_Line4;
	EXTI_Init(&key_Exti);
	
	Bsp_Key_NVIC_Config();
}



