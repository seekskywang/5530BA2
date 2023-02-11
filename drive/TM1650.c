/******************************************************************/
/* 函数名：                                                */
/* 功能：                                              */
/* 修改日期：                                                       */
/* 内容：                                                    */
/* 作者：QQ:363116119                                        */
/******************************************************************/
#include "my_register.h"
#include "tm1650.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
/********************************************************************/
/* 定义IIC引脚 */
#define GPIO_PORT_I2C	GPIOC		/* GPIO*/
#define TM1650_SCL_PIN		GPIO_Pin_7			/* SCL引脚号*/
#define TM1650_SDA_PIN		GPIO_Pin_8			/* SDA引脚号 */

/* 定义引脚动作*/
#define TM1650_SCL_1()  GPIO_SetBits(GPIO_PORT_I2C, TM1650_SCL_PIN)		/* SCL = 1 */
#define TM1650_SCL_0()  GPIO_ResetBits(GPIO_PORT_I2C, TM1650_SCL_PIN)		/* SCL = 0 */

#define TM1650_SDA_1()  GPIO_SetBits(GPIO_PORT_I2C, TM1650_SDA_PIN)		/* SDA = 1 */
#define TM1650_SDA_0()  GPIO_ResetBits(GPIO_PORT_I2C, TM1650_SDA_PIN)		/* SDA = 0 */

#define TM1650_SDA_READ()  GPIO_ReadInputDataBit(GPIO_PORT_I2C, TM1650_SDA_PIN)	/* 读取SDA引脚电平*/

/**********************************************************************************************************
*	函数名: TM1650_GPIO_INT
*	功能: IIC引脚初始化
*	作者：
*	修改时间：
**********************************************************************************************************/
void TM1650_GPIO_INT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//开漏输出
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;//
	GPIO_Init(GPIOC, &GPIO_InitStructure);//
}
/**********************************************************************************************************
*	函数名: IIC_Delay
*	功能: 延时函数
*	作者：
*	修改时间：
**********************************************************************************************************/
static void IIc_Delay(void)
{
	vu8 i;
	for (i = 0; i < 200; i++);
}
/**********************************************************************************************************
*	函数名: IIc_Start
*	功能: 启动函数
*	作者：
*	修改时间：
**********************************************************************************************************/
void IIc_Start(void)
{
	/* 启动IIC */
	TM1650_SCL_1();
	TM1650_SDA_1();
	IIc_Delay();
	TM1650_SDA_0();
	IIc_Delay();
	TM1650_SCL_0();
//	IIc_Delay();
}
/**********************************************************************************************************
*	函数名: IIc_Stop
*	功能: 停止函数
*	作者：
*	修改时间：
**********************************************************************************************************/
void IIc_Stop(void)
{
	/* 发送停止位 */
	TM1650_SDA_0();
	IIc_Delay();
	TM1650_SCL_1();
	IIc_Delay();
	TM1650_SDA_1();
//	IIc_Delay();
//	TM1650_SCL_0();
//	TM1650_SDA_0();
}
/**********************************************************************************************************
*	函数名: IIc_SendByte
*	功能: 发送8位数据
*	作者：
*	修改时间：
**********************************************************************************************************/
void IIc_SendByte(vu8 _ucByte)
{
	vu8 i;

	/* 发送一个8位数据 */
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			TM1650_SDA_1();
		}
		else
		{
			TM1650_SDA_0();
		}
		IIc_Delay();
		TM1650_SCL_1();
		IIc_Delay();	
		TM1650_SCL_0();
		if (i == 7)
		{
			 TM1650_SDA_1(); // 置高
		}
		_ucByte <<= 1;	/* 先送高位 */
		IIc_Delay();
	}
}
/**********************************************************************************************************
*	函数名: IIc_ReadByte
*	功能: 接受8位数据
*	作者：
*	修改时间：
**********************************************************************************************************/
vu8 IIc_ReadByte(void)
{
	vu8 i;
	vu8 value;

	/*接受一个8位数据 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		TM1650_SCL_1();
		IIc_Delay();
		if (TM1650_SDA_READ())
		{
			value++;
		}
		TM1650_SCL_0();
		IIc_Delay();
	}
	return value;
}
/**********************************************************************************************************
*	函数名: IIc_WaitAck
*	功能: 等待ACK信号
*	作者：
*	修改时间：
**********************************************************************************************************/
vu8 IIc_WaitAck(void)
{
	vu8 re;

	TM1650_SDA_1();	/*  */
	IIc_Delay();
	TM1650_SCL_1();	/*  */
	IIc_Delay();
	if (TM1650_SDA_READ())	/* 读取ACK */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	TM1650_SCL_0();
	IIc_Delay();
	return re;
}
/**********************************************************************************************************
*	函数名: IIc_Ack
*	功能: 等待ACK信号
*	作者：
*	修改时间：
**********************************************************************************************************/
void IIc_Ack(void)
{
	TM1650_SDA_0();	/* CPUȽ֯SDA = 0 */
	IIc_Delay();
	TM1650_SCL_1();	/* CPUӺʺ1ٶʱד */
	IIc_Delay();
	TM1650_SCL_0();
	IIc_Delay();
	TM1650_SDA_1();	/* CPUˍ؅SDA؜П */
}

/**********************************************************************************************************
*	函数名: IIc_NAck
*	功能: 等待ACK信号
*	作者：
*	修改时间：
**********************************************************************************************************/
void IIc_NAck(void)
{
	TM1650_SDA_1();	/* CPUȽ֯SDA = 1 */
	IIc_Delay();
	TM1650_SCL_1();	/* CPUӺʺ1ٶʱד */
	IIc_Delay();
	TM1650_SCL_0();
	IIc_Delay();	
}

/**系统设置命令
light -- 亮度级别(00H 8级亮度、10H为1级亮度。。。。。。70H为7级亮度)
segMod -- 段模式设置(00H为8段模式，08H为7段模式)
WorkMod -- 工作模式(00H为正常模式，04H为低功耗模式)
Onoff -- 开关(00H为关显示，01H为开显示)
例如：1级亮度，7段模式，正常工作模式，开显示则函数为
TM1650_SystemCmd(0x10, 0x08, 0x01, 0x01 );
***/
void TM1650_SystemCmd(vu8 light,vu8 segMod, vu8 WorkMod, vu8 Onoff)
{
 	IIc_Start();
	IIc_SendByte(0x48);
	IIc_SendByte(light | segMod | WorkMod | Onoff );
	IIc_Stop();
}

/**4位显示数据
0x68 对应DIG1
0x6A 对应DIG2
0x6C 对应DIG3
0x6E 对应DIG4
如果要DIG1-4显示0-3 则函数为TM1650Disp(DispCode[0],DispCode[1],DispCode[2],DispCode[3]);
***/
void TM1650Disp(vu8 sdate1, vu8 sdate2, vu8 sdate3, vu8 sdate4)
{
		TM1650_SET_LED(0X68,sdate1);  //GID1-sdate1
		TM1650_SET_LED(0X6A,sdate2);  //GID2-sdate2
		TM1650_SET_LED(0X6C,sdate3);  //GID3-sdate3
		TM1650_SET_LED(0X6E,sdate4);  //GID4-sdate4
}

/**********************************************************************************************************
*	函数名: IIc_Read_KEY
*	功能: 读取键值
*	作者：
*	修改时间：
**********************************************************************************************************/
vu8 TM1650_Read_KEY(void)
{
	vu8 ucAck;
	vu8 key;

	IIc_Start();		/* 开始*/

	/* 发送地址 */
	IIc_SendByte(0x4F);//读按键命令
	ucAck = IIc_WaitAck();	/* 等待ACK*/
	IIc_Delay();
	key=IIc_ReadByte();//读取键值
	IIc_Stop();			/* 读完停止 */

	return key;
}

/**********************************************************************************************************
*	函数名: TM1650_SET_LED
*	功能: 发送LED数据
*	作者：
*	修改时间：
**********************************************************************************************************/
void TM1650_SET_LED(vu8 addr,vu8 dat)
{
	vu8 ucAck;
	IIc_Start();		/* 开始*/
	IIc_SendByte(addr);
	ucAck = IIc_WaitAck();	/* 等待ACK*/
	IIc_SendByte(dat);
	ucAck = IIc_WaitAck();	/* 等待ACK*/
	IIc_Stop();			/* 读完停止 */
}