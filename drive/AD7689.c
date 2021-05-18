

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
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//PB3~5复用功能输出	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化

  GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1); //PCB3复用为 SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1); //PBB4复用为 SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1); //PB5复用为 SPI1
	AD7689_CNV_1;
	AD7689_Delay();
	AD7689_CNV_0;
	//这里只针对SPI口初始化
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;		//设置SPI的数据大小:SPI发送接收16位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设*/
}

//DMAx的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_Streamx:DMA数据流,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMA通道选择,@ref DMA_channel DMA_Channel_0~DMA_Channel_7
//par:外设地址
//mar:存储器地址
//ndtr:数据传输量  
void MYDMA_Config(void)
{ 
 
	DMA_InitTypeDef  DMA_InitStructure;
	
//	if((u32)DMA_Streamx>(u32)DMA2)//得到当前stream是属于DMA2还是DMA1
//	{
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2时钟使能 
		
//	}else 
//	{
//	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1时钟使能 
//	}
  DMA_DeInit(DMA2_Stream0);
	
	while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE){}//等待DMA可配置 
	
  /* 配置 DMA Stream */
  DMA_InitStructure.DMA_Channel = DMA_Channel_3;  //通道选择
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&SPI1->DR;//DMA外设地址
  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)AD7689_Buffer;//DMA 存储器0地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//存储器到外设模式
  DMA_InitStructure.DMA_BufferSize = 8;//数据传输量 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度:8位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// 使用普通模式 
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//高优先级
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//存储器突发单次传输
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);//初始化DMA Stream
	
//	DMA_DeInit(DMA2_Stream3);	
//	while (DMA_GetCmdStatus(DMA2_Stream3) != DISABLE){}//等待DMA可配置 
////	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//高优先级
////	DMA_InitStructure.DMA_Channel = DMA_Channel_3;  //通道选择
////	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//存储器到外设模式
////	DMA_Init(DMA2_Stream3, &DMA_InitStructure);//初始化DMA Stream
//		
//  DMA_InitStructure.DMA_Channel = DMA_Channel_3;  //通道选择
//  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&SPI1->DR;//DMA外设地址
//  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)0;//DMA 存储器0地址
//  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//存储器到外设模式
//  DMA_InitStructure.DMA_BufferSize = 0;//数据传输量 
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8位
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度:8位
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// 使用普通模式 
//  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//高优先级
//  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
//  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//存储器突发单次传输
//  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输
//  DMA_Init(DMA2_Stream3, &DMA_InitStructure);//初始化DMA Stream
		
	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Rx,ENABLE);
//	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);
}

//开启一次DMA传输
//DMA_Streamx:DMA数据流,DMA1_Stream0~7/DMA2_Stream0~7 
//ndtr:数据传输量  
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)
{
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_RxOnly;
	SPI_Init(SPI1, &SPI_InitStructure);//只读
	DMA_Cmd(DMA_Streamx, DISABLE);                      //关闭DMA传输 
	
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}	//确保DMA可以被设置  
		
	DMA_SetCurrDataCounter(DMA_Streamx,ndtr);          //数据传输量  
 
	DMA_Cmd(DMA_Streamx, ENABLE);                      //开启DMA传输
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_Init(SPI1, &SPI_InitStructure);//恢复双全工
	
}	  
//DMA发送
void dma_send(vu16 buf,u16 ndtr)
{
	DMA_Cmd(DMA2_Stream3,DISABLE);
	while (DMA_GetCmdStatus(DMA2_Stream3) != DISABLE){}//等待DMA可配置
	DMA2_Stream3->NDTR=ndtr;
	DMA2_Stream3->M0AR=(u32)buf;
	DMA_ClearFlag(DMA2_Stream3,DMA_FLAG_TCIF3|DMA_FLAG_HTIF3|DMA_FLAG_TEIF3|DMA_FLAG_DMEIF3|DMA_FLAG_FEIF3);
	SPI1->DR;
	DMA_Cmd(DMA2_Stream3,ENABLE);
	while(!DMA_GetFlagStatus(DMA2_Stream3,DMA_FLAG_TCIF3));
	DMA_Cmd(DMA2_Stream3,DISABLE);
	DMA_ClearFlag(DMA2_Stream3,DMA_FLAG_TCIF3);
}
//DMA接收
void dma_rec(vu16 buf,u16 ndtr)
{
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_RxOnly;
	SPI_Init(SPI1, &SPI_InitStructure);//只读
	DMA_Cmd(DMA2_Stream0,DISABLE);
	while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE){}//等待DMA可配置
	DMA2_Stream0->NDTR=ndtr;
	DMA2_Stream0->M0AR=(u32)buf;
	DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0|DMA_FLAG_HTIF0|DMA_FLAG_TEIF0|DMA_FLAG_DMEIF0|DMA_FLAG_FEIF0);
	SPI1->DR;
	DMA_Cmd(DMA2_Stream0,ENABLE);
	while(!DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0));
	DMA_Cmd(DMA2_Stream0,DISABLE);
	DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);
		
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_Init(SPI1, &SPI_InitStructure);//恢复双全工
}

vu16 SPI_AD7689_Read(vu16 AD7689_CFG, vu16 AD7689_INx)
{
	vu16 AD7689_Config=0;
	vu16 AD7689_Data;
	vu8 i;
	AD7689_Config = AD7689_CFG<<13|AD7689_INCC<<10|AD7689_INx<<7|AD7689_BW<<6|AD7689_REF<<3|AD7689_SEQ<<1|AD7689_RB;//写入配置参数
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
	if(I_cont==5)
	{
		I_cont=0;
		sum1=0;
		for(f=0;f<5;f++)
		{
			sum1 +=Ad7689_Fit_Imon[f];
		}
		Imon1_value=sum1/5;//璐熻浇鐢垫祦
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
		Imon_value=sum1/30;//鐢垫簮鐢垫祦
	}
	
	Ad7689_Fit_PVmon[V1_cont++]=var_chV1;
	if(V1_cont==10)
	{
		V1_cont=0;
		sum1=0;
		for(f=0;f<10;f++)
		{
			sum1 +=Ad7689_Fit_PVmon[f];
		}
		Vmon_value=sum1/10;//鐢垫簮鐢靛帇
	}
	
	Ad7689_Fit_Vmon[V_cont++]=var_chV;
	if(V_cont==10)
	{
		V_cont=0;
		
	}
	sum1=0;
//		Bubble_sort( Ad7689_Fit_Vmon,100);//排序从大到小
		for(f=0;f<10;f++)
		{
			sum1 +=Ad7689_Fit_Vmon[f];
		}
		Vmon1_value=sum1/10;//璐熻浇鐢靛帇

	Ad7689_Fit_Rmon[R_cont++]=var_chR;
	if(R_cont==30)
	{
		R_cont=0;
		sum1=0;
		for(f=0;f<30;f++)
		{
			sum1 +=Ad7689_Fit_Rmon[f];
		}
		Rmon_value=sum1/30;//鍐呴樆
	}
}

/*
冒泡排序，最大值在第一位，最小值在最后一位
 */
void Bubble_sort(vu16 *D_temp,vu8 num)
{
	unsigned int _temp;
	unsigned char m,n;
	for(m=0;m<num;m++)
	{
		for(n=m;n<num;n++)
		{
			if(D_temp[n]>D_temp[m])//最大的值放在第一位
			{
				_temp = D_temp[m];
				D_temp[m] =D_temp[n];
				D_temp[n]=_temp;		
			}
		}	
	}
}