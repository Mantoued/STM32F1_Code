#ifndef __MID_SPI_H__
#define __MID_SPI_H__

#include "Bsp_Spi.h"

/* FLASH ID */
#define EN25Q64 	0Xc816

/* ָ��� */
#define EN25X_Write_Status_Reg    0x01   //д״̬�Ĵ���
#define EN25X_Page_Program				0x02   //ҳ�༭
#define EN25X_Read_Data          	0x03   //������
#define EN25X_Write_Disable				0x04   //дʧ��
#define EN25X_Read_Status_Reg			0x05   //��ȡ״̬�Ĵ���
#define EN25X_Write_Enable				0x06   //дʹ��
#define EN25X_Sector_Erase				0x20   //������
#define EN25X_Chip_Erase					0xC7   //����Ƭ

uint8_t Mid_Spi_Send_And_Recv(uint8_t _data);
uint16_t Mid_Spi_Flash_Read_Device_ID(void);
void Mid_Spi_Flash_Sector_Erase(uint32_t _addr);
void Mid_Spi_Flash_Chip_Erase(void);
void Mid_Spi_Flash_Read_Data(uint8_t * _buf, uint32_t _addr, uint32_t _num);
void Mid_Spi_Flash_Write_Page(uint8_t *_buf, uint32_t _addr, uint16_t _num);
void Mid_Flash_Write_Data(uint8_t *_buf, uint32_t _addr, uint16_t _num);

#endif
