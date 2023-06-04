#include "Mid_Usart.h"

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (unsigned char) ch);
	while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	return (ch);
}



