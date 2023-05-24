#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "common.h"

void Bsp_Adc_Config(void);
uint16_t Bsp_Adc_Get_Value(uint8_t _chl);

#endif
