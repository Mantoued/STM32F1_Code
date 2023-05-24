#ifndef __BSP_LCD_H__
#define __BSP_LCD_H__

#include "common.h"

/* TFT地址结构体 */
typedef struct
{
	uint16_t TFT_CMD;
	uint16_t TFT_DATA;
} TFT_TypeDef;

/* 使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A10作为数据命令区分线 */ 
/* 注意设置时STM32内部会右移一位对其! 111110=0X3E */			    
#define TFT_BASE        ((uint32_t)(0x6C000000 | 0x000007FE))
#define TFT             ((TFT_TypeDef *) TFT_BASE)

void Bsp_Lcd_Write_Data (uint16_t dat);
void Bsp_Lcd_Write_Cmd (uint16_t cmd);
uint16_t Bsp_Lcd_Read_Data (void);
void Bsp_Lcd_Init (void);

#endif
