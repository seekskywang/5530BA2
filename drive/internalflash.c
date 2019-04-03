#include "internalflash.h"

/****************************************************************************
* 功    能: 获取地址Address对应的sector编号
* 入口参数：地址
* 出口参数：sector编号
* 说    明：无
* 调用方法：无
****************************************************************************/
uint16_t Flash_GetSector(uint32_t Address)
{
uint16_t sector = 0;
if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
{
sector = FLASH_Sector_0;  
}
else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
{
sector = FLASH_Sector_1;  
}
else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
{
sector = FLASH_Sector_2;  
}
else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
{
sector = FLASH_Sector_3;  
}
else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
{
sector = FLASH_Sector_4;  
}
else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
{
sector = FLASH_Sector_5;  
}
else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
{
sector = FLASH_Sector_6;  
}	
else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
{
sector = FLASH_Sector_7;  
}
else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
{
sector = FLASH_Sector_8;  
}
else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
{
sector = FLASH_Sector_9;  
}
else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
{
sector = FLASH_Sector_10;  
}
else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
{
sector = FLASH_Sector_11;  
}
return sector;
}

/****************************************************************************
* 功    能: 擦除指定扇区
* 入口参数：SectorNum 扇区号
* 出口参数：无
* 说    明：无
* 调用方法：无
****************************************************************************/
void Flash_EraseSector(uint16_t SectorNum)
{
FLASH_Unlock(); 
FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
if (FLASH_EraseSector(SectorNum, VoltageRange_3) != FLASH_COMPLETE) while (1);
FLASH_Lock(); 
}

/****************************************************************************
* 功    能: 写入长度为length的32位数据
* 入口参数：address：地址
length： 数据长度
data_32：要写入的数据指针
* 出口参数：无
* 说    明：无
* 调用方法：无
****************************************************************************/
void Flash_Write32BitDatas(uint32_t address, uint16_t length, int32_t* data_32)
{
uint16_t StartSector, EndSector,i;
FLASH_Unlock(); //解锁FLASH后才能向FLASH中写数据。
FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
StartSector = Flash_GetSector(address);  //获取FLASH的Sector编号
EndSector = Flash_GetSector(address+4*length);
for (i = StartSector; i < EndSector; i += 8)  //每次FLASH编号增加8，可参考上边FLASH Sector的定义。
{
if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE) while (1);
}
for(i=0; i<length; i++)
{
if (FLASH_ProgramWord(address, data_32[i]) == FLASH_COMPLETE)   //将DATA_32写入相应的地址。
{
   address = address + 4;
}
else
{ 
while (1);
}
}
FLASH_Lock();  //读FLASH不需要FLASH处于解锁状态。
}

/****************************************************************************
* 功    能: 读取长度为length的32位数据
* 入口参数：address：地址
length： 数据长度
data_32  指向读出的数据
* 出口参数：无
* 说    明：无
* 调用方法：无
****************************************************************************/
void Flash_Read32BitDatas(uint32_t address, uint16_t length, int32_t* data_32)
{
uint8_t i;
for(i=0; i<length; i++)
{
data_32[i]=*(__IO int32_t*)address;
address=address + 4;
}
}

/****************************************************************************
* 功    能: 写入长度为length的16位数据
* 入口参数：address：地址
length： 数据长度
data_16：要写入的数据指针
* 出口参数：无
* 说    明：无
* 调用方法：无
****************************************************************************/
void Flash_Write16BitDatas(uint32_t address, uint16_t length, int16_t* data_16)
{
uint16_t StartSector, EndSector,i;
FLASH_Unlock(); //解锁FLASH后才能向FLASH中写数据。
FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
StartSector = Flash_GetSector(address);  //获取FLASH的Sector编号
EndSector = Flash_GetSector(address+2*length);
for (i = StartSector; i < EndSector+1; i += 8)  //每次FLASH编号增加8，可参考上边FLASH Sector的定义。
{
if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE) while (1);
}
for(i=0; i<length; i++)
{
if (FLASH_ProgramHalfWord(address, data_16[i]) == FLASH_COMPLETE)   
{
   address = address + 2;
}
else
{ 
while (1);
}
}
FLASH_Lock();  //读FLASH不需要FLASH处于解锁状态。
}

/****************************************************************************
* 功    能: 读取长度为length的16位数据
* 入口参数：address：地址
length： 数据长度
data_16  指向读出的数据
* 出口参数：无
* 说    明：无
* 调用方法：无
****************************************************************************/
void Flash_Read16BitDatas(uint32_t address, uint16_t length, int16_t* data_16)
{
uint8_t i;
for(i=0; i<length; i++)
{
data_16[i]=*(__IO int16_t*)address;
address=address + 2;
}
}

/****************************************************************************
* 功    能: 写入长度为length的8位数据
* 入口参数：address：地址
length： 数据长度
data_8：要写入的数据指针
* 出口参数：无
* 说    明：无
* 调用方法：无
****************************************************************************/
void Flash_Write8BitDatas(uint32_t address, uint16_t length, int8_t* data_8)
{
uint16_t StartSector, EndSector,i;
FLASH_Unlock(); //解锁FLASH后才能向FLASH中写数据。
FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
StartSector = Flash_GetSector(address);  //获取FLASH的Sector编号
EndSector = Flash_GetSector(address+length);
for (i = StartSector; i < EndSector; i += 8)  //每次FLASH编号增加8，可参考上边FLASH Sector的定义。
{
if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE) while (1);
}
for(i=0; i<length; i++)
{
if (FLASH_ProgramByte(address, data_8[i]) == FLASH_COMPLETE)   
{
   address++;
}
else
{ 
while (1);
}
}
FLASH_Lock();  //读FLASH不需要FLASH处于解锁状态。
}

/****************************************************************************
* 功    能: 读取长度为length的8位数据
* 入口参数：address：地址
length： 数据长度
data_8  指向读出的数据
* 出口参数：无
* 说    明：无
* 调用方法：无
****************************************************************************/
void Flash_Read8BitDatas(uint32_t address, uint16_t length, int8_t* data_8)
{
uint8_t i;
for(i=0; i<length; i++)
{
data_8[i]=*(__IO int8_t*)address;
address++;
}
}


//读取指定地址的半字(16位数据)
//faddr:读地址(此地址必须为2的倍数!!)
//返回值:对应数据.
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}
#if STM32_FLASH_WREN	//如果使能了写   
//不检查的写入
//WriteAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数   
void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//地址增加2.
	}  
} 
//从指定地址开始写入指定长度的数据
//WriteAddr:起始地址(此地址必须为2的倍数!!)
//pBuffer:数据指针
//NumToWrite:半字(16位)数(就是要写入的16位数据的个数.)
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //字节
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];//最多是2K字节
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   //扇区地址
	u16 secoff;	   //扇区内偏移地址(16位字计算)
	u16 secremain; //扇区内剩余地址(16位字计算)	   
 	u16 i;    
	u32 offaddr;   //去掉0X08000000后的地址
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//非法地址
	FLASH_Unlock();						//解锁
	offaddr=WriteAddr-STM32_FLASH_BASE;		//实际偏移地址.
	secpos=offaddr/STM_SECTOR_SIZE;			//扇区地址  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//在扇区内的偏移(2个字节为基本单位.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//扇区剩余空间大小   
	if(NumToWrite<=secremain)secremain=NumToWrite;//不大于该扇区范围
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//读出整个扇区的内容
		for(i=0;i<secremain;i++)//校验数据
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			FLASH_EraseSector(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,VoltageRange_3);//擦除这个扇区
			for(i=0;i<secremain;i++)//复制
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//写入整个扇区  
		}else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(NumToWrite==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;				//扇区地址增1
			secoff=0;				//偏移位置为0 	 
		   	pBuffer+=secremain;  	//指针偏移
			WriteAddr+=secremain;	//写地址偏移	   
		   	NumToWrite-=secremain;	//字节(16位)数递减
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//下一个扇区还是写不完
			else secremain=NumToWrite;//下一个扇区可以写完了
		}	 
	};	
	FLASH_Lock();//上锁
}
#endif

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//读取2个字节.
		ReadAddr+=2;//偏移2个字节.	
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//WriteAddr:起始地址
//WriteData:要写入的数据
void Test_Write(u32 WriteAddr,u16 WriteData)   	
{
	STMFLASH_Write(WriteAddr,&WriteData,1);//写入一个字 
}