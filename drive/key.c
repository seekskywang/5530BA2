/******************** (C) COPYRIGHT 2015 AVER********************
 * �ļ���  ��KEY.C
 * ����    ������
 * ����    ��3*2�������ɨ��
 * ����    ��ɨ����ɺ����ֵ
 * Ӳ�����ӣ�һ·3*2�������  һ·��������������
 * �޸����ڣ�2015-08-18
********************************************************************/
#include "my_register.h"
#include "beep.h"
#include "flash.h"
#include "gpio.h"
#include "key.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "ssd1963.h"
#include  "gui.h"
#include "MainTask.h"
#include "internalflash.h"
#include "flash_if.h"

extern WM_HWIN CreateR(void);
extern WM_HWIN CreateWindow2(void);
extern WM_HWIN CreateWindow(void);
extern WM_HWIN CreateG(void);
extern WM_HWIN CreateSET(void);
extern WM_HWIN Createcal(void);
void setmode_r(void);
extern WM_HWIN hWinWind;
extern WM_HWIN hWinR;
extern WM_HWIN load_wind;//负载界面句柄
extern WM_HWIN hWinG;
extern WM_HWIN hWinset;
extern WM_HWIN hWincdc;
extern WM_HWIN hWinsysinfo;
extern vu8 para_set2;
extern vu16 s;
extern vu8 cdc_sw;
extern vu8 oct_sw;
extern vu8 timer_sw;
extern vu8 mode_sw;
extern vu8 pow_sw;
extern vu8 load_sw;
extern vu8 admin;
extern vu8 pause_flag;
extern vu16 restart_time;
extern vu8 paused;
extern vu8 finish;
extern vu8 short_finish;
extern float gate_v;
extern vu8 manual;
extern vu8 oc_mode;
extern vu8 cal;
extern char inputv[10];
extern vu8 con_flag;
extern vu8 test_finish;
extern float v;
vu8 t_MODE;
vu8 pass = 0;
vu8 LOAD_t;
vu8 track = face_r;
vu8 clear_flag1 = 0;
vu8 clear_flag2 = 0;
vu8 clear_flag3 = 0;
vu16 menu_time;
vu16 load_time;
vu8 r_test = 0;
float clear_v = 0;
float clear_pv = 0;
float clear_lv = 0;
vu8 clear_r = 0;
vu8 r_raly=0;
vu8 lock;
vu8 c_rec;
vu8 calstep;
vu8 oldcal;
extern vu8 test_start;
extern vu8 step;
extern vu16 r;
extern vu8 staticcdc;
extern vu16 sendload;

//=================================================================
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
//====================================================================



#define MAX_VOL  3200		
#define MAX_CUR  5100	
vu8 t_KeyScan;
vu8 NewKey;
vu8 t_wei;
vu8 t_beep;
vu8 t_Str;
vu8 t_lock;
vu8 t_onoff;
vu8 t_doub;
vu8 t_key_step;//键盘扫描计数�?
vu16 Key1,Key2,Key3,Key4,Key5,Key6,Key7,Key8;
vu32 Key9;
vu16 KeyCounter;
vu16 MAX_limit;//�Զ���������ֵ
vu16 MIN_limit;//�Զ���������ֵ
vu16 Test_Time;
vu16 Test_Time1;
vu16 Time_sw;//��ʱ
vu16 Test_Daley;//�Զ������жϵȴ�ʱ�䣬��ʱ���û�������
vu16 Test_C_Door;//�Զ������ż�����
vu8 OFFSET_Zore;//���ֵ
vu32 Key_Scan(void);
void Lift_Move(void);
void Right_Move(void);
void Setvalue_Add(void);
void IO_OFF(void);
extern u8 calmode;
u8 cswflag;
/* 键值定�?*/
#define        KEY_1                		 0X4E     //
#define        KEY_2                		 0X56     //
#define        KEY_3                		 0X5E     //
#define        KEY_4                		 0X57      //
#define        KEY_5                		 0X5F      //
#define        KEY_6                		 0X76      //
#define        KEY_7                		 0X67     //
#define        KEY_8                		 0X6F      //
#define        KEY_9                		 0X77     //
#define        KEY_0                		 0X5D      //
#define        KEY_dian              		 0X65     //
#define        KEY_ESC              		 0X6D     //

#define        ENTER                     0X4D    //
#define        PUSH_Lift                 0X45     //
#define        PUSH_Right                0X55      //
#define        PUSH_Up                   0X46      //
#define        PUSH_Down                 0X74      //
#define        PUSH_DISP                 0X47      //
#define        PUSH_SETUP                0X4F     //

#define        KEY_Lock                  0X6C     //
#define        KEY_BIAS                  0X6E      //
#define        KEY_Reset                 0X66      //
#define        KEY_TRIG                  0X75      //

//#define        KEY_Powe                  0X6C     //
#define        KEY_Face1                 0X64      //
#define        KEY_Face2                 0X5c      //
#define        KEY_Face3                 0X54      //
#define        KEY_Face4                 0X4c      //
#define        KEY_Face5                 0X44      //

/* 定义按键动作 */
#define        KEY_NULL_VALUE             0X00    //�޶���
#define        KEY_PRESS                  0X10    //����
#define        KEY_LONG                   0X20    //����
#define        KEY_CONTINUE               0X40    //����
#define        KEY_UP                     0X80    //����̧��
/*定义按键处理步骤*/
#define        KEY_INIT_STATE               0      //��̬
#define        KEY_WOBBLE_STATE             1      //����
#define        KEY_PRESS_STATE              2      //��������
#define        KEY_LONG_STATE               3      //��������
#define        KEY_CONTINUE_STATE           4      //��������
#define        KEY_RELEASE_STATE            5      //�ָ���̬
/* 长按时间 */
#define         KEY_LONG_PERIOD             50                /* ����ʱ��1S */
#define        KEY_CONTINUE_PERIOD          10                /* ˫��ʱ��500ms */

void JumpBoot(u8 flag)
{
  	void (*pUserApp)(void);
  uint32_t JumpAddress;
	if(flag==55)
  {		
	__asm("CPSID  I");
        
		JumpAddress = *(volatile uint32_t*) (USER_FLASH_FIRST_PAGE_ADDRESS+4);
		pUserApp = (void (*)(void)) JumpAddress;
		TIM_Cmd(TIM1, DISABLE);	
		TIM_DeInit(TIM1);
		TIM_ITConfig(TIM1,TIM_IT_Update,DISABLE);
		TIM_Cmd(TIM2, DISABLE);	
		TIM_DeInit(TIM2);
		TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);
		TIM_Cmd(TIM4,DISABLE);
		TIM_DeInit(TIM4);
		TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
		TIM_Cmd(TIM6, DISABLE);	
	    TIM_DeInit(TIM6);
		TIM_ITConfig(TIM6,TIM_IT_Update,DISABLE);
		USART_DeInit(USART1);
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);		
		USART_Cmd(USART1,DISABLE);
	    USART_DeInit(USART3);
		USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);		
		USART_Cmd(USART3,DISABLE);
		RCC_DeInit();
		RCC_RTCCLKCmd(DISABLE);
		EXTI_DeInit();
		SysTick->CTRL = 0;
		RTC_DeInit();
		RTC_ITConfig(RTC_IT_WUT,DISABLE);//�ر�WAKE UP ��ʱ���ж�
		RTC_WakeUpCmd( DISABLE);//�ر�WAKE UP ��ʱ����
		__disable_irq();
		NVIC_DisableIRQ(OTG_FS_IRQn);
		NVIC_DisableIRQ(OTG_FS_WKUP_IRQn);
		NVIC_DisableIRQ(OTG_HS_IRQn);
		NVIC_DisableIRQ(OTG_HS_WKUP_IRQn);
		__ASM volatile ("cpsid i");
		/* Initialize user application's Stack Pointer */
		__set_PSP(*(volatile uint32_t*) USER_FLASH_FIRST_PAGE_ADDRESS);
		__set_CONTROL(0);
		__set_MSP(*(volatile uint32_t*) USER_FLASH_FIRST_PAGE_ADDRESS);
		
        
		
//		NVIC_SystemReset();
		pUserApp();
	}
}

/************************************************************************************************************************/
vu32 Key_Scan(void)
{
	static vu8 KeyState = KEY_INIT_STATE;
	static vu8 IsKeyRelease = 1;

	static vu8 KeyValueTemp = 0;
	vu8 KeyValue ;
	KeyValue= KEY_NULL_VALUE;
	
	if((NewKey>0x37)&&(IsKeyRelease==1))
	{
		if(KeyState == KEY_INIT_STATE)                    /*�ް�������*/
		{
			KeyState = KEY_WOBBLE_STATE;
			return KEY_NULL_VALUE;
		}
		else if(KeyState == KEY_WOBBLE_STATE)                /* ���� */
		{
			KeyState = KEY_PRESS_STATE;
			return KEY_NULL_VALUE;
		}
		else if(KeyState == KEY_PRESS_STATE)                /* �а������£����ذ���ֵ */
		{
			KeyValue = NewKey;
			KeyValueTemp = KeyValue;
			KeyState = KEY_CONTINUE_STATE;
			return KeyValue;
		}
		else if(KeyState == KEY_CONTINUE_STATE)           /*˫������*/
		{
			KeyCounter ++;
			if(KeyCounter == KEY_CONTINUE_PERIOD)
			{
				 KeyCounter = 0;
				 KeyState = KEY_LONG_STATE;
			}
		}
		else if(KeyState == KEY_LONG_STATE)                        /* �������� */
		{
			KeyCounter ++;
			if(KeyCounter == KEY_LONG_PERIOD)
			{
				KeyCounter = 0;
				Flag_Long=1; //����������־λ
			}
		}
	}
	else if(NewKey<=0x37)
	{
		KeyState = KEY_INIT_STATE;        /* �󴥷������ص���ʼ״̬ */
		IsKeyRelease = 1;
		Flag_Long=0;
	}
	return KEY_NULL_VALUE;
}
/***************************************************************************************************************************/
void Key_Funtion(void)
{
	vu32 KeyValue = 0;
	static vu8 t_KEYON;
	static vu8 a,b;
/****************************************************短按功能************************************************************/
	if(Flag_Key_Scan==1)
	{
		Flag_Key_Scan = 0;
		KeyValue = Key_Scan();
        if(lock == 0)
        {
            switch(KeyValue)
            {
                case KEY_1 ://
                {
                    switch(page_sw){
                        case face_menu: 
                        {
                            INPUT_POW("1");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_set:
                        {
                             INPUT_NUM("1");
                             KeyCounter = 0;
                             BEEP_Tiggr();//触发蜂鸣�?
                             break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                INPUT_C("1");
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }   
                        case face_load:
                        {
                            INPUT_LOAD("1");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            INPUT_CDC("1");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                INPUT_INFO(1);    
                            }else if(cal == 1){
                                Rlow_cal(1);
                            }else{
                                pass += 1;
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cal:
                        {
                            if(calmode == mode_load)
                            {
								IO_OFF();
								Contr_Laod = 0x08E9;
								Flag_DAC_OFF=1;
								GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CV
								flag_Load_CC = 0;
								GPIO_ResetBits(GPIOC,GPIO_Pin_13);//�򿪵�Դ����̵���
                                c_rec = 1;
								GPIO_ResetBits(GPIOA,GPIO_Pin_15);//֧ؓغ՘On
								calstep = 1;
//                                LoadVCal(1);
                            }else if(calmode == mode_pow){
                                IO_OFF();
//                                SET_Voltage = 100;
//                                SET_Current = 1000;
								Contr_Voltage = 0x0312;
								Contr_Current = 0x1a5f;
								Flag_DAC_OFF=1;								
                                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//打开电源输出继电器
                                GPIO_SetBits(GPIOC,GPIO_Pin_1);//打开电源输出
                                calstep = 1;
                            }else if(calmode == mode_r ){
                                Rlow_cal(1);
                            }else if(calmode == mode_loadc){
                                IO_OFF();
//                                SET_Current_Laod = 1000;
								C_SW(0);
								Contr_Laod = 0x077e;
								Flag_DAC_OFF=1;
                                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
                                flag_Load_CC = 1;
                                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//电子负载On
                                calstep = 1;
                            }else if(calmode == mode_powc){
                                IO_OFF();
								Contr_Voltage = 0x0312;
                                Contr_Current = 0x078d;
								Flag_DAC_OFF=1;  
                                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//打开电源输出继电器
                                GPIO_SetBits(GPIOC,GPIO_Pin_1);//打开电源输出
                                calstep = 1;
                            }else if(calmode == input){
                                inputcal("1");
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
                    }
                    KeyCounter = 0;
                    BEEP_Tiggr();//
                }
                break;
                
                case KEY_2 ://
                {
                    switch(page_sw){
                        case face_menu:  
                        {
                            INPUT_POW("2");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                        }
                        case face_set:
                        {
                            INPUT_NUM("2");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                INPUT_C("2");
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_load:
                        {
                            INPUT_LOAD("2");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            INPUT_CDC("2");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                INPUT_INFO(2);    
                            }else if(cal == 1){
                                Rlow_cal(2);
                            }else{
                                pass += 2;
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cal:
                        {
                            if(calmode == mode_load)
                            {
								IO_OFF();
								Contr_Laod = 0x3BA2;
								Flag_DAC_OFF=1;
								GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CV
								flag_Load_CC = 0;
								GPIO_ResetBits(GPIOC,GPIO_Pin_13);//�򿪵�Դ����̵���
                                c_rec = 1;
								GPIO_ResetBits(GPIOA,GPIO_Pin_15);//֧ؓغ՘On
								calstep = 2;
//                                LoadVCal(2);
                            }else if(calmode == mode_pow){
                                IO_OFF();
                                Contr_Voltage = 0x1338;
								Contr_Current = 0x1a5f;
								Flag_DAC_OFF=1;	  
                                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//打开电源输出继电器
                                GPIO_SetBits(GPIOC,GPIO_Pin_1);//打开电源输出
                                calstep = 2;
                            }else if(calmode == mode_r ){
                                Rlow_cal(2);
                            }else if(calmode == mode_loadc){
                                IO_OFF();
//                                SET_Current_Laod = 5000;
								C_SW(0);
								Contr_Laod = 0x1B7E;
								Flag_DAC_OFF=1;
                                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
                                flag_Load_CC = 1;
                                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//电子负载On
                                calstep = 2;
                            }else if(calmode == mode_powc){
                                IO_OFF();
								Contr_Voltage = 0x0312;
                                Contr_Current = 0x1a5f;
								Flag_DAC_OFF=1;  
                                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//打开电源输出继电器
                                GPIO_SetBits(GPIOC,GPIO_Pin_1);//打开电源输出
                                calstep = 2;
                            }else if(calmode == input){
                                inputcal("2");
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
       
                    }
                    KeyCounter = 0;
                    BEEP_Tiggr();//
                }
                break;
                
                case KEY_3 ://
                {
                    switch(page_sw){
                        case face_menu:  
                        {
                            INPUT_POW("3");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                        }
                        case face_set:
                        {
                            INPUT_NUM("3");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                INPUT_C("3");
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_load:
                        {
                            INPUT_LOAD("3");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            INPUT_CDC("3");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                INPUT_INFO(3);    
                            }else if(cal == 1){
                                Rlow_cal(3);
                            }else{
                                pass += 3;
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cal:
                        {
                            if(calmode == mode_load)
                            {
								IO_OFF();
								Contr_Laod = 0x0FE9;
								Flag_DAC_OFF=1;
								GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CV
								flag_Load_CC = 0;
								GPIO_ResetBits(GPIOC,GPIO_Pin_13);//�򿪵�Դ����̵���
                                c_rec = 1;
								GPIO_ResetBits(GPIOA,GPIO_Pin_15);//֧ؓغ՘On
								calstep = 3;
//                                LoadVCal(3);
                            }else if(calmode == mode_loadc){
                                IO_OFF();
//                                SET_Current_Laod = 5000;
								C_SW(0);
								Contr_Laod = 0x1B7E;
								Contr_Current = 0x1a5f;
								Flag_DAC_OFF=1;
                                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
                                flag_Load_CC = 1;
                                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//电子负载On
                                calstep = 3;
                            }else if(calmode == mode_pow){
                                IO_OFF();
                                Contr_Voltage = 0x1489;
								Contr_Current = 0x1a5f;
								Flag_DAC_OFF=1;	 
                                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//打开电源输出继电器
                                GPIO_SetBits(GPIOC,GPIO_Pin_1);//打开电源输出
                                calstep = 3;
                            }else if(calmode == mode_powc){
                                IO_OFF();
								Contr_Voltage = 0x0312;
                                Contr_Current = 0x1c00;
								Flag_DAC_OFF=1;  
                                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//打开电源输出继电器
                                GPIO_SetBits(GPIOC,GPIO_Pin_1);//打开电源输出
                                calstep = 3;
                            }else if(calmode == mode_r ){
                                Rlow_cal(3);
                            }else if(calmode == input){
                                inputcal("3");
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
                    }
                }
                break;
                
                case KEY_4 ://
                {
                    switch(page_sw){
                        case face_menu:  
                        {
                            INPUT_POW("4");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                        }
                        case face_set:
                        {
                            INPUT_NUM("4");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                INPUT_C("4");
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_load:
                        {
                            INPUT_LOAD("4");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            INPUT_CDC("4");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                INPUT_INFO(4);    
                            }else if(cal == 1){
                                Rlow_cal(4);
                            }else{
                                pass += 4;
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cal:
                        {
                            if(calmode == mode_load)
                            {
								IO_OFF();
								Contr_Laod = 0x1FE9;
								Flag_DAC_OFF=1;
								GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CV
								flag_Load_CC = 0;
								GPIO_ResetBits(GPIOC,GPIO_Pin_13);//�򿪵�Դ����̵���
                                c_rec = 1;
								GPIO_ResetBits(GPIOA,GPIO_Pin_15);//֧ؓغ՘On
								calstep = 4;
//                                LoadVCal(4);
                            }else if(calmode == mode_loadc){
                                IO_OFF();
//                                SET_Current_Laod = 5000;
								C_SW(0);
								Contr_Laod = 0x757E;
								Contr_Current = 0x1a5f;
								Flag_DAC_OFF=1;
                                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
                                flag_Load_CC = 1;
                                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//电子负载On
                                calstep = 4;
                            }else if(calmode == mode_pow){
                                IO_OFF();
                                Contr_Voltage = 0x3788;
								Contr_Current = 0x1a5f;
								Flag_DAC_OFF=1;	  
                                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//打开电源输出继电器
                                GPIO_SetBits(GPIOC,GPIO_Pin_1);//打开电源输出
                                calstep = 4;
                            }else if(calmode == mode_powc){
                                IO_OFF();
								Contr_Voltage = 0x0312;
                                Contr_Current = 0x6ad9;
								Flag_DAC_OFF=1;  
                                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//打开电源输出继电器
                                GPIO_SetBits(GPIOC,GPIO_Pin_1);//打开电源输出
                                calstep = 4;
                            }else if(calmode == mode_r ){
                                Rlow_cal(4);
                            }else if(calmode == input){
                                inputcal("4");
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
                    }
                }
                break;
                
                case KEY_5 ://
                {
                    switch(page_sw){
                        case face_menu:  
                        {
                            INPUT_POW("5");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                        }
                        case face_set:
                        {
                            INPUT_NUM("5");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                INPUT_C("5");
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_load:
                        {
                            INPUT_LOAD("5");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            INPUT_CDC("5");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                INPUT_INFO(5);    
                            }else if(cal == 1){
                                Rlow_cal(5);
                            }else{
                                pass += 5;
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cal:
                        {
                            if(calmode == mode_load)
                            {
                                LoadVCal(5);
                            }else if(calmode == mode_loadc){
                                IO_OFF();
//                                SET_Current_Laod = 5000;
								C_SW(0);
								Contr_Laod = 0x757E;
								Flag_DAC_OFF=1;
                                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
                                flag_Load_CC = 1;
                                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//电子负载On
                                calstep = 5;
                            }else if(calmode == mode_pow){
                                IO_OFF();
								Contr_Current = 0x1a5f;
                                Contr_Voltage = 0x398a;
								Flag_DAC_OFF=1;	  
                                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//打开电源输出继电器
                                GPIO_SetBits(GPIOC,GPIO_Pin_1);//打开电源输出
                                calstep = 5;
                            }else if(calmode == mode_r ){
                                Rlow_cal(5);
                            }else if(calmode == input){
                                inputcal("5");
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
                    }
                }
                break;	
                
                case KEY_6 ://
                {
                    switch(page_sw){
                        case face_menu:  
                        {
                            INPUT_POW("6");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                        }
                        case face_set:
                        {
                            INPUT_NUM("6");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                INPUT_C("6");
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_load:
                        {
                            INPUT_LOAD("6");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            INPUT_CDC("6");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        } 
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                INPUT_INFO(6);    
                            }else if(cal == 1){
                                Rlow_cal(6);
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cal:
                        {
                            if(calmode == mode_load)
                            {
                                LoadVCal(6);
                            }else if(calmode == mode_loadc){
                                IO_OFF();
//                                SET_Current_Laod = 5000;
								C_SW(0);
								Contr_Laod = 0xCF1E;
								Flag_DAC_OFF=1;
                                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
                                flag_Load_CC = 1;
                                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//电子负载On
                                calstep = 6;
                            }else if(calmode == mode_pow){
                                IO_OFF();
								Contr_Current = 0x1a5f;
                                Contr_Voltage = 0x6c88;
								Flag_DAC_OFF=1;	  
                                GPIO_ResetBits(GPIOC,GPIO_Pin_13);//打开电源输出继电器
                                GPIO_SetBits(GPIOC,GPIO_Pin_1);//打开电源输出
                                calstep = 6;
                            }else if(calmode == mode_r ){
                                Rlow_cal(6);
                            }else if(calmode == input){
                                inputcal("6");
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
                    }
                }
                break;
                
                case KEY_7 ://
                {
                    switch(page_sw){
                        case face_menu:  
                        {
                            INPUT_POW("7");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                        }
                        case face_set:
                        {
                            INPUT_NUM("7");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                INPUT_C("7");
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_load:
                        {
                            INPUT_LOAD("7");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            INPUT_CDC("7");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                INPUT_INFO(7);    
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cal:
                        {
                            if(calmode == mode_load)
                            {
                                GPIO_ResetBits(GPIOA,GPIO_Pin_12);//电压档位切换
                            }else if(calmode == mode_pow){
                                
                            }else if(calmode == mode_loadc){
                                IO_OFF();
//                                SET_Current_Laod = 5000;
								C_SW(1);
								Contr_Laod = 0x567E;
								Flag_DAC_OFF=1;
                                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
                                flag_Load_CC = 1;
                                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//电子负载On
                                calstep = 7;
                            }else if(calmode == mode_r ){
                                Rlow_cal(7);
                            }else if(calmode == input){
                                inputcal("7");
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
                    }
                }
                break;
                
                case KEY_8 ://
                {
                    switch(page_sw){
                        case face_menu:  
                        {
                            INPUT_POW("8");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                        }
                        case face_set:
                        {
                            INPUT_NUM("8");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                INPUT_C("8");
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_load:
                        {
                            INPUT_LOAD("8");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            INPUT_CDC("8");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                INPUT_INFO(8);    
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                         case face_cal:
                        {
                            if(calmode == mode_load)
                            {
                                GPIO_SetBits(GPIOA,GPIO_Pin_12);//电压档位切换
                            }else if(calmode == mode_loadc){
                                IO_OFF();
								C_SW(1);
								Contr_Laod = 0xA47E;
								Flag_DAC_OFF=1;
                                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
                                flag_Load_CC = 1;
                                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//电子负载On
                                calstep = 8;
                            }else if(calmode == mode_pow){
                                
                            }else if(calmode == mode_r ){
                                Rlow_cal(8);
                            }else if(calmode == input){
                                inputcal("8");
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
                    }
                }
                break;
                
                case KEY_9 ://
                {
                    switch(page_sw){
                        case face_menu:  
                        {
                            INPUT_POW("9");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                        }
                        case face_set:
                        {
                            INPUT_NUM("9");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                INPUT_C("9");
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_load:
                        {
                            INPUT_LOAD("9");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            INPUT_CDC("9");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                INPUT_INFO(9);    
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                         case face_cal:
                        {
                            if(calmode == mode_load)
                            {
                                LoadVCal(9);
                            }else if(calmode == mode_pow){
                                
                            }else if(calmode == mode_loadc){
                                IO_OFF();
								C_SW(1);
								Contr_Laod = 0xA47E;
								Flag_DAC_OFF=1;
                                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
                                flag_Load_CC = 1;
                                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//电子负载On
                                calstep = 9;
                            }else if(calmode == mode_r ){
                                Rlow_cal(9);
                            }else if(calmode == input){
                                inputcal("9");
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
                    }
                }
                break;
                
                case KEY_0 ://
                {
                    switch(page_sw){
                        case face_menu:  
                        {
                            INPUT_POW("0");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                        }
                        case face_set:
                        {
                            INPUT_NUM("0");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                INPUT_C("0");
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_load:
                        {
                            INPUT_LOAD("0");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            INPUT_CDC("0");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                INPUT_INFO(0);    
                            }else{
                                pass += 1;
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cal:
                        {
                            if(calmode == mode_load)
                            {
                                LoadVCal(0);
                            }else if(calmode == mode_pow){
                                
                            }else if(calmode == mode_r ){
                                Rlow_cal(0);
                            }else if(calmode == mode_loadc){
                                IO_OFF();
								C_SW(1);
								Contr_Laod = 0xD6D8;
								Flag_DAC_OFF=1;
                                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
                                flag_Load_CC = 1;
                                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//电子负载On
                                calstep = 10;
                            }else if(calmode == input){
                                inputcal("0");
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
                    }
                }
                break;
                
                case KEY_dian ://
                {
                    switch(page_sw){
                        case face_menu:
                        {
                            INPUT_POW(".");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_set:
                        {
                            INPUT_NUM(".");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_load:
                        {
                            INPUT_LOAD(".");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                INPUT_C(".");
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_cdc:
                        {
                            INPUT_CDC(".");
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }                     
                    }
                }
                break;
                
                case KEY_ESC :
                {
					switch(page_sw){
                        case face_menu:
                        {
                            DEL_POW();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                            break;
                        }
                        case face_set:
                        {
                            DEL_NUM();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                            break;
                        }
                        case face_load:
                        {
                            DEL_LOAD();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                DEL_C();
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣噿
                                break;
                            }
                        }
                        case face_cdc:
                        {
                            DEL_CDC();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                            break;
                        }                     
                    }
//					Flash_Read16BitDatas(FLASH_USER_START_ADDR,40,InFlashSave);
//                  sLCD_WR_REG(0x01);
    //                main();
    //				timer_sw = 0;
                    KeyCounter = 0;
                   BEEP_Tiggr();//触发蜂鸣�
    //                switch(page_sw){
    //                    case face_r:
    //                    {
    //                         if(oc_mode == 0)
    //                         {
    //                             oc_mode = 1;
    //                         }else{
    //                             oc_mode = 0;
    //                         }
    //                    }break;
    //                    default:sLCD_WR_REG(0x01);
    //                    break;
    //                }
                }
                break;
                
                case PUSH_Lift :
                {
                    vu8 l;
                    switch(page_sw){
						case face_r:
						{
							OC_OP_LEFT();
							KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
						}break;
                        case face_set:  //系统设置
                        {
                            SET_OP_LEFT();  //设置选项切换
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                SYS_INFO_LEFT();  //设置选项切换
                            } 
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:  //系统设置
                        {
                            if(l != 0)
                            {
                                CDC_OP_LEFT();  //设置选项切换
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
						case face_cal:
                        {
                            if(calmode == mode_pow){
								Contr_Voltage -= 100;
                            }else if(calmode == mode_loadc){
								Contr_Laod -= 100;
                            }else if(calmode == mode_powc){
                                Contr_Current -= 100;
                            }else if(calmode == mode_load){
								Contr_Laod -= 100;
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
						case face_load:							
						{
							sendload -= 100;
							KeyCounter = 0;
                            BEEP_Tiggr();
						}break;
						case face_menu:
						{
							Contr_Voltage -= 1;
							KeyCounter = 0;
							BEEP_Tiggr();
						}break;
                    }
                }
                break;
                case PUSH_Right :
                {
                    vu8 l;
                    switch(page_sw){
						case face_r:
						{
							OC_OP_RIGHT();
							KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
						}break;
                        case face_set:  //系统设置
                        {
                            SET_OP_RIGHT();  //设置选项切换
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                SYS_INFO_RIGHT();  //设置选项切换
                            } 
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:  //系统设置
                        {
                            if(l != 0)
                            {
                                CDC_OP_RIGHT();  //设置选项切换
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cal:
                        {
                            if(calmode == mode_pow){
								Contr_Voltage += 100;
                            }else if(calmode == mode_loadc){
								Contr_Laod += 100;
                            }else if(calmode == mode_powc){
                                Contr_Current += 100;
                            }else if(calmode == mode_load){
								Contr_Laod += 100;
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
						case face_load:							
						{
							sendload += 100;
							KeyCounter = 0;
                            BEEP_Tiggr();
						}break;
						case face_menu:
						{
							Contr_Voltage += 1;
							KeyCounter = 0;
							BEEP_Tiggr();
						}break;
                    }
                }
                break;
                case PUSH_Up :
                {
                    switch(page_sw){
                        case face_menu:
                        {
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            MENU_OP_UP();
                            break;
                        }                    
                        case face_load:
                        {
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            LOAD_OP_UP();
                            break;
                        }
                        case face_set:
                        {
                            SET_OP_UP();  //设置选项切换
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on/* && oc_mode ==0*/)
                            {
                                OC_OP_UP();
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }

                        }
                        case face_cdc:
                        {
                            CDC_OP_UP();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                SYS_INFO_UP();  //设置选项切换
                            }                        
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
						case face_cal:
						{
							if(jkflag == 0)
							{
								jkflag = 1;
								Write_Limits();
							}else{
								jkflag = 0;
								Write_Limits();
							}
							KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
						}break;

                    }
                }
                break;
                case PUSH_Down :
                {
                    u8 i;
                    switch(page_sw){
                        case face_menu:
                        {
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            MENU_OP_DOWN();
                            break;
                        }  
                        case face_load:
                        {
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            LOAD_OP_DOWN();
                            break;
                        }
                        case face_set:  //系统设置
                        {
                            SET_OP_DOWN();  //设置选项切换
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on/* && oc_mode ==0*/)
                            {
                                OC_OP_DOWN();
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_cdc:
                        {
                            CDC_OP_DOWN();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            if(admin == 1)
                            {
                                SYS_INFO_DOWN();  //设置选项切换
                            } 
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cal:
                        {
                            if(calmode != input)
                            {
                                oldcal = calmode;
                                calmode = input;
                                for(i=0;i<10;i++)
                                {
                                    inputv[i] = '\0';
                                }
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
                    }
                }
                break;
                
                case ENTER ://
                {
                    switch(page_sw){
                        case face_menu:
                        {
                            MENU_SET();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }  
                        case face_set:
                        {
                            PARA_SET();  //参数设置
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;                        
                        }
                        case face_r:
                        {
                            if(para_set2 == set_2_on)
                            {
                                OC_SET();
                                KeyCounter = 0;
                                BEEP_Tiggr();//触发蜂鸣�?
                                break;
                            }
                        }
                        case face_load:
                        {
                            LOAD_SET();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            CDC_SET();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_sys_info:
                        {
                            CFM_PASS();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cal:
                        {
                            if(calmode == mode_r)
                            {
                                if(r_raly == 1)
                                {
                                    GPIO_ResetBits(GPIOB,GPIO_Pin_13);//R_RALY低档位 
                                    r_raly = 0;
                                }else{
                                     GPIO_SetBits(GPIOB,GPIO_Pin_13);//R_RALY高档位
                                    r_raly = 1;
                                }
                            }else if(calmode == input){
                                confirmcal();
                            }else if(calmode == mode_load){
								if(vflag == 1)
								{
									V_SW(0);
								}else{
									V_SW(1);
								}
							}
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣噿
                        }break;
                    }
                }
                break;
                case PUSH_DISP :
                {
                    switch(track)
                    {
                        case face_r:
                        {
                            WM_DeleteWindow(hWinR);
                            WM_DeleteWindow(hWinWind);
                            WM_DeleteWindow(hWinG);
                            WM_DeleteWindow(load_wind);
                            WM_DeleteWindow(hWinsysinfo);
                            WM_DeleteWindow(hWincdc);
                            WM_DeleteWindow(hWinset);                       
                            CreateR();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_load:
                        {
                            WM_DeleteWindow(hWinR);
                            WM_DeleteWindow(hWinWind);
                            WM_DeleteWindow(hWinG);
                            WM_DeleteWindow(load_wind);
                            WM_DeleteWindow(hWinsysinfo);
                            WM_DeleteWindow(hWincdc);
                            WM_DeleteWindow(hWinset);
                            CreateWindow2();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_menu:
                        {
                            WM_DeleteWindow(hWinR);
                            WM_DeleteWindow(hWinWind);
                            WM_DeleteWindow(hWinG);
                            WM_DeleteWindow(load_wind);
                            WM_DeleteWindow(hWinsysinfo);
                            WM_DeleteWindow(hWincdc);
                            WM_DeleteWindow(hWinset); 
                            CreateWindow();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_graph:
                        {
                            WM_DeleteWindow(hWinR);
                            WM_DeleteWindow(hWinWind);
                            WM_DeleteWindow(hWinG);
                            WM_DeleteWindow(load_wind);
                            WM_DeleteWindow(hWinsysinfo);
                            WM_DeleteWindow(hWincdc);
                            WM_DeleteWindow(hWinset); 
                            CreateG();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                        case face_cdc:
                        {
                            WM_DeleteWindow(hWinR);
                            WM_DeleteWindow(hWinWind);
                            WM_DeleteWindow(hWinG);
                            WM_DeleteWindow(load_wind);
                            WM_DeleteWindow(hWinsysinfo);
                            WM_DeleteWindow(hWincdc);
                            WM_DeleteWindow(hWinset);
                            CreateCDC();
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                            break;
                        }
                    }
                }
                break;
                case PUSH_SETUP :
                {
    // 				KeyCounter = 0;
    // 				BEEP_Tiggr();//
    // 				t_MODE++;
    // 				if(t_MODE>1)
    // 				{
    // 					t_MODE=0;
    // 				}
    // 				if(t_MODE==0)
    // 				{
    // 					flag_Load_CC=1;//CCģʽ
    // 					GPIO_ResetBits(GPIOC,GPIO_Pin_12);//CC
    // 					
    // 				}
    // 				else if(t_MODE==1)
    // 				{
    // 					flag_Load_CC=0;//CVģʽ
    // 					GPIO_SetBits(GPIOC,GPIO_Pin_12);//CV
    // 				}
                    WM_DeleteWindow(hWinR);
                    WM_DeleteWindow(hWinWind);
                    WM_DeleteWindow(hWinG);
                    WM_DeleteWindow(load_wind);
                    WM_DeleteWindow(hWinsysinfo);
                    WM_DeleteWindow(hWincdc);
                    WM_DeleteWindow(hWinset); 
                    CreateSET();
                    KeyCounter = 0;
                    BEEP_Tiggr();//触发蜂鸣�
                }
                break;
                case KEY_TRIG://���Ӹ���/��ԴON/OFF
                {
                    switch(page_sw)
                    {
                        case face_r:
                        {
							if(para_set2 == set_2_on)
							{
								 if(test_start == 0 && DISS_Voltage > gate_v)
								 {
									
									test_start = 1;
									r = R_VLUE;
									v = DISS_Voltage;
									if(staticcdc == 1)
									{
										step = 1;
									}else{
										step = 4;
										SET_Current_Laod = set_init_c;
										GPIO_ResetBits(GPIOA,GPIO_Pin_15);
									}
								 }else if(test_start == 1){
									test_start = 0;
									step = 0;
									con_flag = 0;
								 }
								 KeyCounter = 0;
								 BEEP_Tiggr();//����������
								 break;
							 }
                        }
                        case face_load:
                        {
    //                         t_onoff++;
    //                         if(t_onoff>1)
    //                         {
    //                             t_onoff=0;
    //                         }
                            if(load_sw==load_on)
                            {
								cswflag = 1;
								
                                Flag_Swtich_ON=0;
								GPIO_SetBits(GPIOC,GPIO_Pin_13);//�رյ�Դ����̵���
                                GPIO_SetBits(GPIOA,GPIO_Pin_15);//���Ӹ���OFF
                                c_rec = 0;
                                mode_sw = 0;
                                load_sw = load_off;
								C_SW(0);
                            }
                            else if(load_sw==load_off)
                            {
								cswflag = 0;
								if(flag_Load_CC == 0)
                                {
									GPIO_ResetBits(GPIOC,GPIO_Pin_13);//�򿪵�Դ����̵���
                                    c_rec = 1;									
                                }
                                Flag_Swtich_ON=1;
                                GPIO_ResetBits(GPIOA,GPIO_Pin_15);//���Ӹ���On
                                
                                mode_sw = mode_load;
                                load_sw = load_on;
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//
                        }break;
                        case face_menu:
                        {
    //                         static vu8 POW_t;
    //                         POW_t++;
    //                         if(POW_t>1)
    //                         {
    //                             POW_t=0;
    //                         }
                            if(pow_sw==pow_on)
                            {
                                GPIO_ResetBits(GPIOC,GPIO_Pin_1);//�رյ�Դ���
								Delay_ms(1000);
                                GPIO_SetBits(GPIOC,GPIO_Pin_13);//�رյ�Դ����̵���
                                mode_sw = 0;
                                pow_sw = pow_off;
                            }
                            else if(pow_sw==pow_off)
                            {
//								SET_Voltage = pow_v-12;
								SET_Voltage = pow_v;
                               GPIO_ResetBits(GPIOC,GPIO_Pin_13);//�򿪵�Դ����̵���
                                GPIO_SetBits(GPIOC,GPIO_Pin_1);//�򿪵�Դ���                           
                                mode_sw = mode_pow;
                                pow_sw = pow_on;
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//
                        }break;
                         case face_cdc:
                        {
                            if(cdc_sw == cdc_off)
                            {
                               SET_Voltage = opv1;
                               SET_Current = opc1;
                               cutoff_flag = 0;
    //                           Mode_SW_CONT(0x03);
                               
                               charge_step = 1;
                               GPIO_ResetBits(GPIOC,GPIO_Pin_13);//�򿪵�Դ����̵���
							   Delay_ms(500);
                               GPIO_SetBits(GPIOC,GPIO_Pin_1);//�򿪵�Դ���
                               mode_sw = mode_pow;
                               cdc_sw = cdc_on;
                            }else{
                               
                               GPIO_ResetBits(GPIOC,GPIO_Pin_1);//�رյ�Դ���
								Delay_ms(500);
                               GPIO_SetBits(GPIOC,GPIO_Pin_13);//�رյ�Դ����̵���
                               GPIO_SetBits(GPIOA,GPIO_Pin_15);//���Ӹ���OFF
                               cdc_sw = cdc_off;
                               paused = 0;
                               mode_sw = 0;
                            }
                            KeyCounter = 0;
                            BEEP_Tiggr();//触发蜂鸣�?
                           
                        }break;
                        case face_cal:
                        {
                            if(calmode == mode_pow)
                            {
								PowVCal(calstep);
//                                if(calstep == 1)
//                                {
//                                    PowVCal(1);
//                                }else if(calstep == 2){
//                                    PowVCal(2);
//                                }else if(calstep == 3){
//                                    PowVCal(3);
//                                }else if(calstep == 4){
//                                    PowVCal(4);
//                                }else if(calstep == 5){
//                                    PowVCal(5);
//                                }else if(calstep == 6){
//                                    PowVCal(6);
//                                }
                            }else if(calmode == mode_loadc){
								LoadCCal(calstep);
//                                if(calstep == 1)
//                                {
//                                    LoadCCal(1);
//                                }else if(calstep == 2){
//                                    LoadCCal(2);
//                                }
                            }else if(calmode == mode_powc){
								PowCCal(calstep);
//                                if(calstep == 1)
//                                {
//                                    PowCCal(1);
//                                }else if(calstep == 2){
//                                    PowCCal(2);
//                                }else if(calstep == 3){
//                                    PowCCal(3);
//                                }else if(calstep == 4){
//                                    PowCCal(4);
//                                }
                            }else if(calmode == mode_load){
								LoadVCal(calstep);
							}
                            KeyCounter = 0;
                            BEEP_Tiggr();//
                        }break;
						case face_sys_info:
                        {
//							JumpBoot(55);
						}break;
                    }
                    
                }
                break;
                case KEY_Reset://����ߵ͵�λ�л�
                {
                    static vu8 at = 0;
                    switch(page_sw)
                    {
                        case face_r:
                        {
                            if(at == 0)
                            {
                                GPIO_SetBits(GPIOC,GPIO_Pin_13);//�رյ�Դ����̵���
                                GPIO_ResetBits(GPIOB,GPIO_Pin_13);//R_RALY�͵�λ                           
                                at++;
                                r_raly=0;
                                manual = 1;//�ֶ�����
                            }else if(at == 1){
                                GPIO_SetBits(GPIOC,GPIO_Pin_13);//�رյ�Դ����̵���
                                GPIO_SetBits(GPIOB,GPIO_Pin_13);//R_RALY�ߵ�λ
                                r_raly=1;
                                at++;
                                manual = 1;//�ֶ�����
                            }else if(at == 2){
                                at = 0;
                                manual =0;
                            }
                        }
                        case face_cal:
                        {
                            if(calmode == mode_load)
                            {
                                calmode = mode_loadc;
                                IO_OFF();
                            }else if(calmode == mode_loadc){ 
                                calmode = mode_pow;
                                IO_OFF();
                            }else if(calmode == mode_pow){ 
                                calmode = mode_powc;
                                IO_OFF();
                            }else if(calmode == mode_powc){ 
                                calmode = mode_r;
                                IO_OFF();
                            }else if(calmode == mode_r){ 
                                calmode = mode_load;
                                IO_OFF();
                            }
                        }break;
						case face_load:
						{
							if(cflag == 0)
							{
								C_SW(1);
							}else{
								C_SW(0);
							}
						}break;
						
                    }
                    KeyCounter = 0;
                    BEEP_Tiggr();//
                }
                break;
    // 			case KEY_Powe :
    // 			{
    // 				
    // 				KeyCounter = 0;
    // 				BEEP_Tiggr();//
    // 			}
    // 			break;
                case KEY_Lock :
                {
                    lock = 1;
                    KeyCounter = 0;
                    BEEP_Tiggr();//
                }break;
                case KEY_Face1 :
                {
                    WM_DeleteWindow(hWinR);
                    WM_DeleteWindow(hWinWind);
                    WM_DeleteWindow(hWinG);
                    WM_DeleteWindow(load_wind);
                    WM_DeleteWindow(hWinsysinfo);
                    WM_DeleteWindow(hWincdc);
                    WM_DeleteWindow(hWinset);
                    GPIO_SetBits(GPIOA,GPIO_Pin_15);//���Ӹ���OFF
                    GPIO_ResetBits(GPIOC,GPIO_Pin_1);//�رյ�Դ���
					Delay_ms(500);
				    GPIO_SetBits(GPIOC,GPIO_Pin_13);//�رյ�Դ����̵��
                    CreateR();
                    KeyCounter = 0;
                    BEEP_Tiggr();//
                }
                break;
                case KEY_Face2 :
                {
                    WM_DeleteWindow(hWinR);
                    WM_DeleteWindow(hWinWind);
                    WM_DeleteWindow(hWinG);
                    WM_DeleteWindow(load_wind);
                    WM_DeleteWindow(hWinsysinfo);
                    WM_DeleteWindow(hWincdc);
                    WM_DeleteWindow(hWinset);
                    CreateWindow2();
                    t_onoff = 0;
                    GPIO_ResetBits(GPIOC,GPIO_Pin_1);
					Delay_ms(500);
				    GPIO_SetBits(GPIOC,GPIO_Pin_13);
                    KeyCounter = 0;
                    BEEP_Tiggr();//
                }
                break;
                case KEY_Face3 :
                {
                    WM_DeleteWindow(hWinR);
                    WM_DeleteWindow(hWinWind);
                    WM_DeleteWindow(hWinG);
                    WM_DeleteWindow(load_wind);
                    WM_DeleteWindow(hWinsysinfo);
                    WM_DeleteWindow(hWincdc);
                    WM_DeleteWindow(hWinset);
                    CreateWindow();
                    GPIO_SetBits(GPIOA,GPIO_Pin_15);//���Ӹ���OFF
                    KeyCounter = 0;
                    BEEP_Tiggr();//
                }
                break;
                case KEY_Face4 :
                {
                    WM_DeleteWindow(hWinR);
                    WM_DeleteWindow(hWinWind);
                    WM_DeleteWindow(hWinG);
                    WM_DeleteWindow(load_wind);
                    WM_DeleteWindow(hWinsysinfo);
                    WM_DeleteWindow(hWincdc);
                    WM_DeleteWindow(hWinset);
//					GPIO_ResetBits(GPIOC,GPIO_Pin_1);//�رյ�Դ���
//					Delay_ms(500);
//				    GPIO_SetBits(GPIOC,GPIO_Pin_13);//�رյ�Դ����̵��
                    CreateCDC(); 
                    KeyCounter = 0;
                    BEEP_Tiggr();//
                }
                break;
                case KEY_Face5 :
                {
                    WM_DeleteWindow(hWinR);
                    WM_DeleteWindow(hWinWind);
                    WM_DeleteWindow(hWinG);
                    WM_DeleteWindow(load_wind);
                    WM_DeleteWindow(hWinsysinfo);
                    WM_DeleteWindow(hWincdc);
                    WM_DeleteWindow(hWinset);
                    CreateG();
                    KeyCounter = 0;
                    BEEP_Tiggr();//
                }
                break;
                case KEY_BIAS :
                {
                    WM_DeleteWindow(hWinR);
                    WM_DeleteWindow(hWinWind);
                    WM_DeleteWindow(hWinG);
                    WM_DeleteWindow(load_wind);
                    WM_DeleteWindow(hWinsysinfo);
                    WM_DeleteWindow(hWincdc);
                    WM_DeleteWindow(hWinset);
					GPIO_ResetBits(GPIOC,GPIO_Pin_1);//�رյ�Դ���
					Delay_ms(500);
				    GPIO_SetBits(GPIOC,GPIO_Pin_13);//�رյ�Դ����̵��
                    Createsysinfo();
                    KeyCounter = 0;
                    BEEP_Tiggr();//触发蜂鸣�?
                }
                break;

                        
                
                default:
                break;
            }
        }else{
            switch(KeyValue)
            {
                case KEY_Lock :
                {
                    lock = 0;
                    usartocflag = 0;
                    KeyCounter = 0;
                    BEEP_Tiggr();//
                }break;
            }
        } 
	}
}


void setmode_r(void)
{
    GPIO_ResetBits(GPIOC,GPIO_Pin_1);//�رյ�Դ���
    GPIO_SetBits(GPIOC,GPIO_Pin_13);//�رյ�Դ����̵���  
    GPIO_SetBits(GPIOA,GPIO_Pin_15);//���Ӹ���OFF  
    pow_sw = pow_off;
    load_sw = load_off;
    mode_sw = mode_r;
}
const GUI_POINT aPoints[] = {
{ 0, 0},
{ 13, 0},
{ 13, 9},
{ 0, 9}
};

void DrawLock(void)
{
    if(lock == 1)
    {
        GUI_SetColor(GUI_RED);
        GUI_SetPenSize(2);
        GUI_DrawArc( 390,12,6,3,0, 180 );
        GUI_DrawPolygon(aPoints,4,383,12);
    }else{
        
    }
}

void DrawLockc(void)
{
    if(lock == 1)
    {
        GUI_SetColor(GUI_RED);
        GUI_SetPenSize(2);
        GUI_DrawArc( 405+60,12,6,3,0, 180 );
        GUI_DrawPolygon(aPoints,4,398+60,12);
    }else{
        
    }
}
void IO_OFF(void)
{
    GPIO_ResetBits(GPIOC,GPIO_Pin_1);//�رյ�Դ���
    GPIO_SetBits(GPIOC,GPIO_Pin_13);//�رյ�Դ����̵���  
    GPIO_SetBits(GPIOA,GPIO_Pin_15);//���Ӹ���OFF  
    pow_sw = pow_off;
    load_sw = load_off;
}

