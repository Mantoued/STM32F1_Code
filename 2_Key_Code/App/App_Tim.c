#include "App_Tim.h"

#define APP_TIMING_OCCUR(x) 			(((Tim_Service_Data.times % x) == 0) && ((Tim_Service_Data.times / x) != 0))

static APP_TIM_SERVICE Tim_Service_Data;

#define APP_TIM_20MS_ONCE 						(20)
#define APP_TIM_40MS_ONCE 						(40)
#define APP_TIM_100MS_ONCE 						(100)
#define APP_TIM_200MS_ONCE 						(200)
#define APP_TIM_500MS_ONCE 						(500)
#define APP_TIM_1000MS_ONCE 					(1000)

void App_Tim_Service_Running(void)
{
	if (0 == Tim_Service_Data.occur) return;
	Tim_Service_Data.occur = 0;
	
	Tim_Service_Data.times++;
	
	if (APP_TIMING_OCCUR(APP_TIM_20MS_ONCE))
		Tim_Service_Data.Flag.mBit.once_20ms = 1;
	
	if (APP_TIMING_OCCUR(APP_TIM_40MS_ONCE))
		Tim_Service_Data.Flag.mBit.once_40ms = 1;
	
	if (APP_TIMING_OCCUR(APP_TIM_100MS_ONCE))
		Tim_Service_Data.Flag.mBit.once_100ms = 1;
	
	if (APP_TIMING_OCCUR(APP_TIM_200MS_ONCE))
		Tim_Service_Data.Flag.mBit.once_200ms = 1;
	
	if (APP_TIMING_OCCUR(APP_TIM_500MS_ONCE))
		Tim_Service_Data.Flag.mBit.once_500ms = 1;
	
	if (APP_TIMING_OCCUR(APP_TIM_1000MS_ONCE))
		Tim_Service_Data.Flag.mBit.once_1000ms = 1;
	
	if (Tim_Service_Data.times > 1000)
		Tim_Service_Data.times = 1;
}

uint8_t App_Tim_Get_Flag(TIM_FLAGS_QUERY_STATUS _status)
{
	uint8_t re = 0;
	re = (Tim_Service_Data.Flag.temp & (1 << _status));
	if (re != 0)
		Tim_Service_Data.Flag.temp &= ~(1 << _status);
	return !!(re);
}

//systick定时器中断函数,1ms/次
void SysTick_Handler(void)
{
	Tim_Service_Data.occur = 1;
}


