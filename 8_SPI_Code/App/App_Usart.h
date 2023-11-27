#ifndef __APP_USART_H__
#define __APP_USART_H__

#include "Mid_Usart.h"
#include "Mid_Adc.h"

void App_Usart_Init(void);
void App_Usart_Recv_And_Send(void);
void App_Usart_Send_Adc_Value(void);

#endif
