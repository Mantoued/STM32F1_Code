#ifndef __MID_LCD_H__
#define __MID_LCD_H__

#include "Bsp_Lcd.h"

void Mid_Lcd_Set_Disp_HV (uint8_t _HV);
void Mid_Lcd_Open_Window (u16 x, u16 y, u16 weight, u16 height);
void Mid_Lcd_Set_Point (uint16_t _usX1, uint16_t _usY1, uint16_t _usColor);
uint16_t Mid_Lcd_Get_Point (uint16_t _usX1, uint16_t _usY1);
void Mid_Lcd_Fill_Rect (uint16_t _usX1, uint16_t _usY1, uint16_t _usWeight, uint16_t _usHeight, uint16_t _usColor);
void Mid_Lcd_Draw_H_Line (uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usColor);
void Mid_Lcd_Draw_V_Line (uint16_t _usX1 , uint16_t _usY1 , uint16_t _usY2 , uint16_t _usColor);

#endif
