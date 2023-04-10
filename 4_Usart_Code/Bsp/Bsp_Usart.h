#ifndef __BSP_USART_H__
#define __BSP_USART_H__

#include "common.h"

void Bsp_Usart_Config(void);
void Bsp_Usart_Dma_Config(uint32_t _mem_Addr, uint32_t _len);

#endif
