#include "Bsp_IIC.h"

static void _Bsp_IIC_Gpio_Init(void)
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &gpio);
}

void Bsp_IIC_Config(void)
{
	I2C_InitTypeDef I2C_InitStructure;
	
	_Bsp_IIC_Gpio_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0X0A;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;
	
	I2C_Init(I2C2, &I2C_InitStructure);
	I2C_Cmd(I2C2, ENABLE);
}

