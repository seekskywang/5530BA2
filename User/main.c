/******************************************************************/
/* 名称：main                                                    */
/* 效果：                                                        */
/* 内容：                                                       */
/* 作者：zhan                                                  */
/* 联系方式QQ:363116119                                        */
/******************************************************************/
#include "my_register.h"
#include "stm32f4xx.h"
#include "clock.h"
#include "tim6.h"
#include "tim1.h"
#include "tim2.h"
#include "adc.h"
#include "clock.h"
#include "gpio.h"
#include "bsp_SysTick.h"
#include "usart.h"
#include "ssd1963.h"
#include "iwdg.h"
#include "MainTask.h"
#include "IIC_24C01.h"
#include "flash.h"
#include "tm1650.h"
#include "dac8531.h"
#include "ad7689.h"
#include "internalflash.h"
#include "flash_if.h"


float DISS_Voltage;//负载电压
float DISS_POW_Voltage;//稳压电源电压
float DISS_Current;//负载电流
float DISS_POW_Current;//稳压电源电流
float disloadv;
u16 disrvalue;
void setcompare(void);

//FIL   *file;
//UINT  br, bw;
////u8 *fatbuff;
//#define REC_LEN  			5*1024 //定义最大接收字节数 120K
//u8 RX_BUF[REC_LEN] __attribute__ ((at(0X20001000)));//接收缓冲,最大REC_LEN个字节,起始地址为0X20001000.    
//static  u8    filedatabuf[2048];
//static  UINT   readcount;



struct bitDefine
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

int main(void)
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000);
	__enable_irq();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);//开启CRC时钟，STEMWIN授权使用
	RCC_Configuration();
	SysTick_Init();
	GPIO_Conf();
	flag_Load_CC=1;//开机负载默认进入CC模式
	GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
	GPIO_SetBits(GPIOA,GPIO_Pin_15);//OFF
	GPIO_SetBits(GPIOA,GPIO_Pin_11);//电流切换为高档
	TIM1_PWM_Config();
	TIM2_PWM_Config();
    TIM4_Int_Init(2-1,8400-1);
    TIM3_Int_Init(10000-1,8400-1);
    TIM5_Int_Init(90-1,8400-1);
	TIM6_Config();
	ADC1_DMA_Init();
	USART_Configuration();
    USART3_Configuration();
	i2c_CfgGpio();//24C01引脚初始化
	TM1650_GPIO_INT();		/*TM1650引脚初始化 */  
	DAC8531_GPIOCoing();//DAC初始化
	DAC8531_Send(0);
	AD7689_InitializeSPI1();//AD7689初始化
	LCD_Initializtion();//液晶屏初始化	
	EEPROM_READ_Coeff();//读取校准参数
	IWDG_Inte();
	Flash_Read32BitDatas(FLASH_USER_START_ADDR,40,InFlashSave);
	if(jkflag > 1)
	{
		jkflag = 1;
		Write_Limits();
	}
	setcompare();
//	MYDMA_Config();
//    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
//    GPIO_SetBits(GPIOC,GPIO_Pin_13);//关闭电源输出继电器
	MainTask();
}

void setcompare(void)
{
	u8 i;
	for(i=0;i<44;i++)
	{
		if(Run_Control[i] == 65535)
		{
			Run_Control[i] = 0;
		}
	}
}

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/
