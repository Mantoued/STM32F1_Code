#include "App_Exti_Key.h"
#include "App_Gpio.h"
#include "App_Tim.h"

EXTI_KEY_STRUCT Exti_Key_Up;
EXTI_KEY_STRUCT Exti_Key_Left;
EXTI_KEY_STRUCT Exti_Key_Down;
EXTI_KEY_STRUCT Exti_Key_Right;

static void _App_Exti_Key_Null(void)
{
	;
}

void App_Exti_Struct_Init(EXTI_KEY_STRUCT *_key_Data, uint8_t _valid)
{
	memset(_key_Data, 0, sizeof(EXTI_KEY_STRUCT));
	_key_Data->valid = _valid;
	_key_Data->Key_Short_Func = _App_Exti_Key_Null;
}

void App_Exti_Key_Data_Init(void)
{
	App_Exti_Struct_Init(&Exti_Key_Up, 1);
	App_Exti_Struct_Init(&Exti_Key_Left, 0);
	App_Exti_Struct_Init(&Exti_Key_Down, 0);
	App_Exti_Struct_Init(&Exti_Key_Right, 0);
}

void App_Exti_Key_Handle(uint8_t _port, EXTI_KEY_STRUCT *_key)
{
	if (1 == _key->press_Short)
	{
		if (_key->valid != _port)
		{
			_key->Key_Short_Func();
			_key->press_Short = 0;
			_key->occur = 0;
		}
		return;
	}
	if (0 == _key->occur) {_key->timer = 0; _key->delay = 0; return;}
	
	if (_key->timer == 0)
	{
		_key->delay = App_Tim_Get_MS_Inc();
		_key->delay += 20;
		_key->timer = 1;
	}
	if (_key->delay != App_Tim_Get_MS_Inc()) return;
	if (_key->valid == _port)
		_key->press_Short = 1;
	
	_key->occur = 0;
	_key->timer = 0;
	_key->delay = 0;
}

static void _App_Exti_Key_K0_Up_Short(void)
{
	uint8_t status;
	status = SysTick->VAL;
	App_Gpio_Led_Ctrl(LED_CTRL_STATUS, status, 0);			//随机点亮
}

static void _App_Exti_Key_K1_Left_Short(void)
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

static void _App_Exti_Key_K2_Down_Short(void)
{
	if (0xFF != App_Gpio_Get_Led_Status())
		App_Gpio_Led_Ctrl(LED_CTRL_STATUS, 0xFF, 0);	//全灭
	else
		App_Gpio_Led_Ctrl(LED_CTRL_STATUS, 0, 0);			//全亮
}

static void _App_Exti_Key_K3_Right_Short(void)
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

void App_Exti_Key_Set_Func(void)
{
	Exti_Key_Up.Key_Short_Func = _App_Exti_Key_K0_Up_Short;
	Exti_Key_Left.Key_Short_Func = _App_Exti_Key_K1_Left_Short;
	Exti_Key_Down.Key_Short_Func = _App_Exti_Key_K2_Down_Short;
	Exti_Key_Right.Key_Short_Func = _App_Exti_Key_K3_Right_Short;
}

void App_Exit_Key_Running(void)
{
	App_Exti_Key_Handle(KEY_K0_UP, &Exti_Key_Up);
	App_Exti_Key_Handle(KEY_K1_LEFT, &Exti_Key_Left);
	App_Exti_Key_Handle(KEY_K2_DOWN, &Exti_Key_Down);
	App_Exti_Key_Handle(KEY_K3_RIGHT, &Exti_Key_Right);
}

void EXTI0_IRQHandler(void)
{
	if (1 == KEY_K0_UP)
		Exti_Key_Up.occur = 1;
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}

void EXTI2_IRQHandler(void)
{
	if (0 == KEY_K1_LEFT)
		Exti_Key_Left.occur = 1;
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除EXTI2线路挂起位
}

void EXTI3_IRQHandler(void)
{
	if (0 == KEY_K2_DOWN)
		Exti_Key_Down.occur = 1;
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除EXTI3线路挂起位
}

void EXTI4_IRQHandler(void)
{
	if (0 == KEY_K3_RIGHT)
		Exti_Key_Right.occur = 1;
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除EXTI4线路挂起位
}



