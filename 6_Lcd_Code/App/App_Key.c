#include "App_Key.h"
#include "App_Gpio.h"

static KEY_DATA_STRUCT Key_Up;
static KEY_DATA_STRUCT Key_Left;
static KEY_DATA_STRUCT Key_Down;
static KEY_DATA_STRUCT Key_Right;

static void _App_Key_Null(void)
{
	;
}

static void _App_Key_Data_Struct_Init(KEY_DATA_STRUCT * _key_Data, uint8_t _valid)
{
	memset(_key_Data, 0, sizeof(KEY_DATA_STRUCT));
	_key_Data->Key_Long_Func = _App_Key_Null;
	_key_Data->Key_Short_Func = _App_Key_Null;
	_key_Data->Key_Push_Func = _App_Key_Null;
	_key_Data->Key_Release_Func = _App_Key_Null;
	
	_key_Data->valid = _valid;
}

void App_Key_Data_Init(void)
{
	_App_Key_Data_Struct_Init(&Key_Up, 1);
	_App_Key_Data_Struct_Init(&Key_Left, 0);
	_App_Key_Data_Struct_Init(&Key_Down, 0);
	_App_Key_Data_Struct_Init(&Key_Right, 0);
}
/***************************************************************/
static void _App_Key_K0_Up_Long(void)
{
	;
}
static void _App_Key_K0_Up_Short(void)
{
	uint8_t status;
	status = SysTick->VAL;
	App_Gpio_Led_Ctrl(LED_CTRL_STATUS, status, 0);			//随机点亮
}

static void _App_Key_K1_Left_Long(void)
{
	;
}
static void _App_Key_K1_Left_Short(void)
{
	uint8_t i;
	uint8_t status;
	status = App_Gpio_Get_Led_Status();
	for (i = LED_MAX_NUM; i > 0; i--)
	{
		if (0 == (status & (1 << (i - 1))))
			break;
	}
	App_Gpio_Led_Ctrl(LED_CTRL_BIT, LED_OFF_STA, i - 1);	
}

static void _App_Key_K2_Down_Long(void)
{
	;
}
static void _App_Key_K2_Down_Short(void)
{
	if (0xFF != App_Gpio_Get_Led_Status())
		App_Gpio_Led_Ctrl(LED_CTRL_STATUS, 0xFF, 0);	//全灭
	else
		App_Gpio_Led_Ctrl(LED_CTRL_STATUS, 0, 0);			//全亮
}

static void _App_Key_K3_Right_Long(void)
{
	;
}
static void _App_Key_K3_Right_Short(void)
{
	int8_t i;
	uint8_t status;
	status = App_Gpio_Get_Led_Status();
	for (i = 0; i < LED_MAX_NUM; i++)
	{
		if (0 != (status & (1 << i)))
			break;
	}
	App_Gpio_Led_Ctrl(LED_CTRL_BIT, LED_ON_STA, i);	
}
/***************************************************************/
void App_Key_Set_Func(void)
{
	Key_Up.Key_Long_Func = _App_Key_K0_Up_Long;
	Key_Up.Key_Short_Func = _App_Key_K0_Up_Short;
	
	Key_Left.Key_Long_Func = _App_Key_K1_Left_Long;
	Key_Left.Key_Short_Func = _App_Key_K1_Left_Short;
	
	Key_Down.Key_Long_Func = _App_Key_K2_Down_Long;
	Key_Down.Key_Short_Func = _App_Key_K2_Down_Short;
	
	Key_Right.Key_Long_Func = _App_Key_K3_Right_Long;
	Key_Right.Key_Short_Func = _App_Key_K3_Right_Short;
}

void App_Key_Running(void)
{
	Mid_Key_Handling(KEY_K0_UP, &Key_Up);
	Mid_Key_Handling(KEY_K1_LEFT, &Key_Left);
	Mid_Key_Handling(KEY_K2_DOWN, &Key_Down);
	Mid_Key_Handling(KEY_K3_RIGHT, &Key_Right);
}


