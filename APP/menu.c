/******************************************************************/
/* 名称：                                                  */
/* 效果：                                                        */
/* 内容：电源界面                                                       */
/* 作者：zhan                                                  */
/* 联系方式QQ:363116119                                        */
/******************************************************************/
#include "MainTask.h"
#include  "gui.h"
#include "my_register.h" 
#include "tm1650.h"
#include "stdio.h"
#include "stdlib.h"
#include "key.h"
#include "string.h"
#include "beep.h"
#include "internalflash.h"

WM_HWIN hWinWind;
void test_pow(void);

vu8 pow_sw = pow_off;
extern vu16 menu_time;
extern vu16 s_time;
extern vu8 wait_flag;
extern vu8 test_num;
float pow_cutoffc;

#define ID_WINDOW_0      	(GUI_ID_USER + 0x00)
#define ID_BUTTON_0     	(GUI_ID_USER + 0x01)
#define ID_BUTTON_1     	(GUI_ID_USER + 0x02)
#define ID_BUTTON_2     	(GUI_ID_USER + 0x03)
#define ID_BUTTON_3     	(GUI_ID_USER + 0x04)
#define ID_BUTTON_4     	(GUI_ID_USER + 0x05)
#define ID_BUTTON_5     	(GUI_ID_USER + 0x06)
#define ID_TEXT_9    	 	(GUI_ID_USER + 0x07)
#define ID_TEXT_10     		(GUI_ID_USER + 0x08)
#define ID_TEXT_15     		(GUI_ID_USER + 0x20)
#define ID_TEXT_16    		(GUI_ID_USER + 0x21)
#define ID_TEXT_33    	    (GUI_ID_USER + 0x3D)
#define ID_TEXT_34    	    (GUI_ID_USER + 0x3E)
#define ID_TEXT_41    	    (GUI_ID_USER + 0x66)
#define ID_TEXT_42    	    (GUI_ID_USER + 0x67)
#define ID_TEXT_86          (GUI_ID_USER + 0x93)
#define ID_TEXT_87          (GUI_ID_USER + 0x94)
#define ID_TEXT_88          (GUI_ID_USER + 0x95)
#define ID_TEXT_115         (GUI_ID_USER + 0x10B)
#define ID_TEXT_125         (GUI_ID_USER + 0x10C)
#define ID_TEXT_144         (GUI_ID_USER + 0x012E)
#define ID_TEXT_159         (GUI_ID_USER + 0x013A)
#define ID_TEXT_161         (GUI_ID_USER + 0x013C)
#define ID_TimerTime2    3

static const GUI_WIDGET_CREATE_INFO _aDialogCreate1[] = {
    { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 480, 272, 0, 0x0, 0 },
//    { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 3, 226, 77, 45, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 83, 226, 77, 45, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 163, 226, 77, 45, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 243, 226, 77, 45, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "Button", ID_BUTTON_4, 323, 226, 77, 45, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "Button", ID_BUTTON_5, 403, 226, 77, 45, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_9,   28, 50, 64, 32, 0, 0x64, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_10,  28, 120, 64, 32, 0, 0x64, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_15,  240, 50, 32, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_16,  240, 121, 32, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_33, 290, 75, 80, 20, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_34, 290, 100, 80, 20, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_41, 380, 75, 53, 20, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_42, 370, 100, 65, 20, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_86, 95, 48, 150, 40, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_87, 95, 116, 150, 40, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_88, 400, 4, 50, 20, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_115, 95, 184, 150, 40, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_125, 300, 2, 80, 20, 0, 0x0, 0 },
    { TEXT_CreateIndirect,   "Text",   ID_TEXT_144, 370, 150, 65, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect,   "Text",   ID_TEXT_159, 290, 150, 80, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_161, 380, 8, 20, 15, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};


static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  static vu8 status_flash;
  char buf[5];    

  float dis_output_v = (float)pow_v/100;
  float dis_output_c = (float)SET_Current/1000;
  static u8 cdelay,vdec;
  
  
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {

	case WM_PAINT://无效化重绘
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
//      GUI_SetFont(&GUI_FontD24x32);//
// 		GUI_GotoXY(95,72);//设置显示坐标
// 		GUI_DispFloatFix(DISS_POW_Voltage,5,2);//显示电压值
// 		GUI_GotoXY(95,140);//设置显示坐标
// 		GUI_DispFloatFix(DISS_POW_Current,5,2);//显示电流值
        GUI_SetFont(&GUI_Font24_1);
        GUI_DispStringAt("V",435,75);
        GUI_DispStringAt("A",435,100);
        GUI_DispStringAt("A",435,150);
        
        GUI_SetFont(&GUI_FontEN40);
        GUI_SetColor(GUI_LIGHTGRAY);
        GUI_DispStringAt("C:", 28, 190);
        GUI_SetColor(GUI_LIGHTGRAY);
        GUI_DispStringAt("m", 217+24, 196);
        GUI_DispStringAt("AH", 238+24, 187);
        
        GUI_SetColor(GUI_GREEN);
        GUI_SetFont(&GUI_Fontunit);
        GUI_DispStringAt("°",342, 2);
        GUI_SetFont(&GUI_Font24_1);
        GUI_DispStringAt("C",350, 2);
//        DrawLock();
//        GUI_SetColor(GUI_WHITE);
//        GUI_SetFont(&GUI_Fontset_font);
//        GUI_DispStringAt("过充电压",290, 150);
		break;
    
	case WM_TIMER://定时模块消息
	if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime2)
	{
//        lockstat2 = lockstat1;
//        lockstat1 = lock;
//        if(lockstat1 != lockstat2)
//        {
//            WM_InvalidateWindow(hWinWind);
//        }
//         if(clear_flag2 == 1)
//         {
		if(lock == 1)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_161);
			TEXT_SetText(hItem,"锁");
		}else{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_161);
			TEXT_SetText(hItem,"");
		}
		if(disloadv < 0.1)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_86);
			sprintf(buf,"%.3f",0.00);       
			TEXT_SetText(hItem,buf);
		}else{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_86);
			sprintf(buf,"%.3f",disloadv);       
			TEXT_SetText(hItem,buf);
		}
//         }else{
//             hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_86);
//             sprintf(buf,"%.2f",DISS_POW_Voltage);       
//             TEXT_SetText(hItem,buf);
//         }
        
        
       
        
//        test_pow();
        if(pow_sw == pow_on)
        {
//			if((int)(disloadv*1000) > SET_Voltage*10 && vdec > 30)
//			{
//				Contr_Voltage --;
//				vdec = 0;
//			}else{
//				vdec ++;
//			}
            battery_c = (int)bc_raw;
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_115);
            sprintf(buf,"%06d",battery_c);      
            TEXT_SetText(hItem,buf);
             hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_87);
            sprintf(buf,"%.3f",DISS_POW_Current);        
            TEXT_SetText(hItem,buf);
            if(status_flash == 0){
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_88);
                TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
                 if(lang == 0)
                {
                    TEXT_SetFont(hItem,&GUI_FontHZ16);//设定文本字体
                    GUI_UC_SetEncodeUTF8();        
                    TEXT_SetText(hItem,"充电中");
                }else{
                    TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
                    GUI_UC_SetEncodeUTF8();        
                    TEXT_SetText(hItem,"Charging");
                }
                status_flash = 1;
            }else{
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_88);
                TEXT_SetText(hItem,"");
                status_flash = 0;
           }
           if(pow_cutoffc != 0 && DISS_POW_Current < pow_cutoffc && cdelay > 20)
           {
              GPIO_ResetBits(GPIOC,GPIO_Pin_1);
              GPIO_SetBits(GPIOC,GPIO_Pin_13);
              mode_sw = 0;
              pow_sw = pow_off;
              cdelay = 0;
           }else{
               cdelay++;
           }
        }else{
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_88);
            TEXT_SetText(hItem,"");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_87);
            sprintf(buf,"%.3f",0.000);        
            TEXT_SetText(hItem,buf);
            
            cdelay = 0;
        }
//        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_144);       
//        sprintf(buf,"%.3f",overchargev);
//        TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_125);       
        sprintf(buf,"%.1f",temp);
        TEXT_SetText(hItem,buf);
        
		WM_RestartTimer(pMsg->Data.v, 50);//复位定时器数值越大刷新时间越短
	}
	break;
  case WM_INIT_DIALOG://重绘外观
    //
    // Initialization of 'Window'
    //
        hItem = pMsg->hWin;
        WINDOW_SetBkColor(hItem, GUI_BLACK);
        WM_CreateTimer(hItem,ID_TimerTime2,1000,0);//创建本窗口定时器
    //
    // Initialization of 'Button'
    //
//         hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
// 		BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
// 		BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
// 		GUI_UC_SetEncodeUTF8();
// 		BUTTON_SetText(hItem,"充放电");
    //
    // Initialization of 'Button'
    //
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_161);
		TEXT_SetTextColor(hItem, GUI_RED);//设置字体颜色
		TEXT_SetFont(hItem,&GUI_FontHZ14);
		TEXT_SetText(hItem,"");
		
		
       if(lang == 0)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem, "内阻测试");
        //
        // Initialization of 'Button'
        //
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem, "程控负载");
        //
        // Initialization of 'Button'
        //
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
            BUTTON_SetPressed(hItem,1);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem, "程控电源");
        //
        // Initialization of 'Button'
        //
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem, "充放电");
        //
        // Initialization of 'Button'
        //
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem, "曲线");
        }else{
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem, "I.R. TEST");
        //
        // Initialization of 'Button'
        //
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem, "LOAD");
        //
        // Initialization of 'Button'
        //
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
            BUTTON_SetPressed(hItem,1);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem, "POWER");
        //
        // Initialization of 'Button'
        //
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem, "C&DC");
        //
        // Initialization of 'Button'
        //
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
            BUTTON_SetTextColor(hItem,0,GUI_BLACK);//设置字体颜色为黑色
            BUTTON_SetFont      (hItem,    &GUI_Font16B_ASCII);//设定按钮文本字体
            GUI_UC_SetEncodeUTF8();
            BUTTON_SetText(hItem, "GRAPH");
        }
		
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
		TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"V:");
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
		TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"I:");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_15);
		TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"V");
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_16);
		TEXT_SetTextColor(hItem, GUI_LIGHTGRAY);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontEN40);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"A");
        
		if(lang == 0)
        {
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_33);
			TEXT_SetTextColor(hItem, GUI_BLACK);//设置字体颜色
			TEXT_SetBkColor(hItem,0x00BFFFFF);
			TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
			GUI_UC_SetEncodeUTF8();
			TEXT_SetText(hItem,"输出电压");        
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_34);
			TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
			TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
			GUI_UC_SetEncodeUTF8();
			TEXT_SetText(hItem,"限制电流");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_159);
			TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
			TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
			GUI_UC_SetEncodeUTF8();
			TEXT_SetText(hItem,"截止电流");
		}else{
			 hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_33);
            TEXT_SetTextColor(hItem, GUI_BLACK);//设置字体颜色
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"Output V");        
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_34);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
            GUI_UC_SetEncodeUTF8();
            TEXT_SetText(hItem,"Limiting C");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_159);
			TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
			TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
			GUI_UC_SetEncodeUTF8();
			TEXT_SetText(hItem,"Cutoff C");
		}
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_41);
        sprintf(buf,"%.2f",dis_output_v);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_42);
        sprintf(buf,"%.3f",dis_output_c);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_86);
        sprintf(buf,"%.3f",0.00);
		TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_87);
        sprintf(buf,"%.3f",0.000);
		TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_115);
        sprintf(buf,"%05d",0);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_FontD24x32);//设定文本字体
        GUI_UC_SetEncodeUTF8();        
        TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_125);
        TEXT_SetTextColor(hItem, GUI_GREEN);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体       
        sprintf(buf,"%.1f",temp);
        TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_144);
        sprintf(buf,"%.3f",pow_cutoffc);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();     
		TEXT_SetText(hItem,buf);
        
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
				
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_4: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_5: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

WM_HWIN CreateWindow(void) {
  if(page_sw == face_graph || page_sw == face_menu)
  {      
  }else{
	  GPIO_SetBits(GPIOA,GPIO_Pin_15);//µç×Ó¸ºÔØOFF
	  GPIO_ResetBits(GPIOC,GPIO_Pin_1);//¹Ø±ÕµçÔ´Êä³ö
	  Delay_ms(500);
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);//¹Ø±ÕµçÔ´Êä³ö¼ÌµçÆ
//      IO_OFF();
	  
  }
  page_sw = face_menu;
  track = face_menu;
  set_sw = set_10;
//  SET_Voltage = pow_v-12;
  SET_Voltage = pow_v;
  SET_Current = pow_c;
  pow_cutoffc = (float)set_pow_cutoffc/1000;
  pass = 0;
  mode_sw = mode_pow;
//  USART_SendData(USART3,1);//连接电源
  TM1650_SET_LED(0x68,0x70);
  GPIO_ResetBits(GPIOD,GPIO_Pin_12);//灭灯
  hWinWind = GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog, WM_HBKWIN, 0, 0);
  return hWinWind;
}

WM_HWIN ResetPow(void) {
    hWinWind = GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog, WM_HBKWIN, 0, 0);
//    WM_InvalidateWindow(hWinWind);
    return hWinWind;
}


void MENU_OP_DOWN(void);
void MENU_OP_DOWN(void)
{
    switch(set_sw)
    {
        case set_10:
        {
            WM_HWIN hItem;
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_33);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_34);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_11;
            break;
        }
        case set_11:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_34);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
            
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_159);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);

            set_sw = set_88;
            break;
        }                     
        default: break;
    }
}

void MENU_OP_UP(void);
void MENU_OP_UP(void)
{
    switch(set_sw)
    {
        case set_11:
		{
			 WM_HWIN hItem;
//                 WM_InvalidateWindow(hWinWind);
			 hItem = WM_GetDialogItem(hWinWind, ID_TEXT_34);
			 TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
			 TEXT_SetTextColor(hItem, GUI_WHITE);
		   
			 hItem = WM_GetDialogItem(hWinWind, ID_TEXT_33);
			 TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
			 TEXT_SetTextColor(hItem, GUI_BLACK);

			 set_sw = set_10;
			 break;
		 } 
		case set_88:
		{
			 WM_HWIN hItem;
//                 WM_InvalidateWindow(hWinWind);
			 hItem = WM_GetDialogItem(hWinWind, ID_TEXT_159);
			 TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
			 TEXT_SetTextColor(hItem, GUI_WHITE);
		   
			 hItem = WM_GetDialogItem(hWinWind, ID_TEXT_34);
			 TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
			 TEXT_SetTextColor(hItem, GUI_BLACK);

			 set_sw = set_11;
			 break;
		 }                     
		 default: break;
    }
}

//电源界面设置确认
void MENU_SET(void);
void MENU_SET(void)
{
    vu8 i;
    char buf[6];    

    float dis_output_v;
    float dis_output_c; 
    
    if(SET_Voltage > /*3000*/ 6200)
    {
      SET_Voltage = /*3000*/ 6200;
    }
    if(SET_Current > 10000)
    {
      SET_Current = 10000;
    }
    switch(set_sw){
        case set_10:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_33);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
                   
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_41);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<6;i++)
            {
                set_limit[i] = '\0';
            }

            set_sw = set_18;
            break;                        
        }
        case set_18:
        {           
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_41);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
			if(dot_flag == 0){
				pow_v = atoi(set_limit)*100;					
			}else if(dot_flag != 0){
				memset(buf, '\0', sizeof(buf));
				strncpy(buf,set_limit,dot_flag + 3);
				pow_v = atof(buf)*100;
			}
			if(pow_v > 6200)
			{
				pow_v = 6200;
			}
			if(pow_v/100 * SET_Current/1000 > 200)
            {
                pow_v = 0;
            }
//            SET_Voltage = pow_v - 12;
			SET_Voltage = pow_v;
            
            dis_output_v = (float)pow_v/100;
            
            sprintf(buf,"%.2f",dis_output_v);
            TEXT_SetText(hItem,buf);
            
                                                                     
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_33);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);
                            
            Write_Limits();
            set_sw = set_10;
            bit = 0;
            dot_flag = 0;
            break; 
         }
         case set_11:
         {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_34);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
                                
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_42);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<6;i++)
            {
                set_limit[i] = '\0';
            }

            set_sw = set_19;
            break;                        
         }
         case set_19:
         {           
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_42);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
			if(dot_flag == 0){
				pow_c = atoi(set_limit)*1000;					
			}else if(dot_flag != 0){
				memset(buf, '\0', sizeof(buf));
				strncpy(buf,set_limit,dot_flag + 4);
				pow_c = atof(buf)*1000;
			}
              
            if(pow_c > 10000)
            {
                pow_c = 10000;               
            }
			if(pow_v/100 * pow_c/1000 > 200)
            {
                pow_c = 0;
            }
			SET_Current = pow_c;
            
            dis_output_c = (float)SET_Current/1000;
            sprintf(buf,"%.3f",dis_output_c);
            TEXT_SetText(hItem,buf);            
                   
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_34);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);
                                                 
            Write_Limits();
            set_sw = set_11;
            bit = 0;
            dot_flag = 0;
            break; 
         }
		 case set_88:
         {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_159);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
                                
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_144);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);
            for(i=0;i<6;i++)
            {
                set_limit[i] = '\0';
            }

            set_sw = set_89;
            break;                        
         }
         case set_89:
         {           
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_144);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
            TEXT_SetTextColor(hItem, GUI_WHITE);
			if(dot_flag == 0){
				set_pow_cutoffc = atoi(set_limit)*1000;					
			}else if(dot_flag != 0){
				memset(buf, '\0', sizeof(buf));
				strncpy(buf,set_limit,dot_flag + 4);
				set_pow_cutoffc = atof(buf)*1000;
			}
            if(set_pow_cutoffc > 10000)
            {
                set_pow_cutoffc = 10000;               
            }
            pow_cutoffc = (float)set_pow_cutoffc/1000;
            sprintf(buf,"%.3f",pow_cutoffc);
            TEXT_SetText(hItem,buf);            
                   
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_159);
            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
            TEXT_SetTextColor(hItem, GUI_BLACK);
                                                 
            Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
            set_sw = set_88;
            bit = 0;
            dot_flag = 0;
            break; 
         }
         default:break;
     }
}
void DEL_POW(void)
{
	switch(set_sw){
		case set_18:
        {
			WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_41);
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
		}break;
		case set_19:
        {
			WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_42);
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
		}break;
		case set_89:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_144);
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
		}break;
	}
}



void INPUT_POW(char* num);            
void INPUT_POW(char* num){ 
	u8 i;
    switch(set_sw){
		case set_18:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_41);
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
//                    pow_v = atoi(num) * 100;
//                    strcat(set_limit,num);            
//                    TEXT_SetText(hItem,set_limit);
//                    bit = 2;
//                    break;
//                }
//                case 2:
//                {
//                    strcat(set_limit,num);
//					if(set_limit[bit-1] == 0x62){
//						set_limit[bit-1] = '\0';
//						set_limit[bit-2] = '\0';
//						bit -= 1;
//						pow_v = pow_v - atoi(num) * 100;
//						TEXT_SetText(hItem,set_limit);
//						break;
//					}
//                    if(set_limit[1] == 0x2e)//判断输入是否为小数点
//                    {
//                        dot_flag = 1;
//                    }else{
//                        pow_v = pow_v * 10 + atoi(num) * 100;
//                    }           
//                    TEXT_SetText(hItem,set_limit);
//                    bit = 3;
//                    break;
//                }
//                case 3:
//                {
//                    strcat(set_limit,num);
//					if(set_limit[bit-1] == 0x62){
//						set_limit[bit-1] = '\0';
//						set_limit[bit-2] = '\0';
//						bit -= 1;
//						TEXT_SetText(hItem,set_limit);
//						break;
//					}
//                    if(dot_flag == 0)
//                    {
//                        if(set_limit[2] == 0x2e)//判断输入是否为小数点
//                        {                            
//                            dot_flag = 2;
//                        }else{
//                            pow_v = /*3000*/ 6200;
//                        }
//                    }else{
//						pow_v = pow_v + atoi(num) * 10;
//                    }
//                    TEXT_SetText(hItem,set_limit);                  
//                    bit = 4;
//                    break;
//                }
//                case 4:
//                {
//                    strcat(set_limit,num);
//					if(set_limit[bit-1] == 0x62){
//						set_limit[bit-1] = '\0';
//						set_limit[bit-2] = '\0';
//						bit -= 1;
//						TEXT_SetText(hItem,set_limit);
//						pow_v = pow_v - atoi(num) * 10;
//						break;
//					}
//                    if(dot_flag == 0)
//                    {
//                        pow_v = /*3000*/ 6200;
//                    }else if(dot_flag == 2){
//                        pow_v = pow_v + atoi(num) * 10;
//                    }else{
//                        pow_v = pow_v + atoi(num);
//                    }
//                    TEXT_SetText(hItem,set_limit);                   
//                    bit = 5;
//                    break;
//                }
//                case 5:
//                {
//                    strcat(set_limit,num);
//					if(set_limit[bit-1] == 0x62){
//						set_limit[bit-1] = '\0';
//						set_limit[bit-2] = '\0';
//						bit -= 1;
//						TEXT_SetText(hItem,set_limit);
//						break;
//					}
//                    if(dot_flag == 0)
//                    {
//                        pow_v = /*3000*/ 6200;
//                    }else if(dot_flag == 1){
//                        pow_v = pow_v;
//                    }else{
//                        pow_v = pow_v + atoi(num);
//                    }
//                    TEXT_SetText(hItem,set_limit);                   
//                    bit = 0;
//                    break;
//                }
//            }
            break;
        }
        case set_19:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_42);
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
//                    pow_c = atoi(num) * 1000;
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
//                        pow_c = pow_c * 10 + atoi(num) * 1000;
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
//                            pow_c = 5000;
//                        }
//                    }else{
//                        pow_c = pow_c + atoi(num) * 100;
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
//                        pow_c = 5000;
//                    }else if(dot_flag == 2){
//                        pow_c = pow_c + atoi(num) * 100;
//                    }else{
//                        pow_c = pow_c + atoi(num) * 10;
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
//                        pow_c = 5000;
//                    }else if(dot_flag == 1){
//                        pow_c = pow_c + atoi(num);
//                    }else{
//                        pow_c = pow_c + atoi(num) * 10;
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
//                        pow_c = 0;
//                    }else if(dot_flag == 2){
//                        pow_c = pow_c + atoi(num);
//                    }                 
//                    bit = 0;
//                    break;
//                }
//            }
        }
        break;
		case set_89:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinWind);
            hItem = WM_GetDialogItem(hWinWind, ID_TEXT_144);
			if(bit < 7)
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
//                    set_pow_cutoffc = atoi(num) * 1000;
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
//                        set_pow_cutoffc = set_pow_cutoffc * 10 + atoi(num) * 1000;
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
//                            set_pow_cutoffc = 5000;
//                        }
//                    }else{
//                        set_pow_cutoffc = set_pow_cutoffc + atoi(num) * 100;
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
//                        set_pow_cutoffc = 5000;
//                    }else if(dot_flag == 2){
//                        set_pow_cutoffc = set_pow_cutoffc + atoi(num) * 100;
//                    }else{
//                        set_pow_cutoffc = set_pow_cutoffc + atoi(num) * 10;
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
//                        set_pow_cutoffc = 5000;
//                    }else if(dot_flag == 1){
//                        set_pow_cutoffc = set_pow_cutoffc + atoi(num);
//                    }else{
//                        set_pow_cutoffc = set_pow_cutoffc + atoi(num) * 10;
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
//                        set_pow_cutoffc = 0;
//                    }else if(dot_flag == 2){
//                        set_pow_cutoffc = set_pow_cutoffc + atoi(num);
//                    }                 
//                    bit = 0;
//                    break;
//                }
//            }
        }
        break;
    }    
}

void test_pow(void)
{

    if(pow_sw == pow_on && para_set1 == set_1_on)
    {
        if(DISS_POW_Voltage*100 > set_max_v || DISS_POW_Voltage*100 < set_min_v || DISS_POW_Current * 100 > set_max_c || DISS_POW_Current * 100 < set_min_c)
        {
            if(para_set4 == set_4_on){
                BEEP_Tiggr();
            }
            TM1650_SET_LED(0x68,0x70);//FAIL灯
            GPIO_SetBits(GPIOD,GPIO_Pin_12);//            
        }else{
            GPIO_ResetBits(GPIOD,GPIO_Pin_12);
            TM1650_SET_LED(0x48,0x71);
            TM1650_SET_LED(0x68,0xF2);//PASS灯
        }        
    }else
    {
        TM1650_SET_LED(0x68,0x70);
        GPIO_ResetBits(GPIOD,GPIO_Pin_12);//灭灯
    }
}

