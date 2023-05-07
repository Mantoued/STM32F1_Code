#ifndef __APP_TIM_H__
#define __APP_TIM_H__

#include "Mid_Tim.h"

typedef struct {
	uint8_t occur;
	uint32_t times;
	union {
		uint8_t temp;
		struct {
			uint8_t once_20ms 		:	1;
			uint8_t once_40ms 		:	1;
			uint8_t once_100ms 		:	1;
			uint8_t once_200ms 		:	1;
			uint8_t once_500ms 		:	1;
			uint8_t once_1000ms 	:	1;
		}mBit;
	}Flag;
}APP_TIM_SERVICE;

typedef enum {
	TIM_20MS_SET = 0,
	TIM_40MS_SET,
	TIM_100MS_SET,
	TIM_200MS_SET,
	TIM_500MS_SET,
	TIM_1000MS_SET,
}TIM_FLAGS_QUERY_STATUS;

void App_Tim_Service_Running(void);
uint8_t App_Tim_Get_Flag(TIM_FLAGS_QUERY_STATUS _status);

#endif
