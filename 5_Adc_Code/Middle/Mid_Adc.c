#include "Mid_Adc.h"

uint16_t Mid_Adc_Get_Adc0(void)
{
	return Bsp_Adc_Get_Value(0);
}

uint16_t Mid_Adc_Get_Adc1(void)
{
	return Bsp_Adc_Get_Value(1);
}

uint16_t Mid_Adc_Get_Adc2(void)
{
	return Bsp_Adc_Get_Value(2);
}
