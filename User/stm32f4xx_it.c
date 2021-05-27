/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "bsp_SysTick.h"
#include "my_register.h"
#include  "gui.h"
#include "MainTask.h"
#include "internalflash.h"
extern WM_HWIN CreateR(void);
extern WM_HWIN CreateWindow2(void);
extern WM_HWIN CreateWindow(void);
extern WM_HWIN CreateG(void);
extern WM_HWIN CreateSET(void);
extern WM_HWIN Createcal(void);
extern WM_HWIN hWinWind;
extern WM_HWIN hWinR;
extern WM_HWIN load_wind;//è´Ÿè½½ç•Œé¢å¥æŸ„
extern WM_HWIN hWinG;
extern WM_HWIN hWinset;
extern WM_HWIN hWincdc;
extern WM_HWIN hWinsysinfo;
extern vu8 cdc_sw;
extern vu8 paused;
extern vu8 mode_sw;
extern vu8 pow_sw;
extern vu8 c_rec;
extern vu8 load_sw;
extern u8 load_mode;
extern u8 sendmodeflag;
extern float v;
u8 rmtrig[3];
extern __IO int32_t OS_TimeMS;
static void MODS_03H(void);
static void MODS_06H(void);
static void MODS_50H(void);
static void MODS_51H(void);
static void MODS_52H(void);
static void MODS_SendAckErr(uint8_t _ucErrCode);
static uint8_t MODS_Load(uint16_t reg_addr, uint16_t reg_value);
static uint8_t MODS_Pow(uint16_t reg_addr, uint16_t reg_value);
static uint8_t MODS_CDC(uint16_t reg_addr, uint16_t reg_value);
static uint8_t MODS_WriteRegValue(uint16_t reg_addr, uint16_t reg_value);
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
} flagA,flagB,flagC,flagD,flagE,flagF;
/** @addtogroup Template_Project
  * @{
  */
float temp;
u8 g_mods_timeout = 0;
struct MODS_T g_tModS;
extern float shortv;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
	OS_TimeMS++;
	t_KeyScan++;
	if(t_KeyScan>10)
	{
		t_KeyScan=0;
		Flag_Key_Scan=1;//§Õ?§Ý???
	}
	t_0_5S++;
	if(t_0_5S>20)
	{
		t_0_5S=0;
		Flag_0_5S =1;//???§¾????
	}
//--------------------------------------------
	if(flag_Tim_USART==1)//???¡ê??
	{
		t_USART++;
	}
	if(t_USART>40)//??2.6ms
	{
		t_USART=0;
		flag_Tim_USART=0;
		UART_Buffer_Size=0;	
	}
}

/*
*********************************************************************************************************
*	º¯ Êý Ãû: MODS_SendAckErr
*	¹¦ÄÜËµÃ÷: ·¢ËÍ´íÎóÓ¦´ð
*	ÐÎ    ²Î: _ucErrCode : ´íÎó´úÂë
*	·µ »Ø Öµ: ÎÞ
*********************************************************************************************************
*/
static void MODS_SendAckErr(uint8_t _ucErrCode)
{
	uint8_t txbuf[3];

	txbuf[0] = g_tModS.RxBuf[0];					/* 485µØÖ· */
	txbuf[1] = g_tModS.RxBuf[1] | 0x80;				/* Òì³£µÄ¹¦ÄÜÂë */
	txbuf[2] = _ucErrCode;							/* ´íÎó´úÂë(01,02,03,04) */

	MODS_SendWithCRC(txbuf, 3);
}


/*
*********************************************************************************************************
*	º¯ Êý Ãû: MODS_SendAckOk
*	¹¦ÄÜËµÃ÷: ·¢ËÍÕýÈ·µÄÓ¦´ð.
*	ÐÎ    ²Î: ÎÞ
*	·µ »Ø Öµ: ÎÞ
*********************************************************************************************************
*/
static void MODS_SendAckOk(void)
{
	uint8_t txbuf[6];
	uint8_t i;

	for (i = 0; i < 6; i++)
	{
		txbuf[i] = g_tModS.RxBuf[i];
	}
	MODS_SendWithCRC(txbuf, 6);
}

/*
*********************************************************************************************************
*	º¯ Êý Ãû: BEBufToUint16
*	¹¦ÄÜËµÃ÷: ½«2×Ö½ÚÊý×é(´ó¶ËBig Endian´ÎÐò£¬¸ß×Ö½ÚÔÚÇ°)×ª»»Îª16Î»ÕûÊý
*	ÐÎ    ²Î: _pBuf : Êý×é
*	·µ »Ø Öµ: 16Î»ÕûÊýÖµ
*
*   ´ó¶Ë(Big Endian)ÓëÐ¡¶Ë(Little Endian)
*********************************************************************************************************
*/
uint16_t BEBufToUint16(uint8_t *_pBuf)
{
    return (((uint16_t)_pBuf[0] << 8) | _pBuf[1]);
}

/*****************  ·¢ËÍÒ»¸ö×Ö·û **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ·¢ËÍÒ»¸ö×Ö½ÚÊý¾Ýµ½USART */
	USART_SendData(pUSARTx,ch);
		
	/* µÈ´ý·¢ËÍÊý¾Ý¼Ä´æÆ÷Îª¿Õ */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

void uart1SendChars(u8 *str, u16 strlen)
{ 
	  u16 k= 0 ; 
   do { 
       USART_SendData(USART1,*(str + k));
       while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
       k++; 
       }   //Ñ­»··¢ËÍ,Ö±µ½·¢ËÍÍê±Ï   
    while (k < strlen); 
} 


 // CRC ¸ßÎ»×Ö½ÚÖµ±í
static const uint8_t s_CRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
} ;
// CRC µÍÎ»×Ö½ÚÖµ±í
const uint8_t s_CRCLo[] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
	0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
	0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
	0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
	0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
	0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
	0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
	0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
	0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
	0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
	0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
	0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
	0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
	0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
	0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
	0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
	0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
	0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};



void  DMA2_Stream0_IRQHandler(void)
{
	DMA_ClearITPendingBit(DMA2_Stream0,DMA_IT_TCIF0);
	Flag_ADC_Full=1;
}

void  TIM6_DAC_IRQHandler (void)
{
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);//?????¦Ë
}

void USART1_IRQHandler(void)
{
//	flag_Tim_USART=1;
    
 	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		
        g_mods_timeout = 2;
        if (g_tModS.RxCount < S_RX_BUF_SIZE)
        {
            g_tModS.RxBuf[g_tModS.RxCount++] = USART_ReceiveData(USART1);
        }
		if(g_tModS.RxCount > 7 && g_tModS.RxBuf[1] == 6)
		{
			MODS_SendAckOk();
		}
	}
}


void USART3_IRQHandler(void)
{
    static vu8 count = 0;
    u8 res; 
    static vu8 i = 0;
    static float sum;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        
        res =USART_ReceiveData(USART3);//(USART1->DR); //????????
        if(count == 0)
        {
            if(res == 0x03)
            {
                count = 1;
            }else{
                count = 0;
            }
        }else if(count == 1){
             if(res == 0xff)
            {
                count = 2;
            }else{
                count = 0;
            }
            
        }else if(count > 1 && count <4)
        {
            UART_Buffer_Rece[count] = res;               
//            temp = (UART_Buffer_Rece[2] * 256 + UART_Buffer_Rece[3])/10.0;
            count ++;
        }else if(count == 4)
        {
            if(i < 10)
            {
             sum += (UART_Buffer_Rece[2] * 256 + UART_Buffer_Rece[3])/10.0;
            }else{
                temp = sum/10.0;
                sum = 0;
                i = 0;
            }
             count =0;
             i ++;
        }
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
     }
}


void RecHandle(void)
{
    u8 crec[6];
    u8 *csend;
    static u8 *sendbuf;
    u8 sendlen;
    static u16 recrc;
    static u16 scrc;
    u8 i;
    
    switch(g_tModS.RxBuf[1])
    {
        case 0x03:
        {
            MODS_03H();
        }break;
        case 0x06:
        {
            MODS_06H();
        }break;
		case 0x50:
        {
            MODS_50H();
        }break;
		case 0x51:
        {
            MODS_51H();
        }break;
		case 0x52:
        {
            MODS_52H();
        }break;
        default:break;
    }
}

/*
*********************************************************************************************************
*	º¯ Êý Ãû: MODS_ReadRegValue
*	¹¦ÄÜËµÃ÷: ¶ÁÈ¡±£³Ö¼Ä´æÆ÷µÄÖµ
*	ÐÎ    ²Î: reg_addr ¼Ä´æÆ÷µØÖ·
*			  reg_value ´æ·Å¼Ä´æÆ÷½á¹û
*	·µ »Ø Öµ: 1±íÊ¾OK 0±íÊ¾´íÎó
*********************************************************************************************************
*/
static uint8_t MODS_ReadRegValue(uint16_t reg_addr, uint8_t *reg_value)
{
    uint16_t value;
	lock = 1;
	switch (reg_addr)									/* ÅÐ¶Ï¼Ä´æÆ÷µØÖ· */
	{
        case SLAVE_REG_P00:
//			C_SW(1);
			v= DISS_Voltage;
			value =	R_VLUE;	
			break;
		case SLAVE_REG_P01:
            shortv = DISS_Voltage;
			value =	(int)(DISS_Voltage*1000);	
			break;

		case SLAVE_REG_P02:
			value =	(int)(DISS_Current*1000);       /* ½«¼Ä´æÆ÷Öµ¶Á³ö */
			break;
		case SLAVE_REG_P03: 
			value =	(int)(DISS_POW_Voltage*100);
			break;

		case SLAVE_REG_P04:
			value =	(int)(DISS_POW_Current*1000);		/* ½«¼Ä´æÆ÷Öµ¶Á³ö */
			break;
		case SLAVE_REG_P05:
			IO_OFF();
            SET_Current_Laod = 0;
            usartocflag = 1; 
//            while(usartocflag == 1);
            value = (int)(oc_data*1000);
			break;
		case SLAVE_REG_P06:
			value = 0;							/* ½«¼Ä´æÆ÷Öµ¶Á³ö */
			break;
		case SLAVE_REG_P07:
			value =	0;							/* ½«¼Ä´æÆ÷Öµ¶Á³ö */
			break;
		case SLAVE_REG_P08:
			value =	0;	
			break;

		case SLAVE_REG_P09:
			value =	0;							/* ½«¼Ä´æÆ÷Öµ¶Á³ö */
			break;
		case SLAVE_REG_P10:
			value =	0;	
			break;

		case SLAVE_REG_P11:
			value =	(int)temp;							/* ½«¼Ä´æÆ÷Öµ¶Á³ö */
			break;
		case SLAVE_REG_P12:
			value =	0;	
			break;

		case SLAVE_REG_P13:
			value =	0;							/* ½«¼Ä´æÆ÷Öµ¶Á³ö */
			break;
		case SLAVE_REG_P14:
			value =	!flag_Load_CC;	
			break;

		case SLAVE_REG_P15:
			value =	load_v;							/* ½«¼Ä´æÆ÷Öµ¶Á³ö */
			break;
		case SLAVE_REG_P16:
			value =	load_c;	
			break;

		case SLAVE_REG_P17:
			value =	pow_v*10;							/* ½«¼Ä´æÆ÷Öµ¶Á³ö */
			break;
		case SLAVE_REG_P18:
			value =	pow_c;							/* ½«¼Ä´æÆ÷Öµ¶Á³ö */
			break;	
		default:
			return 0;
    }
	reg_value[0] = value >> 8;
	reg_value[1] = value;

	return 1;											/* ¶ÁÈ¡³É¹¦ */
}

/*
*********************************************************************************************************
*	º¯ Êý Ãû: MODS_WriteRegValue
*	¹¦ÄÜËµÃ÷: ¶ÁÈ¡±£³Ö¼Ä´æÆ÷µÄÖµ
*	ÐÎ    ²Î: reg_addr ¼Ä´æÆ÷µØÖ·
*			  reg_value ¼Ä´æÆ÷Öµ
*	·µ »Ø Öµ: 1±íÊ¾OK 0±íÊ¾´íÎó
*********************************************************************************************************
*/
static uint8_t MODS_WriteRegValue(uint16_t reg_addr, uint16_t reg_value)
{
	lock = 1;
	switch (reg_addr)							/* ÅÐ¶Ï¼Ä´æÆ÷µØÖ· */
	{	
		case SLAVE_REG_P00://è´Ÿè½½æ¨¡å¼
			if(reg_value == 0)
			{
				load_mode = 1;
                Write_LOAD();
				GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
				flag_Load_CC = 1;
			}else if(reg_value == 1){
				load_mode = 0;
                Write_LOAD();
				GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CV
				flag_Load_CC = 0;
			}
			break;
		case SLAVE_REG_P01://è´Ÿè½½ç”µåŽ‹
			load_v = reg_value;
			SET_Voltage_Laod = load_v;
			Write_Limits();
			break;
		
		case SLAVE_REG_P02://è´Ÿè½½ç”µæµ
			load_c = reg_value;
			SET_Current_Laod = load_c;
			Write_Limits();
			break;
		case SLAVE_REG_P03://è¾“å‡ºç”µåŽ‹
			pow_v = reg_value;
			SET_Voltage = pow_v;
			Write_Limits();
			break;

		case SLAVE_REG_P04://é™åˆ¶ç”µæµ
			pow_c = reg_value;
			SET_Current = pow_c;
			Write_Limits();
			break;
		case SLAVE_REG_P05://å……æ”¾ç”µè¾“å‡ºç”µåŽ‹
			opv1 = reg_value;
			SET_Voltage = opv1;
			Write_Limits();
			break;

		case SLAVE_REG_P06://å……æ”¾é™åˆ¶ç”µæµ
			opc1 = reg_value;
			SET_Current = opc1;
			Write_Limits();
			break;
		case SLAVE_REG_P07://å……ç”µæˆªæ­¢ç”µåŽ‹
			cov1 = reg_value;
			Write_Limits();
			break;
		case SLAVE_REG_P08://å……ç”µæˆªæ­¢ç”µæµ
			coc1 = reg_value;
			Write_Limits();
			break;
		case SLAVE_REG_P09:	//å……æ”¾ç”µè´Ÿè½½ç”µæµ
			cdc_dc = reg_value;
			SET_Current_Laod = cdc_dc;
			Write_Limits();
			break;
		case SLAVE_REG_P10:	//æ”¾ç”µæˆªæ­¢ç”µåŽ‹
			set_dc_cutoff_v = reg_value;
			Write_Limits();
			break;

		case SLAVE_REG_P11://å¾ªçŽ¯æ¬¡æ•°
			set_loop_count = reg_value;
			Write_Limits();
			break;
		case SLAVE_REG_P12:
			set_load_cutoffv = reg_value;
			Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
			break;

		case SLAVE_REG_P13:
			set_pow_cutoffc = reg_value;
			Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
			break;
		case SLAVE_REG_P14:
			break;

		case SLAVE_REG_P15:
			break;
		case SLAVE_REG_P16:
			break;

		case SLAVE_REG_P17:
			break;
		default:
			return 0;
	}

	return 1;
}

static uint8_t MODS_Load(uint16_t reg_addr, uint16_t reg_value)
{
	lock = 1;
	switch (reg_addr)							
	{	
		case SLAVE_REG_P00://å¼€å§‹åœæ­¢è´Ÿè½½
			if(reg_value == 1)//å¼€å§‹è´Ÿè½½
			{
				WM_DeleteWindow(hWinR);
				WM_DeleteWindow(hWinWind);
				WM_DeleteWindow(hWinG);
				WM_DeleteWindow(load_wind);
				WM_DeleteWindow(hWinsysinfo);
				WM_DeleteWindow(hWincdc);
				WM_DeleteWindow(hWinset);
				CreateWindow2();
				Delay_ms(500);
				t_onoff = 0;
				GPIO_ResetBits(GPIOC,GPIO_Pin_1);
				Delay_ms(500);
				GPIO_SetBits(GPIOC,GPIO_Pin_13);
				
				if(flag_Load_CC == 0)
				{
					GPIO_ResetBits(GPIOC,GPIO_Pin_13);
					c_rec = 1;									
				}
				Flag_Swtich_ON=1;
				GPIO_ResetBits(GPIOA,GPIO_Pin_15);
				
				mode_sw = mode_load;
				load_sw = load_on;
				rmtrig[0] = 1;
			}else if(reg_value == 4){//åœæ­¢è´Ÿè½½
				Flag_Swtich_ON=0;
				GPIO_SetBits(GPIOC,GPIO_Pin_13);
				GPIO_SetBits(GPIOA,GPIO_Pin_15);
				c_rec = 0;
				mode_sw = 0;
				load_sw = load_off;
				rmtrig[0] = 0;
			}
			break;
		case SLAVE_REG_P01://

			break;
		
		case SLAVE_REG_P02://

			break;
		case SLAVE_REG_P03://

			break;

		case SLAVE_REG_P04://

			break;
		case SLAVE_REG_P05://

			break;

		case SLAVE_REG_P06://

			break;
		case SLAVE_REG_P07://

			break;
		case SLAVE_REG_P08://

			break;
		case SLAVE_REG_P09:	//

			break;
		case SLAVE_REG_P10:	//

			break;

		case SLAVE_REG_P11://

			break;
		case SLAVE_REG_P12:
			break;

		case SLAVE_REG_P13:
			break;
		case SLAVE_REG_P14:
			break;

		case SLAVE_REG_P15:
			break;
		case SLAVE_REG_P16:
			break;

		case SLAVE_REG_P17:
			break;
		default:
			return 0;
	}

	return 1;
}

static uint8_t MODS_Pow(uint16_t reg_addr, uint16_t reg_value)
{
	lock = 1;
	switch (reg_addr)							
	{	
		case SLAVE_REG_P00://å¼€å§‹åœæ­¢ç”µæº
			if(reg_value == 1)//å¼€å§‹ç”µæº
			{
				WM_DeleteWindow(hWinR);
				WM_DeleteWindow(hWinWind);
				WM_DeleteWindow(hWinG);
				WM_DeleteWindow(load_wind);
				WM_DeleteWindow(hWinsysinfo);
				WM_DeleteWindow(hWincdc);
				WM_DeleteWindow(hWinset);
				CreateWindow();
				Delay_ms(500);
				GPIO_SetBits(GPIOA,GPIO_Pin_15);
				GPIO_ResetBits(GPIOC,GPIO_Pin_13);//Õ²ßªÖ§Ô´Ë¤Ô¶ÝŒÖ§Ç·
				GPIO_SetBits(GPIOC,GPIO_Pin_1);//Õ²ßªÖ§Ô´Ë¤Ô¶                           
				mode_sw = mode_pow;
				pow_sw = pow_on;
				rmtrig[1] = 1;
					
			}else if(reg_value == 4){//åœæ­¢ç”µæº
				GPIO_ResetBits(GPIOC,GPIO_Pin_1);//Ú˜Ò•Ö§Ô´Ë¤Ô¶
				Delay_ms(1000);
				GPIO_SetBits(GPIOC,GPIO_Pin_13);//Ú˜Ò•Ö§Ô´Ë¤Ô¶ÝŒÖ§Ç·
				mode_sw = 0;
				pow_sw = pow_off;
				rmtrig[1] = 0;
			}
			break;
		case SLAVE_REG_P01://

			break;
		
		case SLAVE_REG_P02://

			break;
		case SLAVE_REG_P03://

			break;

		case SLAVE_REG_P04://

			break;
		case SLAVE_REG_P05://

			break;

		case SLAVE_REG_P06://

			break;
		case SLAVE_REG_P07://

			break;
		case SLAVE_REG_P08://

			break;
		case SLAVE_REG_P09:	//

			break;
		case SLAVE_REG_P10:	//

			break;

		case SLAVE_REG_P11://

			break;
		case SLAVE_REG_P12:
			break;

		case SLAVE_REG_P13:
			break;
		case SLAVE_REG_P14:
			break;

		case SLAVE_REG_P15:
			break;
		case SLAVE_REG_P16:
			break;

		case SLAVE_REG_P17:
			break;
		default:
			return 0;
	}

	return 1;
}

static uint8_t MODS_CDC(uint16_t reg_addr, uint16_t reg_value)
{
	lock = 1;
	switch (reg_addr)							
	{	
		case SLAVE_REG_P00://å¼€å§‹åœæ­¢ç”µæº
			if(reg_value == 1)//å¼€å§‹ç”µæº
			{
				WM_DeleteWindow(hWinR);
				WM_DeleteWindow(hWinWind);
				WM_DeleteWindow(hWinG);
				WM_DeleteWindow(load_wind);
				WM_DeleteWindow(hWinsysinfo);
				WM_DeleteWindow(hWincdc);
				WM_DeleteWindow(hWinset);				
				CreateCDC(); 
				Delay_ms(500);
				GPIO_ResetBits(GPIOC,GPIO_Pin_1);//Ú˜Ò•Ö§Ô´Ë¤Ô¶
				Delay_ms(500);
				GPIO_SetBits(GPIOC,GPIO_Pin_13);//Ú˜Ò•Ö§Ô´Ë¤Ô¶ÝŒÖ§Æ
				SET_Voltage = opv1;
			    SET_Current = opc1;
			    cutoff_flag = 0;
//                           Mode_SW_CONT(0x03);
			   
			    charge_step = 1;
			    GPIO_ResetBits(GPIOC,GPIO_Pin_13);//Õ²ßªÖ§Ô´Ë¤Ô¶ÝŒÖ§Ç·
			    Delay_ms(500);
			    GPIO_SetBits(GPIOC,GPIO_Pin_1);//Õ²ßªÖ§Ô´Ë¤Ô¶
			    mode_sw = mode_pow;
			    cdc_sw = cdc_on;
				rmtrig[2] = 1;
				sendmodeflag = 1;
			}else if(reg_value == 4){//åœæ­¢ç”µæº
				GPIO_ResetBits(GPIOC,GPIO_Pin_1);//Ú˜Ò•Ö§Ô´Ë¤Ô¶
				Delay_ms(500);
			   GPIO_SetBits(GPIOC,GPIO_Pin_13);//Ú˜Ò•Ö§Ô´Ë¤Ô¶ÝŒÖ§Ç·
			   GPIO_SetBits(GPIOA,GPIO_Pin_15);//Ö§Ø“ØºÕ˜OFF
			   cdc_sw = cdc_off;
			   paused = 0;
			   mode_sw = 0;
			   rmtrig[2] = 0;
			}
			break;
		case SLAVE_REG_P01://

			break;
		
		case SLAVE_REG_P02://

			break;
		case SLAVE_REG_P03://

			break;

		case SLAVE_REG_P04://

			break;
		case SLAVE_REG_P05://

			break;

		case SLAVE_REG_P06://

			break;
		case SLAVE_REG_P07://

			break;
		case SLAVE_REG_P08://

			break;
		case SLAVE_REG_P09:	//

			break;
		case SLAVE_REG_P10:	//

			break;

		case SLAVE_REG_P11://

			break;
		case SLAVE_REG_P12:
			break;

		case SLAVE_REG_P13:
			break;
		case SLAVE_REG_P14:
			break;

		case SLAVE_REG_P15:
			break;
		case SLAVE_REG_P16:
			break;

		case SLAVE_REG_P17:
			break;
		default:
			return 0;
	}

	return 1;
}

static void MODS_03H(void)
{
    uint16_t reg;
	uint16_t num;
	uint16_t i;
	uint8_t reg_value[64];

    
    g_tModS.RspCode = RSP_OK;

	if (g_tModS.RxCount != 8)								/* 03HÃüÁî±ØÐëÊÇ8¸ö×Ö½Ú */
	{
		g_tModS.RspCode = RSP_ERR_VALUE;					/* Êý¾ÝÖµÓò´íÎó */
		goto err_ret;
	}

	reg = BEBufToUint16(&g_tModS.RxBuf[2]); 				/* ¼Ä´æÆ÷ºÅ */
	num = BEBufToUint16(&g_tModS.RxBuf[4]);					/* ¼Ä´æÆ÷¸öÊý */
	if (num > sizeof(reg_value) / 2)
	{
		g_tModS.RspCode = RSP_ERR_VALUE;					/* Êý¾ÝÖµÓò´íÎó */
		goto err_ret;
	}

	for (i = 0; i < num; i++)
	{
		if (MODS_ReadRegValue(reg, &reg_value[2 * i]) == 0)	/* ¶Á³ö¼Ä´æÆ÷Öµ·ÅÈëreg_value */
		{
			g_tModS.RspCode = RSP_ERR_REG_ADDR;				/* ¼Ä´æÆ÷µØÖ·´íÎó */
			break;
		}
		reg++;
	}

err_ret:
	if (g_tModS.RspCode == RSP_OK)							/* ÕýÈ·Ó¦´ð */
	{
		g_tModS.TxCount = 0;
		g_tModS.TxBuf[g_tModS.TxCount++] = g_tModS.RxBuf[0];
		g_tModS.TxBuf[g_tModS.TxCount++] = g_tModS.RxBuf[1];
		g_tModS.TxBuf[g_tModS.TxCount++] = num * 2;			/* ·µ»Ø×Ö½ÚÊý */

		for (i = 0; i < num; i++)
		{
			g_tModS.TxBuf[g_tModS.TxCount++] = reg_value[2*i];
			g_tModS.TxBuf[g_tModS.TxCount++] = reg_value[2*i+1];
		}
//         if(usartocflag == 0)
//         {
//             MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);	/* ·¢ËÍÕýÈ·Ó¦´ð */
//         }
	}
	else
	{
//		MODS_SendAckErr(g_tModS.RspCode);					/* ·¢ËÍ´íÎóÓ¦´ð */
	}
    
}


void MODS_SendWithCRC(uint8_t *_pBuf, uint8_t _ucLen)
{
	uint16_t crc;
	uint8_t i;
	uint8_t buf[S_TX_BUF_SIZE];
	memcpy(buf, _pBuf, _ucLen);
	crc = CRC16(_pBuf, _ucLen);
	buf[_ucLen++] = crc >> 8;
	buf[_ucLen++] = crc;
//Í¨¹ý485·¢Êý¾Ý
//	RS485_SendBuf(buf, _ucLen);
	for(i=0;i<_ucLen+2;i++)
	{
		Usart_SendByte(USART1,buf[i]);
	}
//	uart1SendChars(buf, _ucLen);
	
// #if 1									/* ´Ë²¿·ÖÎªÁË´®¿Ú´òÓ¡½á¹û,Êµ¼ÊÔËÓÃÖÐ¿É²»Òª */
// 	g_tPrint.Txlen = _ucLen;
// 	memcpy(g_tPrint.TxBuf, buf, _ucLen);
// #endif
}

static void MODS_06H(void)
{
    uint16_t reg;
	uint16_t value;

	g_tModS.RspCode = RSP_OK;

	if (g_tModS.RxCount != 8)
	{
		g_tModS.RspCode = RSP_ERR_VALUE;		/* Êý¾ÝÖµÓò´íÎó */
		goto err_ret;
	}

	reg = BEBufToUint16(&g_tModS.RxBuf[2]); 	/* ¼Ä´æÆ÷ºÅ */
	value = BEBufToUint16(&g_tModS.RxBuf[4]);	/* ¼Ä´æÆ÷Öµ */
    
//    if(reg == 0x0E)
//    {
//        if(value == 00)
//        {
//            GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
//            flag_Load_CC = 1;
//        }else if(value == 01){
//            GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CV
//            flag_Load_CC = 0;
//        }
//    }
 	if (MODS_WriteRegValue(reg, value) == 1)	/* ¸Ãº¯Êý»á°ÑÐ´ÈëµÄÖµ´æÈë¼Ä´æÆ÷ */
 	{
 		;
 	}
 	else
 	{
 		g_tModS.RspCode = RSP_ERR_REG_ADDR;		/* ¼Ä´æÆ÷µØÖ·´íÎó */
 	}

err_ret:
	if (g_tModS.RspCode == RSP_OK)				/* ÕýÈ·Ó¦´ð */
	{
		
	}
	else
	{
		MODS_SendAckErr(g_tModS.RspCode);		/* ¸æËßÖ÷»úÃüÁî´íÎó */
	}
}

static void MODS_50H(void)
{
    uint16_t reg;
	uint16_t value;

	g_tModS.RspCode = RSP_OK;

	if (g_tModS.RxCount != 8)
	{
		g_tModS.RspCode = RSP_ERR_VALUE;		
		goto err_ret;
	}

	reg = BEBufToUint16(&g_tModS.RxBuf[2]);
	value = BEBufToUint16(&g_tModS.RxBuf[4]);
    

 	if (MODS_Load(reg, value) == 1)
 	{
 		;
 	}
 	else
 	{
 		g_tModS.RspCode = RSP_ERR_REG_ADDR;
 	}

err_ret:
	if (g_tModS.RspCode == RSP_OK)
	{
		MODS_SendAckOk();
	}
	else
	{
		MODS_SendAckErr(g_tModS.RspCode);
	}
}

static void MODS_51H(void)
{
    uint16_t reg;
	uint16_t value;

	g_tModS.RspCode = RSP_OK;

	if (g_tModS.RxCount != 8)
	{
		g_tModS.RspCode = RSP_ERR_VALUE;		
		goto err_ret;
	}

	reg = BEBufToUint16(&g_tModS.RxBuf[2]);
	value = BEBufToUint16(&g_tModS.RxBuf[4]);
    

 	if (MODS_Pow(reg, value) == 1)
 	{
 		;
 	}
 	else
 	{
 		g_tModS.RspCode = RSP_ERR_REG_ADDR;
 	}

err_ret:
	if (g_tModS.RspCode == RSP_OK)
	{
		MODS_SendAckOk();
	}
	else
	{
		MODS_SendAckErr(g_tModS.RspCode);
	}
}

static void MODS_52H(void)
{
    uint16_t reg;
	uint16_t value;

	g_tModS.RspCode = RSP_OK;

	if (g_tModS.RxCount != 8)
	{
		g_tModS.RspCode = RSP_ERR_VALUE;		
		goto err_ret;
	}

	reg = BEBufToUint16(&g_tModS.RxBuf[2]);
	value = BEBufToUint16(&g_tModS.RxBuf[4]);
    

 	if (MODS_CDC(reg, value) == 1)
 	{
		
 	}
 	else
 	{
 		g_tModS.RspCode = RSP_ERR_REG_ADDR;
 	}

err_ret:
	if (g_tModS.RspCode == RSP_OK)
	{
		MODS_SendAckOk();
	}
	else
	{
		MODS_SendAckErr(g_tModS.RspCode);
	}
}

uint16_t CRC16(uint8_t *_pBuf, uint16_t _usLen)
{    
    uint8_t ucCRCHi = 0xFF; /* ¸ßCRC×Ö½Ú³õÊ¼»¯ */
	uint8_t ucCRCLo = 0xFF; /* µÍCRC ×Ö½Ú³õÊ¼»¯ */
	uint16_t usIndex;  /* CRCÑ­»·ÖÐµÄË÷Òý */

    while (_usLen--)
    {
		usIndex = ucCRCHi ^ *_pBuf++; /* ¼ÆËãCRC */
		ucCRCHi = ucCRCLo ^ s_CRCHi[usIndex];
		ucCRCLo = s_CRCLo[usIndex];
    }
    return ((uint16_t)ucCRCHi << 8 | ucCRCLo);
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
