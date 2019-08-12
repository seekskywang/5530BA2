/******************************************************************/
/* 名称：                                                  				*/
/* 效果：                                                        */
/* 内容：内阻仪界面                                              */
/* 作者：zhan                                                  */
/* 联系方式QQ:363116119                                        */


#include "MainTask.h"
#include  "gui.h"
#include "DIALOG.h"
#include "my_register.h" 
#include "tm1650.h"
#include "stdio.h"
#include "stdlib.h"
#include "key.h"
#include "string.h"
#include "beep.h"



WM_HWIN hWinR;
void OC_ADD(void); 
void test_r(void);
vu8 bit = 0;
vu8 dot_flag = 0;
vu8 page_sw = face_r;
vu8 para_set1;
vu8 para_set2 = set_2_on;
vu8 para_set3;
vu8 para_set4 = set_4_off;
vu8 r_stable = 0;
float gate_v = 0;
char set_limit[6];
vu16 stable_time;
vu8 alert_flag;
vu8 mode_sw;
vu16 stepcount;
vu8 b_type;
vu8 buffer;
vu8 set_sw;
vu8 oc_mode;
vu8 rpow;
vu8 test_start = 0;
float static_pc;
float static_lv;
vu8 staticcdc;
vu8 step;
////////////////////////////////////
extern vu8 ocf;
vu16 dis_gate_v;
float DISS_R;//内阻
extern vu8 page_sw;
static vu8 oc_sw = set_20;
float oc_data;
vu16 s_time;
vu8 wait_flag;
vu8 test_num = 0;
vu8 con_flag = 0;
vu8 short_flag = 0;
vu16 r;
vu16 short_start;
vu16 short_time;
vu8 short_finish = 0;
float v;
float time1;
vu8 finish = 0;
vu8 test_finish = 0;
vu16 steptime = 1;
vu8 ocstop = 0;
int test_ftime;
extern vu8 dot_flag;
vu8 oct_sw = oct_off;
vu8 oc_test = 0;
extern vu8 t_onoff;
extern vu8 mode_sw;
float crec1,crec2;
extern vu8 LOAD_t;
//extern vu8 status_flash;
extern vu8 pass;
extern vu8 track;
extern vu8 clear_r;
extern vu8 r_test;
extern vu16 stepcount;
vu8 manual = 0;
u8 lockstat1,lockstat2;

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
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_1     (GUI_ID_USER + 0x12)
#define ID_TEXT_0     	(GUI_ID_USER + 0x13)
#define ID_TEXT_1     	(GUI_ID_USER + 0x14)
#define ID_TEXT_3     	(GUI_ID_USER + 0x15)
#define ID_TEXT_4     	(GUI_ID_USER + 0x16)
#define ID_TEXT_6     	(GUI_ID_USER + 0x17)
#define ID_TEXT_43    	(GUI_ID_USER + 0x68)
#define ID_TEXT_44    	(GUI_ID_USER + 0x69)
#define ID_TEXT_45    	(GUI_ID_USER + 0x6A)
#define ID_TEXT_46    	(GUI_ID_USER + 0x6B)
#define ID_TEXT_47    	(GUI_ID_USER + 0x6C)
#define ID_TEXT_80   	(GUI_ID_USER + 0x8D)
#define ID_TEXT_81   	(GUI_ID_USER + 0x8E)
#define ID_TEXT_82      (GUI_ID_USER + 0x8F)
#define ID_TEXT_83      (GUI_ID_USER + 0x90)
#define ID_TEXT_96     	(GUI_ID_USER + 0x0104)
#define ID_TEXT_97     	(GUI_ID_USER + 0x0105)
#define ID_TEXT_98     	(GUI_ID_USER + 0x0106)
#define ID_TEXT_117     (GUI_ID_USER + 0x0107)
#define ID_TEXT_118     (GUI_ID_USER + 0x0108)
#define ID_TEXT_124     (GUI_ID_USER + 0x0109)
#define ID_TEXT_125     (GUI_ID_USER + 0x010A)
#define ID_TEXT_126     (GUI_ID_USER + 0x010B)
#define ID_TEXT_127     (GUI_ID_USER + 0x010C)
#define ID_TEXT_128     (GUI_ID_USER + 0x010D)
#define ID_TEXT_130     (GUI_ID_USER + 0x010E)
#define ID_TEXT_132     (GUI_ID_USER + 0x0121)
#define ID_BUTTON_12    (GUI_ID_USER + 0x18)
#define ID_BUTTON_13    (GUI_ID_USER + 0x19)
#define ID_BUTTON_14    (GUI_ID_USER + 0x1A)
#define ID_BUTTON_15   	(GUI_ID_USER + 0x1B)
#define ID_BUTTON_16   	(GUI_ID_USER + 0x1C)
#define ID_BUTTON_17    (GUI_ID_USER + 0x1D)
#define ID_TEXT_145     (GUI_ID_USER + 0x012F)
#define ID_TEXT_146     (GUI_ID_USER + 0x0130)
#define ID_TEXT_147     (GUI_ID_USER + 0x0131)
#define ID_TEXT_148     (GUI_ID_USER + 0x0132)
#define ID_TEXT_149     (GUI_ID_USER + 0x0133)
#define ID_TEXT_150     (GUI_ID_USER + 0x0134)
#define ID_TEXT_151     (GUI_ID_USER + 0x0135)
#define ID_TEXT_152     (GUI_ID_USER + 0x0136)
#define ID_TEXT_153     (GUI_ID_USER + 0x0137)
#define ID_TEXT_160     (GUI_ID_USER + 0x013B)

#define ID_TimerTime    1
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "R", ID_WINDOW_1, 0, 0, 480, 272, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 28, 50, 64, 32, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 270, 50+10, 60, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 240, 50, 32, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 239, 121, 32, 32, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_6, 217, 128, 32, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_43, 270, 130+10, 60, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_44, 270, 70+10, 60, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_45, 270, 90+10, 60, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_46, 335, 70+10, 40, 15, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_47, 335, 90+10, 40, 15, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_80, 95, 48, 150, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_81, 95, 116, 150, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_82, 95, 184, 150, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_83, 400, 130, 40, 15, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_96, 240, 5, 120, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_97, 335, 110+10, 40, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_98, 405, 5, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_117, 400, 90, 60, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_118, 270, 110+10, 60, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_124, 300, 2, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_125, 5, 225, 80, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_130, 335, 130+10, 40, 15, 0, 0x0, 0 },
//   { BUTTON_CreateIndirect, "Button", ID_BUTTON_12, 3, 226, 77, 45, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_126, 5, 255, 50, 20, 20, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_127, 54, 255, 20, 20, 20, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_128, 68, 254, 20, 20, 20, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_132, 335, 50+10, 40, 15, 20, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_145, 270, 150+10, 60, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_146, 270, 170+10, 60, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_147, 270, 190+10, 60, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_148, 335, 150+10, 40, 15, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_149, 335, 170+10, 40, 15, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_150, 335, 190+10, 40, 15, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_151, 400, 170, 40, 15, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_152, 270, 40, 60, 15, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_153, 335, 40, 40, 15, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_160, 380, 8, 20, 15, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_13, 83, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_14, 163, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_15, 243, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_16, 323, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_17, 403, 226, 77, 45, 0, 0x0, 0 }
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
    WM_HWIN hItem;
//     int     NCode;
//     int     Id;
    char  buf[5];
    float dis_init_c = (float)set_init_c/1000;
    float dis_sbs_c = (float)set_sbs_c/1000;
    static vu8 led_sw = 0;


  // USER START (Optionally insert additional variables)
  // USER END
//    int i;
        


  switch (pMsg->MsgId) {
		
	case WM_PAINT:
	GUI_SetColor(GUI_WHITE);//设置画笔颜色
	GUI_FillRect(0,25,480,26);//画一条实线
    GUI_SetColor(GUI_ORANGE);
	GUI_SetFont(&GUI_Fontsymbol);
	GUI_UC_SetEncodeUTF8();
	GUI_SetTextMode(GUI_TM_TRANS);//设置文本模式为底色透明
	if(jkflag == 1)
	{
		GUI_DispStringAt("Jinko", 5, 1);//SET
	}
	if(lang == 0)
    {
        GUI_SetColor(GUI_WHITE);
        GUI_SetFont(&GUI_FontHZ20S);
        GUI_UC_SetEncodeUTF8();
        GUI_SetTextMode(GUI_TM_TRANS);//设置文本模式为底色透明
        GUI_DispStringAt("测量显示", 130, 3);//SET
    }else{
        GUI_SetColor(GUI_WHITE);
        GUI_SetFont(&GUI_Font20_ASCII);
        GUI_DispStringAt("DISPLAY", 130, 3);
    }
    
    GUI_SetColor(GUI_GREEN);
    GUI_SetFont(&GUI_Fontunit);
    GUI_DispStringAt("°",342, 2);
    GUI_SetFont(&GUI_Font24_1);
    GUI_DispStringAt("C",350, 2);
//    DrawLock();
//    GUI_DispDecAt(R_VLUE,50,140,4);//显示内阻值
//      GUI_GotoXY(220,4);
//      GUI_DispDec(short_time,6);
    
// 	GUI_SetColor(GUI_WHITE);//设置前景色为白色
// 	GUI_SetFont(&GUI_FontD24x32);//
// 	GUI_GotoXY(95,48);//
// 	GUI_DispFloatFix(DISS_Voltage,5,2);//显示电压值
//     
//     if(R_VLUE == 0){
//         GUI_SetFont(&GUI_Font24_1);
//         GUI_DispStringAt("___", 130, 116);
//     }
//     else if(R_VLUE >= 1000){
//         GUI_SetFont(&GUI_FontEN40);
//         GUI_DispStringAt("OVER", 112, 120);
//     }else{
//         GUI_GotoXY(95,116);//
//         GUI_DispDec(R_VLUE,count_num(R_VLUE));//显示内阻值
//     }
    

    switch(para_set2){
            case set_2_on:
            {
//                 GUI_SetFont(&GUI_FontD24x32);
//                 GUI_GotoXY(95,184);//
//                 GUI_DispFloatFix(DISS_Current,5,2);
                GUI_SetFont(&GUI_FontEN40);
                GUI_SetColor(GUI_LIGHTGRAY);
                GUI_DispStringAt("I:", 28, 190);
                GUI_DispStringAt("R:", 28, 120);
                GUI_SetColor(GUI_LIGHTGRAY);
                GUI_DispStringAt("A", 240, 187);
                GUI_SetFont(&GUI_Font16_1);
                GUI_SetColor(GUI_WHITE);
                GUI_DispStringAt("A",375+10,70+10);
                GUI_DispStringAt("A",375+10,90+10);
                GUI_DispStringAt("V",375+10,110+10);
                GUI_DispStringAt("ms",365+10,130+10);
				GUI_DispStringAt("V",375+10,150+10);
                GUI_DispStringAt("A",375+10,170+10);
                GUI_DispStringAt("A",375+10,190+10);
//                GUI_DispStringAt("A",400,110);
                GUI_DispStringAt("ms",430,90);
				GUI_DispStringAt("V",440,130);
                GUI_DispStringAt("A",440,170);
				
                
				GUI_SetColor(GUI_GREEN);
				if(lang == 0)
                {
                    GUI_SetFont(&GUI_FontHZ14);
                   GUI_DispStringAt("测试结果", 400, 50);
					GUI_DispStringAt("短路时间", 400, 70);//SET
					GUI_DispStringAt("负载电压", 400, 110);//SET
					GUI_DispStringAt("充电电流", 400, 150);//SET
                }else{
                    GUI_SetFont(&GUI_Font16_1);
                    GUI_DispStringAt("Result", 400, 50);
                    GUI_DispStringAt("Short Time", 400, 70);//SET
                    GUI_DispStringAt("Load V", 400, 110);//SET
					GUI_DispStringAt("Charge C", 400, 150);//SET
                }
                
//                 if(oc_data == 0)
//                 {
//                     GUI_SetFont(&GUI_Font24_1);
//                     GUI_DispStringAt("__", 410, 140);

//                 }else{
//                     GUI_SetFont(&GUI_Font24_1);
//                     GUI_GotoXY(400,150);//
//                     GUI_DispFloatFix(oc_data,5,2);
//                 }
                break;
            }
            case set_2_off:
            {
                GUI_SetFont(&GUI_FontEN40);
                GUI_SetColor(GUI_LIGHTGRAY);
                GUI_DispStringAt("R:", 28, 120);
                break;
            }
    }
	break;
	case WM_TIMER://定时模块消息
	if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime)
	{
//        lockstat1 = lock;
//        if(lockstat1 != lockstat2)
//        {
//            WM_InvalidateWindow(hWinR);
//        }//锁屏处理
		if(lock == 1)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_160);
			TEXT_SetText(hItem,"锁");
		}else{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_160);
			TEXT_SetText(hItem,"");
		}
		if(manual == 0)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_125);
            TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,"Range");
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_126);       
            TEXT_SetText(hItem,"Auto");
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_127);       
            TEXT_SetText(hItem,"");
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_128);       
            TEXT_SetText(hItem,"");
            if(R_VLUE < 180 && DISS_Voltage > 1)
            {
                GPIO_ResetBits(GPIOB,GPIO_Pin_13);//R_RALY低档位 
                r_raly = 0;
            }else{
                GPIO_SetBits(GPIOB,GPIO_Pin_13);//R_RALY高档位
                r_raly = 1;
            }
        }else{
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_125);
            TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,"Range");
            if(r_raly == 1)
            {
				GPIO_SetBits(GPIOB,GPIO_Pin_13);//R_RALY高档位
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_126);       
                TEXT_SetText(hItem,"2000");
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_127);       
                TEXT_SetText(hItem,"m");
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_128);       
                TEXT_SetText(hItem,"Ω");
            }else{
				GPIO_ResetBits(GPIOB,GPIO_Pin_13);//R_RALY低档位 
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_126);       
                TEXT_SetText(hItem,"200");
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_127);       
                TEXT_SetText(hItem,"m");
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_128);       
                TEXT_SetText(hItem,"Ω");
            }
        }
         
		if(para_set2 == set_2_on)
        {
			if(oc_mode == 0)
            {
                GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
                flag_Load_CC = 1;
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_132);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,"CC");
            }else if(oc_mode == 1){
                GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CV
                flag_Load_CC = 0;
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_132);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,"CV");
            }
			
			if(staticcdc == 1)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_153);
				if(lang == 0)
                {
                    GUI_SetFont(&GUI_FontHZ14);
                   TEXT_SetText(hItem, "开");
                }else{
                    GUI_SetFont(&GUI_Font16_1);
                    TEXT_SetText(hItem, "ON");
                }
				
			}else{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_153);
				if(lang == 0)
                {
                    GUI_SetFont(&GUI_FontHZ14);
                   TEXT_SetText(hItem, "关");
                }else{
                    GUI_SetFont(&GUI_Font16_1);
                    TEXT_SetText(hItem, "OFF");
                }
			}
			
			
			
			if(test_start == 0)
			{
				if(DISS_Voltage > 1 && DISS_Voltage > gate_v && R_VLUE > 20 && con_flag == 0)
				{
					con_flag = 1;
					time1 = (float)GUI_GetTime()/500.0;
				}
				if(con_flag == 1)
				{
					if(test_mode == 0)
					{
						if((float)(GUI_GetTime()/500.0 - time1) > 0.5)
						{
							if(staticcdc == 1)
							{
								step = 1;
							}else{
								step = 4;
								SET_Current_Laod = set_init_c;
								GPIO_ResetBits(GPIOA,GPIO_Pin_15);
							}
							test_start = 1;
							r = R_VLUE;
							v = DISS_Voltage;
						}
					}else if(test_mode == 1){
						if((float)(GUI_GetTime()/500.0 - time1) > 1.5)
						{
							if(staticcdc == 1)
							{
								step = 1;
							}else{
								step = 4;
								SET_Current_Laod = set_init_c;
								GPIO_ResetBits(GPIOA,GPIO_Pin_15);
							}
							test_start = 1;
							r = R_VLUE;
							v = DISS_Voltage;
						}
					}
				}
			
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
                 if(lang == 0)
                {
                    GUI_SetFont(&GUI_Fontset_font);
                    TEXT_SetText(hItem, "未测试");
                }else{
                    GUI_SetFont(&GUI_Font20_ASCII);
                    TEXT_SetText(hItem, "Untested");
                }
				
				if(DISS_Voltage < 0.3)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
                    sprintf(buf,"%.3f",0.000);
                    TEXT_SetText(hItem,buf);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);					
					sprintf(buf,"%04d",0);       
					TEXT_SetText(hItem,buf);
                }else{
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
                    sprintf(buf,"%.3f",DISS_Voltage);       
                    TEXT_SetText(hItem,buf);
					
					if(R_VLUE >= 2000)
					{
//						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
//						TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
//						TEXT_SetText(hItem,"OVER");
					}else{
						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);					
						sprintf(buf,"%04d",R_VLUE);       
						TEXT_SetText(hItem,buf);
					}
                }
				
				
				
				short_time = 0;
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_117);
                sprintf(buf,"%4d",short_time);
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体      
                TEXT_SetText(hItem,buf);
                
                oc_data = 0;
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_82);
                TEXT_SetTextColor(hItem, GUI_GREEN);
                sprintf(buf,"%.3f",oc_data);
                TEXT_SetText(hItem,buf);
				
				static_lv = 0;
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_83);  
				sprintf(buf,"%.3f",static_lv);
				TEXT_SetText(hItem,buf); 
				
				static_pc = 0;
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_151);
				sprintf(buf,"%.3f",static_pc);       
				TEXT_SetText(hItem,buf);
				
			}else if(test_start == 1){
				if(step == 0)
				{
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
					 if(lang == 0)
					{
						GUI_SetFont(&GUI_Fontset_font);
						TEXT_SetText(hItem, "未测试");
					}else{
						GUI_SetFont(&GUI_Font20_ASCII);
						TEXT_SetText(hItem, "Untested");
					}
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);					
					sprintf(buf,"%04d",r);       
					TEXT_SetText(hItem,buf);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
                    sprintf(buf,"%.3f",v);       
                    TEXT_SetText(hItem,buf);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_117);
					sprintf(buf,"%4d",short_time/10);
					TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体      
					TEXT_SetText(hItem,buf);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_82);
					TEXT_SetTextColor(hItem, GUI_GREEN);
					sprintf(buf,"%.3f",oc_data);
					TEXT_SetText(hItem,buf);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_83);  
					sprintf(buf,"%.3f",static_lv);
					TEXT_SetText(hItem,buf); 
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_151);
					sprintf(buf,"%.3f",static_pc);       
					TEXT_SetText(hItem,buf);
					//分选
					if(para_set1 == set_1_on)
					{
						test_r();
					}
					//归零
					if(DISS_Voltage < gate_v || DISS_Voltage < 1)
					{
						test_start = 0;
						con_flag = 0;
						v = 0;
						r= 0;
					}
				}else{
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
                    if(lang == 0)
					{
						GUI_SetFont(&GUI_Fontset_font);
						TEXT_SetText(hItem, "测试中");
					}else{
						GUI_SetFont(&GUI_Font20_ASCII);
						TEXT_SetText(hItem, "Testing");
					}
				}
			}
			
			
		}else{
			if(DISS_Voltage < 0.3)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
				sprintf(buf,"%.3f",0.000);
				TEXT_SetText(hItem,buf);
				
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);					
				sprintf(buf,"%04d",0);       
				TEXT_SetText(hItem,buf);
			}else{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
				sprintf(buf,"%.3f",disloadv);       
				TEXT_SetText(hItem,buf);
				
				if(R_VLUE >= 2000)
				{
//						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
//						TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
//						TEXT_SetText(hItem,"OVER");
				}else{
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);					
					sprintf(buf,"%04d",disrvalue);       
					TEXT_SetText(hItem,buf);
				}
			}
			//分选
			if(para_set1 == set_1_on)
			{
				test_r();
			}
		}
		//显示温度
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_124);       
        sprintf(buf,"%.1f",temp);
        TEXT_SetText(hItem,buf);
		WM_RestartTimer(pMsg->Data.v, 20);//复位定时器数值越大刷新时间越短
	}
	break;
    
		
  case WM_INIT_DIALOG:
    //
    // Initialization of 'R'
	
    //
        hItem = pMsg->hWin;
        WINDOW_SetBkColor(hItem, GUI_BLACK);
		WM_CreateTimer(hItem,ID_TimerTime,500,0);//创建本窗口定时器  
        
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_160);
		TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
		TEXT_SetFont(hItem,&GUI_FontHZ14);
		TEXT_SetText(hItem,"");
	
	
		if(lang == 0)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_13);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetPressed(hItem,1);
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"内阻测试");
        
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_14);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"程控负载");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_15);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"程控电源");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_16);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"充放电");
            
            
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_17);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,&GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"曲线");
        }else{
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_13);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetPressed(hItem,1);
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"I.R. TEST");
        
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_14);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"LOAD");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_15);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"POWER");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_16);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"C&DC");
            
            
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_17);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,&GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem,"GRAPH");           
        }
		
    // Initialization of 'Text'
    //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
        TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);
        TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
        GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"V:");
    //
    // Initialization of 'Text'
    //
    //
    // Initialization of 'Text'
    //
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		TEXT_SetText(hItem, "V");
        TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);
        TEXT_SetFont(hItem, &GUI_FontEN40);
    //
    // Initialization of 'Text'
    //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem, "Ω");
        TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);
		TEXT_SetFont(hItem,&GUI_FontHZ32);//设定按钮文本字体
    //
    // Initialization of 'Text'
    //		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
        GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem, "m");
        TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);
		TEXT_SetFont(hItem, &GUI_FontEN40);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_80);
        sprintf(buf,"%.3f",0.000);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,buf);
            
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_81);
        sprintf(buf,"%04d",0);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_96);
        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,"");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_124);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体       
        sprintf(buf,"%.1f",temp);
        TEXT_SetText(hItem,buf);
        
        if(manual == 0)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_125);
                    TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                    TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                    GUI_UC_SetEncodeUTF8();        
                    TEXT_SetText(hItem,"Range");
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_126);
                    TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                    TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                    GUI_UC_SetEncodeUTF8();        
                    TEXT_SetText(hItem,"Auto");
                    
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_127);
                    TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                    TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                    GUI_UC_SetEncodeUTF8(); 
                    TEXT_SetText(hItem,"");
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_128);
                    TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                    TEXT_SetFont(hItem,&GUI_FontHZ16);//设定文本字体
                    GUI_UC_SetEncodeUTF8();                         
                    TEXT_SetText(hItem,"");  
                        
                }else{
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_125);
                    TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                    TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                    GUI_UC_SetEncodeUTF8();        
                    TEXT_SetText(hItem,"Range");
                    
                    if(r_raly == 1)
                    {
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_126);
                        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                        GUI_UC_SetEncodeUTF8();        
                        TEXT_SetText(hItem,"2000"); 

                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_127);
                        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                        GUI_UC_SetEncodeUTF8(); 
                        TEXT_SetText(hItem,"m");
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_128);
                        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                        TEXT_SetFont(hItem,&GUI_FontHZ16);//设定文本字体
                        GUI_UC_SetEncodeUTF8();                         
                        TEXT_SetText(hItem,"Ω");                        
                    }else{
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_126);
                        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                        GUI_UC_SetEncodeUTF8();        
                        TEXT_SetText(hItem,"200");
                        
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_127);
                        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
                        GUI_UC_SetEncodeUTF8(); 
                        TEXT_SetText(hItem,"m");
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_128);
                        TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                        TEXT_SetFont(hItem,&GUI_FontHZ16);//设定文本字体
                        GUI_UC_SetEncodeUTF8();                         
                        TEXT_SetText(hItem,"Ω");  
                    }
                }
        
        switch(para_set2){
            case set_2_on:
            {
				if(lang == 0)
                {
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "过流模式");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_FontHZ14);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_43);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "步进时间");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_FontHZ14);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_44);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "起始电流");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_FontHZ14);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_45);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "步进电流");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_FontHZ14);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_118);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "门槛电压");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_FontHZ14);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_145);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "充电电压");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_FontHZ14);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_146);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "充电电流");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_FontHZ14);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_147);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "负载电流");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_FontHZ14);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_152);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "充放测试");
					TEXT_SetBkColor(hItem,0x00BFFFFF);
					TEXT_SetTextColor(hItem, GUI_BLACK);
					TEXT_SetFont(hItem, &GUI_FontHZ14);
				}else{
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "OC Mode");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_Font16_1);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_43);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "Step Time");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_Font16_1);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_44);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "Start C");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_Font16_1);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_45);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "Step C");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_Font16_1);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_118);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "Threshold V");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_Font16_1);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_145);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "Charge V");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_Font16_1);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_146);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "Charge C");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_Font16_1);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_147);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "Load C");
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem, &GUI_Font16_1);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_152);
					GUI_UC_SetEncodeUTF8();
					TEXT_SetText(hItem, "CD TEST");
					TEXT_SetBkColor(hItem,0x00BFFFFF);
					TEXT_SetTextColor(hItem, GUI_BLACK);
					TEXT_SetFont(hItem, &GUI_Font16_1);
				}
				
				if(lang == 0)
                {
					if(staticcdc == 1)
					{
						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_153);
						GUI_UC_SetEncodeUTF8();
						TEXT_SetText(hItem, "开");
						TEXT_SetTextColor(hItem, GUI_WHITE);
						TEXT_SetFont(hItem, &GUI_FontHZ14);
					}else{
						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_153);
						GUI_UC_SetEncodeUTF8();
						TEXT_SetText(hItem, "关");
						TEXT_SetTextColor(hItem, GUI_WHITE);
						TEXT_SetFont(hItem, &GUI_FontHZ14);
					}
				}else{
					if(staticcdc == 1)
					{
						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_153);
						GUI_UC_SetEncodeUTF8();
						TEXT_SetText(hItem, "ON");
						TEXT_SetTextColor(hItem, GUI_WHITE);
						TEXT_SetFont(hItem, &GUI_Font16_1);
					}else{
						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_153);
						GUI_UC_SetEncodeUTF8();
						TEXT_SetText(hItem, "OFF");
						TEXT_SetTextColor(hItem, GUI_WHITE);
						TEXT_SetFont(hItem, &GUI_Font16_1);
					}
				}
				
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_97);
                sprintf(buf,"%.3f",gate_v);
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                TEXT_SetText(hItem,buf);
                TEXT_SetTextColor(hItem, GUI_WHITE);
                
                
                if(lang == 0)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "未测试");
                    TEXT_SetTextColor(hItem, GUI_WHITE);
                    TEXT_SetFont(hItem, &GUI_Fontset_font);
                }else{
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
                    GUI_UC_SetEncodeUTF8();
                    TEXT_SetText(hItem, "Untested");
                    TEXT_SetTextColor(hItem, GUI_WHITE);
                    TEXT_SetFont(hItem, &GUI_Font20_ASCII);
                }
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_46);
                sprintf(buf,"%.3f",dis_init_c);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
//                SET_Current_Laod = set_init_c;

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_47);
                sprintf(buf,"%.3f",dis_sbs_c);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_82);
                sprintf(buf,"%.3f",0.000);
                TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_83);
                sprintf(buf,"%.3f",0.000);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
				
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_151);
                sprintf(buf,"%.3f",0.000);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
				
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_148);
                sprintf(buf,"%.2f",(float)set_static_pv/100);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_149);
                sprintf(buf,"%.3f",(float)set_static_pc/1000);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_150);
                sprintf(buf,"%.3f",(float)set_static_lc/1000);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_117);
                sprintf(buf,"%4d",short_time/10);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
                
                hItem = WM_GetDialogItem(pMsg->hWin,ID_TEXT_130);
                sprintf(buf,"%4d",steptime);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                GUI_UC_SetEncodeUTF8();        
                TEXT_SetText(hItem,buf);
                
                if(oc_mode == 0)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_132);
                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                    TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                    GUI_UC_SetEncodeUTF8();        
                    TEXT_SetText(hItem,"CC");
                }else if(oc_mode == 1){
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_132);
                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                    TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
                    GUI_UC_SetEncodeUTF8();        
                    TEXT_SetText(hItem,"CV");
                }
                
                
                
                break;
            }
            case set_2_off:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_43);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_44);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
               
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_45);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_46);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_47);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_97);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_118);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_98);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_117);
                TEXT_SetText(hItem, "");      
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_130);
                TEXT_SetText(hItem, "");      
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_132);
                TEXT_SetText(hItem, "");
                TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
                break;
            }
        }
        
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
        break;
        
  // USER START (Optionally insert additional message handling)
  // USER END
    default:
        WM_DefaultProc(pMsg);
    break;
  }
}


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateR
*/
WM_HWIN CreateR(void);
WM_HWIN CreateR(void) {
  oc_sw = set_81;
  page_sw = face_r;
  track = face_r;
    con_flag = 0;
    setmode_r();
	C_SW(1);
//    GPIO_SetBits(GPIOA,GPIO_Pin_15);//电子负载OFF
//    GPIO_SetBits(GPIOB,GPIO_Pin_13);
//    r_raly = 1;
//  set_init_c = SET_Current_Laod;
//    r_raly = 1;
  pass = 0;
	gate_v = (float)dis_gate_v/1000;
  hWinR = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWinR;
}

WM_HWIN ResetR(void) {
  hWinR = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWinR;
}


void OC_OP_DOWN(void);
void OC_OP_DOWN(void)
{
    switch(oc_sw)
    {
		case set_81:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_152);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_1);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_72;
            break;
        }
		
        case set_72:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_1);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_20;
            break;
        }
        
        case set_20:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_21;
            break;
        }
        case set_21:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_64;
            break;
        }
        case set_64:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_70;
            break;
        }
        case set_70:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_145);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_75;
            break;
        }
		case set_75:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_145);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_146);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_76;
            break;
        }
        case set_76:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_146);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_147);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_77;
            break;
        }
		case set_77:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_147);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_152);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_81;
            break;
        }
    }
    
}

void OC_OP_UP(void);
void OC_OP_UP(void)
{
    switch(oc_sw)
    {
		case set_81:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_152);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_147);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_77;
            break;
        }
		
        case set_72:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_1);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_152);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_81;
            break;
        }
        
        case set_20:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_1);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_72;
            break;
        }
        case set_21:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_20;
            break;
        }
        case set_64:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_21;
            break;
        }
        case set_70:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_64;
            break;
        }
		case set_75:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_145);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_70;
            break;
        }
		case set_76:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_146);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_145);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_75;
            break;
        }
		case set_77:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_147);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_146);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            oc_sw = set_76;
            break;
        }
        
    }
    
}

//内阻页面过流设置
void OC_SET(void);
void OC_SET(void) {
    vu8 i;
    char  buf[6];

    float dis_init_c;
    float dis_sbs_c;
	float dis_setv;
	float dis_setc;
	float dis_setlc;
    vu16 dis_steptime = steptime;
    switch(oc_sw)
    {
        case set_20:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_46);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<6;i++)
            {
                set_limit[i] = '\0';
            }
            oc_sw = set_22;
            break;
        }
        case set_22:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_46);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
			if(dot_flag == 0){
				set_init_c = atoi(set_limit)*1000;					
			}else if(dot_flag != 0){
				memset(buf, '\0', sizeof(buf));
				strncpy(buf,set_limit,dot_flag + 4);
				set_init_c = atof(buf)*1000;
			}
			if(set_init_c > 30000){
                set_init_c = 0;
            }
            SET_Current_Laod = set_init_c;
            
            dis_init_c = (float)set_init_c/1000;
            sprintf(buf,"%.3f",dis_init_c);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_44);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            Write_Limits();
            
            oc_sw = set_20;
            bit = 0;
            dot_flag = 0;
            break;
        }
        case set_21:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<6;i++)
            {
                set_limit[i] = '\0';
            }
            
            oc_sw = set_23;
            break;
        }
        case set_23:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
			if(dot_flag == 0){
				set_sbs_c = atoi(set_limit)*1000;					
			}else if(dot_flag != 0){
				memset(buf, '\0', sizeof(buf));
				strncpy(buf,set_limit,dot_flag + 4);
				set_sbs_c = atof(buf)*1000;
			}
            dis_sbs_c = (float)set_sbs_c/1000;
            sprintf(buf,"%.3f",dis_sbs_c);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_45);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            Write_Limits();
            
            oc_sw = set_21;
            bit = 0;
            dot_flag = 0;
            break;
        }
        case set_64:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_97);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<6;i++)
            {
                set_limit[i] = '\0';
            }
            
            oc_sw = set_65;
            break;
        }
        case set_65:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_97);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
			if(dot_flag == 0){
				dis_gate_v = atoi(set_limit)*1000;					
			}else if(dot_flag != 0){
				memset(buf, '\0', sizeof(buf));
				strncpy(buf,set_limit,dot_flag + 4);
				dis_gate_v = atof(buf)*1000;
			}
            gate_v = (float)dis_gate_v/1000;
            sprintf(buf,"%.3f",gate_v);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_118);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            Write_Limits();
            
            oc_sw = set_64;
            bit = 0;
            dot_flag = 0;
            break;
        }
        case set_70:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_130);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<6;i++)
            {
                set_limit[i] = '\0';
            }
            
            oc_sw = set_71;
            break;
        }
        case set_71:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_130);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
			if(dot_flag == 0){
				steptime = atoi(set_limit);					
			}else if(dot_flag != 0){
				memset(buf, '\0', sizeof(buf));
				strncpy(buf,set_limit,dot_flag);
				steptime = atof(buf);
			}
            sprintf(buf,"%4d",steptime);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_43);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            Write_Limits();
            
            oc_sw = set_70;
            bit = 0;
            dot_flag = 0;
            Wrtite_step();
            break;
        }
        
        case set_72:
        {
            WM_HWIN hItem;
            if(oc_mode == 0)
            {
                oc_mode = 1;
            }else{
                oc_mode = 0;
            }
            Write_Limits();
            break;
        }
		
		case set_81:
        {
            WM_HWIN hItem;
            if(staticcdc == 0)
            {
                staticcdc = 1;
            }else{
                staticcdc = 0;
            }
            Write_Limits();
            break;
        }
        
		case set_75:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_145);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_148);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<6;i++)
            {
                set_limit[i] = '\0';
            }
            
            oc_sw = set_78;
            break;
        }
        case set_78:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_148);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
			if(dot_flag == 0){
				set_static_pv = atoi(set_limit)*100;					
			}else if(dot_flag != 0){
				memset(buf, '\0', sizeof(buf));
				strncpy(buf,set_limit,dot_flag + 2);
				set_static_pv = atof(buf)*100;
			}
			dis_setv = (float)set_static_pv/100;
            sprintf(buf,"%.2f",dis_setv);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_145);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            Write_Limits();
            
            oc_sw = set_75;
            bit = 0;
            dot_flag = 0;
            break;
        }
		case set_76:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_146);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_149);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<6;i++)
            {
                set_limit[i] = '\0';
            }
            
            oc_sw = set_79;
            break;
        }
        case set_79:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_149);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
			if(dot_flag == 0){
				set_static_pc = atoi(set_limit)*1000;					
			}else if(dot_flag != 0){
				memset(buf, '\0', sizeof(buf));
				strncpy(buf,set_limit,dot_flag + 4);
				set_static_pc = atof(buf)*1000;
			}
			dis_setc = (float)set_static_pc/1000;
            sprintf(buf,"%.3f",dis_setc);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_146);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            Write_Limits();
            
            oc_sw = set_76;
            bit = 0;
            dot_flag = 0;
            break;
        }
		case set_77:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_147);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_150);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<6;i++)
            {
                set_limit[i] = '\0';
            }
            
            oc_sw = set_80;
            break;
        }
        case set_80:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_150);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, GUI_WHITE);
			if(dot_flag == 0){
				set_static_lc = atoi(set_limit)*1000;					
			}else if(dot_flag != 0){
				memset(buf, '\0', sizeof(buf));
				strncpy(buf,set_limit,dot_flag + 4);
				set_static_lc = atof(buf)*1000;
			}
			dis_setlc = (float)set_static_lc/1000;
            sprintf(buf,"%.3f",dis_setlc);
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_147);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            Write_Limits();
            
            oc_sw = set_77;
            bit = 0;
            dot_flag = 0;
            break;
        }
    }
}
void DEL_C(void){
	u8 i;
    switch(oc_sw)
    {
        case set_22:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_46);
			if(bit > 0)
			{
				bit --;
				set_limit[bit] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;        
        }
        case set_23:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
			if(bit > 0)
			{
				bit --;
				set_limit[bit] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;        
        }
        case set_65:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_97);
			if(bit > 0)
			{
				bit --;
				set_limit[bit] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;        
        }
        case set_71:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_130);
			if(bit > 0)
			{
				bit --;
				set_limit[bit] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);  
        }
		case set_78:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_148);
			if(bit > 0)
			{
				bit --;
				set_limit[bit] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
        case set_79:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_149);
			if(bit > 0)
			{
				bit --;
				set_limit[bit] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
        }
        break;
        case set_80:
        {
            WM_HWIN hItem;
 //           WM_InvalidateWindow(load_wind);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_150);
			if(bit > 0)
			{
				bit --;
				set_limit[bit] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;
            
        }
    }
}

//内阻页面数字输入
void INPUT_C(char* num);            
void INPUT_C(char* num){
	u8 i;
    switch(oc_sw)
    {
        case set_22:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_46);
			if(bit < 6)
			{
				strcat(set_limit,num);
				if(dot_flag != 0 && strcmp(num,".") == 0)
				{
					
				}else{			
					
					if(dot_flag == 0 && strcmp(num,".") == 0)
					{
						dot_flag = bit;
					}
					bit ++;
				}
			}else{
				bit = 0;
				for(i=0;i<6;i++)
				{
					set_limit[i] = '\0';
				}
			}
			TEXT_SetText(hItem,set_limit);
//            switch(bit){
//                case 1:
//                {
//					for(i=0;i<6;i++)
//					{
//						set_limit[i] = '\0';
//					}
//                    set_init_c = atoi(num) * 1000;
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    
//                    bit = 2;
//                    break;
//                }
//                case 2:
//                {
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    if(set_limit[1] == 0x2e)//判断输入是否为小数点
//                    {
//                        dot_flag = 1;
//                    }else{
//                        set_init_c = set_init_c * 10 + atoi(num) * 1000;
//                    }
//                    bit = 3;
//                    break;
//                }
//                case 3:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        if(set_limit[2] == 0x2e)//判断输入是否为小数点
//                        {                            
//                            dot_flag = 2;
//                        }else{
//                            set_init_c = 0;
//                        }
//                    }else{
//                        set_init_c = set_init_c + atoi(num) * 100;
//                    }                  
//                    bit = 4;
//                    break;
//                }
//                case 4:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        SET_Current_Laod = 0;
//                    }else if(dot_flag == 2){
//                        set_init_c = set_init_c + atoi(num) * 100;
//                    }else{
//                        set_init_c = set_init_c + atoi(num)*10;
//                    }                  
//                    bit = 5;
//                    break;
//                }
//                case 5:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_init_c = 0;
//                    }else if(dot_flag == 1){
//                        set_init_c = set_init_c + atoi(num);
//                    }else{
//                        set_init_c = set_init_c + atoi(num) * 10;
//                    }                 
//                    bit = 6;
//                    break;
//                }
//                case 6:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_init_c = 0;
//                    }else if(dot_flag == 2){
//                        set_init_c = set_init_c + atoi(num);
//                    }                 
//                    bit = 0;
//                    break;
//                }
//            }
            break;        
        }
        case set_23:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
			if(bit < 6)
			{
				strcat(set_limit,num);
				if(dot_flag != 0 && strcmp(num,".") == 0)
				{
					
				}else{			
					
					if(dot_flag == 0 && strcmp(num,".") == 0)
					{
						dot_flag = bit;
					}
					bit ++;
				}
			}else{
				bit = 0;
				for(i=0;i<6;i++)
				{
					set_limit[i] = '\0';
				}
			}
			TEXT_SetText(hItem,set_limit);
//            switch(bit){
//                case 1:
//                {
//					for(i=0;i<6;i++)
//					{
//						set_limit[i] = '\0';
//					}
//                    set_sbs_c = atoi(num) * 1000;
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    
//                    bit = 2;
//                    break;
//                }
//                case 2:
//                {
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    if(set_limit[1] == 0x2e)//判断输入是否为小数点
//                    {
//                        dot_flag = 1;
//                    }else{
//                        set_sbs_c = set_sbs_c * 10 + atoi(num) * 1000;
//                    }
//                    bit = 3;
//                    break;
//                }
//                case 3:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        if(set_limit[2] == 0x2e)//判断输入是否为小数点
//                        {                            
//                            dot_flag = 2;
//                        }else{
//                            set_sbs_c = 0;
//                        }
//                    }else{
//                        set_sbs_c = set_sbs_c + atoi(num) * 100;
//                    }                  
//                    bit = 4;
//                    break;
//                }
//                case 4:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_sbs_c = 0;
//                    }else if(dot_flag == 2){
//                        set_sbs_c = set_sbs_c + atoi(num) * 100;
//                    }else{
//                        set_sbs_c = set_sbs_c + atoi(num)*10;
//                    }                  
//                    bit = 5;
//                    break;
//                }
//                case 5:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_sbs_c = 0;
//                    }else if(dot_flag == 1){
//                        set_sbs_c = set_sbs_c + atoi(num);
//                    }else{
//                        set_sbs_c = set_sbs_c + atoi(num) * 10;
//                    }                 
//                    bit = 6;
//                    break;
//                }
//                case 6:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_sbs_c = 0;
//                    }else if(dot_flag == 2){
//                        set_sbs_c = set_sbs_c + atoi(num);
//                    }                 
//                    bit = 0;
//                    break;
//                }
//            }
            break;        
        }
        case set_65:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinR);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_97);
			if(bit < 6)
			{
				strcat(set_limit,num);
				if(dot_flag != 0 && strcmp(num,".") == 0)
				{
					
				}else{			
					
					if(dot_flag == 0 && strcmp(num,".") == 0)
					{
						dot_flag = bit;
					}
					bit ++;
				}
			}else{
				bit = 0;
				for(i=0;i<6;i++)
				{
					set_limit[i] = '\0';
				}
			}
			TEXT_SetText(hItem,set_limit);
//            switch(bit){
//                case 1:
//                {
//					for(i=0;i<6;i++)
//					{
//						set_limit[i] = '\0';
//					}
//                    dis_gate_v = atoi(num) * 1000;
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    
//                    bit = 2;
//                    break;
//                }
//                case 2:
//                {
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    if(set_limit[1] == 0x2e)//判断输入是否为小数点
//                    {
//                        dot_flag = 1;
//                    }else{
//                        dis_gate_v = dis_gate_v * 10 + atoi(num) * 1000;
//                    }
//                    bit = 3;
//                    break;
//                }
//                case 3:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        if(set_limit[2] == 0x2e)//判断输入是否为小数点
//                        {                            
//                            dot_flag = 2;
//                        }else{
//                            dis_gate_v = 0;
//                        }
//                    }else{
//                        dis_gate_v = dis_gate_v + atoi(num) * 100;
//                    }                  
//                    bit = 4;
//                    break;
//                }
//                case 4:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        dis_gate_v = 0;
//                    }else if(dot_flag == 2){
//                        dis_gate_v = dis_gate_v + atoi(num) * 100;
//                    }else{
//                        dis_gate_v = dis_gate_v + atoi(num)*10;
//                    }                  
//                    bit = 5;
//                    break;
//                }
//                case 5:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        dis_gate_v = 0;
//                    }else if(dot_flag == 1){
//                        dis_gate_v = dis_gate_v + + atoi(num);
//                    }else{
//                        dis_gate_v = dis_gate_v + atoi(num)*10;
//                    }                 
//                    bit = 6;
//                    break;
//                }
//                case 6:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        dis_gate_v = 0;
//                    }else if(dot_flag == 2){
//                        dis_gate_v = dis_gate_v + atoi(num);
//                    }                 
//                    bit = 0;
//                    break;
//                }
//            }
            break;        
        }
        case set_71:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_130);
			if(bit < 6)
			{
				strcat(set_limit,num);
				if(dot_flag != 0 && strcmp(num,".") == 0)
				{
					
				}else{			
					
					if(dot_flag == 0 && strcmp(num,".") == 0)
					{
						dot_flag = bit;
					}
					bit ++;
				}
			}else{
				bit = 0;
				for(i=0;i<6;i++)
				{
					set_limit[i] = '\0';
				}
			}
			TEXT_SetText(hItem,set_limit);
//            switch(bit){
//                case 1:
//                {
//					for(i=0;i<6;i++)
//					{
//						set_limit[i] = '\0';
//					}
//                    steptime = atoi(num);
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    bit = 2;
//                    break; 
//                }
//                case 2:
//                {
//                    steptime = steptime * 10 + atoi(num);
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    bit = 3;
//                    break; 
//                }
//                case 3:
//                {
//                    steptime = steptime * 10 + atoi(num);
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    bit = 4;
//                    break; 
//                }
//                case 4:
//                {
//                    steptime = steptime * 10 + atoi(num);
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    bit = 0;
//                    break; 
//                }
//            }
            break;           
        }
		case set_78:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_148);
			if(bit < 6)
			{
				strcat(set_limit,num);
				if(dot_flag != 0 && strcmp(num,".") == 0)
				{
					
				}else{			
					
					if(dot_flag == 0 && strcmp(num,".") == 0)
					{
						dot_flag = bit;
					}
					bit ++;
				}
			}else{
				bit = 0;
				for(i=0;i<6;i++)
				{
					set_limit[i] = '\0';
				}
			}
			TEXT_SetText(hItem,set_limit);
//            switch(bit){
//                case 1:
//                {
//					for(i=0;i<6;i++)
//					{
//						set_limit[i] = '\0';
//					}
//                    set_static_pv = atoi(num) * 100;
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    bit = 2;
//                    break;
//                }
//                case 2:
//                {
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    if(set_limit[1] == 0x2e)//判断输入是否为小数点
//                    {
//                        dot_flag = 1;
//                    }else{
//                        set_static_pv = set_static_pv * 10 + atoi(num) * 100;
//                    }
//                    bit = 3;
//                    break;
//                }
//                case 3:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        if(set_limit[2] == 0x2e)//判断输入是否为小数点
//                        {                            
//                            dot_flag = 2;
//                        }else{
//                            set_static_pv = /*3000*/ 6200;
//                        }
//                    }else{
//                        set_static_pv = set_static_pv + atoi(num) * 10;
//                    }
//                                       
//                    bit = 4;
//                    break;
//                }
//                case 4:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_static_pv = /*3000*/ 6200;
//                    }else if(dot_flag == 2){
//                        set_static_pv = set_static_pv + atoi(num) * 10;
//                    }else{
//                        set_static_pv = set_static_pv + atoi(num);
//                    }
//                                       
//                    bit = 5;
//                    break;
//                }
//                case 5:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_static_pv = /*3000*/ 6200;
//                    }else if(dot_flag == 1){
//                        set_static_pv = set_static_pv;
//                    }else{
//                        set_static_pv = set_static_pv + atoi(num);
//                    }
//                                       
//                    bit = 0;
//                    break;
//                }
//            }
            break;
        }
        case set_79:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_149);
			if(bit < 6)
			{
				strcat(set_limit,num);
				if(dot_flag != 0 && strcmp(num,".") == 0)
				{
					
				}else{			
					
					if(dot_flag == 0 && strcmp(num,".") == 0)
					{
						dot_flag = bit;
					}
					bit ++;
				}
			}else{
				bit = 0;
				for(i=0;i<6;i++)
				{
					set_limit[i] = '\0';
				}
			}
			TEXT_SetText(hItem,set_limit);
//            switch(bit){
////                 case 1:
////                 {
////                     SET_Current = atoi(num) * 1000;
////                     strcat(set_limit,num);            
////                     TEXT_SetText(hItem,set_limit);
////                     bit = 2;
////                     break;
////                 }
////                 case 2:
////                 {
////                     strcat(set_limit,num);            
////                     TEXT_SetText(hItem,set_limit);
////                     if(set_limit[1] == 0x2e)//判断输入是否为小数点
////                     {
////                         dot_flag = 1;
////                     }else{
////                         SET_Current = 15000;
////                     }
////                     bit = 3;
////                     break;
////                 }
////                 case 3:
////                 {
////                     strcat(set_limit,num);
////                     TEXT_SetText(hItem,set_limit);
////                     if(dot_flag == 0)
////                     {                                                                       
////                         SET_Current = 15000;
////                     }else{
////                         SET_Current = SET_Current + atoi(num) * 100;
////                     }                                       
////                     bit = 4;
////                     break;
////                 }
////                 case 4:
////                 {
////                     strcat(set_limit,num);
////                     TEXT_SetText(hItem,set_limit);
////                     if(dot_flag == 0)
////                     {
////                         SET_Current = 15000;
////                     }else{
////                         SET_Current = SET_Current + atoi(num) * 10;
////                     }
////                                        
////                     bit = 0;
////                     break;
////                 }
//                case 1:
//                {
//					for(i=0;i<6;i++)
//					{
//						set_limit[i] = '\0';
//					}
//                    set_static_pc = atoi(num) * 1000;
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    bit = 2;
//                    break;
//                }
//                case 2:
//                {
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    if(set_limit[1] == 0x2e)//判断输入是否为小数点
//                    {
//                        dot_flag = 1;
//                    }else{
//                        set_static_pc = set_static_pc * 10 + atoi(num) * 1000;
//                    }
//                    bit = 3;
//                    break;
//                }
//                case 3:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        if(set_limit[2] == 0x2e)//判断输入是否为小数点
//                        {                            
//                            dot_flag = 2;
//                        }else{
//                            set_static_pc = 5000;
//                        }
//                    }else{
//                        set_static_pc = set_static_pc + atoi(num) * 100;
//                    }
//                                       
//                    bit = 4;
//                    break;
//                }
//                case 4:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_static_pc = 5000;
//                    }else if(dot_flag == 2){
//                        set_static_pc = set_static_pc + atoi(num) * 100;
//                    }else{
//                        set_static_pc = set_static_pc + atoi(num) * 10;
//                    }
//                                       
//                    bit = 5;
//                    break;
//                }
//                case 5:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_static_pc = 5000;
//                    }else if(dot_flag == 1){
//                        set_static_pc = set_static_pc + atoi(num);
//                    }else{
//                        set_static_pc = set_static_pc + atoi(num) * 10;
//                    }
//                                       
//                    bit = 6;
//                    break;
//                }
//                case 6:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_static_pc = 0;
//                    }else if(dot_flag == 2){
//                        set_static_pc = set_static_pc + atoi(num);
//                    }                 
//                    bit = 0;
//                    break;
//                }
//            }
        }
        break;
        case set_80:
        {
            WM_HWIN hItem;
 //           WM_InvalidateWindow(load_wind);
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_150);
			if(bit < 6)
			{
				strcat(set_limit,num);
				if(dot_flag != 0 && strcmp(num,".") == 0)
				{
					
				}else{			
					
					if(dot_flag == 0 && strcmp(num,".") == 0)
					{
						dot_flag = bit;
					}
					bit ++;
				}
			}else{
				bit = 0;
				for(i=0;i<6;i++)
				{
					set_limit[i] = '\0';
				}
			}
			TEXT_SetText(hItem,set_limit);
//            switch(bit){
//                case 1:
//                {
//					for(i=0;i<6;i++)
//					{
//						set_limit[i] = '\0';
//					}
//                    set_static_lc = atoi(num) * 1000;
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    
//                    bit = 2;
//                    break;
//                }
//                case 2:
//                {
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    if(set_limit[1] == 0x2e)//判断输入是否为小数点
//                    {
//                        dot_flag = 1;
//                    }else{
//                        set_static_lc = set_static_lc * 10 + atoi(num) * 1000;
//                    }
//                    bit = 3;
//                    break;
//                }
//                case 3:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        if(set_limit[2] == 0x2e)//判断输入是否为小数点
//                        {                            
//                            dot_flag = 2;
//                        }else{
//                            set_static_lc = 0;
//                        }
//                    }else{
//                        set_static_lc = set_static_lc + atoi(num) * 100;
//                    }                  
//                    bit = 4;
//                    break;
//                }
//                case 4:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_static_lc = 0;
//                    }else if(dot_flag == 2){
//                        set_static_lc = set_static_lc + atoi(num) * 100;
//                    }else{
//                        set_static_lc = set_static_lc + atoi(num) * 10;
//                    }                  
//                    bit = 5;
//                    break;
//                }
//                case 5:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_static_lc = 0;
//                    }else if(dot_flag == 1){
//                        set_static_lc = set_static_lc + atoi(num);
//                    }else{
//                        set_static_lc = set_static_lc + atoi(num) * 10;
//                    }                 
//                    bit = 6;
//                    break;
//                }
//                case 6:
//                {
//                    strcat(set_limit,num);
//                    TEXT_SetText(hItem,set_limit);
//                    if(dot_flag == 0)
//                    {
//                        set_static_lc = 0;
//                    }else if(dot_flag == 2){
//                        set_static_lc = set_static_lc + atoi(num);
//                    }                 
//                    bit = 0;
//                    break;
//                }
//            }
            break;
            
        }
    }
}

void OC_CHECK(void){
    WM_HWIN hItem;
    char sbs_c[6];
    float change_sbs_c;   
    crec2 = crec1;
    crec1 = DISS_Current;    
    if(DISS_Voltage * DISS_Current > 200)
    {
         oc_data = crec2;
        SET_Current_Laod = set_init_c;
        hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
        change_sbs_c = (float)set_sbs_c/1000;
        sprintf(sbs_c,"%.3f",change_sbs_c);
        TEXT_SetText(hItem,sbs_c);
        GPIO_SetBits(GPIOA,GPIO_Pin_15);//电子负载OFF   
        t_onoff = 0;
        stepcount = 0;
        oct_sw = oct_off;
        finish = 1;
        oc_test = 0;
        crec1 = 0;
        crec2 = 0;
        rpow = 1;
		step =5;
    }
    if(((crec1 < crec2 && crec2 > 0.3) || v - /*DISS_Voltage*/DISS_Voltage > v*0.9) && para_set2 == set_2_on)
    {
        if(oc_mode == 0)
        {
            //        oc_data = (float)(SET_Current_Laod+csum)/1000;       
            oc_data = crec2;
            SET_Current_Laod = set_init_c;
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
            change_sbs_c = (float)set_sbs_c/1000;
            sprintf(sbs_c,"%.3f",change_sbs_c);
            TEXT_SetText(hItem,sbs_c);
            GPIO_SetBits(GPIOA,GPIO_Pin_15);//电子负载OFF   
            t_onoff = 0;
            stepcount = 0;
            oct_sw = oct_off;
            finish = 1;
            oc_test = 0;
            crec1 = 0;
            crec2 = 0;
            rpow = 1;
			step =5;
        }else if(oc_mode == 1){
            oc_data = crec2;
            GPIO_SetBits(GPIOA,GPIO_Pin_15);//电子负载OFF   
            t_onoff = 0;
            stepcount = 0;
            oct_sw = oct_off;
            finish = 1;
            oc_test = 0;
            crec1 = 0;
            crec2 = 0;
            rpow = 1;
			step =5;
        }

    }
}

           
void OC_ADD(void){
    WM_HWIN hItem;
    char sbs_c[6];
    float change_sbs_c;
    static vu16 csum;
             
    if(v - /*DISS_Voltage*/DISS_Voltage > v*0.9 && para_set2 == set_2_on)
    {
        if(oc_mode == 0)
        {
            //        oc_data = (float)(SET_Current_Laod+csum)/1000;       
            oc_data = crec2;
            SET_Current_Laod = set_init_c;
            hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
            change_sbs_c = (float)set_sbs_c/1000;
            sprintf(sbs_c,"%.3f",change_sbs_c);
            TEXT_SetText(hItem,sbs_c);
            GPIO_SetBits(GPIOA,GPIO_Pin_15);//电子负载OFF   
            t_onoff = 0;
            stepcount = 0;
            oct_sw = oct_off;
            oc_test = 0;
            finish = 1;
            crec1 = 0;
            crec2 = 0;
            rpow = 1;
			step =5;
			
        }else if(oc_mode == 1){
            oc_data = crec2;
            GPIO_SetBits(GPIOA,GPIO_Pin_15);//电子负载OFF   
            t_onoff = 0;
            stepcount = 0;
            oct_sw = oct_off;
            finish = 1;
            crec1 = 0;
            crec2 = 0;
            oc_test = 0;
            rpow = 1;
			step =5;
        }

    }else{
        if(oc_mode == 0)
        {
			
			GPIO_ResetBits(GPIOC,GPIO_Pin_1);//关闭电源输出
			GPIO_SetBits(GPIOC,GPIO_Pin_13);//关闭电源输出继电器
//                GPIO_ResetBits(GPIOC,GPIO_Pin_12);//CC
			flag_Load_CC = 1;
			GPIO_SetBits(GPIOC,GPIO_Pin_10);//CC
			GPIO_ResetBits(GPIOA,GPIO_Pin_15);//电子负载On
			ocf = 1;
            SET_Current_Laod = SET_Current_Laod + set_sbs_c;
            
            if(crec1 < crec2)
            {
                oc_data = crec2;
                SET_Current_Laod = set_init_c;
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_47);
                change_sbs_c = (float)set_sbs_c/1000;
                sprintf(sbs_c,"%.3f",change_sbs_c);
                TEXT_SetText(hItem,sbs_c);
                GPIO_SetBits(GPIOA,GPIO_Pin_15);//电子负载OFF  
                t_onoff = 0;
                stepcount = 0;
                oct_sw = oct_off;
                finish = 1;
                crec1 = 0;
                crec2 = 0;
                oc_test = 0;
                rpow = 1;
				step =5;
            }
        }else if(oc_mode == 1){
            SET_Voltage_Laod = 0;
            crec2 = crec1;
            crec1 = DISS_Current;
            if(crec1 < crec2)
            {
                oc_data = crec2;
                GPIO_SetBits(GPIOA,GPIO_Pin_15);//电子负载OFF   
                t_onoff = 0;
                stepcount = 0;
                oct_sw = oct_off;
                finish = 1;
                crec1 = 0;
                crec2 = 0;
                oc_test = 0;
                rpow = 1;
				step =5;
            }
        }       
    }        
}

void test_r(void)
{
    WM_HWIN hItem;
	u32 rcomp;
    if(para_set2 == set_2_off)
    {
		if(DISS_Voltage < 0.3)
		{
			rcomp = 0;
		}else{
			rcomp = R_VLUE;
		}
		if(rcomp != 0)
		{
			if(rcomp > set_max_r || rcomp < set_min_r || DISS_Voltage*1000 > set_max_v || DISS_Voltage*1000 < set_min_v)
			{
				if(para_set4 == set_4_on){
					BEEP_Tiggr();
				}
				TM1650_SET_LED(0x68,0x70);//FAIL灯
				GPIO_SetBits(GPIOD,GPIO_Pin_12);//
				if(R_VLUE > set_max_r || R_VLUE < set_min_r)
				{
					hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
					TEXT_SetTextColor(hItem, GUI_RED);
				}else{
					hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
					TEXT_SetTextColor(hItem, GUI_GREEN);
				}
				if(DISS_Voltage*1000 > set_max_v || DISS_Voltage*1000 < set_min_v){
					hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
					TEXT_SetTextColor(hItem, GUI_RED);
				}else{
					hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
					TEXT_SetTextColor(hItem, GUI_GREEN);
				}
			}else{
				hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
				TEXT_SetTextColor(hItem, GUI_GREEN);
				hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
				TEXT_SetTextColor(hItem, GUI_GREEN);
				
				GPIO_ResetBits(GPIOD,GPIO_Pin_12);
				TM1650_SET_LED(0x48,0x71);
				TM1650_SET_LED(0x68,0xF2);//PASS灯
			}
		}else{
			hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
			TEXT_SetTextColor(hItem, GUI_GREEN);
			hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
			TEXT_SetTextColor(hItem, GUI_GREEN);
			
			TM1650_SET_LED(0x68,0x70);
			GPIO_ResetBits(GPIOD,GPIO_Pin_12);//灭灯
		}
    }else{
        if(finish == 0)
        {
            if(r > set_max_r || r < set_min_r || DISS_Voltage*1000 > set_max_v || DISS_Voltage*1000 < set_min_v)
            {
                if(para_set4 == set_4_on){
                    BEEP_Tiggr();
                }
                TM1650_SET_LED(0x68,0x70);//FAIL灯
                GPIO_SetBits(GPIOD,GPIO_Pin_12);//
                if(r > set_max_r || r < set_min_r)
                {
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                    TEXT_SetTextColor(hItem, GUI_RED);
                }else{
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
                }
                if(DISS_Voltage*1000 > set_max_v || DISS_Voltage*1000 < set_min_v){
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                    TEXT_SetTextColor(hItem, GUI_RED);
                }else{
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
                }
            }else{
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                TEXT_SetTextColor(hItem, GUI_GREEN);
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                TEXT_SetTextColor(hItem, GUI_GREEN);
                
                GPIO_ResetBits(GPIOD,GPIO_Pin_12);
                TM1650_SET_LED(0x48,0x71);
                TM1650_SET_LED(0x68,0xF2);//PASS灯
            }
        }else{
            if(r > set_max_r || r < set_min_r || v*1000 > set_max_v || v*1000 < set_min_v || oc_data*1000 > set_max_c || oc_data*1000 < set_min_c || static_lv*1000 > set_max_lv || static_lv*1000 < set_min_lv || static_pc*1000 > set_max_pc || static_pc*1000 < set_min_pc)
            {
                if(para_set4 == set_4_on){
                    BEEP_Tiggr();
                }
                TM1650_SET_LED(0x68,0x70);//FAIL灯
                GPIO_SetBits(GPIOD,GPIO_Pin_12);//
                if(r > set_max_r || r < set_min_r)
                {
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                    TEXT_SetTextColor(hItem, GUI_RED);
                }else{
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
                }
                if(v*1000 > set_max_v || v*1000 < set_min_v){
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                    TEXT_SetTextColor(hItem, GUI_RED);
                }else{
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
                }
                if(oc_data*1000 > set_max_c || oc_data*1000 < set_min_c){
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_82);
                    TEXT_SetTextColor(hItem, GUI_RED);
                }else{
                    hItem = WM_GetDialogItem(hWinR, ID_TEXT_82);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
                }
				
				if(static_lv*1000 > set_max_lv || static_lv*1000 < set_min_lv)
				{
					hItem = WM_GetDialogItem(hWinR, ID_TEXT_83);
                    TEXT_SetTextColor(hItem, GUI_RED);
				}else{
					hItem = WM_GetDialogItem(hWinR, ID_TEXT_83);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
				}
				
				if(static_pc*1000 > set_max_pc || static_pc*1000 < set_min_pc)
				{
					hItem = WM_GetDialogItem(hWinR, ID_TEXT_151);
                    TEXT_SetTextColor(hItem, GUI_RED);
				}else{
					hItem = WM_GetDialogItem(hWinR, ID_TEXT_151);
                    TEXT_SetTextColor(hItem, GUI_GREEN);
				}
				
            }else{
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_80);
                TEXT_SetTextColor(hItem, GUI_GREEN);
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_81);
                TEXT_SetTextColor(hItem, GUI_GREEN);
                hItem = WM_GetDialogItem(hWinR, ID_TEXT_82);
                TEXT_SetTextColor(hItem, GUI_GREEN);				
				hItem = WM_GetDialogItem(hWinR, ID_TEXT_83);
                TEXT_SetTextColor(hItem, GUI_GREEN);
				hItem = WM_GetDialogItem(hWinR, ID_TEXT_151);
                TEXT_SetTextColor(hItem, GUI_GREEN);
                
                GPIO_ResetBits(GPIOD,GPIO_Pin_12);
                TM1650_SET_LED(0x48,0x71);
                TM1650_SET_LED(0x68,0xF2);//PASS灯
            }
        }
               
    }
//     else
//     {
//         TM1650_SET_LED(0x68,0x70);
//         GPIO_ResetBits(GPIOD,GPIO_Pin_12);//灭灯
//     }
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
