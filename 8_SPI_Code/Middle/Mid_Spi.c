#include "Mid_Spi.h"

uint8_t Mid_Spi_Send_And_Recv(uint8_t _data)
{
	//发送为空
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2, _data);
	
	//等待接收
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	return (SPI_I2S_ReceiveData(SPI2));
}

//读取设备ID
uint16_t Mid_Spi_Flash_Read_Device_ID(void)
{
	uint16_t re = 0;
	SPI2_FLASH_CS(0);
	
	Mid_Spi_Send_And_Recv(0x90);
	Mid_Spi_Send_And_Recv(0x00);
	Mid_Spi_Send_And_Recv(0x00);
	Mid_Spi_Send_And_Recv(0x00);
	
	re = Mid_Spi_Send_And_Recv(0xFF);
	re <<= 8;
	re |= Mid_Spi_Send_And_Recv(0xFF);
	SPI2_FLASH_CS(1);
	return re;
}

void Mid_Spi_Flash_Write_Enable(void)
{
	SPI2_FLASH_CS(0);
	Mid_Spi_Send_And_Recv(EN25X_Write_Enable);
	SPI2_FLASH_CS(1);
}

static int8_t _Mid_Spi_Flash_Check_Busy(void)
{
	int8_t status = 0;
	uint32_t timeout = 0;
	
	do {
		if ((timeout++) > 0xEFFFFFFF)
			return -1;
		
		SPI2_FLASH_CS(0);
		Mid_Spi_Send_And_Recv(EN25X_Read_Status_Reg);
		status = Mid_Spi_Send_And_Recv(0xFF);
		SPI2_FLASH_CS(1);
	}while((status & 0x01) == 0x01);	//等待BUSY 位清空
	
	return 0;
}

void Mid_Spi_Flash_Read_Data(uint8_t * _buf, uint32_t _addr, uint32_t _num)
{
	_Mid_Spi_Flash_Check_Busy();
	SPI2_FLASH_CS(0);
	//发送读取指令
	Mid_Spi_Send_And_Recv(EN25X_Read_Data);
	//发送地址
	Mid_Spi_Send_And_Recv(_addr >> 16);
	Mid_Spi_Send_And_Recv(_addr >> 8);
	Mid_Spi_Send_And_Recv(_addr);
	//读取数据
	while(_num --)
	{
		*_buf = Mid_Spi_Send_And_Recv(0xFF);
		_buf ++;
	}
	SPI2_FLASH_CS(1);
}

void Mid_Spi_Flash_Sector_Erase(uint32_t _addr)
{
	_Mid_Spi_Flash_Check_Busy();
	//开启写使能
	Mid_Spi_Flash_Write_Enable();
	SPI2_FLASH_CS(0);
	
	//发送擦除指令
	Mid_Spi_Send_And_Recv(EN25X_Sector_Erase);
	//发送地址
	Mid_Spi_Send_And_Recv(_addr >> 16);
	Mid_Spi_Send_And_Recv(_addr >> 8);
	Mid_Spi_Send_And_Recv(_addr);
	
	SPI2_FLASH_CS(1);
}

void Mid_Spi_Flash_Chip_Erase(void)
{
	_Mid_Spi_Flash_Check_Busy();
	//开启写使能
	Mid_Spi_Flash_Write_Enable();
	SPI2_FLASH_CS(0);
	
	//发送擦除指令
	Mid_Spi_Send_And_Recv(EN25X_Chip_Erase);
	
	SPI2_FLASH_CS(1);
}

void Mid_Spi_Flash_Write_Page(uint8_t *_buf, uint32_t _addr, uint16_t _num)
{
	uint16_t byte_Num, i;
	
	//首页剩余地址
	byte_Num = 256 - (_addr % 256);
	
	if (_num < byte_Num)
		byte_Num = _num;
	
	while(1)
	{
		_Mid_Spi_Flash_Check_Busy();
		//开启写使能
		Mid_Spi_Flash_Write_Enable();
		SPI2_FLASH_CS(0);
		//开启页编辑
		Mid_Spi_Send_And_Recv(EN25X_Page_Program);
		//发送地址
		Mid_Spi_Send_And_Recv(_addr >> 16);
		Mid_Spi_Send_And_Recv(_addr >> 8);
		Mid_Spi_Send_And_Recv(_addr);
		
		for (i = 0; i < byte_Num; i++)
		{
			Mid_Spi_Send_And_Recv(*_buf);
			_buf ++;
		}
		
		SPI2_FLASH_CS(1);
		
		if (_num == byte_Num)
			break;
		else
		{
			_addr += byte_Num;		//最新地址
			_num = _num - byte_Num;
			
			if (_num > 256)
				byte_Num = 256;
			else
				byte_Num = _num;
		}
	}
}

static uint8_t Flash_Buf[4096];
void Mid_Flash_Write_Data(uint8_t *_buf, uint32_t _addr, uint16_t _num)
{
	uint16_t sector_Addr, byte_Addr, remain_Byte, i;
	sector_Addr = _addr / 4096;				//扇区地址
	byte_Addr = _addr % 4096;					//扇区偏移地址
	remain_Byte = 4096 - byte_Addr;		//扇区剩余地址
	
	if (_num < remain_Byte)
		remain_Byte = _num;
	
	while(1)
	{
		//读取扇区数据
		Mid_Spi_Flash_Read_Data(Flash_Buf, sector_Addr * 4096, 4096);
		for (i = 0; i < remain_Byte; i++)
		{
			//出错，要写入的地方不为空
			if (Flash_Buf[byte_Addr + i] != 0xFF)
				break;
		}
		
		//扇区里有数据, 需要先擦除再写入
		if (i < remain_Byte)
		{
			Mid_Spi_Flash_Sector_Erase(sector_Addr * 4096);
			//复制数据
			for (i = 0; i < remain_Byte; i++)
				Flash_Buf[byte_Addr + i] = _buf[i];
			
			Mid_Spi_Flash_Write_Page(Flash_Buf, sector_Addr * 4096, 4096);
			
		}
		else
			Mid_Spi_Flash_Write_Page(_buf, _addr, remain_Byte);
		
		if (remain_Byte == _num)
			break;
		else
		{
			_buf += remain_Byte;
			_addr += remain_Byte;
			_num -= remain_Byte;
			
			sector_Addr++;
			byte_Addr = 0;
			
			if (_num > 4096)
				remain_Byte = 4096;
			else
				remain_Byte = _num;
		}
	}
}



