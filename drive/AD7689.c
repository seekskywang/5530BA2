

#include "AD7689.h"
#include "GPIO.h"
#include "my_register.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_rcc.h"
#include "dma.h"																	   	  
#include "delay.h"	

extern struct bitDefine
{
    unsigned bit0: 1;
    unsigned bit1: 1;
    unsigned bit2: 1;
    unsigned bit3: 1;
    unsigned bit4: 1;
    unsigned bit5: 1;
    unsigned bit6: 1;
    unsigned bit7: 1;
} flagA, flagB,flagC,flagD,flagE,flagF,flagG;
#define AD7689_CNV_0			GPIO_ResetBits(GPIOB,GPIO_Pin_6);
#define AD7689_CNV_1			GPIO_SetBits(GPIOB,GPIO_Pin_6);
vu16 AD7689_Buffer[8];
vu16 DMA_Buffer[8];
vu16 Ad7689_Fit_Imon[60];
vu16 Ad7689_Fit_Imon1[50];
vu16 Ad7689_Fit_Vmon[100];
vu16 Ad7689_Fit_Rmon[30];
vu16 Ad7689_Fit_PVmon[100];
void Bubble_sort(vu16 *D_temp,vu8 num);
void AD7689_InitializeSPI1(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//inv
	GPIO_Init(GPIOB, &GPIO_InitStructure);//
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//PB3~5���ù������	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��

  GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1); //PCB3����Ϊ SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1); //PBB4����Ϊ SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1); //PB5����Ϊ SPI1
	AD7689_CNV_1;
	AD7689_Delay();
	AD7689_CNV_0;
	//����ֻ���SPI�ڳ�ʼ��
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;		//����SPI�����ݴ�С:SPI���ͽ���16λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	
	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����*/
}

//DMAx�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMAͨ��ѡ��,@ref DMA_channel DMA_Channel_0~DMA_Channel_7
//par:�����ַ
//mar:�洢����ַ
//ndtr:���ݴ�����  
void MYDMA_Config(void)
{ 
 
	DMA_InitTypeDef  DMA_InitStructure;
	
//	if((u32)DMA_Streamx>(u32)DMA2)//�õ���ǰstream������DMA2����DMA1
//	{
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ�� 
		
//	}else 
//	{
//	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1ʱ��ʹ�� 
//	}
  DMA_DeInit(DMA2_Stream0);
	
	while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE){}//�ȴ�DMA������ 
	
  /* ���� DMA Stream */
  DMA_InitStructure.DMA_Channel = DMA_Channel_3;  //ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&SPI1->DR;//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)AD7689_Buffer;//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//�洢��������ģʽ
  DMA_InitStructure.DMA_BufferSize = 8;//���ݴ����� 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ 
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�����ȼ�
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);//��ʼ��DMA Stream
	
//	DMA_DeInit(DMA2_Stream3);	
//	while (DMA_GetCmdStatus(DMA2_Stream3) != DISABLE){}//�ȴ�DMA������ 
////	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�����ȼ�
////	DMA_InitStructure.DMA_Channel = DMA_Channel_3;  //ͨ��ѡ��
////	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//�洢��������ģʽ
////	DMA_Init(DMA2_Stream3, &DMA_InitStructure);//��ʼ��DMA Stream
//		
//  DMA_InitStructure.DMA_Channel = DMA_Channel_3;  //ͨ��ѡ��
//  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&SPI1->DR;//DMA�����ַ
//  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)0;//DMA �洢��0��ַ
//  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//�洢��������ģʽ
//  DMA_InitStructure.DMA_BufferSize = 0;//���ݴ����� 
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ 
//  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�����ȼ�
//  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
//  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
//  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
//  DMA_Init(DMA2_Stream3, &DMA_InitStructure);//��ʼ��DMA Stream
		
	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Rx,ENABLE);
//	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);
}

//����һ��DMA����
//DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7 
//ndtr:���ݴ�����  
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)
{
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_RxOnly;
	SPI_Init(SPI1, &SPI_InitStructure);//ֻ��
	DMA_Cmd(DMA_Streamx, DISABLE);                      //�ر�DMA���� 
	
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}	//ȷ��DMA���Ա�����  
		
	DMA_SetCurrDataCounter(DMA_Streamx,ndtr);          //���ݴ�����  
 
	DMA_Cmd(DMA_Streamx, ENABLE);                      //����DMA����
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_Init(SPI1, &SPI_InitStructure);//�ָ�˫ȫ��
	
}	  
//DMA����
void dma_send(vu16 buf,u16 ndtr)
{
	DMA_Cmd(DMA2_Stream3,DISABLE);
	while (DMA_GetCmdStatus(DMA2_Stream3) != DISABLE){}//�ȴ�DMA������
	DMA2_Stream3->NDTR=ndtr;
	DMA2_Stream3->M0AR=(u32)buf;
	DMA_ClearFlag(DMA2_Stream3,DMA_FLAG_TCIF3|DMA_FLAG_HTIF3|DMA_FLAG_TEIF3|DMA_FLAG_DMEIF3|DMA_FLAG_FEIF3);
	SPI1->DR;
	DMA_Cmd(DMA2_Stream3,ENABLE);
	while(!DMA_GetFlagStatus(DMA2_Stream3,DMA_FLAG_TCIF3));
	DMA_Cmd(DMA2_Stream3,DISABLE);
	DMA_ClearFlag(DMA2_Stream3,DMA_FLAG_TCIF3);
}
//DMA����
void dma_rec(vu16 buf,u16 ndtr)
{
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_RxOnly;
	SPI_Init(SPI1, &SPI_InitStructure);//ֻ��
	DMA_Cmd(DMA2_Stream0,DISABLE);
	while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE){}//�ȴ�DMA������
	DMA2_Stream0->NDTR=ndtr;
	DMA2_Stream0->M0AR=(u32)buf;
	DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0|DMA_FLAG_HTIF0|DMA_FLAG_TEIF0|DMA_FLAG_DMEIF0|DMA_FLAG_FEIF0);
	SPI1->DR;
	DMA_Cmd(DMA2_Stream0,ENABLE);
	while(!DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0));
	DMA_Cmd(DMA2_Stream0,DISABLE);
	DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);
		
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_Init(SPI1, &SPI_InitStructure);//�ָ�˫ȫ��
}

vu16 SPI_AD7689_Read(vu16 AD7689_CFG, vu16 AD7689_INx)
{
	vu16 AD7689_Config=0;
	vu16 AD7689_Data;
	vu8 i;
	AD7689_Config = AD7689_CFG<<13|AD7689_INCC<<10|AD7689_INx<<7|AD7689_BW<<6|AD7689_REF<<3|AD7689_SEQ<<1|AD7689_RB;//д�����ò���
	AD7689_Config <<=2;
	AD7689_CNV_0;
	AD7689_Data=AD7689_TransferByte(AD7689_Config);
	AD7689_CNV_1;
	AD7689_Delay();
	return AD7689_Data;
}

/************************************************************************/
/* Function Name:	AD7689_TransferByte.								*/
/* Purpose:			Send of recive a byte.								*/
/* Resources:		SPI controler.										*/
/* Params:																*/
/*	@uiTxData:			The byte data will be sent.						*/
/* Return:			The byte data recived.						+		*/
/* Limitation:		None.												*/
/************************************************************************/
vu16 AD7689_TransferByte(vu16 uiTxData)
{
	vu16 uiRxData;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//	dma_send(uiTxData,1);
	SPI_I2S_SendData(SPI1,uiTxData);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//	dma_rec(uiRxData,1);
	uiRxData = SPI_I2S_ReceiveData(SPI1);
	return uiRxData;
}
/************************************************************************/
/* Function Name:	AD7689_Delay.									*/
/* Purpose:			Wait for device DRDY signal.						*/
/* Resources:		DRDY GPIO pin.										*/
/* Params:			None.												*/
/* Return:			None.												*/
/* Limitation:		None.												*/
/************************************************************************/
void AD7689_Delay(void)
{
	vu16 count ;
  for(count = 1000; count != 0; count--);
}
void AD7689_Delay1(void)
{
	vu16 count ;
  for(count = 3000; count != 0; count--);
}
void AD7689_Scan_CH(void)
{
	static vu8 I_cont,I1_cont,V_cont,R_cont,V1_cont;
	vu8 i,f;
	vu32 sum1;
	vu16 var_chI,var_chI1,var_chV,var_chV1,var_chR;
	for(i=0;i<8;i++)
	{
		AD7689_Buffer[i]=SPI_AD7689_Read(1, i);
		var_chV=AD7689_Buffer[2];
		var_chI=AD7689_Buffer[3];
		var_chI1=AD7689_Buffer[5];
		var_chV1=AD7689_Buffer[6];
		var_chR=AD7689_Buffer[7];
	}
	Ad7689_Fit_Imon[I_cont++]=var_chI;
	if(I_cont==60)
	{
		I_cont=0;
		sum1=0;
		for(f=0;f<60;f++)
		{
			sum1 +=Ad7689_Fit_Imon[f];
		}
		Imon1_value=sum1/60;//负载电流
	}
	
	Ad7689_Fit_Imon1[I1_cont++]=var_chI1;
	if(I1_cont==30)
	{
		I1_cont=0;
		sum1=0;
		for(f=0;f<30;f++)
		{
			sum1 +=Ad7689_Fit_Imon1[f];
		}
		Imon_value=sum1/30;//电源电流
	}
	
	Ad7689_Fit_PVmon[V1_cont++]=var_chV1;
	if(V1_cont==100)
	{
		V1_cont=0;
		sum1=0;
		for(f=0;f<100;f++)
		{
			sum1 +=Ad7689_Fit_PVmon[f];
		}
		Vmon_value=sum1/100;//电源电压
	}
	
	Ad7689_Fit_Vmon[V_cont++]=var_chV;
	if(V_cont==100)
	{
		V_cont=0;
		
	}
	sum1=0;
//		Bubble_sort( Ad7689_Fit_Vmon,100);//����Ӵ�С
		for(f=0;f<100;f++)
		{
			sum1 +=Ad7689_Fit_Vmon[f];
		}
		Vmon1_value=sum1/100;//负载电压

	Ad7689_Fit_Rmon[R_cont++]=var_chR;
	if(R_cont==30)
	{
		R_cont=0;
		sum1=0;
		for(f=0;f<30;f++)
		{
			sum1 +=Ad7689_Fit_Rmon[f];
		}
		Rmon_value=sum1/30;//内阻
	}
}

/*
ð���������ֵ�ڵ�һλ����Сֵ�����һλ
 */
void Bubble_sort(vu16 *D_temp,vu8 num)
{
	unsigned int _temp;
	unsigned char m,n;
	for(m=0;m<num;m++)
	{
		for(n=m;n<num;n++)
		{
			if(D_temp[n]>D_temp[m])//����ֵ���ڵ�һλ
			{
				_temp = D_temp[m];
				D_temp[m] =D_temp[n];
				D_temp[n]=_temp;		
			}
		}	
	}
}