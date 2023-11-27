#include "Bsp_Adc.h"

#define BSP_ADC_NUM				(3)

static uint16_t Adc_Value[BSP_ADC_NUM];

static void _Bsp_Adc_Gpio_Init(void)
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &gpio);
}

#define ADC1_DR_Address 			((u32)0x40012400+0x4c)

static void _Bsp_Adc_Dma_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;/*ADC 地址*/
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Adc_Value;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //外设为数据源
	DMA_InitStructure.DMA_BufferSize = BSP_ADC_NUM;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;/*内存地址固定*/
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //半字
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //循环传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);
}

void Bsp_Adc_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	_Bsp_Adc_Gpio_Init();
	_Bsp_Adc_Dma_Config();

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	 			/*扫描模式用于多通道采集*/
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = BSP_ADC_NUM;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 3, ADC_SampleTime_55Cycles5);
	
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

uint16_t Bsp_Adc_Get_Value(uint8_t _chl)
{
	if (_chl >= 3) _chl = 0;
	return Adc_Value[_chl];
}

