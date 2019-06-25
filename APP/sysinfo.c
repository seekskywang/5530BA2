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
extern WM_HWIN Createcal(void);
WM_HWIN hWinsysinfo;
vu8 info_set = set_48;
vu16 year1 = 0;
vu16 year2 = 0;
vu16 year3 = 0;
vu16 year4 = 0;
vu8 month1 = 0;
vu8 month2 = 0;
vu8 day1 = 0;
vu8 day2 = 0;
vu8 admin = 0;
vu8 code1 = 0;
vu8 code2 = 0;
vu8 code3 = 0;
vu8 code4 = 0;
vu8 code5 = 0;
vu8 code6 = 0;
vu8 code7 = 0;
vu8 code8 = 0;
vu8 cal = 0;
extern vu8 pass;
extern vu16 Modify_A_READ;
extern vu16 Modify_C_READ;
extern vu16 Modify_A_ACT;
	
extern vu16 Modify_B_READ;
extern vu16 Modify_D_READ;
extern vu16 Modify_B_ACT;
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
} flagA,flagB,flagC,flagD,flagE,flagG;
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_8     (GUI_ID_USER + 0x98)
#define ID_TEXT_99      (GUI_ID_USER + 0x99)
#define ID_TEXT_100     (GUI_ID_USER + 0x9A)
#define ID_TEXT_101     (GUI_ID_USER + 0x9B)
#define ID_TEXT_102    	(GUI_ID_USER + 0x9C)
#define ID_TEXT_103    	(GUI_ID_USER + 0x9D)
#define ID_TEXT_104    	(GUI_ID_USER + 0x9E)
#define ID_TEXT_105    	(GUI_ID_USER + 0x115)
#define ID_TEXT_106   	(GUI_ID_USER + 0x116)
#define ID_TEXT_107    	(GUI_ID_USER + 0x117)
#define ID_TEXT_108    	(GUI_ID_USER + 0x118)
#define ID_TEXT_109    	(GUI_ID_USER + 0x119)
#define ID_TEXT_110    	(GUI_ID_USER + 0x11A)
#define ID_TEXT_111    	(GUI_ID_USER + 0x11B)
#define ID_TEXT_112    	(GUI_ID_USER + 0x11C)
#define ID_TEXT_113    	(GUI_ID_USER + 0x11D)
#define ID_TEXT_114    	(GUI_ID_USER + 0x11E)
#define ID_TEXT_136     (GUI_ID_USER + 0x0125)

#define ID_TimerTime7    8
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
static const GUI_WIDGET_CREATE_INFO _aDialogCreate7[] = {
  { WINDOW_CreateIndirect, "SYSINFO", ID_WINDOW_8, 0, 0, 480, 272, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_99, 140, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_100, 152, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_101, 164, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_102, 176, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_103, 200, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_104, 212, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_105, 236, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_106, 248, 125, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_107, 176, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_108, 188, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_109, 200, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_110, 212, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_111, 224, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_112, 236, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_113, 140, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_114, 152, 150, 12, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_136, 192, 200, 80, 20, 0, 0x0, 0 },
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
    static char buf[5];

    
  
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
        GUI_DispStringAt("系统信息", 130, 3);//SET
        GUI_SetColor(GUI_LIGHTBLUE);
        GUI_SetFont(&GUI_Fontset_font);
        GUI_DispStringAt("仪器型号", 30, 50);
        GUI_DispStringAt("软件版本", 30, 75);
        GUI_DispStringAt("硬件版本", 30, 100);
        GUI_DispStringAt("生产日期", 30, 125);
        GUI_DispStringAt("仪器编号", 30, 150);
        GUI_SetColor(0x00BFFFFF);
        GUI_SetFont(&GUI_Font24_1);
        GUI_DispStringAt("JK5530B", 140, 50);
        GUI_DispStringAt("Ver:3.1", 140, 75);
		//2.6修复内阻测试过流没分开bug
		//2.7增加风扇断路保护
		//2.8电源电压显示改成测量端
		//2.9增加动态测试协议
		//3.0修复截止电压电流输入只有2位有效数字bug
        GUI_DispStringAt("Ver:1.3", 140, 100);
        GUI_DispStringAt("-", 191, 125);
        GUI_DispStringAt("-", 227, 125);
        GUI_DispStringAt("A", 164, 150);
//        DrawLock();
	break;
	case WM_TIMER:
	if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime7)
	{
//        lockstat2 = lockstat1;
//        lockstat1 = lock;
//        if(lockstat1 != lockstat2)
//        {
//            WM_InvalidateWindow(hWinsysinfo);
//        }
        
        if(pass == 14)
        {
            admin = 1;
        }else if(pass == 10){
            cal = 1;
        }else{
            admin = 0;
            cal = 0;
        }
        
        if(cal ==  1)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_136);
            TEXT_SetTextColor(hItem, GUI_WHITE);//设置字体颜色
            sprintf(buf,"%4d",disrvalue);
            TEXT_SetFont(hItem,&GUI_Font24_1);//设定文本字体
            GUI_UC_SetEncodeUTF8();        
            TEXT_SetText(hItem,buf);
        }else{
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_136);
            TEXT_SetText(hItem, "");
            TEXT_SetTextColor(hItem, GUI_INVALID_COLOR);
        }
		WM_RestartTimer(pMsg->Data.v,500);//شλ֨ʱǷ˽ֵԽճˢтʱݤԽ׌
        
        
	}
	break;
    
		
  case WM_INIT_DIALOG:
      hItem = pMsg->hWin;
      WINDOW_SetBkColor(hItem, GUI_BLACK);
      WM_CreateTimer(hItem,ID_TimerTime7,20,0);
  
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_99);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",year1);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
	
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_100);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",year2);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_101);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",year3);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_102);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",year4);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_103);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",month1);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
	
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_104);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",month2);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_105);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",day1);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_106);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",day2);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
	
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_107);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code3);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_108);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code4);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_109);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code5);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_110);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code6);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_111);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code7);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_112);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code8);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_113);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code1);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_114);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",code2);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
      


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
WM_HWIN Createsysinfo(void);
WM_HWIN Createsysinfo(void) {
  hWinsysinfo  = GUI_CreateDialogBox(_aDialogCreate7, GUI_COUNTOF(_aDialogCreate7), _cbDialog, WM_HBKWIN, 0, 0);
  pass = 0;
  page_sw = face_sys_info;
  info_set = set_48;
  return hWinsysinfo;
}



void SYS_INFO_RIGHT(void)
{
    WM_HWIN hItem;
    switch(info_set)
    {
        case set_48:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_49;
            break;
        }
        case set_49:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_50;
            break;
        }
        case set_50:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_51;
            break;
        }
        case set_51:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_52;
            break;
        }
        case set_52:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_53;
            break;
        }
        case set_53:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_54;
            break;
        }
        case set_54:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_55;
            break;
        }
        case set_55:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_62:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_63;
            break;
        }
        case set_63:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_56;
            break;
        }
        case set_56:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_57;
            break;
        }
        case set_57:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_58;
            break;
        }
        case set_58:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_59;
            break;
        }
        case set_59:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_60;
            break;
        }
        case set_60:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_61;
            break;
        }
        case set_61:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
    }
    
}



void SYS_INFO_LEFT(void)
{
    WM_HWIN hItem;
    switch(info_set)
    {
        case set_48:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_55;
            break;
        }
        case set_49:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_50:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_49;
            break;
        }
        case set_51:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_50;
            break;
        }
        case set_52:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_51;
            break;
        }
        case set_53:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_52;
            break;
        }
        case set_54:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_53;
            break;
        }
        case set_55:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_54;
            break;
        }
        case set_62:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_61;
            break;
        }
        case set_63:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_56:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_63;
            break;
        }
        case set_57:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_56;
            break;
        }
        case set_58:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_57;
            break;
        }
        case set_59:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_58;
            break;
        }
        case set_60:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_59;
            break;
        }
        case set_61:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_60;
            break;
        }
    }
    
}



void SYS_INFO_UP(void)
{
    WM_HWIN hItem;
    switch(info_set)
    {
        case set_48:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_49:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_50:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_51:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_52:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_53:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_54:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_55:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_56:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_62:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_63:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_57:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_58:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_59:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_60:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_61:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
    }
    
}



void SYS_INFO_DOWN(void)
{
    WM_HWIN hItem;
    switch(info_set)
    {
        case set_48:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_49:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_50:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_51:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_52:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_53:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_54:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_55:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_62;
            break;
        }
        case set_62:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_63:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_56:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_57:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_58:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_59:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_60:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
        case set_61:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
            TEXT_SetTextColor(hItem, 0x00BFFFFF);
            
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            TEXT_SetBkColor(hItem,0x00BFFFFF);
            TEXT_SetTextColor(hItem, GUI_BLACK);
            
            info_set = set_48;
            break;
        }
    }
    
}


           
void INPUT_INFO(vu8 num){
    static char buf[5];
    WM_HWIN hItem;
    switch(info_set)
    {
        case set_48:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            year1 = num;
            Write_info();
            break;
        }
        case set_49:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_100);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            year2= num;
            Write_info();
            break;
        }
        case set_50:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_101);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            year3= num;
            Write_info();
            break;
        }
        case set_51:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_102);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            year4= num;
            Write_info();
            break;
        }
        case set_52:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_103);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            month1 = num;
            Write_info();
            break;
        }
        case set_53:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_104);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            month2 = num;
            Write_info();
            break;
        }
        case set_54:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_105);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            day1 = num;
            Write_info();
            break;
        }
        case set_55:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_106);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            day2 = num;
            Write_info();
            break;
        }
        case set_56:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_107);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code3 = num;
            Write_info();
            break;
        }
        case set_57:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_108);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code4 = num;
            Write_info();
            break;
        }
        case set_58:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_109);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code5 = num;
            Write_info();
            break;
        }
        case set_59:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_110);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code6 = num;
            Write_info();
            break;
        }
        case set_60:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_111);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code7 = num;
            Write_info();
            break;
        }
        case set_61:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_112);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code8 = num;
            Write_info();
            break;
        }
        case set_62:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_113);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code1 = num;
            Write_info();
            break;
        }
        case set_63:
        {
            hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_114);
            sprintf(buf,"%d",num);
            TEXT_SetText(hItem,buf);
            code2 = num;
            Write_info();
            break;
        }
        
    }
}

void CFM_PASS(void);            
void CFM_PASS(void){
    if(admin == 1)
    {
        WM_HWIN hItem;
        hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
        TEXT_SetBkColor(hItem,0x00BFFFFF);
        TEXT_SetTextColor(hItem, GUI_BLACK);
    }else if(cal == 1){
        Createcal();
    }else{
        WM_HWIN hItem;
        hItem = WM_GetDialogItem(hWinsysinfo, ID_TEXT_99);
        TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);
        TEXT_SetTextColor(hItem, 0x00BFFFFF);
        info_set = set_48;
    }
}


