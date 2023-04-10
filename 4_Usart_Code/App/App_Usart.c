#include "App_Usart.h"

typedef struct {
	uint8_t cnt;
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
//	uint8_t i;
	if (Usart_Data.cnt == 0) return;
	
	Bsp_Usart_Dma_Config((uint32_t)Usart_Data.buf, Usart_Data.cnt);
	
//	for (i = 0; i < Usart_Data.cnt; i++)
//	{
//		USART_SendData(USART1, Usart_Data.buf[i]);
//		while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
//	}
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
		DMA_ClearFlag(DMA1_FLAG_TC4 |DMA1_FLAG_GL4 |DMA1_FLAG_HT4);
}
