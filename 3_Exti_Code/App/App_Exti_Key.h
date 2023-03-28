#ifndef __APP_EXTI_KEY_H__
#define __APP_EXTI_KEY_H__

#include "Mid_Key.h"

typedef struct {
	uint8_t valid;
	uint8_t press_Short;
	uint8_t occur;
	uint8_t timer;
	uint32_t delay;
	VOID_FUNC_VOID Key_Short_Func;
}EXTI_KEY_STRUCT;
void App_Exti_Key_Data_Init(void);
void App_Exti_Key_Set_Func(void);
void App_Exit_Key_Running(void);

#endif
