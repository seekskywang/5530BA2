/******************************************************************/
/* ???TIM3 PWM                                                */
/* ßπ?®≤                                                        */
/* ??®≤????200HZ ????®≤60.9% ????®≤30.9%?PWM      */
/* ??®≤n?                                                    */
/* j???®≤QQ:363116119                                        */
/******************************************************************/
#include "my_register.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "tim6.h"
#include "MainTask.h"
#include "ssd1963.h"
#include "bsp_SysTick.h"
/*****************************************************************/
/*****************************************************************/

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

void SendToPC(u8 mode);
vu32 battery_c;
float bc_raw;
float cbc_raw;
float c_sum;
extern vu8 pow_sw;
extern vu8 cdc_sw;
extern vu8 load_sw;
extern vu8 oct_sw; 
extern vu8 oc_test;
extern vu8 c_rec;
extern vu8 second ;
extern vu8 minute;
extern vu8 hour;
extern vu8 second1;
extern vu8 minute1;
extern vu8 hour1;
extern u8 sendmodeflag;
vu8 resetflag;
vu8 resdone;
float watch;
extern float crec1,crec2;
extern vu16 ocImon1,ocImon2;
extern u8 g_mods_timeout;
extern struct MODS_T g_tModS;
u32 Tick_10ms=0;
u32 OldTick;
u8 usartocflag = 0;//‰∏ä‰ΩçÊú∫ËøáÊµÅÊ†áÂøó‰Ωç
u8 usartshortflag = 0;//‰∏ä‰ΩçÊú∫Áü≠Ë∑ØÊ†áÂøó‰Ωç
float shortv;
extern vu16 short_time;
extern vu8 rpow;
extern vu8 short_finish;
extern vu8 short_flag;
extern float v;
extern vu8 oc_mode;
extern vu8 test_start;
extern float static_pc;
extern float static_lv;
extern vu8 staticcdc;
extern vu8 step;
extern vu16 sendload;
extern vu8 con_flag;
extern vu8 ocf;
vu8 sendpcflag;
u8 sendmodepow[6] = {0x01,0x53,0x00,0x00,0x00,0x01};
u8 sendmodeload[6] = {0x01,0x53,0x00,0x00,0x00,0x02};
u8 sendmodestop[6] = {0x01,0x52,0x00,0x00,0x00,0x04};
//????? 3 ?????
//arr®≤?????c psc®≤??????
//???????????:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=??????®∫,?¶À:Mhz
//?o???°¶??? 3!
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); //®¥?? TIM3 ??
    TIM_TimeBaseInitStructure.TIM_Period = arr; //??????
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //?????
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //ß”?????
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);// ®≤?????? TIM3
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //?????? 3 ?ß‰??
    NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //??? 3 ??
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //????? 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //ßæ???? 3
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);// ®π??? NVIC
    TIM_Cmd(TIM4,ENABLE); //Y????? 3
}
//??? 3 ??????
void TIM4_IRQHandler(void)
{
    static vu16 resetcount;
    static vu8 read1963;
    static vu16 scancount;
    static vu16 uocount;
    static vu16 powcount;
    static vu16 powflag;
    static vu16 finishflag;
//    static float crec1,crec2;
    u8 crec[6];
    u8 *csend;
    static u8 *sendbuf;
    u8 sendlen;
    static u16 recrc;
    static u16 scrc;
	static vu8 staticloadflag,staticpowflag;
    u8 i;
//     static float crec1,crec2;
    
    if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //????
    {
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //«Â≥˝÷–∂œ±Í÷æŒª
		
        IWDG_ReloadCounter();
        if(page_sw != face_starter)
        {
             if(resetflag == 1)
             {
                 if(resetcount == 3000)
                 {
//                     sLCD_GPIO_Config();
                     sLCD_Init();
//                     sLCD_WR_REG(0xf1);
                     GUI_Init();
                     if(page_sw == face_menu)
                     {
                         ResetPow();
                     }else if(page_sw == face_cdc){
                         ResetCDC();
                     }else if(page_sw == face_r){
                         ResetR();
                     }else if(page_sw == face_load){
                         ResetLoad();
                     }else if(page_sw == face_graph){
                         ResetG();
                     }else if(page_sw == face_set){
                         ResetSET();
                     }
//                     resdone = 1;
//                     resetflag = 0;
                     resetcount = 0;
                 }else{
                     resetcount++;
                 }                
             }
         }
         if(page_sw == face_r)
		 {
			 if(step == 1)
			 {
//				 C_SW(0);
				if(powcount < 10000)
				{
					SET_Current_Laod = set_static_lc;
					flag_Load_CC = 1;
					GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
					GPIO_ResetBits(GPIOA,GPIO_Pin_15);//÷ßÿìÿ∫’òOn
					static_lv = DISS_Voltage;
					powcount++;																		
				}else{
					powcount = 0;
					C_SW(0);
					IO_OFF();
					
					step = 2;
				}
			 }else if(step == 2){
				if(powcount < 10000)
				{
					SET_Voltage = set_static_pv;
					SET_Current = set_static_pc;
					GPIO_SetBits(GPIOA,GPIO_Pin_15);//÷ßÿìÿ∫’òOFF
					GPIO_ResetBits(GPIOC,GPIO_Pin_13);//’≤ﬂ™÷ß‘¥À§‘∂›å÷ß«∑
					GPIO_SetBits(GPIOC,GPIO_Pin_1);//’≤ﬂ™÷ß‘¥À§‘∂
					powcount++;
					static_pc = DISS_POW_Current;
				}else{
					GPIO_ResetBits(GPIOC,GPIO_Pin_1);//πÿ±’µÁ‘¥ ‰≥ˆ
					Delay_ms(500);
				    GPIO_SetBits(GPIOC,GPIO_Pin_13);//πÿ±’µÁ‘¥ ‰≥ˆºÃµÁ∆˜				
					powcount = 0;
					step = 3;
//					IO_OFF();		
					
				}
			 }else if(step == 3){
				if(powcount < 5000)
				{
//					C_SW(1);
					powcount++;
				}else{
					
					powcount = 0;	
//					sendload = 200;				
					SET_Current_Laod = set_init_c;
					GPIO_ResetBits(GPIOA,GPIO_Pin_15);//ÊâìÂºÄË¥üËΩΩ+
					ocf = 1;
					step = 4;
				}
			 }else if(step == 4){
				 stepcount ++;
				 OC_CHECK();
				
				if(stepcount == steptime*10)
				{
					OC_ADD();
					stepcount = 0;
				}
			 }else if(step == 5){
				if(powcount < 2000)
				{
					SET_Voltage = (int)v*100+200;
					SET_Current = 1000;
					GPIO_SetBits(GPIOA,GPIO_Pin_15);//÷ßÿìÿ∫’òOFF
					GPIO_ResetBits(GPIOC,GPIO_Pin_13);//’≤ﬂ™÷ß‘¥À§‘∂›å÷ß«∑
					GPIO_SetBits(GPIOC,GPIO_Pin_1);//’≤ﬂ™÷ß‘¥À§‘∂
					powcount++;
				}else{
					GPIO_ResetBits(GPIOC,GPIO_Pin_1);//πÿ±’µÁ‘¥ ‰≥ˆ
					Delay_ms(500);
				    GPIO_SetBits(GPIOC,GPIO_Pin_13);//πÿ±’µÁ‘¥ ‰≥ˆºÃµÁ∆˜				
					powcount = 0;
					step = 6; 
//					IO_OFF();
				}
			 }else if(step == 6){
//				if(oc_mode == 0)
//				{
//					SET_Current_Laod = (int)(oc_data*1000)+8000; 
//					flag_Load_CC = 1;                              
//					GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
//					GPIO_ResetBits(GPIOA,GPIO_Pin_15);//÷ßÿìÿ∫’òOn
//				}else if(oc_mode == 1){
					GPIO_ResetBits(GPIOC,GPIO_Pin_13);
					SET_Voltage_Laod = 0;
					GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CV
					flag_Load_CC = 0;
					GPIO_ResetBits(GPIOA,GPIO_Pin_15);//÷ßÿìÿ∫’òOn
//				}
				if(((v - DISS_Voltage) > v*0.5)/* || (DISS_Current < 0.05)*/)
				{
					IO_OFF();
					if(oc_mode == 0)
					{
						flag_Load_CC = 1;                              
						GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
					}
					step = 7;
				}else{
					short_time++;                
				}
			 }else if(step == 7){
				 if(powcount < 5000)
				{
					SET_Voltage =(int)v*100+300;
					SET_Current = 1000;
					GPIO_ResetBits(GPIOC,GPIO_Pin_13);//’≤ﬂ™÷ß‘¥À§‘∂›å÷ß«∑
					GPIO_SetBits(GPIOC,GPIO_Pin_1);//’≤ﬂ™÷ß‘¥À§‘∂
					powcount++;
	//                 shortv = DISS_Voltage;
				}else{
					GPIO_ResetBits(GPIOC,GPIO_Pin_1);//πÿ±’µÁ‘¥ ‰≥ˆ
					Delay_ms(500);
				    GPIO_SetBits(GPIOC,GPIO_Pin_13);//πÿ±’µÁ‘¥ ‰≥ˆºÃµÁ∆
					powcount = 0;
					step = 0;
					con_flag = 0;
					SET_Current_Laod = set_init_c;
					C_SW(0);
//					GPIO_ResetBits(GPIOA,GPIO_Pin_11);//µÁ¡˜«–ªªŒ™µÕµµ
//					Delay_ms(500);
//					IO_OFF();                
				}
			 }else if(step == 8){
				 powcount++;
				 if(powcount == 5000)
				 {
//					 GPIO_SetBits(GPIOA,GPIO_Pin_11);//µÁ¡˜«–ªªŒ™∏ﬂµµ
				 }else if(powcount == 10000){
					 step = 0;
					 powcount = 0;
				 }
				 
			 }else if(step == 0 && powcount == 0)
			 {
				 if(dropflag == 0){
					 SET_Current_Laod = set_init_c;
					 rpow= 0;
					 powcount = 0;
				 }
//				 IO_OFF();
			 }
		}
        
		
        if(usartocflag == 1)
        {
			
            if(flag_Load_CC == 1)
            {   
//				load_sw = load_on;
                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
				flag_Load_CC = 1;
                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//µÁ◊”∏∫‘ÿOn
            }else if(flag_Load_CC == 0){
				GPIO_ResetBits(GPIOC,GPIO_Pin_13);
                SET_Voltage_Laod = 0;
                GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CV
                flag_Load_CC = 0;
                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//µÁ◊”∏∫‘ÿOn
            }
            crec1 = DISS_Current;  
			if(crec1 > crec2)
			{
				crec2 = crec1;
			}
            if(v - DISS_Voltage > v*0.9)
            {     
                oc_data = crec2;
                g_tModS.TxBuf[13] = (int)(oc_data*1000)>>8;
                g_tModS.TxBuf[14] = (int)(oc_data*1000);
                SET_Current_Laod = set_init_c;
                GPIO_SetBits(GPIOA,GPIO_Pin_15);//ÂÖ≥Èó≠Ë¥üËΩΩ 
//                MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);
                t_onoff = 0;
                usartocflag = 0;
                crec1 = 0;
                crec2 = 0;
                powflag = 1;
                
            }else{
                if(flag_Load_CC == 1)
                {
                    if(uocount == 20)
                    {
                        SET_Current_Laod = SET_Current_Laod + 10;
                        uocount = 0;
                    }else{
                        uocount++;
                    }
                }                    
            }
        }
        if(powflag == 1)
        {
            if(powcount < 2000)
            {
                SET_Voltage =v*1000+200;
                SET_Current = 1000;
                GPIO_SetBits(GPIOA,GPIO_Pin_15);//µÁ◊”∏∫‘ÿOFF
                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//¥Úø™µÁ‘¥ ‰≥ˆºÃµÁ∆˜
                GPIO_SetBits(GPIOC,GPIO_Pin_1);//¥Úø™µÁ‘¥ ‰≥ˆ
                powcount++;
//                 shortv = DISS_Voltage;
            }else{
                powcount = 0;
                powflag = 0;
                GPIO_ResetBits(GPIOC,GPIO_Pin_1);//πÿ±’µÁ‘¥ ‰≥ˆ
				Delay_ms(500);
                GPIO_SetBits(GPIOC,GPIO_Pin_13);//πÿ±’µÁ‘¥ ‰≥ˆºÃµÁ∆˜ 
                usartshortflag = 1;
                
            }
        }
        if(usartshortflag == 1)
        {
//            if(flag_Load_CC == 1)
//            {
//                SET_Current_Laod = (int)(oc_data*1000)+8000; 
//                flag_Load_CC = 1;                              
//				GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
//				GPIO_ResetBits(GPIOA,GPIO_Pin_15);//÷ßÿìÿ∫’òOn
//            }else if(flag_Load_CC == 0){
                SET_Voltage_Laod = 0;
                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CV
                flag_Load_CC = 0;
                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//µÁ◊”∏∫‘ÿOn
//            }
            if(((shortv - DISS_Voltage) > shortv*0.6)/* || (DISS_Current < 0.05)*/)
            {
                IO_OFF();
                usartshortflag = 0;
				flag_Load_CC = 1;                              
				GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC				
                g_tModS.TxBuf[15] = (short_time/10)>>8;
                g_tModS.TxBuf[16] = (short_time/10);
                MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);
                finishflag=1;
                short_time = 0;
            }else{
                short_time++;                
            }
        }
        if(finishflag == 1)
        {
            if(powcount < 1000)
            {
                SET_Voltage =3000;
                SET_Current = 1000;
                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//¥Úø™µÁ‘¥ ‰≥ˆºÃµÁ∆˜
                GPIO_SetBits(GPIOC,GPIO_Pin_1);//¥Úø™µÁ‘¥ ‰≥ˆ
                powcount++;
//                 shortv = DISS_Voltage;
            }else{
                SET_Current_Laod = 1000;
                powcount = 0;
                finishflag = 0;
                IO_OFF(); 
				C_SW(0);
            }
        }
    }    
}

//void TIM6_Config(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	/* TIM3 ??? ---------------------------------------------------
//   TIM3 ????(TIM3CLK) ??? APB2 ?? (PCLK2)    
//    => TIM3CLK = PCLK2 = SystemCoreClock
//   TIM3CLK = SystemCoreClock, Prescaler = 0, TIM3 counter clock = SystemCoreClock
//   SystemCoreClock ?48 MHz */
//  /* TIM16 ???? */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
//	
//  /* Time ??????*/
//  TIM_TimeBaseStructure.TIM_Prescaler = 4800-1;//?????
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  /* Time ????????????*/
//  TIM_TimeBaseStructure.TIM_Period = 5000;
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
////  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

//  TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
//	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);//??????ß‰??
//	TIM_SetAutoreload(TIM6, 0xFF);//??PWM??®∫
//	TIM6_NVIC_Config();
//  /* TIM3 ?????*/
//  TIM_Cmd(TIM6, ENABLE);
//}
///***********************************************************************/
//static void TIM6_NVIC_Config(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure; 
//	
//	/* Enable the USART1 Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;	 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}
/*****************************************************************/
/*****************************************************************/
void TIM6_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/* TIM3 µƒ≈‰÷√ ---------------------------------------------------
   TIM3  ‰»Î ±÷”(TIM3CLK) …Ë÷√Œ™ APB2  ±÷” (PCLK2)    
    => TIM3CLK = PCLK2 = SystemCoreClock
   TIM3CLK = SystemCoreClock, Prescaler = 0, TIM3 counter clock = SystemCoreClock
   SystemCoreClock Œ™48 MHz */
  /* TIM16  ±÷” πƒ‹ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
  /* Time ∂® ±ª˘¥°…Ë÷√*/
  TIM_TimeBaseStructure.TIM_Prescaler = 2;// ±÷”‘§∑÷∆µ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  /* Time ∂® ±…Ë÷√Œ™…œ…˝—ÿº∆À„ƒ£ Ω*/
  TIM_TimeBaseStructure.TIM_Period = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);//ø™∆Ù∂® ±∆˜∏¸–¬÷–∂œ
	TIM_SetAutoreload(TIM6, 0xFF);//…Ë÷√PWM∑÷±Ê¬ 
	TIM6_NVIC_Config();
  /* TIM3 º∆À„∆˜ πƒ‹*/
  TIM_Cmd(TIM6, ENABLE);
}
/***********************************************************************/
static void TIM6_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
//????? 3 ?????
//arr®≤?????c psc®≤??????
//???????????:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=??????®∫,?¶À:Mhz
//?o???°¶??? 3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //®¥?? TIM3 ??
    TIM_TimeBaseInitStructure.TIM_Period = arr; //??????
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //?????
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //ß”?????
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);// ®≤?????? TIM3
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //?????? 3 ?ß‰??
    NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //??? 3 ??
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //????? 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //ßæ???? 3
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);// ®π??? NVIC
    TIM_Cmd(TIM3,ENABLE); //Y????? 3
}
//??? 3 ??????
void TIM3_IRQHandler(void)
{
    static vu8 calert = 0;
    static vu16 resetcount;
    static vu8 read1963,i;
    static vu16 scancount;
    static vu32 ctime,dctime;

    
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //????
    {
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //??????¶À
		
//         if(page_sw != face_starter)
//         {
//              if(resetflag == 1)
//              {
//                  if(resetcount == 1)
//                  {
//                      LCD_Initializtion();
//                      sLCD_WR_REG(0xf1);
//                      GUI_Init();
//                      if(page_sw == face_menu)
//                      {
//                          ResetPow();
//                      }else if(page_sw == face_cdc){
//                          ResetCDC();
//                      }else if(page_sw == face_r){
//                          ResetR();
//                      }else if(page_sw == face_load){
//                          ResetLoad();
//                      }else if(page_sw == face_graph){
//                          ResetG();
//                      }else if(page_sw == face_set){
//                          ResetSET();
//                      }
//                      resdone = 1;
// //                     resetflag = 0;
//                      resetcount = 0;
//                  }else{
//                      resetcount++;
//                  }                
//              }
//          }
        switch(page_sw)
        {
            case face_menu:
            {
                if(pow_sw == pow_on)
                {
                    bc_raw += DISS_POW_Current * 1000 * 1/3600;
					if(rmtrig[1] == 1)
					{
						SendToPC(1);
					}
                }else{
                    bc_raw = 0;
                }
            }break;
            case face_cdc:
            {
                if(mode_sw == mode_pow && cdc_sw == cdc_on)
                {
					if(sendmodeflag == 1)
					{
						for(i=0;i<3;i++)
						{
							MODS_SendWithCRC(sendmodepow,6);
							Delay_ms(50);
						}
						sendmodeflag = 0;
					}
                    ctime++;
                    second = ctime%60;//Áßí
                    minute = (ctime/60)%60;//ÂàÜ
                    hour   = ctime/3600;//Êó∂
                    cbc_raw += DISS_POW_Current * 1000 * 1/3600;
                    bc_raw = 0;
					if(rmtrig[2] == 1)
					{
						SendToPC(2);
					}
//                    bc_raw += DISS_POW_Current * 1000 * 1/3600;
                }else if(mode_sw == mode_load && cdc_sw == cdc_on){
					if(sendmodeflag == 1)
					{
						for(i=0;i<3;i++)
						{
							MODS_SendWithCRC(sendmodeload,6);
							Delay_ms(50);
							
						}
						sendmodeflag = 0;
					}
                    dctime++;
                    second1 = dctime%60;//Áßí
                    minute1 = (dctime/60)%60;//ÂàÜ
                    hour1   = dctime/3600;//Êó∂
                    bc_raw += DISS_Current * 1000 * 1/3600;
//                    c_sum += DISS_Current * 1000 * 1/3600;
                    cbc_raw = 0;
					if(rmtrig[2] == 1)
					{
						SendToPC(2);
					}
                }else if(cdc_sw == cdc_off){
                    bc_raw = 0;
                    cbc_raw = 0;
                    c_sum = 0;
                    ctime=0;
                    dctime=0;
					if(sendmodeflag == 1)
					{
						for(i=0;i<3;i++)
						{
							if(rmtrig[2] == 1)
							{
//								SendToPC(2);
							}
							Delay_ms(50);
							MODS_SendWithCRC(sendmodestop,6);
							Delay_ms(50);
						}
						sendmodeflag = 0;
					}
                }
            }break;
            case face_load:
            {
                if(load_sw == load_on)
                {
                    if(alert_flag == 1)
                    {
                        calert ++;
                        if(calert == 9)
                        {
                            t_onoff = 0;
                            GPIO_SetBits(GPIOA,GPIO_Pin_15);//????OFF
                            mode_sw = 0;
                            load_sw = load_off;
                            calert = 0;                                
                        }
                    }
                    bc_raw += DISS_Current * 1000 * 1/3600;
					if(rmtrig[0] == 1)
					{
						SendToPC(0);
					}
                }else{
                    bc_raw = 0;
                }
            }break;
            case face_graph:
            {
                if(mode_sw == mode_pow)
                {
                    if(pow_sw == pow_on)
                    {
                        bc_raw += DISS_POW_Current * 1000 * 1/3600;
                    }else if(mode_sw == mode_pow && cdc_sw == cdc_on)
                    {
                        bc_raw += DISS_POW_Current * 1000 * 1/3600;
                    }
                    else{
                        bc_raw = 0;
                    }
                }               
                
                if(mode_sw == mode_load)
                {
                    if(load_sw == load_on)
                    {
                        bc_raw += DISS_Current * 1000 * 1/3600;
                    }else{
                        bc_raw = 0;
                    }
                }
            }break;
            case face_r:
            {
                if(oct_sw == oct_on)
                {
                    if(alert_flag == 1)
                    {
                        calert ++;
                        if(calert == 3)
                        {
                            ocstop = 1;
                            calert = 0;
                        }
                    }
                }
            }break;
        }
//         GPIO_ResetBits(GPIOD,GPIO_Pin_12);
//         TM1650_SET_LED(0x48,0x71);
//         TM1650_SET_LED(0x68,0xF2);//PASS?
    }    
    
}

void TIM5_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE); //√ô π≈ú TIM3  ±◊ì
    TIM_TimeBaseInitStructure.TIM_Period = arr; //ÿî÷Ø◊ò◊∞’ò÷µ
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //÷® ±«∑ÿñ∆µ
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //–≤ è›ÜÀΩƒ£ Ω
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);// √ö‘µ º€Ø÷® ±«∑ TIM3
    TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //√õ’ä—≠÷® ±«∑ 3 Ÿº—Ç◊ê◊è
    NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //÷® ±«∑ 3 ◊ê◊è
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //»Ä’º‘Ö–à‹∂ 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //–¨”¶‘Ö–à‹∂ 3
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);// √ú‘µ º€Ø NVIC
    TIM_Cmd(TIM5,ENABLE); //√ù π≈ú÷® ±«∑ 3
}


void TIM5_IRQHandler(void)
{
    
    if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //”ß‘∂◊ê◊è
    {
        TIM_ClearITPendingBit(TIM5,TIM_IT_Update); //Ê∏ÖÈô§‰∏≠Êñ≠Ê†áÂøó‰Ω?
        Tick_10ms ++;
        MODS_Poll();
    }
}

void SendToPC(u8 mode)
{
	uint8_t vccbuf[13];
	
	vccbuf[0] = 0x01;
	vccbuf[2] = 0x0A;
	if(mode == 0)
	{
		vccbuf[1] = 0x50;
		
		vccbuf[3] = (vu16)(DISS_Voltage*1000)>>8;
		vccbuf[4] = (vu16)(DISS_Voltage*1000);
		
		vccbuf[5] = (vu16)(DISS_Current*1000)>>8;
		vccbuf[6] = (vu16)(DISS_Current*1000);
		
		vccbuf[7] = battery_c>>24;
		vccbuf[8] = battery_c>>16;
		vccbuf[9] = battery_c>>8;
		vccbuf[10] = battery_c;
		vccbuf[11] = Temperature>>8;
		vccbuf[12] = (vu8)Temperature;
	}else if(mode == 1){
		vccbuf[1] = 0x51;
		
		vccbuf[3] = (vu16)(DISS_Voltage*1000)>>8;
		vccbuf[4] = (vu16)(DISS_Voltage*1000);
		
		vccbuf[5] = (vu16)(DISS_POW_Current*1000)>>8;
		vccbuf[6] = (vu16)(DISS_POW_Current*1000);
		
		vccbuf[7] = battery_c>>24;
		vccbuf[8] = battery_c>>16;
		vccbuf[9] = battery_c>>8;
		vccbuf[10] = battery_c;
		vccbuf[11] = Temperature>>8;
		vccbuf[12] = (vu8)Temperature;
	}else if(mode == 2){
		vccbuf[1] = 0x52;
		
		vccbuf[3] = (vu16)(DISS_Voltage*1000)>>8;
		vccbuf[4] = (vu16)(DISS_Voltage*1000);
		if(mode_sw == mode_pow)
		{
			vccbuf[5] = (vu16)(DISS_POW_Current*1000)>>8;
			vccbuf[6] = (vu16)(DISS_POW_Current*1000);
		}else if(mode_sw == mode_load){
			vccbuf[5] = (vu16)(DISS_Current*1000)>>8;
			vccbuf[6] = (vu16)(DISS_Current*1000);
		}
		
		vccbuf[7] = battery_c>>24;
		vccbuf[8] = battery_c>>16;
		vccbuf[9] = battery_c>>8;
		vccbuf[10] = battery_c;
		vccbuf[11] = Temperature>>8;
		vccbuf[12] = (vu8)Temperature;
	}
	MODS_SendWithCRC(vccbuf, 13);
}

void MODS_Poll(void)
{
	uint16_t addr;
	static uint16_t crc1;
    static u32 testi;
	/* Ë∂ÖËøá3.5‰∏™Â≠óÁ¨¶Êó∂Èó¥ÂêéÊâßË°åMODH_RxTimeOut()ÂáΩÊï∞„ÄÇÂÖ®Â±ÄÂèòÈáè g_rtu_timeout = 1; ÈÄöÁü•‰∏ªÁ®ãÂ∫èÂºÄÂßãËß£Á†?*/
//	if (g_mods_timeout == 0)	
//	{
//		return;								/* Ê≤°ÊúâË∂ÖÊó∂ÔºåÁªßÁª≠Êé•Êî∂„ÄÇ‰∏çË¶ÅÊ∏ÖÈõ?g_tModS.RxCount */
//	}

    testi=g_tModS.RxCount;
    testi=g_tModS.RxCount;
    testi=g_tModS.RxCount;
	if(testi>7)				/* Ω” ’µΩµƒ ˝æ›–°”⁄4∏ˆ◊÷Ω⁄æÕ»œŒ™¥ÌŒÛ */
	{
		testi=testi;
	}
	testi=g_tModS.RxCount;
    if(testi==8)				/* Ω” ’µΩµƒ ˝æ›–°”⁄4∏ˆ◊÷Ω⁄æÕ»œŒ™¥ÌŒÛ */
	{
		testi=testi+1;
	}
	//≈–∂œÕ®—∂Ω” ’ «∑Ò≥¨ ±
	if(OldTick!=Tick_10ms)
  	{  
	  OldTick=Tick_10ms;
	   if(g_mods_timeout>0)
      { 
	    g_mods_timeout--;
      }
	  if(g_mods_timeout==0 && g_tModS.RxCount>0)   //”– ˝µ´≥¨ ±¡À
      { 
		// goto err_ret;
	
      }
      else if(g_mods_timeout==0 && g_tModS.RxCount==0) //√ª ˝≥¨ ±¡À
         return;
      else //√ª≥¨ ±¡À£¨ºÃ–¯ ’
         return;
	}
	else   //√ª”–µΩ10ms£¨≤ªΩ¯»ÎΩ‚Œˆ
		return;
	//g_mods_timeout = 0;	 					/* «Â±Í÷æ */

	if (g_tModS.RxCount < 4)				/* Ω” ’µΩµƒ ˝æ›–°”⁄4∏ˆ◊÷Ω⁄æÕ»œŒ™¥ÌŒÛ */
	{
		goto err_ret;
	}

	/* º∆À„CRC–£—È∫Õ */
// 	crc1 = CRC16(g_tModS.RxBuf, g_tModS.RxCount);
// 	if (crc1 != 0)
// 	{
// 		goto err_ret;
// 	}

// 	/* ’æµÿ÷∑ (1◊÷Ω⁄£© */
// 	addr = g_tModS.RxBuf[0];				/* µ⁄1◊÷Ω⁄ ’æ∫≈ */
// 	if (addr != SADDR485)		 			/* ≈–∂œ÷˜ª˙∑¢ÀÕµƒ√¸¡Óµÿ÷∑ «∑Ò∑˚∫œ */
// 	{
// 		goto err_ret;
// 	}

	/* ÂàÜÊûêÂ∫îÁî®Â±ÇÂçèËÆ?*/
    if(g_tModS.RxBuf[2] == 0xA5)
    {
        UART_Action();
    }else{
//        usartocflag = 1;
        RecHandle();
    }
							
	
err_ret:
#if 0										/* Ê≠§ÈÉ®ÂàÜ‰∏∫‰∫Ü‰∏≤Âè£ÊâìÂç∞ÁªìÊû?ÂÆûÈôÖËøêÁî®‰∏≠ÂèØ‰∏çË¶Å */
	g_tPrint.Rxlen = g_tModS.RxCount;
	memcpy(g_tPrint.RxBuf, g_tModS.RxBuf, g_tModS.RxCount);
#endif
	
 	g_tModS.RxCount = 0;					/* ÂøÖÈ°ªÊ∏ÖÈõ∂ËÆ°Êï∞Âô®ÔºåÊñπ‰æø‰∏ãÊ¨°Â∏ßÂêåÊ≠?*/
}

