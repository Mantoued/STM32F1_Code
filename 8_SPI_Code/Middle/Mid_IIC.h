#ifndef __MID_IIC_H__
#define __MID_IIC_H__

#include "Bsp_IIC.h"

void Mid_IIC_Buffer_Read(uint8_t * _buf, uint8_t _addr, uint8_t _devide_addr, uint16_t _num);
void Mid_IIC_Buffer_Write(uint8_t *_buf, uint8_t _addr, uint8_t _devide_addr, uint16_t _num, const uint8_t _page_size);

#endif
