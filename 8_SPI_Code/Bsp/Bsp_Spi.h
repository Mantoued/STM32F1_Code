#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__

#include "common.h"

#define SPI2_FLASH_CS(x) 	((x == 0) ? GPIO_ResetBits(GPIOG, GPIO_Pin_13) : GPIO_SetBits(GPIOG, GPIO_Pin_13))

void Bsp_SPI_Config(void);

#endif
