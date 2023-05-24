#include "Bsp_Lcd.h"

static void _Bsp_Lcd_Gpio_Init (void)
{
	/* ʹ��FSMC��Ӧ��Ӧ�ܽ�ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE  
	                      | RCC_APB2Periph_GPIOG, ENABLE);
	GPIOD->CRL &= 0xFF00FF00;	//PD0��1��4��5
	GPIOD->CRL |= 0x00BB00BB;	//�����������
	
	GPIOD->CRH &= 0x00000000;	//PD8��9��10��11��12��13��14��15
	GPIOD->CRH |= 0xBBBBBBBB;	//�����������
	
	GPIOG->CRL &= 0xFFFFFFF0;	//PG0
	GPIOG->CRL |= 0x0000000B;	//�����������
	
	GPIOG->CRH &= 0xFFF0FFFF;	//PG12
	GPIOG->CRH |= 0x000B0000;	//�����������
	
	GPIOE->CRL &= 0x0FFFFFFF;	//PE7
	GPIOE->CRL |= 0xB0000000;	//�����������
	
	GPIOE->CRH &= 0x00000000;	//PE8��9��10��11��12��13��14��15
	GPIOE->CRH |= 0xBBBBBBBB;	//�����������
}

static void _Bsp_Lcd_FSMC_Config (void)
{
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef p;
	
	p.FSMC_AddressSetupTime = 0x02;					//��ַ����ʱ�� //��С������ٶ�
	p.FSMC_AddressHoldTime = 0x00;					//��ַ����ʱ��
	p.FSMC_DataSetupTime = 0x05;						//���ݱ���ʱ�� //��С������ٶ�
	p.FSMC_BusTurnAroundDuration = 0x00;		//���߻ָ�ʱ��
	p.FSMC_CLKDivision = 0x00;							//ʱ�ӷ�Ƶ
	p.FSMC_DataLatency = 0x00;							//���ݱ���ʱ��
	p.FSMC_AccessMode = FSMC_AccessMode_B;	//һ��ʹ��ģʽB������LCD
	
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;						//NOR FLASH �� Bank1
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;	//���������ַ�߲�����
//FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;	
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;				//�洢������Ϊ NOR
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;		//���ݿ�� 16 λ
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;	//ʹ���첽дģʽ, ��ֹͻ��ģʽ
//FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;//Ϊewim�޸ģ�ԭ��������û��������
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;//����Ա������ֻ��ͻ��ģʽ����Ч, �ȴ��źż���Ϊ��
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;				//��ֹ�Ƕ���ͻ��ģʽ
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;//����Ա������ֻ��ͻ��ģʽ����Ч, NWAIT�ź���ʲôʱ�ڲ���
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;		//дʹ��
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;			//����Ա������ֻ��ͻ��ģʽ����Ч������NWAIT�ź�
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;		//��ֹ��չģʽ����չģʽ����ʹ�ö����Ķ���дģʽ
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;			//��ֹͻ��д����
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;						//���ö�дʱ��
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;  						//����дʱ��
	
	/* ��FSMC��ʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
	
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
	
	/* ʹ�� FSMC Bank1_SRAM Bank */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  
}

void Bsp_Lcd_Write_Data (uint16_t dat)
{
	TFT->TFT_DATA = dat;
}

void Bsp_Lcd_Write_Cmd (uint16_t cmd)
{
	TFT->TFT_CMD = cmd;
}

uint16_t Bsp_Lcd_Read_Data (void)
{
	return TFT->TFT_DATA;
}

void Bsp_Lcd_Init (void)
{
	uint16_t i;
	_Bsp_Lcd_Gpio_Init();
	_Bsp_Lcd_FSMC_Config();
	
	Bsp_Lcd_Write_Cmd(0xE9); 
	Bsp_Lcd_Write_Data(0x20); 
	
	Bsp_Lcd_Write_Cmd(0x11); //Exit Sleep 
	for(i = 500; i > 0; i--);
	
	Bsp_Lcd_Write_Cmd(0x3A);
	Bsp_Lcd_Write_Data(0x55);  //16Bit colors
	
	Bsp_Lcd_Write_Cmd(0xD1); 
	Bsp_Lcd_Write_Data(0x00); 
	Bsp_Lcd_Write_Data(0x65); //���Դ�ֵ����ˮ��
	Bsp_Lcd_Write_Data(0x1F); 
	
	Bsp_Lcd_Write_Cmd(0xD0); 
	Bsp_Lcd_Write_Data(0x07); 
	Bsp_Lcd_Write_Data(0x07); 
	Bsp_Lcd_Write_Data(0x80); 
	
	Bsp_Lcd_Write_Cmd(0x36); 	 //Set_address_mode
	Bsp_Lcd_Write_Data(0x48);   	//48
	
	Bsp_Lcd_Write_Cmd(0xC1); 
	Bsp_Lcd_Write_Data(0x10); 
	Bsp_Lcd_Write_Data(0x10); 
	Bsp_Lcd_Write_Data(0x02); 
	Bsp_Lcd_Write_Data(0x02); 
	
	Bsp_Lcd_Write_Cmd(0xC0); //Set Default Gamma 
	Bsp_Lcd_Write_Data(0x00);  
	Bsp_Lcd_Write_Data(0x35); 
	Bsp_Lcd_Write_Data(0x00); 
	Bsp_Lcd_Write_Data(0x00); 
	Bsp_Lcd_Write_Data(0x01); 
	Bsp_Lcd_Write_Data(0x02); 

	Bsp_Lcd_Write_Cmd(0xC4);			
	Bsp_Lcd_Write_Data(0x03);

	Bsp_Lcd_Write_Cmd(0xC5); //Set frame rate 
	Bsp_Lcd_Write_Data(0x01); 
	
	Bsp_Lcd_Write_Cmd(0xD2); //power setting 
	Bsp_Lcd_Write_Data(0x01); 
	Bsp_Lcd_Write_Data(0x22); 

	Bsp_Lcd_Write_Cmd(0xE7);			
	Bsp_Lcd_Write_Data(0x38);
	
	Bsp_Lcd_Write_Cmd(0xF3);			
  Bsp_Lcd_Write_Data(0x08); 
	Bsp_Lcd_Write_Data(0x12);
	Bsp_Lcd_Write_Data(0x12);
	Bsp_Lcd_Write_Data(0x08);

	Bsp_Lcd_Write_Cmd(0xC8); //Set Gamma 
	Bsp_Lcd_Write_Data(0x01); 
	Bsp_Lcd_Write_Data(0x52); 
	Bsp_Lcd_Write_Data(0x37); 
	Bsp_Lcd_Write_Data(0x10); 
	Bsp_Lcd_Write_Data(0x0d); 
	Bsp_Lcd_Write_Data(0x01); 
	Bsp_Lcd_Write_Data(0x04); 
	Bsp_Lcd_Write_Data(0x51); 
	Bsp_Lcd_Write_Data(0x77); 
	Bsp_Lcd_Write_Data(0x01); 
	Bsp_Lcd_Write_Data(0x01); 
	Bsp_Lcd_Write_Data(0x0d); 
	Bsp_Lcd_Write_Data(0x08); 
	Bsp_Lcd_Write_Data(0x80); 
	Bsp_Lcd_Write_Data(0x00);  

	Bsp_Lcd_Write_Cmd(0x29); //display on
}	

