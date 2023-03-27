#ifndef __MID_KEY_H__
#define __MID_KEY_H__

#include "Bsp_Key.h"

typedef void(*VOID_FUNC_VOID)(void);

typedef struct {
	uint8_t cnt;
	uint8_t valid;
	uint8_t press_Long;
	uint8_t press_Short;
	
	VOID_FUNC_VOID Key_Long_Func;				//长按功能
	VOID_FUNC_VOID Key_Short_Func;			//短按功能
	VOID_FUNC_VOID Key_Push_Func;				//按下
	VOID_FUNC_VOID Key_Release_Func;		//释放
}KEY_DATA_STRUCT;

void Mid_Key_Handle(uint8_t _port, KEY_DATA_STRUCT * _key_Data);

#endif
