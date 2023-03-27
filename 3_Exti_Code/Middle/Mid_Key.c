#include "Mid_Key.h"



void Mid_Key_Handle(uint8_t _port, KEY_DATA_STRUCT * _key_Data)
{
	if (_port == _key_Data->valid)
	{
		_key_Data->press_Short = 1;
		_key_Data->cnt++;
		if ((_key_Data->cnt > 25) && (0 == _key_Data->press_Long))
		{
			_key_Data->press_Short = 0;
			_key_Data->press_Long = 1;
			
			_key_Data->Key_Long_Func();
		}
		
		_key_Data->Key_Push_Func();
	}
	else
	{
		if (1 == _key_Data->press_Short)
		{
			_key_Data->Key_Short_Func();
		}
		
		_key_Data->Key_Release_Func();
		
		_key_Data->cnt = 0;
		_key_Data->press_Short = 0;
		_key_Data->press_Long = 0;
	}
}


