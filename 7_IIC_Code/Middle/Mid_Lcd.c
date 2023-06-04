#include "Mid_Lcd.h"
#include "Mid_Ascii.h"

void Mid_Lcd_Set_Disp_HV (uint8_t _HV)
{
	if (_HV == 1)
	{
		Bsp_Lcd_Write_Cmd(0x36); 	 //Set_address_mode
		Bsp_Lcd_Write_Data(0x48);   	//48
	}
	else
	{
		Bsp_Lcd_Write_Cmd(0x36); 	 //Set_address_mode
		Bsp_Lcd_Write_Data(0x88);   	//48
	}
}

void Mid_Lcd_Open_Window (u16 x, u16 y, u16 weight, u16 height)
{
	Bsp_Lcd_Write_Cmd(0x2a);						//设置 X 坐标
	Bsp_Lcd_Write_Data(x >> 8);					//先高八位后低八位
	Bsp_Lcd_Write_Data(x & 0xff);				//设置起始点和结束点
	Bsp_Lcd_Write_Data((x + weight - 1) >> 8);	
	Bsp_Lcd_Write_Data((x + weight - 1) & 0xff);
	
	Bsp_Lcd_Write_Cmd(0x2b);						//设置 Y 坐标
	Bsp_Lcd_Write_Data(y >> 8);					//起始点
	Bsp_Lcd_Write_Data(y & 0xff);
	Bsp_Lcd_Write_Data((y + height - 1) >> 8);	//结束点
	Bsp_Lcd_Write_Data((y + height - 1) & 0xff);
	
	Bsp_Lcd_Write_Cmd(0x2c);	
}

//画点
void Mid_Lcd_Set_Point (uint16_t _usX1, uint16_t _usY1, uint16_t _usColor)
{
	Mid_Lcd_Open_Window(_usX1, _usY1, 1, 1);
	Bsp_Lcd_Write_Data(_usColor);
}

//获取点
uint16_t Mid_Lcd_Get_Point (uint16_t _usX1, uint16_t _usY1)
{
	uint16_t temp,r,g,b;
	Mid_Lcd_Open_Window(_usX1, _usY1, 1, 1);
	Bsp_Lcd_Write_Cmd(0x2e);
	r = Bsp_Lcd_Read_Data();
	r = Bsp_Lcd_Read_Data();
	g = Bsp_Lcd_Read_Data();
	b = Bsp_Lcd_Read_Data();
	temp = ((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11);
	return temp;
}

//填充矩形
void Mid_Lcd_Fill_Rect (uint16_t _usX1, uint16_t _usY1, uint16_t _usWeight, uint16_t _usHeight, uint16_t _usColor)
{
	uint32_t n;
	Mid_Lcd_Open_Window(_usX1, _usY1, _usWeight, _usHeight);
	for (n = 0; n < _usWeight * _usHeight; n++)
	{
		TFT->TFT_DATA = _usColor;
	}
}

//画平行线
void Mid_Lcd_Draw_H_Line (uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usColor)
{
	uint16_t i;
	Mid_Lcd_Open_Window(_usX1, _usY1, (_usX2- _usX1 + 1), 1);
	
	for (i = 0; i <_usX2-_usX1+1; i++)
	{
		TFT->TFT_DATA = _usColor;
	}
}

//画垂直线
void Mid_Lcd_Draw_V_Line (uint16_t _usX1 , uint16_t _usY1 , uint16_t _usY2 , uint16_t _usColor)
{
	uint16_t i;
	Mid_Lcd_Open_Window(_usX1, _usY1, 1, (_usY2- _usY1 + 1));
	
	for (i = 0; i < (_usY2- _usY1 + 1); i++)
	{
		TFT->TFT_DATA = _usColor;
	}
}

//显示16x16字符
void Mid_Lcd_Show_16x16_Ascii(uint16_t _x, uint16_t _y, const char _buf[], uint16_t _len, uint16_t _color, uint16_t _bkColor)
{
	uint16_t i;
	uint8_t row, p;
	uint8_t c;
	Mid_Lcd_Open_Window(_x, _y, 8, 16);
	for (i = 0; i < _len; i++)
	{
		Mid_Lcd_Open_Window(_x + (i * 8), _y, 8, 16);
		for (row = 0; row < 16; row++)
		{
			c = Mid_Ascii[_buf[i] - MID_ASCII_START_INDEX][row];
			for (p = 0; p < 8; p++)
			{
				TFT->TFT_DATA = ((c & 0x01) == 0) ? _bkColor : _color;
				c >>= 1;
			}
		}
	}
}

