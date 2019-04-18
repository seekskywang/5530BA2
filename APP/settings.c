/******************************************************************/
/* ĻԆú                                                  				*/
/* Чڻú                                                        */
/* ŚɝúȺПͼާĦ                                             */
/* ط֟ú                                                 */
/* jϵ׽ʽQQ:                                        */


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
#include "internalflash.h"

WM_HWIN hWinset;
extern int count_num(int data);
int32_t InFlashSave[40];
vu8 test_mode;

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_6     (GUI_ID_USER + 0x2A)
#define ID_TEXT_21      (GUI_ID_USER + 0x2B)
#define ID_TEXT_22      (GUI_ID_USER + 0x2C)
#define ID_TEXT_23      (GUI_ID_USER + 0x2D)
#define ID_TEXT_24   	(GUI_ID_USER + 0x2E)
#define ID_TEXT_25   	(GUI_ID_USER + 0x2F)
#define ID_TEXT_26      (GUI_ID_USER + 0x30)
#define ID_TEXT_27     	(GUI_ID_USER + 0x31)
#define ID_TEXT_28     	(GUI_ID_USER + 0x32)
#define ID_TEXT_29     	(GUI_ID_USER + 0x33)
#define ID_TEXT_30    	(GUI_ID_USER + 0x34)
#define ID_TEXT_31    	(GUI_ID_USER + 0x3B)
#define ID_TEXT_32    	(GUI_ID_USER + 0x3C)
#define ID_TEXT_35     	(GUI_ID_USER + 0x60)  
#define ID_TEXT_36     	(GUI_ID_USER + 0x61)
#define ID_TEXT_37     	(GUI_ID_USER + 0x62)
#define ID_TEXT_38    	(GUI_ID_USER + 0x63)
#define ID_TEXT_39    	(GUI_ID_USER + 0x64)
#define ID_TEXT_40    	(GUI_ID_USER + 0x65)
#define ID_TEXT_90     	(GUI_ID_USER + 0x9E)
#define ID_TEXT_91     	(GUI_ID_USER + 0x9F)
#define ID_TEXT_92     	(GUI_ID_USER + 0x0100)
#define ID_TEXT_93     	(GUI_ID_USER + 0x0101)
#define ID_TEXT_94     	(GUI_ID_USER + 0x0102)
#define ID_TEXT_95     	(GUI_ID_USER + 0x0103)
#define ID_TEXT_133    	(GUI_ID_USER + 0x0122)
#define ID_TEXT_134     (GUI_ID_USER + 0x0123)
#define ID_BUTTON_30    (GUI_ID_USER + 0x35)
#define ID_BUTTON_31    (GUI_ID_USER + 0x36)
#define ID_BUTTON_32    (GUI_ID_USER + 0x37)
#define ID_BUTTON_33   	(GUI_ID_USER + 0x38)
#define ID_BUTTON_34   	(GUI_ID_USER + 0x39)
#define ID_BUTTON_35    (GUI_ID_USER + 0x3A)
#define ID_TEXT_129     (GUI_ID_USER + 0x10A)
#define ID_TEXT_154     (GUI_ID_USER + 0x0135)
#define ID_TEXT_155     (GUI_ID_USER + 0x0136)
#define ID_TEXT_156     (GUI_ID_USER + 0x0137)
#define ID_TEXT_157     (GUI_ID_USER + 0x0138)


#define ID_TimerTime5    6
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
static const GUI_WIDGET_CREATE_INFO _aDialogCreate5[] = {
  { WINDOW_CreateIndirect, "SYSSET", ID_WINDOW_6, 0, 0, 480, 272, 0, 0x0, 0 },
//   { BUTTON_CreateIndirect, "Button", ID_BUTTON_30, 3, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_31, 83, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_32, 163, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_33, 243, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_34, 323, 226, 77, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_35, 403, 226, 77, 45, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_21, 30, 50, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_22, 30, 75, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_23, 30, 100, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_24, 30, 125, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_25, 30, 150, 140, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_26, 30, 175, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_27, 30, 200, 80, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_28, 118, 50, 40, 20, 0, 0x64, 0 },   
  { TEXT_CreateIndirect, "Text", ID_TEXT_29, 118, 75, 40, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_30, 118, 100, 40, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_31, 260, 50, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_32, 260, 75, 140, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_35, 185, 122, 40, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_36, 185, 136, 40, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_154, 185, 150, 40, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_155, 185, 164, 40, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_37, 118, 175, 48, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_38, 118, 200, 48, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_39, 414, 47, 40, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_40, 414, 61, 40, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_156, 414, 75, 40, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_157, 414, 89, 40, 14, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_90, 260, 100, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_91, 348, 100, 120, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_92, 360, 125, 120, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_93, 360, 150, 120, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_94, 360, 175, 120, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_95, 360, 200, 120, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_133, 260, 125, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_134, 360, 125, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "Text",   ID_TEXT_129, 300, 2, 80, 20, 0, 0x0, 0 },
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

    char buf[5];   

    float dis_max_v = (float)set_max_v/1000;
    float dis_min_v = (float)set_min_v/1000;
    vu16 dis_max_r = set_max_r;
    vu16 dis_min_r = set_min_r;
    float dis_max_c = (float)set_max_c/1000;
    float dis_min_c = (float)set_min_c/1000;
    
  
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
            
		
	case WM_PAINT:
	GUI_SetColor(GUI_WHITE);//ʨ׃ۭҊҕɫ
	GUI_FillRect(0,25,480,26);//ۭһ͵ʵП
    GUI_SetColor(GUI_ORANGE);
	GUI_SetFont(&GUI_Fontsymbol);
	GUI_UC_SetEncodeUTF8();
	GUI_SetTextMode(GUI_TM_TRANS);//ʨ׃τѾģʽΪ֗ɫ͸ķ
	GUI_DispStringAt("Jinko", 5, 1);//SET
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontHZ20S);
	GUI_UC_SetEncodeUTF8();
	GUI_SetTextMode(GUI_TM_TRANS);//ʨ׃τѾģʽΪ֗ɫ͸ķ
	GUI_DispStringAt("系统设置", 130, 3);//SET
 	GUI_SetColor(GUI_WHITE);//ʨ׃ǰްɫΪїɫ
 	GUI_SetFont(&GUI_Font24_1);//
    GUI_DispStringAt("V",220,125);
    GUI_DispStringAt("V",220,150);
    GUI_DispStringAt("A",451,50);
    GUI_DispStringAt("A",451,75);
    GUI_DispStringAt("m",195,175);
    GUI_DispStringAt("m",195,200);
    GUI_SetFont(&GUI_FontHZ16);
    GUI_DispStringAt("Ω",211,182);
    GUI_DispStringAt("Ω",211,207);
	GUI_SetColor(GUI_WHITE);//ʨ׃ǰްɫΪїɫ
 	GUI_SetFont(&GUI_Font16_1);//
	GUI_DispStringAt("H",173,122);
    GUI_DispStringAt("L",173,136);
    GUI_DispStringAt("H",173,150);
    GUI_DispStringAt("L",173,164);
	GUI_DispStringAt("H",404,47);
    GUI_DispStringAt("L",404,61);
    GUI_DispStringAt("H",404,75);
    GUI_DispStringAt("L",404,89);
    
    GUI_SetColor(GUI_GREEN);
    GUI_SetFont(&GUI_Fontunit);
    GUI_DispStringAt("°",342, 2);
    GUI_SetFont(&GUI_Font24_1);
    GUI_DispStringAt("C",350, 2);
    DrawLock();
    
	break;
	case WM_TIMER://֨ʱģࠩлϢ
	if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime5)
	{
        lockstat2 = lockstat1;
        lockstat1 = lock; 
        if(lockstat1 != lockstat2)
        {
            WM_InvalidateWindow(hWinset);
        }
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_129);       
        sprintf(buf,"%.1f",temp);
        TEXT_SetText(hItem,buf);
        
//		WM_InvalidateWindow(hWinset);//ϞЧۯ԰ࠚ        
		WM_RestartTimer(pMsg->Data.v,500);//شλ֨ʱǷ˽ֵԽճˢтʱݤԽ׌
	}
	break;
    
		
  case WM_INIT_DIALOG:
    //
    // Initialization of 'R'
	
    //
        hItem = pMsg->hWin;
        WINDOW_SetBkColor(hItem, GUI_BLACK);
		WM_CreateTimer(hItem,ID_TimerTime5,1000,0);//ԴݨѾ԰ࠚ֨ʱǷ
    //

    //    
// 		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_30);
// 		BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
// 		BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
// 		GUI_UC_SetEncodeUTF8();
// 		BUTTON_SetText(hItem,"充放电");
	
	
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_31);
//		BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
		BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
		GUI_UC_SetEncodeUTF8();
		BUTTON_SetText(hItem,"内阻测试");
	
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_32);
//		BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
		BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
		GUI_UC_SetEncodeUTF8();
		BUTTON_SetText(hItem,"程控负载");
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_33);
//		BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
		BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
		GUI_UC_SetEncodeUTF8();
		BUTTON_SetText(hItem,"程控电源");
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_34);
//		BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
		BUTTON_SetFont      (hItem,    &GUI_FontHZ16);//ʨ֨дťτѾؖͥ
		GUI_UC_SetEncodeUTF8();
		BUTTON_SetText(hItem,"充放电"); 
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_35);
//		BUTTON_SetTextColor(hItem,0,GUI_BLACK);//ʨ׃ؖͥҕɫΪۚɫ
		BUTTON_SetFont      (hItem,&GUI_FontHZ16);//ʨ֨дťτѾؖͥ
		GUI_UC_SetEncodeUTF8();
		BUTTON_SetText(hItem,"曲线");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_21);
		TEXT_SetTextColor(hItem, GUI_BLACK);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
        TEXT_SetBkColor(hItem,0x00BFFFFF);
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"分选开关");
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_22);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"过流测试");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_23);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"报警声音");
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_24);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"电压上下限");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_25);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"负载电压上下限");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_26);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"内阻上限");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_27);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"内阻下限");
        
        switch(para_set1){
            case set_1_on:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_28);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
                GUI_UC_SetEncodeUTF8();
                TEXT_SetText(hItem,"ON");
                break;
            }
            case set_1_off:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_28);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
                GUI_UC_SetEncodeUTF8();
                TEXT_SetText(hItem,"OFF");
                break;
            }
        }

        switch(para_set2){
            case set_2_on:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_29);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
                GUI_UC_SetEncodeUTF8();
                TEXT_SetText(hItem,"ON");
                break;
            }
            case set_2_off:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_29);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
                GUI_UC_SetEncodeUTF8();
                TEXT_SetText(hItem,"OFF");
                break;
            }
        }
        
        switch(para_set4){
            case set_4_on:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_30);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
                GUI_UC_SetEncodeUTF8();
                TEXT_SetText(hItem,"ON");
                break;
            }
            case set_4_off:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_30);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Font20_ASCII);//设定文本字体
                GUI_UC_SetEncodeUTF8();
                TEXT_SetText(hItem,"OFF");
                break;
            }
        }
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_31);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"过流上下限");

        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_32);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"充电电流上下限");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_90);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
		GUI_UC_SetEncodeUTF8();
		TEXT_SetText(hItem,"电池类型");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_133);
        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
        GUI_UC_SetEncodeUTF8();
        TEXT_SetText(hItem,"测试模式");
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_134);
        TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
        GUI_UC_SetEncodeUTF8();
        if(test_mode == 1)
        {
            TEXT_SetText(hItem,"精准");
        }else if(test_mode == 0){
            TEXT_SetText(hItem,"快速");
        }
        
        
        
        
        
        
        switch(b_type)
        {
            case Lion:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_91);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                GUI_UC_SetEncodeUTF8();
                TEXT_SetText(hItem,"锂电池");
                break;
            }
            case NiMH:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_91);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                GUI_UC_SetEncodeUTF8();
                TEXT_SetText(hItem,"镍氢电池");
                break;
            }
            case NiCd:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_91);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                GUI_UC_SetEncodeUTF8();
                TEXT_SetText(hItem,"镍镉电池");
                break;
            }
            case SLA:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_91);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                GUI_UC_SetEncodeUTF8();
                TEXT_SetText(hItem,"小型铅酸电池");
                break;
            }
            case LiMH:
            {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_91);
                TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                GUI_UC_SetEncodeUTF8();
                TEXT_SetText(hItem,"锂锰电池");
                break;
            }
            
        }

        


        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_35);
        sprintf(buf,"%.3f",dis_max_v);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_36);
        sprintf(buf,"%.3f",dis_min_v);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_154);
        sprintf(buf,"%.3f",(float)set_max_lv/1000);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_155);
        sprintf(buf,"%.3f",(float)set_min_lv/1000);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
//         
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_37);
        sprintf(buf,"%4d",set_max_r);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_38);
        sprintf(buf,"%4d",set_min_r);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
// // // 		
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_39);
        sprintf(buf,"%.3f",dis_max_c);        
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_156);
        sprintf(buf,"%.3f",(float)set_max_pc/1000);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
		GUI_UC_SetEncodeUTF8(); 
		TEXT_SetText(hItem,buf);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_157);
        sprintf(buf,"%.3f",(float)set_min_pc/1000);        
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
		GUI_UC_SetEncodeUTF8();        
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_40);
        sprintf(buf,"%.3f",dis_min_c);
		TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
        TEXT_SetFont(hItem,&GUI_Font16_1);//设定文本字体
		GUI_UC_SetEncodeUTF8(); 
		TEXT_SetText(hItem,buf);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_129);
        TEXT_SetTextColor(hItem, GUI_GREEN);//����������ɫ
        TEXT_SetFont(hItem,&GUI_Font24_1);//�趨�ı�����       
        sprintf(buf,"%.1f",temp);
        TEXT_SetText(hItem,buf);
        
        

        
        
        

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
WM_HWIN CreateSET(void);
WM_HWIN CreateSET(void) {
  page_sw = face_set;
  set_sw = set_1;
  pass = 0;
  TM1650_SET_LED(0x68,0x70);
  GPIO_ResetBits(GPIOD,GPIO_Pin_12);//���
  hWinset = GUI_CreateDialogBox(_aDialogCreate5, GUI_COUNTOF(_aDialogCreate5), _cbDialog, WM_HBKWIN, 0, 0);
  return hWinset;
}

WM_HWIN ResetSET(void) {
  hWinset = GUI_CreateDialogBox(_aDialogCreate5, GUI_COUNTOF(_aDialogCreate5), _cbDialog, WM_HBKWIN, 0, 0);
  return hWinset;
}

/*********************************************************************
*
*       设置界面选项切换
*/
//向下选择

void SET_OP_DOWN(void) {
				vu8 i;
                char buf[5];
  

                float dis_max_v = (float)set_max_v/1000;
                float dis_min_v = (float)set_min_v/1000;
                vu16 dis_max_r = set_max_r;
                vu16 dis_min_r = set_min_r;
                float dis_max_c = (float)set_max_c/1000;
                float dis_min_c = (float)set_min_c/1000;
                switch(set_sw){
                    case set_1:
                    {
                        WM_HWIN hItem;
 //                       WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_21);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);

                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_22);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        set_sw = set_2; 
                        break;
                    }                        
                    case set_2:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_22);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_23);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_3;
                        break;
                    }
                    case set_3:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_23);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为，米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_4;
                        break;
                    }
                    case set_4:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_25);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_5;
                        break;
                    }
                    case set_5:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_25);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_26);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_6;
                        break;
                    }
                    case set_6:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_26);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_27);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_7;
                        break;
                    }
                    case set_7:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_27);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_21);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_1;
                        break;
                    }
                    case set_8:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_31);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_32);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_9;
                        break;
                    }
                    case set_9:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_32);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_42;
                        break;
                    }
                    case set_42:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_133);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_73;
                        break;
                    }
                    case set_73:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_133);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_31);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_8;
                        break;
                    }
					case set_12:
                    {
						WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_35);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
						if(set_max_v > 80000)
                        {
                            set_max_v = 80000;
                            TEXT_SetText(hItem,"80.00");                                                       
                        }
                        sprintf(buf,"%.3f",dis_max_v);
                        TEXT_SetText(hItem,buf);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_36);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
						
						for(i=0;i<5;i++){
							set_limit[i] = '\0';
						}
						bit = 1;
                        dot_flag = 0;
                        set_sw = set_13;
                        break;
					}
					case set_82:
                    {
						WM_HWIN hItem;						
						hItem = WM_GetDialogItem(hWinset, ID_TEXT_154);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                       
                        sprintf(buf,"%.3f",(float)set_max_lv/1000);
                        TEXT_SetText(hItem,buf);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_155);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
							
						for(i=0;i<5;i++){
							set_limit[i] = '\0';
						}
						bit = 1;
                        dot_flag = 0;
                        set_sw = set_83;
                        break;
					}
					
					case set_16:
                    {
						WM_HWIN hItem;						
						hItem = WM_GetDialogItem(hWinset, ID_TEXT_39);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                       
                        sprintf(buf,"%.3f",(float)set_max_c/1000);
                        TEXT_SetText(hItem,buf);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_40);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
							
						for(i=0;i<5;i++){
							set_limit[i] = '\0';
						}
						bit = 1;
                        dot_flag = 0;
                        set_sw = set_17;
                        break;
					}
					
					case set_84:
                    {
						WM_HWIN hItem;						
						hItem = WM_GetDialogItem(hWinset, ID_TEXT_156);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                       
                        sprintf(buf,"%.3f",(float)set_max_pc/1000);
                        TEXT_SetText(hItem,buf);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_157);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
							
						for(i=0;i<5;i++){
							set_limit[i] = '\0';
						}
						bit = 1;
                        dot_flag = 0;
                        set_sw = set_85;
                        break;
					}
					
                    case set_43:
                    {
                        WM_HWIN hItem;
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                        
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        switch(b_type)
                        {
                            case Lion:
                            {
                                buffer = NiMH;
                                break;
                            }
                            case NiMH:
                            {
                                buffer = Lion;
                                break;
                            }
                            case NiCd:
                            {
                                buffer = Lion;
                                break;
                            }
                            case SLA:
                            {
                                buffer = Lion;
                                break;
                            }
                            case LiMH:
                            {
                                buffer = Lion;
                                break;
                            }
                        }

                        set_sw = set_44;
                        break;
                    }
                    case set_44:
                    {
                        WM_HWIN hItem;
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        switch(b_type)
                        {
                            case Lion:
                            {
                                buffer = NiCd;
                                break;
                            }
                            case NiMH:
                            {
                                buffer = NiCd;
                                break;
                            }
                            case NiCd:
                            {
                                buffer = NiMH;
                                break;
                            }
                            case SLA:
                            {
                                buffer = NiMH;
                                break;
                            }
                            case LiMH:
                            {
                                buffer = NiMH;
                                break;
                            }
                        }

                        set_sw = set_45;
                        break;
                    }
                    case set_45:
                    {
                        WM_HWIN hItem;
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        switch(b_type)
                        {
                            case Lion:
                            {
                                buffer = SLA;
                                break;
                            }
                            case NiMH:
                            {
                                buffer = SLA;
                                break;
                            }
                            case NiCd:
                            {
                                buffer = SLA;
                                break;
                            }
                            case SLA:
                            {
                                buffer = NiCd;
                                break;
                            }
                            case LiMH:
                            {
                                buffer = NiCd;
                                break;
                            }
                        }

                        set_sw = set_46;
                        break;
                    }
                    case set_46:
                    {
                        WM_HWIN hItem;
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        switch(b_type)
                        {
                            case Lion:
                            {
                                buffer = LiMH;
                                break;
                            }
                            case NiMH:
                            {
                                buffer = LiMH;
                                break;
                            }
                            case NiCd:
                            {
                                buffer = LiMH;
                                break;
                            }
                            case SLA:
                            {
                                buffer = LiMH;
                                break;
                            }
                            case LiMH:
                            {
                                buffer = SLA;
                                break;
                            }
                        }

                        set_sw = set_47;
                        break;
                    }
                    case set_47:
                    {
                        WM_HWIN hItem;
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                        
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        switch(b_type)
                        {
                            case Lion:
                            {
                                buffer = Lion;
                                break;
                            }
                            case NiMH:
                            {
                                buffer = NiMH;
                                break;
                            }
                            case NiCd:
                            {
                                buffer = NiCd;
                                break;
                            }
                            case SLA:
                            {
                                buffer = SLA;
                                break;
                            }
                            case LiMH:
                            {
                                buffer = LiMH;
                                break;
                            }
                        }

                        set_sw = set_43;
                        break;
                    }
                    default: break;
                 }
//                return set_sw;
//                return b_type;
}

//向上选择

void SET_OP_UP(void) {
				vu8 i;
                char buf[5];
  

                float dis_max_v = (float)set_max_v/1000;
                float dis_min_v = (float)set_min_v/1000;
                vu16 dis_max_r = set_max_r;
                vu16 dis_min_r = set_min_r;
                float dis_max_c = (float)set_max_c/1000;
                float dis_min_c = (float)set_min_c/1000;
                switch(set_sw){
                    case set_1:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_21);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);

                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_27);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        
                        set_sw = set_7; 
                        break;
                    }                        
                    case set_2:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_22);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_21);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_1;
                        break;
                    }
                    case set_3:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_23);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_22);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_2;
                        break;
                    }
                    case set_4:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_23);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_3;
                        break;
                    }
                    case set_5:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_25);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_4;
                        break;
                    }
                    case set_6:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_26);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_25);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_5;
                        break;
                    }
                    case set_7:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_27);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_26);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_6;
                        break;
                    }
                    case set_8:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_31);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_133);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_73;
                        break;
                    }
                    case set_9:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_32);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_31);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_8;
                        break;
                    }
                    case set_42:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_32);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_9;
                        break;
                    }
                    case set_73:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_133);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_42;
                        break;
                    }
					
					case set_13:
                    {
						WM_HWIN hItem;						
						hItem = WM_GetDialogItem(hWinset, ID_TEXT_36);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                       
                        sprintf(buf,"%.3f",dis_min_v);
                        TEXT_SetText(hItem,buf);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_35);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
							
						for(i=0;i<5;i++){
							set_limit[i] = '\0';
						}
						bit = 1;
                        dot_flag = 0;
                        set_sw = set_12;
                        break;
					}
					
					case set_83:
                    {
						WM_HWIN hItem;						
						hItem = WM_GetDialogItem(hWinset, ID_TEXT_155);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                       
                        sprintf(buf,"%.3f",(float)set_min_lv/1000);
                        TEXT_SetText(hItem,buf);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_154);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
							
						for(i=0;i<5;i++){
							set_limit[i] = '\0';
						}
						bit = 1;
                        dot_flag = 0;
                        set_sw = set_82;
                        break;
					}
					
					case set_17:
                    {
						WM_HWIN hItem;						
						hItem = WM_GetDialogItem(hWinset, ID_TEXT_40);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                       
                        sprintf(buf,"%.3f",(float)set_min_c/1000);
                        TEXT_SetText(hItem,buf);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_39);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
							
						for(i=0;i<5;i++){
							set_limit[i] = '\0';
						}
						bit = 1;
                        dot_flag = 0;
                        set_sw = set_16;
                        break;
					}
					
					case set_85:
                    {
						WM_HWIN hItem;						
						hItem = WM_GetDialogItem(hWinset, ID_TEXT_157);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                       
                        sprintf(buf,"%.3f",(float)set_min_pc/1000);
                        TEXT_SetText(hItem,buf);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_156);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
							
						for(i=0;i<5;i++){
							set_limit[i] = '\0';
						}
						bit = 1;
                        dot_flag = 0;
                        set_sw = set_84;
                        break;
					}
					
                    case set_43:
                    {
                        WM_HWIN hItem;
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                        
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        switch(b_type)
                        {
                            case Lion:
                            {
                                buffer = LiMH;
                                break;
                            }
                            case NiMH:
                            {
                                buffer = LiMH;
                                break;
                            }
                            case NiCd:
                            {
                                buffer = LiMH;
                                break;
                            }
                            case SLA:
                            {
                                buffer = LiMH;
                                break;
                            }
                            case LiMH:
                            {
                                buffer = SLA;
                                break;
                            }
                        }

                        set_sw = set_47;
                        break;
                    }
                    case set_44:
                    {
                        WM_HWIN hItem;
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        switch(b_type)
                        {
                            case Lion:
                            {
                                buffer = Lion;
                                break;
                            }
                            case NiMH:
                            {
                                buffer = NiMH;
                                break;
                            }
                            case NiCd:
                            {
                                buffer = NiCd;
                                break;
                            }
                            case SLA:
                            {
                                buffer = SLA;
                                break;
                            }
                            case LiMH:
                            {
                                buffer = LiMH;
                                break;
                            }
                        }

                        set_sw = set_43;
                        break;
                    }
                    case set_45:
                    {
                        WM_HWIN hItem;
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        switch(b_type)
                        {
                            case Lion:
                            {
                                buffer = NiMH;
                                break;
                            }
                            case NiMH:
                            {
                                buffer = Lion;
                                break;
                            }
                            case NiCd:
                            {
                                buffer = Lion;
                                break;
                            }
                            case SLA:
                            {
                                buffer = Lion;
                                break;
                            }
                            case LiMH:
                            {
                                buffer = Lion;
                                break;
                            }
                        }

                        set_sw = set_44;
                        break;
                    }
                    case set_46:
                    {
                        WM_HWIN hItem;
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        switch(b_type)
                        {
                            case Lion:
                            {
                                buffer = NiCd;
                                break;
                            }
                            case NiMH:
                            {
                                buffer = NiCd;
                                break;
                            }
                            case NiCd:
                            {
                                buffer = NiMH;
                                break;
                            }
                            case SLA:
                            {
                                buffer = NiMH;
                                break;
                            }
                            case LiMH:
                            {
                                buffer = NiMH;
                                break;
                            }
                        }

                        set_sw = set_45;
                        break;
                    }
                    case set_47:
                    {
                        WM_HWIN hItem;
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                        
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        switch(b_type)
                        {
                            case Lion:
                            {
                                buffer = SLA;
                                break;
                            }
                            case NiMH:
                            {
                                buffer = SLA;
                                break;
                            }
                            case NiCd:
                            {
                                buffer = SLA;
                                break;
                            }
                            case SLA:
                            {
                                buffer = NiCd;
                                break;
                            }
                            case LiMH:
                            {
                                buffer = NiCd;
                                break;
                            }
                        }

                        set_sw = set_46;
                        break;
                    }
                    default: break;
                }
//                return set_sw;
}

//向右选择

void SET_OP_RIGHT(void) {
                switch(set_sw){
                    case set_1:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_21);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);

                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_31);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        set_sw = set_8; 
                        break;
                    }                        
                    case set_2:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_22);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_32);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_9;
                        break;
                    }
                    case set_3:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_23);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_42;
                        break;
                    }
                    case set_4:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_133);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        set_sw = set_73;
                        break;                                 
                    }
                    case set_5:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_25);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_42;
                        break;
                    }
                    case set_6:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_26);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_42;
                        break;
                    }
                    case set_7:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_27);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_42;
                        break;
                    }
                    case set_8:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_31);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_21);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_1;
                        break;
                    }
                    case set_9:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_32);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_22);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_2;
                        break;
                    }
                    case set_42:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_23);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_3;
                        break;
                    }
                    case set_73:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_133);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_4;
                        break;
                    }
//                     case set_11:
//                     {
//                         WM_HWIN hItem;
//                         WM_InvalidateWindow(hWinset);
//                         hItem = WM_GetDialogItem(hWinset, ID_TEXT_34);
//                         TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
//                
//                         hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
//                         TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色

//                         set_sw = set_4;
//                         break;
//                     }
                    default: break;
                }
//                return set_sw;
}

//向左选择

void SET_OP_LEFT(void) {
                switch(set_sw){
                    case set_1:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_21);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);

                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_31);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                        set_sw = set_8; 
                        break;
                    }                        
                    case set_2:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_22);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_32);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_9;
                        break;
                    }
                    case set_3:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_23);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                         TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_42;
                        break;
                    }
                    case set_4:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_133);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_73;
                        break;
                    }
                    case set_5:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_25);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_42;
                        break;
                    }
                    case set_6:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_26);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_42;
                        break;
                    }
                    case set_7:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_27);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_42;
                        break;
                    }
                    case set_8:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_31);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_21);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_1;
                        break;
                    }
                    case set_9:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_32);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_22);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_2;
                        break;
                    }
                    case set_42:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_23);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_3;
                        break;
                    }
                    case set_73:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_133);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        set_sw = set_4;
                        break;
                    }
//                     case set_11:
//                     {
//                         WM_HWIN hItem;
//                         WM_InvalidateWindow(hWinset);
//                         hItem = WM_GetDialogItem(hWinset, ID_TEXT_34);
//                         TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
//                
//                         hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
//                         TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色

//                         set_sw = set_4;
//                         break;
//                     }
                    default: break;
                }
//                return set_sw;
}

//参数设置

void PARA_SET(void) {
                vu8 i;
                char buf[5];
  

                float dis_max_v = (float)set_max_v/1000;
                float dis_min_v = (float)set_min_v/1000;
                vu16 dis_max_r = set_max_r;
                vu16 dis_min_r = set_min_r;
                float dis_max_c = (float)set_max_c/1000;
                float dis_min_c = (float)set_min_c/1000;
    
                switch(set_sw){
                    case set_1:
                    {
                        switch(para_set1){
                            case set_1_on:
                            {
                                WM_HWIN hItem;
//                                WM_InvalidateWindow(hWinset);
                                hItem = WM_GetDialogItem(hWinset, ID_TEXT_28);
                                TEXT_SetText(hItem,"OFF");
                                para_set1 = set_1_off;
                                Wrtite_S();
                                break;
                            }
                            case set_1_off:
                            {
                                WM_HWIN hItem;
//                                WM_InvalidateWindow(hWinset);
                                hItem = WM_GetDialogItem(hWinset, ID_TEXT_28);
                                TEXT_SetText(hItem,"ON");
                                para_set1 = set_1_on;
                                Wrtite_S();
                                break;
                            }
                        }                        
                        break;
                    }
                    case set_2:
                    {
                        switch(para_set2){
                            case set_2_on:
                            {
                                WM_HWIN hItem;
//                                WM_InvalidateWindow(hWinset);
                                hItem = WM_GetDialogItem(hWinset, ID_TEXT_29);
                                TEXT_SetText(hItem,"OFF");
                                para_set2 = set_2_off;
                                Write_oct();
                                break;
                            }
                            case set_2_off:
                            {
                                WM_HWIN hItem;
//                                WM_InvalidateWindow(hWinset);
                                hItem = WM_GetDialogItem(hWinset, ID_TEXT_29);
                                TEXT_SetText(hItem,"ON");
                                para_set2 = set_2_on;
                                Write_oct();
                                break;
                            }                       
                        }
                        break;
                    }
                    case set_3:
                    {
                        switch(para_set4){
                        case set_4_on:
                        {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_30);
                            TEXT_SetText(hItem,"OFF");
                            para_set4 = set_4_off;
                            Write_alarm();
                            break;
                        }
                        case set_4_off:
                        {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_30);
                            TEXT_SetText(hItem,"ON");
                            para_set4 = set_4_on;
                            Write_alarm();
                            break;
                        }
//                        break;
                        }
                    break;
                    }
                    case set_4:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
                            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                            TEXT_SetTextColor(hItem, GUI_WHITE);
               
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_35);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);
                            
                            for(i=0;i<6;i++){
                                set_limit[i] = '\0';
                            }
                            set_sw = set_12;
                            break;                        
                    }
                    case set_12:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);

                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_35);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
						if(dot_flag == 0){
							set_max_v = atoi(set_limit)*1000;					
						}else if(dot_flag != 0){
							memset(buf, '\0', sizeof(buf));
							strncpy(buf,set_limit,dot_flag + 2);
							set_max_v = atof(buf)*1000;
						}
						if(set_max_v > 62000)
						{
							set_max_v = 62000;
						}
						dis_max_v = (float)set_max_v/1000;
//                        if(set_max_v > 80000)
//                        {
//                            set_max_v = 80000;
//                            TEXT_SetText(hItem,"80.00");                                                       
//                        }
                        sprintf(buf,"%.3f",dis_max_v);
                        TEXT_SetText(hItem,buf);
						
						hItem = WM_GetDialogItem(hWinset, ID_TEXT_36);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                       
                        sprintf(buf,"%.3f",dis_min_v);
                        TEXT_SetText(hItem,buf);
                        
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        Write_Limits();
                        set_sw = set_4;
                        bit = 1;
                        dot_flag = 0;
                        break; 
                    }
					 case set_13:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);

                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_35);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
//                        if(set_max_v > 80000)
//                        {
//                            set_max_v = 80000;
//                            TEXT_SetText(hItem,"80.00");                                                       
//                        }
						if(dot_flag == 0){
							set_min_v = atoi(set_limit)*1000;					
						}else if(dot_flag != 0){
							memset(buf, '\0', sizeof(buf));
							strncpy(buf,set_limit,dot_flag + 2);
							set_min_v = atof(buf)*1000;
						}
						if(set_min_v > 62000)
						{
							set_min_v = 62000;
						}
						dis_min_v = (float)set_min_v/1000;
                        sprintf(buf,"%.3f",dis_max_v);
                        TEXT_SetText(hItem,buf);
						
						hItem = WM_GetDialogItem(hWinset, ID_TEXT_36);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                       
                        sprintf(buf,"%.3f",dis_min_v);
                        TEXT_SetText(hItem,buf);
						
                    
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_24);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
   
                        Write_Limits();
                        set_sw = set_4;
                        bit = 1;
                        dot_flag = 0;
                        break; 
                    }
					
					case set_82:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);

                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_154);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
						if(dot_flag == 0){
							set_max_lv = atoi(set_limit)*1000;					
						}else if(dot_flag != 0){
							memset(buf, '\0', sizeof(buf));
							strncpy(buf,set_limit,dot_flag + 3);
							set_max_lv = atof(buf)*1000;
						}
                        sprintf(buf,"%.3f",(float)set_max_lv/1000);
                        TEXT_SetText(hItem,buf);
						
						hItem = WM_GetDialogItem(hWinset, ID_TEXT_155);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                       
                        sprintf(buf,"%.3f",(float)set_min_lv/1000);
                        TEXT_SetText(hItem,buf);
                        
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_25);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
                        Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
                        set_sw = set_5;
                        bit = 1;
                        dot_flag = 0;
                        break; 
                    }
					 case set_83:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);

                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_154);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
						if(dot_flag == 0){
							set_min_lv = atoi(set_limit)*1000;					
						}else if(dot_flag != 0){
							memset(buf, '\0', sizeof(buf));
							strncpy(buf,set_limit,dot_flag + 3);
							set_min_lv = atof(buf)*1000;
						}
                        sprintf(buf,"%.3f",(float)set_max_lv/1000);
                        TEXT_SetText(hItem,buf);
						
						hItem = WM_GetDialogItem(hWinset, ID_TEXT_155);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                       
                        sprintf(buf,"%.3f",(float)set_min_lv/1000);
                        TEXT_SetText(hItem,buf);
						
                    
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_25);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);
   
                        Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
                        set_sw = set_5;
                        bit = 1;
                        dot_flag = 0;
                        break; 
                    }
					
                    case set_5:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_25);
                            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                            TEXT_SetTextColor(hItem, GUI_WHITE);
               
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_154);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);

                            for(i=0;i<6;i++){
                                set_limit[i] = '\0';
                            }
                            set_sw = set_82;
                            break;                        
                    }
                   
                    case set_6:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_26);
                            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                            TEXT_SetTextColor(hItem, GUI_WHITE);
               
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_37);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);
                            
                            for(i=0;i<6;i++){
                                set_limit[i] = '\0';
                            }
                            set_sw = set_14;
                            break;                        
                    }
                    case set_14:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_37);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
						if(dot_flag == 0){
							set_max_r = atoi(set_limit);					
						}else if(dot_flag != 0){
							memset(buf, '\0', sizeof(buf));
							strncpy(buf,set_limit,dot_flag);
							set_max_r = atof(buf);
						}
                        sprintf(buf,"%4d",set_max_r);
                        TEXT_SetText(hItem,buf);
               
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_26);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        Write_Limits();
                        set_sw = set_6;
                        bit = 1;
                        dot_flag = 0;
                        break; 
                    }
                    case set_7:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_27);
                            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                            TEXT_SetTextColor(hItem, GUI_WHITE);
               
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_38);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);
                            
                            for(i=0;i<6;i++){
                                set_limit[i] = '\0';
                            }
                            set_sw = set_15;
                            break;                        
                    }
                    case set_15:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_38);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                        if(dot_flag == 0){
							set_min_r = atoi(set_limit);					
						}else if(dot_flag != 0){
							memset(buf, '\0', sizeof(buf));
							strncpy(buf,set_limit,dot_flag);
							set_min_r = atof(buf);
						}
                        sprintf(buf,"%4d",set_min_r);
                        TEXT_SetText(hItem,buf);
                        
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_27);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        Write_Limits();
                        set_sw = set_7;
                        bit = 1;
                        dot_flag = 0;
                        break; 
                    }
                    case set_8:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_31);
                            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                            TEXT_SetTextColor(hItem, GUI_WHITE);
               
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_39);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);

                            for(i=0;i<6;i++){
                                set_limit[i] = '\0';
                            }
                            set_sw = set_16;
                            break;                        
                    }
                    case set_16:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_39);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
						if(dot_flag == 0){
							set_max_c = atoi(set_limit)*1000;					
						}else if(dot_flag != 0){
							memset(buf, '\0', sizeof(buf));
							strncpy(buf,set_limit,dot_flag + 3);
							set_max_c = atof(buf)*1000;
						}
                        if(set_max_c > 30000)
                        {
                            set_max_c = 30000;
                        }
						dis_max_c = (float)set_max_c/1000;
                        sprintf(buf,"%.3f",dis_max_c);
                        TEXT_SetText(hItem,buf);
						
						 hItem = WM_GetDialogItem(hWinset, ID_TEXT_40);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                        if(set_min_c >= set_max_c)
                        {
                            set_min_c = 0;
                            TEXT_SetText(hItem,"0.000");
                        }
                        
                        sprintf(buf,"%.3f",dis_min_c);
                        TEXT_SetText(hItem,buf);
						
						
                        
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_31);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        Write_Limits();
                        set_sw = set_8;
                        bit = 1;
                        dot_flag = 0;
                        break; 
                    }
					
					case set_17:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_39);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
//                        if(set_max_c > 60000)
//                        {
//                            set_max_c = 60000;
//                            TEXT_SetText(hItem,"60.00");
//                        }
                        sprintf(buf,"%.3f",dis_max_c);
                        TEXT_SetText(hItem,buf);
						
						 hItem = WM_GetDialogItem(hWinset, ID_TEXT_40);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
						if(dot_flag == 0){
							set_min_c = atoi(set_limit)*1000;					
						}else if(dot_flag != 0){
							memset(buf, '\0', sizeof(buf));
							strncpy(buf,set_limit,dot_flag + 3);
							set_min_c = atof(buf)*1000;
						}
                        if(set_max_c > 30000)
                        {
                            set_max_c = 30000;
                        }
                        if(set_min_c >= set_max_c)
                        {
                            set_min_c = 0;
                        }
                        dis_min_c = (float)set_min_c/1000;
                        sprintf(buf,"%.3f",dis_min_c);
                        TEXT_SetText(hItem,buf);
						
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_31);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        Write_Limits();
                        set_sw = set_8;
                        bit = 1;
                        dot_flag = 0;
                        break; 
                    }
					
                    case set_9:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_32);
                            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                            TEXT_SetTextColor(hItem, GUI_WHITE);
                            
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_156);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);

                            for(i=0;i<6;i++){
                                set_limit[i] = '\0';
                            }
                            set_sw = set_84;
                            break;                        
                    }
					
					case set_84:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_156);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
						if(dot_flag == 0){
							set_max_pc = atoi(set_limit)*1000;					
						}else if(dot_flag != 0){
							memset(buf, '\0', sizeof(buf));
							strncpy(buf,set_limit,dot_flag + 3);
							set_max_pc = atof(buf)*1000;
						}
                        if(set_max_pc > 10000)
                        {
                            set_max_pc = 10000;
                        }
//						dis_max_c = (float)set_max_c/1000;
//                        if(set_max_pc > 60000)
//                        {
//                            set_max_pc = 60000;
//                            TEXT_SetText(hItem,"60.000");
//                        }
                        sprintf(buf,"%.3f",(float)set_max_pc/1000);
                        TEXT_SetText(hItem,buf);
						
						 hItem = WM_GetDialogItem(hWinset, ID_TEXT_157);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
                        if(set_min_pc >= set_max_pc)
                        {
                            set_min_pc = 0;
                            TEXT_SetText(hItem,"0.000");
                        }
                        
                        sprintf(buf,"%.3f",(float)set_min_pc/1000);
                        TEXT_SetText(hItem,buf);
						
						
                        
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_32);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
                        set_sw = set_9;
                        bit = 1;
                        dot_flag = 0;
                        break; 
                    }
					
					case set_85:
                    {
                        WM_HWIN hItem;
//                        WM_InvalidateWindow(hWinset);
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_156);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
//                        if(set_max_pc > 60000)
//                        {
//                            set_max_pc = 60000;
//                            TEXT_SetText(hItem,"60.000");
//                        }
                        sprintf(buf,"%.3f",(float)set_max_pc/1000);
                        TEXT_SetText(hItem,buf);
						
						 hItem = WM_GetDialogItem(hWinset, ID_TEXT_157);
                        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        TEXT_SetTextColor(hItem, GUI_WHITE);
						if(dot_flag == 0){
							set_min_pc = atoi(set_limit)*1000;					
						}else if(dot_flag != 0){
							memset(buf, '\0', sizeof(buf));
							strncpy(buf,set_limit,dot_flag + 3);
							set_min_pc = atof(buf)*1000;
						}
                        if(set_min_pc > 10000)
                        {
                            set_min_pc = 10000;
                        }
                        if(set_min_pc >= set_max_pc)
                        {
                            set_min_pc = 0;
//                            TEXT_SetText(hItem,"0.000");
                        }
                        
                        sprintf(buf,"%.3f",(float)set_min_pc/1000);
                        TEXT_SetText(hItem,buf);
						
                        hItem = WM_GetDialogItem(hWinset, ID_TEXT_32);
                        TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                        TEXT_SetTextColor(hItem, GUI_BLACK);

                        Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
                        set_sw = set_9;
                        bit = 1;
                        dot_flag = 0;
                        break; 
                    }
                    
                    case set_73:
                    {
                        if(test_mode > 1)
                        {
                            test_mode = 1;
                        }
                        if(test_mode == 1)
                        {
                            WM_HWIN hItem;
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_134);
                            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                            TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                            GUI_UC_SetEncodeUTF8();
                            TEXT_SetText(hItem,"快速");
                            test_mode = 0;
                            Wrtite_S();
                        }else if(test_mode == 0){
                            WM_HWIN hItem;
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_134);
                            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                            TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                            GUI_UC_SetEncodeUTF8();
                            TEXT_SetText(hItem,"精准");
                            test_mode = 1;
                            Wrtite_S();
                        }
                    }break;
                    case set_42:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                            TEXT_SetTextColor(hItem, GUI_WHITE);
               
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_134);
                            TEXT_SetText(hItem,"");
                            if(b_type > 5)
                            {
                                b_type = 1;
                            }
                            
                            switch(b_type)
                            {
                                case Lion:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"镍氢电池");
                                
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"镍镉电池");
                                    
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"小型铅酸电池");
                                    
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"锂锰电池");
                                    break;
                                }
                                case NiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"锂电池");
                                
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"镍镉电池");
                                    
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"小型铅酸电池");
                                    
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"锂锰电池");
                                    break;
                                }
                                case NiCd:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"锂电池");
                                
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"镍氢电池");
                                    
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"小型铅酸电池");
                                    
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"锂锰电池");
                                    break;
                                }
                                case SLA:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"锂电池");
                                
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"镍氢电池");
                                    
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"镍镉电池");
                                    
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"锂锰电池");
                                    break;
                                }
                                case LiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"锂电池");
                                
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"镍氢电池");
                                    
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"镍镉电池");
                                    
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                                    TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
                                    TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                    GUI_UC_SetEncodeUTF8();
                                    TEXT_SetText(hItem,"小型铅酸电池");
                                    break;
                                }
                            }
                            

                            set_sw = set_43;
                            break;                        
                    }
                    case set_43:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
                            
               
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_134);
                            if(test_mode == 1)
                            {
                                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                TEXT_SetText(hItem,"精准");
                            }else if(test_mode == 0){
                                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                TEXT_SetText(hItem,"快速");
                            }
                                                   
                            switch(buffer)
                            {
                                case Lion:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"锂电池");
                                    b_type = Lion;      
                                    break;
                                }
                                case NiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"镍氢电池");
                                    b_type = NiMH;
                                    break;
                                }
                                case NiCd:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"镍镉电池");
                                    b_type = NiCd;
                                    break;
                                }
                                case SLA:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"小型铅酸电池");
                                    b_type = SLA;
                                    break;
                                }
                                case LiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"锂锰电池");
                                    b_type = LiMH;
                                    break;
                                }
                            }

                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                            TEXT_SetText(hItem,"");
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                            TEXT_SetText(hItem,"");
                            
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                            TEXT_SetText(hItem,"");
                            
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                            TEXT_SetText(hItem,"");
                            
                            Write_btype();
                            set_sw = set_42;
                            break;                        
                    }
                    case set_44:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
               
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_134);
                            if(test_mode == 1)
                            {
                                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                TEXT_SetText(hItem,"精准");
                            }else if(test_mode == 0){
                                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                TEXT_SetText(hItem,"快速");
                            }
                        
                            switch(buffer)
                            {
                                case Lion:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"锂电池");
                                    b_type = Lion;
                                    break;
                                }
                                case NiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"镍氢电池");
                                    b_type = NiMH;
                                    break;
                                }
                                case NiCd:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"镍镉电池");
                                    b_type = NiCd;
                                    break;
                                }
                                case SLA:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"小型铅酸电池");
                                    b_type = SLA;
                                    break;
                                }
                                case LiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"锂锰电池");
                                    b_type = LiMH;
                                    break;
                                }
                            }
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                            TEXT_SetText(hItem,"");
                            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                            TEXT_SetText(hItem,"");
                            
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                            TEXT_SetText(hItem,"");
                            
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                            TEXT_SetText(hItem,"");

                            Write_btype();
                            set_sw = set_42;
                            break;                        
                    }
                    case set_45:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
               
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_134);
                            if(test_mode == 1)
                            {
                                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                TEXT_SetText(hItem,"精准");
                            }else if(test_mode == 0){
                                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                TEXT_SetText(hItem,"快速");
                            }
                        
                            switch(buffer)
                            {
                                case Lion:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"锂电池");
                                    b_type = Lion;
                                    break;
                                }
                                case NiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"镍氢电池");
                                    b_type = NiMH;
                                    break;
                                }
                                case NiCd:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"镍镉电池");
                                    b_type = NiCd;
                                    break;
                                }
                                case SLA:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"小型铅酸电池");
                                    b_type = SLA;
                                    break;
                                }
                                case LiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"锂锰电池");
                                    b_type = LiMH;
                                    break;
                                }
                            }
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                            TEXT_SetText(hItem,"");
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                            TEXT_SetText(hItem,"");
                            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                            
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                            TEXT_SetText(hItem,"");
                            
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                            TEXT_SetText(hItem,"");

                            Write_btype();
                            set_sw = set_42;
                            break;                        
                    }
                    case set_46:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
               
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_134);
                            if(test_mode == 1)
                            {
                                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                TEXT_SetText(hItem,"精准");
                            }else if(test_mode == 0){
                                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                TEXT_SetText(hItem,"快速");
                            }
                        
                            switch(buffer)
                            {
                                case Lion:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"锂电池");
                                    b_type = Lion;
                                    break;
                                }
                                case NiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"镍氢电池");
                                    b_type = NiMH;
                                    break;
                                }
                                case NiCd:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"镍镉电池");
                                    b_type = NiCd;
                                    break;
                                }
                                case SLA:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"小型铅酸电池");
                                    b_type = SLA;
                                    break;
                                }
                                case LiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"锂锰电池");
                                    b_type = LiMH;
                                    break;
                                }
                            }
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                            TEXT_SetText(hItem,"");
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                            TEXT_SetText(hItem,"");
                            
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                            TEXT_SetText(hItem,"");
                            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                            
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                            TEXT_SetText(hItem,"");

                            Write_btype();
                            set_sw = set_42;
                            break;                        
                    }
                    case set_47:
                    {
                            WM_HWIN hItem;
//                            WM_InvalidateWindow(hWinset);
               
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_90);
                            TEXT_SetBkColor(hItem,0x00BFFFFF);//选项背景色设为米色
                            TEXT_SetTextColor(hItem, GUI_BLACK);
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_134);
                            if(test_mode == 1)
                            {
                                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                TEXT_SetText(hItem,"精准");
                            }else if(test_mode == 0){
                                TEXT_SetFont(hItem,&GUI_Fontset_font);//设定文本字体
                                TEXT_SetText(hItem,"快速");
                            }
                        
                            switch(buffer)
                            {
                                case Lion:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"锂电池");
                                    b_type = Lion;
                                    break;
                                }
                                case NiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"镍氢电池");
                                    b_type = NiMH;
                                    break;
                                }
                                case NiCd:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"镍镉电池");
                                    b_type = NiCd;
                                    break;
                                }
                                case SLA:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"小型铅酸电池");
                                    b_type = SLA;
                                    break;
                                }
                                case LiMH:
                                {
                                    hItem = WM_GetDialogItem(hWinset, ID_TEXT_91);
                                    TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明
                                    TEXT_SetTextColor(hItem, GUI_WHITE);
                                    TEXT_SetText(hItem,"锂锰电池");
                                    b_type = LiMH;
                                    break;
                                }
                            }
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_92);
                            TEXT_SetText(hItem,"");
                        
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_93);
                            TEXT_SetText(hItem,"");
                            
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_94);
                            TEXT_SetText(hItem,"");
                            
                            hItem = WM_GetDialogItem(hWinset, ID_TEXT_95);
                            TEXT_SetText(hItem,"");
                            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//选项背景色设为透明

                            Write_btype();
                            set_sw = set_42;
                            break;                        
                    }
                    
                    default:break;
//                    return Beep_Flag;
                }
            }

            
// char* Strcat(char *arr1,char *arr2)
// {
//    char* tempt = arr1;
//    while(*arr1!='\0')
//    {
//       arr1++;
//    }
//    
//    while(*arr2!='\0')
//    {
//        *arr1 = *arr2;
//        arr1++;
//        arr2++;
//    }
//    
//    *arr1 = '\0';
//    
//    return tempt;
// }

void DEL_NUM(void){
    u8 i;
    switch(set_sw){
        case set_12:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_35);
            if(bit > 1)
			{
				bit --;
				set_limit[bit-1] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
        case set_13:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_36);
            if(bit > 1)
			{
				bit --;
				set_limit[bit-1] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
		case set_82:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_154);
            if(bit > 1)
			{
				bit --;
				set_limit[bit-1] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
        case set_83:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_155);
           if(bit > 1)
			{
				bit --;
				set_limit[bit-1] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
		
        case set_14:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_37);
            if(bit > 1)
			{
				bit --;
				set_limit[bit-1] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;           
        }
        case set_15:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_38);
            if(bit > 1)
			{
				bit --;
				set_limit[bit-1] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
        case set_16:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_39);
            if(bit > 1)
			{
				bit --;
				set_limit[bit-1] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
        case set_17:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_40);
            if(bit > 1)
			{
				bit --;
				set_limit[bit-1] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;
		}
		case set_84:
		{
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_156);
            if(bit > 1)
			{
				bit --;
				set_limit[bit-1] = '\0';
			}
			if(bit == dot_flag)
			{
				dot_flag = 0;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
        case set_85:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_157);
            if(bit > 1)
			{
				bit --;
				set_limit[bit-1] = '\0';
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
//系统设置界面数据输入
void INPUT_NUM(char* num);            
void INPUT_NUM(char* num){
    u8 i;
    switch(set_sw){
        case set_12:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_35);
            if(bit < 7)
			{
				strcat(set_limit,num);
			}
			if(dot_flag != 0 && strcmp(num,".") == 0)
			{
				
			}else{			
				
				if(dot_flag == 0 && strcmp(num,".") == 0)
				{
					dot_flag = bit;
				}
				bit ++;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
        case set_13:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_36);
            if(bit < 7)
			{
				strcat(set_limit,num);
			}
			if(dot_flag != 0 && strcmp(num,".") == 0)
			{
				
			}else{			
				
				if(dot_flag == 0 && strcmp(num,".") == 0)
				{
					dot_flag = bit;
				}
				bit ++;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
		case set_82:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_154);
            if(bit < 7)
			{
				strcat(set_limit,num);
			}
			if(dot_flag != 0 && strcmp(num,".") == 0)
			{
				
			}else{			
				
				if(dot_flag == 0 && strcmp(num,".") == 0)
				{
					dot_flag = bit;
				}
				bit ++;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
        case set_83:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_155);
            if(bit < 7)
			{
				strcat(set_limit,num);
			}
			if(dot_flag != 0 && strcmp(num,".") == 0)
			{
				
			}else{			
				
				if(dot_flag == 0 && strcmp(num,".") == 0)
				{
					dot_flag = bit;
				}
				bit ++;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
		
        case set_14:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_37);
            if(bit < 7)
			{
				strcat(set_limit,num);
			}
			if(dot_flag != 0 && strcmp(num,".") == 0)
			{
				
			}else{			
				
				if(dot_flag == 0 && strcmp(num,".") == 0)
				{
					dot_flag = bit;
				}
				bit ++;
			}
			TEXT_SetText(hItem,set_limit);
            break;           
        }
        case set_15:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_38);
            if(bit < 7)
			{
				strcat(set_limit,num);
			}
			if(dot_flag != 0 && strcmp(num,".") == 0)
			{
				
			}else{			
				
				if(dot_flag == 0 && strcmp(num,".") == 0)
				{
					dot_flag = bit;
				}
				bit ++;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
        case set_16:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_39);
            if(bit < 7)
			{
				strcat(set_limit,num);
			}
			if(dot_flag != 0 && strcmp(num,".") == 0)
			{
				
			}else{			
				
				if(dot_flag == 0 && strcmp(num,".") == 0)
				{
					dot_flag = bit;
				}
				bit ++;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
        case set_17:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_40);
            if(bit < 7)
			{
				strcat(set_limit,num);
			}
			if(dot_flag != 0 && strcmp(num,".") == 0)
			{
				
			}else{			
				
				if(dot_flag == 0 && strcmp(num,".") == 0)
				{
					dot_flag = bit;
				}
				bit ++;
			}
			TEXT_SetText(hItem,set_limit);
            break;
		}
		case set_84:
		{
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_156);
            if(bit < 7)
			{
				strcat(set_limit,num);
			}
			if(dot_flag != 0 && strcmp(num,".") == 0)
			{
				
			}else{			
				
				if(dot_flag == 0 && strcmp(num,".") == 0)
				{
					dot_flag = bit;
				}
				bit ++;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
        case set_85:
        {
            WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
            hItem = WM_GetDialogItem(hWinset, ID_TEXT_157);
            if(bit < 7)
			{
				strcat(set_limit,num);
			}
			if(dot_flag != 0 && strcmp(num,".") == 0)
			{
				
			}else{			
				
				if(dot_flag == 0 && strcmp(num,".") == 0)
				{
					dot_flag = bit;
				}
				bit ++;
			}
			TEXT_SetText(hItem,set_limit);
            break;
        }
	}
        
}






