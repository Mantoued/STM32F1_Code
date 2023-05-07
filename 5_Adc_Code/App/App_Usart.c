#include "App_Usart.h"

typedef struct {
	uint8_t cnt;
	uint8_t flag;
	char buf[128];
}USART_RECV_DATA;

USART_RECV_DATA Usart_Data;

void App_Usart_Init(void)
{
	memset(&Usart_Data, 0, sizeof(USART_RECV_DATA));
	printf("Hello World!");
}

void App_Usart_Recv_And_Send(void)
{
	if (Usart_Data.cnt == 0) return;
	
	Bsp_Usart_Dma_Config((uint32_t)Usart_Data.buf, Usart_Data.cnt);
	Usart_Data.cnt = 0;
}

void App_Usart_Send_Adc_Value(void)
{
	uint16_t value = 0;
	value = Mid_Adc_Get_Adc0();
	while (Usart_Data.flag == 1);
	Usart_Data.flag = 1;
	sprintf(Usart_Data.buf, "  Adc0: %d", value);
	Usart_Data.cnt = strlen(Usart_Data.buf);
	
	Bsp_Usart_Dma_Config((uint32_t)Usart_Data.buf, Usart_Data.cnt);
	Usart_Data.cnt = 0;
	
	value = Mid_Adc_Get_Adc1();
	while (Usart_Data.flag == 1);
	Usart_Data.flag = 1;
	sprintf(Usart_Data.buf, "  Adc1: %d", value);
	Usart_Data.cnt = strlen(Usart_Data.buf);
	
	Bsp_Usart_Dma_Config((uint32_t)Usart_Data.buf, Usart_Data.cnt);
	Usart_Data.cnt = 0;
	
	value = Mid_Adc_Get_Adc2();
	while (Usart_Data.flag == 1);
	Usart_Data.flag = 1;
	sprintf(Usart_Data.buf, "  Adc2: %d\n", value);
	Usart_Data.cnt = strlen(Usart_Data.buf);
	
	Bsp_Usart_Dma_Config((uint32_t)Usart_Data.buf, Usart_Data.cnt);
	Usart_Data.cnt = 0;
}

void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
		Usart_Data.buf[Usart_Data.cnt++] = USART1->DR;
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

void DMA1_Channel4_IRQHandler(void)
{
	//判断是否为 DMA 发送完成中断
	if(DMA_GetFlagStatus(DMA1_FLAG_TC4)==SET)
	{
		Usart_Data.flag = 0;
		DMA_ClearFlag(DMA1_FLAG_TC4 |DMA1_FLAG_GL4 |DMA1_FLAG_HT4);
	}
}
