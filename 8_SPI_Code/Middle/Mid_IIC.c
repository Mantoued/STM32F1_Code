#include "Mid_IIC.h"

void Mid_IIC_Page_Write(uint8_t *_buf, uint8_t _addr, uint8_t _devide_addr, uint8_t _num)
{
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2, _devide_addr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2, _addr);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	while(_num--)
	{
		I2C_SendData(I2C2, *_buf);
		_buf ++;
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
	
	I2C_GenerateSTOP(I2C2, ENABLE);
}

void Mid_IIC_Buffer_Read(uint8_t * _buf, uint8_t _addr, uint8_t _devide_addr, uint16_t _num)
{
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2, _devide_addr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_Cmd(I2C2, ENABLE);
	I2C_SendData(I2C2, _addr);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2, _devide_addr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	
	while(_num)
	{
		if (_num == 1)
		{
			I2C_AcknowledgeConfig(I2C2, DISABLE);
			I2C_GenerateSTOP(I2C2, ENABLE);
		}
		
		if (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))
		{
			*_buf = I2C_ReceiveData(I2C2);
			_buf++;
			_num--;
		}
	}
	I2C_AcknowledgeConfig(I2C2, ENABLE);
}

void Mid_IIC_Wait_Standby_Status(uint8_t _devide_addr)
{
	volatile uint16_t sr1_tmp = 0;
	
	do {
		I2C_GenerateSTART(I2C2, ENABLE);
		sr1_tmp = I2C_ReadRegister(I2C2, I2C_Register_SR1);
		I2C_Send7bitAddress(I2C2, _devide_addr, I2C_Direction_Transmitter);
		
	}while(!(I2C_ReadRegister(I2C2, I2C_Register_SR1) & 0x0002));
	
	I2C_ClearFlag(I2C2, I2C_FLAG_AF);
	I2C_GenerateSTOP(I2C2, ENABLE);
}

void Mid_IIC_Buffer_Write(uint8_t *_buf, uint8_t _addr, uint8_t _devide_addr, uint16_t _num, const uint8_t _page_size)
{
	uint8_t page_num = 0, single_num = 0, addr = 0, count = 0;
	
	addr = _addr % _page_size;
	count = _page_size - addr;
	page_num = _num / _page_size;
	single_num = _num % _page_size;
	
	if (addr == 0)
	{
		if (page_num == 0)
		{
			Mid_IIC_Page_Write(_buf, _addr, _devide_addr, single_num);
			Mid_IIC_Wait_Standby_Status(_devide_addr);
		}
		else
		{
			while(page_num--)
			{
				Mid_IIC_Page_Write(_buf, _addr, _devide_addr, _page_size);
				Mid_IIC_Wait_Standby_Status(_devide_addr);
				_addr += _page_size;
				_buf += _page_size;
			}
			
			if (single_num != 0)
			{
				Mid_IIC_Page_Write(_buf, _addr, _devide_addr, single_num);
				Mid_IIC_Wait_Standby_Status(_devide_addr);
			}
		}
	}
	else
	{
		if (page_num == 0)
		{
			Mid_IIC_Page_Write(_buf, _addr, _devide_addr, single_num);
			Mid_IIC_Wait_Standby_Status(_devide_addr);
		}
		else
		{
			page_num = _num / _page_size;
			single_num = _num % _page_size;
			
			if (count != 0)
			{
				Mid_IIC_Page_Write(_buf, _addr, _devide_addr, count);
				Mid_IIC_Wait_Standby_Status(_devide_addr);
				_addr += count;
				_buf += count;
			}
			
			while(page_num--)
			{
				Mid_IIC_Page_Write(_buf, _addr, _devide_addr, _page_size);
				Mid_IIC_Wait_Standby_Status(_devide_addr);
				_addr += _page_size;
				_buf += _page_size;
			}
			if (single_num != 0)
			{
				Mid_IIC_Page_Write(_buf, _addr, _devide_addr, single_num);
				Mid_IIC_Wait_Standby_Status(_devide_addr);
			}
		}
	}
}




