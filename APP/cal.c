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

WM_HWIN hWincal;
WM_HWIN Createcal(void);
extern vu16 Modify_A_READ;
extern vu16 Modify_C_READ;
extern vu16 Modify_A_ACT;
	
extern vu16 Modify_B_READ;
extern vu16 Modify_D_READ;
extern vu16 Modify_B_ACT;
extern void Rlow_cal(u8 step);
u8 calmode = mode_load;
u32 inputvalue;
extern vu8 oldcal;
char inputv[10];

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

#define ID_WINDOW_9     (GUI_ID_USER + 0x0126)
#define ID_TEXT_137     (GUI_ID_USER + 0x0127)
#define ID_TEXT_138     (GUI_ID_USER + 0x0128)
#define ID_TEXT_139     (GUI_ID_USER + 0x0129)
#define ID_TEXT_140     (GUI_ID_USER + 0x012A)
#define ID_TEXT_141     (GUI_ID_USER + 0x012B)
#define ID_TEXT_142     (GUI_ID_USER + 0x012C)

#define ID_TimerTime8    9

static const GUI_WIDGET_CREATE_INFO _aDialogCreate8[] = {
  { WINDOW_CreateIndirect, "CAL", ID_WINDOW_9, 0, 0, 480, 272, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_137, 140, 50, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_138, 140, 75, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_139, 140, 100, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_140, 140, 125, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_141, 140, 150, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_142, 140, 175, 120, 20, 0, 0x0, 0 },

};


static void _cbDialog(WM_MESSAGE * pMsg) {
    WM_HWIN hItem;
    static char buf[5];

  switch (pMsg->MsgId) {
		
	case WM_PAINT:
        GUI_SetColor(GUI_WHITE);//??????
        GUI_FillRect(0,25,480,26);//????ß±
        GUI_SetColor(GUI_ORANGE);
        GUI_SetFont(&GUI_Fontsymbol);
        GUI_UC_SetEncodeUTF8();
        GUI_SetTextMode(GUI_TM_TRANS);//??¶”????????
        if(jkflag == 1)
		{
			GUI_DispStringAt("Jinko", 5, 1);//SET
		}
        GUI_SetColor(GUI_WHITE);
        GUI_SetFont(&GUI_FontHZ20S);
        GUI_UC_SetEncodeUTF8();
//        GUI_SetTextMode(GUI_TM_TRANS);//??¶”????????
//        GUI_DispStringAt("–£◊º", 130, 3);//SET
        GUI_SetColor(GUI_WHITE);
        GUI_SetFont(&GUI_Fontset_font);
        GUI_DispStringAt("Ê®°Âºè", 30, 50);
        GUI_DispStringAt("ÁîµÂéã", 30, 75);
        GUI_DispStringAt("ÁîµÊµÅ", 30, 100);
        GUI_DispStringAt("ÂÜÖÈòª", 30, 125);
        GUI_DispStringAt("ÂÜÖÈòªÈáèÁ®ã", 30, 150);
        GUI_DispStringAt("ËæìÂÖ•ÂÄº", 30, 175);
//        GUI_DispStringAt("Ê≠•È™§", 30, 150);
//         GUI_DispStringAt("“«∆˜±‡∫≈", 30, 150);
//         GUI_SetColor(0x00BFFFFF);
//         GUI_SetFont(&GUI_Font24_1);
//         GUI_DispStringAt("JK5530B", 140, 50);
//         GUI_DispStringAt("Ver:1.7", 140, 75);
//        
//         GUI_DispStringAt("Ver:1.2", 140, 100);
//         GUI_DispStringAt("-", 191, 125);
//         GUI_DispStringAt("-", 227, 125);
//         GUI_DispStringAt("A", 164, 150);
        DrawLock();
	break;
	case WM_TIMER:
	if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime8)
	{
        lockstat2 = lockstat1;
        lockstat1 = lock;
        if(lockstat1 != lockstat2)
        {
            WM_InvalidateWindow(hWincal);
        }
        if(calmode == mode_load)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_137);
            GUI_UC_SetEncodeUTF8();
			if(vflag == 0)
			{ 
				TEXT_SetTextColor(hItem, GUI_GREEN);
				
			}else{
				TEXT_SetTextColor(hItem, GUI_RED);
			}
        //  sprintf(buf,"%.3f",0);
            TEXT_SetText(hItem,"Ë¥üËΩΩÁîµÂéã");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_138);
            TEXT_SetTextColor(hItem, GUI_WHITE);// ®◊ÉÿñÕ•“ï…´
            sprintf(buf,"%.3f",DISS_Voltage);
            TEXT_SetFont(hItem,&GUI_Font24_1);// ®÷®œÑ—æÿñÕ•
            GUI_UC_SetEncodeUTF8();  
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_139);
            TEXT_SetTextColor(hItem, GUI_WHITE);// ®◊ÉÿñÕ•“ï…´
            sprintf(buf,"%.3f",DISS_Current);
            TEXT_SetFont(hItem,&GUI_Font24_1);// ®÷®œÑ—æÿñÕ•
            GUI_UC_SetEncodeUTF8();  
            TEXT_SetText(hItem,buf);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_142);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//ÈÄâÈ°πËÉåÊôØËâ≤ËÆæ‰∏∫ÈÄèÊòé
            TEXT_SetTextColor(hItem, GUI_WHITE);
        }else if(calmode == mode_pow){
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_137);
            GUI_UC_SetEncodeUTF8();
        //  sprintf(buf,"%.3f",0);
            TEXT_SetText(hItem,"ÂÖÖÁîµÁîµÂéã");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_138);
            TEXT_SetTextColor(hItem, GUI_WHITE);// ®◊ÉÿñÕ•“ï…´
            sprintf(buf,"%.3f",DISS_POW_Voltage);
            TEXT_SetFont(hItem,&GUI_Font24_1);// ®÷®œÑ—æÿñÕ•
            GUI_UC_SetEncodeUTF8();  
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_139);
            TEXT_SetTextColor(hItem, GUI_WHITE);// ®◊ÉÿñÕ•“ï…´
            sprintf(buf,"%.3f",DISS_POW_Current);
            TEXT_SetFont(hItem,&GUI_Font24_1);// ®÷®œÑ—æÿñÕ•
            GUI_UC_SetEncodeUTF8();  
            TEXT_SetText(hItem,buf);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_142);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//ÈÄâÈ°πËÉåÊôØËâ≤ËÆæ‰∏∫ÈÄèÊòé
            TEXT_SetTextColor(hItem, GUI_WHITE);
        }else if(calmode == mode_r ){
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_137);
            GUI_UC_SetEncodeUTF8();
        //  sprintf(buf,"%.3f",0);
            TEXT_SetText(hItem,"ÂÜÖÈòª");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_138);
            TEXT_SetTextColor(hItem, GUI_WHITE);// ®◊ÉÿñÕ•“ï…´
            sprintf(buf,"%.3f",DISS_Voltage);
            TEXT_SetFont(hItem,&GUI_Font24_1);// ®÷®œÑ—æÿñÕ•
            GUI_UC_SetEncodeUTF8();  
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_139);
            TEXT_SetTextColor(hItem, GUI_WHITE);// ®◊ÉÿñÕ•“ï…´
            sprintf(buf,"%.3f",DISS_Current);
            TEXT_SetFont(hItem,&GUI_Font24_1);// ®÷®œÑ—æÿñÕ•
            GUI_UC_SetEncodeUTF8();  
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_141);
            GUI_UC_SetEncodeUTF8();
            if(r_raly == 0)
            {
                TEXT_SetText(hItem,"200");
            }else if(r_raly == 1){
                TEXT_SetText(hItem,"2000");
            } 
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_142);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//ÈÄâÈ°πËÉåÊôØËâ≤ËÆæ‰∏∫ÈÄèÊòé
            TEXT_SetTextColor(hItem, GUI_WHITE);
        }else if(calmode == mode_loadc)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_137);
            GUI_UC_SetEncodeUTF8();
        //  sprintf(buf,"%.3f",0);
            TEXT_SetText(hItem,"Ë¥üËΩΩÁîµÊµÅ");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_138);
            TEXT_SetTextColor(hItem, GUI_WHITE);// ®◊ÉÿñÕ•“ï…´
            sprintf(buf,"%.3f",DISS_Voltage);
            TEXT_SetFont(hItem,&GUI_Font24_1);// ®÷®œÑ—æÿñÕ•
            GUI_UC_SetEncodeUTF8();  
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_139);
            TEXT_SetTextColor(hItem, GUI_WHITE);// ®◊ÉÿñÕ•“ï…´
            sprintf(buf,"%.3f",DISS_Current);
            TEXT_SetFont(hItem,&GUI_Font24_1);// ®÷®œÑ—æÿñÕ•
            GUI_UC_SetEncodeUTF8();  
            TEXT_SetText(hItem,buf);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_142);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//ÈÄâÈ°πËÉåÊôØËâ≤ËÆæ‰∏∫ÈÄèÊòé
            TEXT_SetTextColor(hItem, GUI_WHITE);
        }else if(calmode == mode_powc){
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_137);
            GUI_UC_SetEncodeUTF8();
        //  sprintf(buf,"%.3f",0);
            TEXT_SetText(hItem,"ÂÖÖÁîµÁîµÊµÅ");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_138);
            TEXT_SetTextColor(hItem, GUI_WHITE);// ®◊ÉÿñÕ•“ï…´
            sprintf(buf,"%.3f",DISS_POW_Voltage);
            TEXT_SetFont(hItem,&GUI_Font24_1);// ®÷®œÑ—æÿñÕ•
            GUI_UC_SetEncodeUTF8();  
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_139);
            TEXT_SetTextColor(hItem, GUI_WHITE);// ®◊ÉÿñÕ•“ï…´
            sprintf(buf,"%.3f",DISS_POW_Current);
            TEXT_SetFont(hItem,&GUI_Font24_1);// ®÷®œÑ—æÿñÕ•
            GUI_UC_SetEncodeUTF8();  
            TEXT_SetText(hItem,buf);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_142);
            TEXT_SetBkColor(hItem,GUI_INVALID_COLOR);//ÈÄâÈ°πËÉåÊôØËâ≤ËÆæ‰∏∫ÈÄèÊòé
            TEXT_SetTextColor(hItem, GUI_WHITE);
        }else if(calmode == input){
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_142);
            TEXT_SetTextColor(hItem, GUI_BLACK);//ËÆæÁΩÆÂ≠ó‰ΩìÈ¢úËâ≤
            TEXT_SetBkColor(hItem,0x00BFFFFF);
        }
        
        
        
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_140);
        TEXT_SetTextColor(hItem, GUI_WHITE);//…Ë÷√◊÷ÃÂ—’…´
        sprintf(buf,"%4d",R_VLUE);
        TEXT_SetFont(hItem,&GUI_Font24_1);//…Ë∂®Œƒ±æ◊÷ÃÂ
        GUI_UC_SetEncodeUTF8();  
        TEXT_SetText(hItem,buf);
		WM_RestartTimer(pMsg->Data.v,50);
        
        
	}
	break;
    
		
  case WM_INIT_DIALOG:
      hItem = pMsg->hWin;
      WINDOW_SetBkColor(hItem, GUI_BLACK);
      WM_CreateTimer(hItem,ID_TimerTime8,20,0);
  
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_137);
      GUI_UC_SetEncodeUTF8();
//      sprintf(buf,"%.3f",0);
      TEXT_SetText(hItem,"Ë¥üËΩΩ");
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Fontset_font);
	
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_138);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%.3f",0);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_139);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%.3f",0);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
		
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_140);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",R_VLUE);
      TEXT_SetText(hItem,buf);
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_141);
      GUI_UC_SetEncodeUTF8();
      if(r_raly == 0)
      {
          TEXT_SetText(hItem,"200");
      }else if(r_raly == 1){
          TEXT_SetText(hItem,"2000");
      }          
      TEXT_SetTextColor(hItem, 0x00BFFFFF);
      TEXT_SetFont(hItem, &GUI_Font24_1);
// 	
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_142);
      GUI_UC_SetEncodeUTF8();
      sprintf(buf,"%d",inputvalue);
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


WM_HWIN Createcal(void) {
  hWincal  = GUI_CreateDialogBox(_aDialogCreate8, GUI_COUNTOF(_aDialogCreate8), _cbDialog, WM_HBKWIN, 0, 0);
  pass = 0;
  page_sw = face_cal;
  return hWincal;
}

void inputcal(char* num)
{
    
    WM_HWIN hItem;
//            WM_InvalidateWindow(hWinset);
    hItem = WM_GetDialogItem(hWincal, ID_TEXT_142);
    
    switch(bit){
        case 1:
        {
            inputvalue = atoi(num);
            strcat(inputv,num);            
            TEXT_SetText(hItem,inputv);
            bit = 2;
            break; 
        }
        case 2:
        {
            inputvalue = inputvalue * 10 + atoi(num);
            strcat(inputv,num);            
            TEXT_SetText(hItem,inputv);
            bit = 3;
            break; 
        }
        case 3:
        {
            inputvalue = inputvalue * 10 + atoi(num);
            strcat(inputv,num);            
            TEXT_SetText(hItem,inputv);
            bit = 4;
            break; 
        }
        case 4:
        {
            inputvalue = inputvalue * 10 + atoi(num);
            strcat(inputv,num);            
            TEXT_SetText(hItem,inputv);
            bit = 5;
            break; 
        }
        case 5:
        {
            inputvalue = inputvalue * 10 + atoi(num);
            strcat(inputv,num);            
            TEXT_SetText(hItem,inputv);
            bit = 6;
            break; 
        }
        case 6:
        {
            inputvalue = inputvalue * 10 + atoi(num);
            strcat(inputv,num);            
            TEXT_SetText(hItem,inputv);
            bit = 1;
            break; 
        }
    }
}

void confirmcal(void)
{
    calmode = oldcal;
    bit = 1;  
}

void Rlow_cal(u8 step)
{
    if(step == 1)
    {
        Modify_A_READ = Rmon_value;//≤‚¡øµÁ—π÷µ
		Modify_A_ACT = inputvalue;//∂¡»°µÕ∂Œ
    }else if(step == 2){
        vu16 var16;
        vu32 var32a;
        vu32 var32b;
        
        vu16 var16a;
        vu32 var32c;
        vu32 var32d;
        Modify_B_READ =Rmon_value;//≤‚¡øµÁ—π÷µ
        flag_OverV=1;
        Modify_B_ACT = inputvalue;//∂¡»°∏ﬂ∂Œ
        if(flag_OverV==1)//÷ª”–µ±”– ˝æ›–¥»Î ±≤≈ƒ‹Ω´–£◊º ˝æ›–¥»ÎFLASH
        {
            var32a = Modify_B_ACT;
            var32a = var32a - Modify_A_ACT;
            var32a = var32a << 12;
            var16 = Modify_B_READ - Modify_A_READ;
            var32a = var32a / var16;
            REG_CorrectionRL = var32a;
            var32a=0;
            var32a = Modify_B_ACT;
            var32a = var32a << 12;
            var32b = Modify_B_READ;
            var32b = var32b * REG_CorrectionRL;
            if (var32a < var32b)
            {
                var32b = var32b - var32a;
                REG_ReadRL_Offset = var32b;
                Polar15 |= 0x01;
            }
            else 
            {
                var32a = var32a - var32b;
                REG_ReadRL_Offset = var32a;
                Polar15 &= ~0x01;
            }
//---------------------------------------------------------------------------------------//
            Flash_Write_all();	//≤Œ ˝–¥Ω¯FLASH
            flag_OverV=0;
            Flag_DAC_OFF=0;
        }
        flag_ADJ_VH=0;//«ÂµÙ±Í÷æŒª∑¿÷π“ª÷±Ω¯»Î
    }else if(step == 3){
        Modify_A_READ = Rmon_value;//≤‚¡øµÁ—π÷µ
		Modify_A_ACT = inputvalue;//∂¡»°µÕ∂Œ
    }else if(step == 4){
        vu16 var16;
        vu32 var32a;
        vu32 var32b;
        
        vu16 var16a;
        vu32 var32c;
        vu32 var32d;
        Modify_B_READ =Rmon_value;//≤‚¡øµÁ—π÷µ
        flag_OverV=1;
        Modify_B_ACT = inputvalue;//∂¡»°∏ﬂ∂Œ
        if(flag_OverV==1)//÷ª”–µ±”– ˝æ›–¥»Î ±≤≈ƒ‹Ω´–£◊º ˝æ›–¥»ÎFLASH
        {
            var32a = Modify_B_ACT;
            var32a = var32a - Modify_A_ACT;
            var32a = var32a << 12;
            var16 = Modify_B_READ - Modify_A_READ;
            var32a = var32a / var16;
            REG_CorrectionRH = var32a;
            var32a=0;
            var32a = Modify_B_ACT;
            var32a = var32a << 12;
            var32b = Modify_B_READ;
            var32b = var32b * REG_CorrectionRH;
            if (var32a < var32b)
            {
                var32b = var32b - var32a;
                REG_ReadRH_Offset = var32b;
                Polar16 |= 0x01;
            }
            else 
            {
                var32a = var32a - var32b;
                REG_ReadRH_Offset = var32a;
                Polar16 &= ~0x01;
            }
//---------------------------------------------------------------------------------------//
            Flash_Write_all();	//≤Œ ˝–¥Ω¯FLASH
			Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
            flag_OverV=0;
            Flag_DAC_OFF=0;
        }
    }else if(step == 5){
        Modify_A_READ = Rmon_value;//≤‚¡øµÁ—π÷µ
		Modify_A_ACT = inputvalue;//∂¡»°µÕ∂Œ
    }else if(step == 6){
        vu16 var16;
        vu32 var32a;
        vu32 var32b;
        
        vu16 var16a;
        vu32 var32c;
        vu32 var32d;
        Modify_B_READ =Rmon_value;//≤‚¡øµÁ—π÷µ
        flag_OverV=1;
        Modify_B_ACT = inputvalue;//∂¡»°∏ﬂ∂Œ
        if(flag_OverV==1)//÷ª”–µ±”– ˝æ›–¥»Î ±≤≈ƒ‹Ω´–£◊º ˝æ›–¥»ÎFLASH
        {
            var32a = Modify_B_ACT;
            var32a = var32a - Modify_A_ACT;
            var32a = var32a << 12;
            var16 = Modify_B_READ - Modify_A_READ;
            var32a = var32a / var16;
            REG_CorrectionR = var32a;
            var32a=0;
            var32a = Modify_B_ACT;
            var32a = var32a << 12;
            var32b = Modify_B_READ;
            var32b = var32b * REG_CorrectionR;
            if (var32a < var32b)
            {
                var32b = var32b - var32a;
                REG_ReadR_Offset = var32b;
                Polar3 |= 0x01;
            }
            else 
            {
                var32a = var32a - var32b;
                REG_ReadR_Offset = var32a;
                Polar3 &= ~0x01;
            }
//---------------------------------------------------------------------------------------//
            Flash_Write_all();	//≤Œ ˝–¥Ω¯FLASH
            flag_OverV=0;
            Flag_DAC_OFF=0;
        }
    }
}

void LoadVCal(u8 step)
{
    if(step == 1)
    {
        Modify_A_READ = Vmon1_value;//????
        Modify_A_ACT = inputvalue;//????
    }else if(step == 2){
        vu32 var16;
        vu32 var32a;
        vu32 var32b;
        
        vu32 var16a;
        vu32 var32c;
        vu32 var32d;
        Modify_B_READ =Vmon1_value;//????
        Modify_B_ACT = inputvalue;//????
        var32a = Modify_B_ACT;
        var32a = var32a - Modify_A_ACT;
        var32a = var32a << 12;
        var16 = Modify_B_READ - Modify_A_READ;
        var32a = var32a / var16;
        REG_CorrectionV = var32a;
        var32a=0;
        var32a = Modify_B_ACT;
        var32a = var32a << 12;
        var32b = Modify_B_READ;
        var32b = var32b * REG_CorrectionV;
        if (var32a < var32b)
        {
            var32b = var32b - var32a;
            REG_ReadV_Offset = var32b;
            Polar |= 0x01;
        }
        else
        {
            var32a = var32a - var32b;
            REG_ReadV_Offset = var32a;
            Polar &= ~0x01;
        }
        Flash_Write_all();	//??ß’?FLASH
//        Flag_DAC_OFF=0;
    }else if(step == 3){
        Modify_A_READ = Vmon1_value;//????
        Modify_A_ACT = inputvalue;//????
    }else if(step == 4){
        vu32 var16;
        vu32 var32a;
        vu32 var32b;
        
        vu32 var16a;
        vu32 var32c;
        vu32 var32d;
        Modify_B_READ =Vmon1_value;//????
        Modify_B_ACT = inputvalue;//????
        var32a = Modify_B_ACT;
        var32a = var32a - Modify_A_ACT;
        var32a = var32a << 12;
        var16 = Modify_B_READ - Modify_A_READ;
        var32a = var32a / var16;
        REG_CorrectionV1 = var32a;
        var32a=0;
        var32a = Modify_B_ACT;
        var32a = var32a << 12;
        var32b = Modify_B_READ;
        var32b = var32b * REG_CorrectionV1;
        if (var32a < var32b)
        {
            var32b = var32b - var32a;
            REG_ReadV_Offset1 = var32b;
            Polar6 |= 0x01;
        }
        else
        {
            var32a = var32a - var32b;
            REG_ReadV_Offset1 = var32a;
            Polar6 &= ~0x01;
        }
        Flash_Write_all();	//??ß’?FLASH
		Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
//        Flag_DAC_OFF=0;
    }else if(step == 5){
        Modify_A_READ = Vmon1_value;//????
        Modify_A_ACT = inputvalue;//????
    }else if(step == 6){
        vu32 var16;
        vu32 var32a;
        vu32 var32b;
        
        vu32 var16a;
        vu32 var32c;
        vu32 var32d;
        Modify_B_READ =Vmon1_value;//????
        Modify_B_ACT = inputvalue;//????
        var32a = Modify_B_ACT;
        var32a = var32a - Modify_A_ACT;
        var32a = var32a << 12;
        var16 = Modify_B_READ - Modify_A_READ;
        var32a = var32a / var16;
        REG_CorrectionV2 = var32a;
        var32a=0;
        var32a = Modify_B_ACT;
        var32a = var32a << 12;
        var32b = Modify_B_READ;
        var32b = var32b * REG_CorrectionV2;
        if (var32a < var32b)
        {
            var32b = var32b - var32a;
            REG_ReadV_Offset2 = var32b;
            Polar7 |= 0x01;
        }
        else
        {
            var32a = var32a - var32b;
            REG_ReadV_Offset2 = var32a;
            Polar7 &= ~0x01;
        }
        Flash_Write_all();	//??ß’?FLASH
//        Flag_DAC_OFF=0;
    }
}

void LoadCCal(u8 step)
{
    if(step == 1)
    {
        Modify_A_READ = Imon1_value;//
		Modify_C_READ = Contr_Laod;//
		Modify_A_ACT = inputvalue;
    }else if(step == 2){
       vu32 var16;
		vu32 var32a;
		vu32 var32b;
		
		vu32 var16a;
		vu32 var32c;
		vu32 var32d;
		
		Modify_B_READ = Imon1_value;
		Modify_D_READ = Contr_Laod;
		Modify_B_ACT = inputvalue;
		
		var32a = Modify_B_ACT;
		var32a = var32a - Modify_A_ACT;
		var32a = var32a << 12;
		var16 = Modify_B_READ - Modify_A_READ;
		var32a = var32a / var16;
		REG_Load_A = var32a;
		var32a = Modify_B_ACT;
		var32a = var32a << 12;
		var32b = Modify_B_READ;
		var32b = var32b * REG_Load_A;
		if (var32a < var32b)
		{
			var32b = var32b - var32a;
			REG_LoadA_Offset = var32b;
			Polar1 |= 0x01;
		}
		else 
		{
			var32a = var32a - var32b;
			REG_LoadA_Offset = var32a;
			Polar1 &= ~0x01;					
		}
//---------------------------------------------------------------------------------//
		var32c = Modify_B_ACT; 
		var32c = var32c - Modify_A_ACT;
		var32c = var32c << 12;
		var16a=Modify_D_READ-Modify_C_READ;
		var16a=var16a*2;
		var32c=var32c/var16a;
		SET_LoadA = var32c;
		var32c = Modify_B_ACT;
		var32c = var32c << 12;
		var32d = SET_LoadA;
		var32d = var32d * (Modify_D_READ*2);
		if (var32c < var32d)
		{
			var32d = var32d - var32c;
			SET_LoadA_Offset = var32d;
			Polar1 |= 0x04;
		}
		else 
		{
			var32c = var32c - var32d;
			SET_LoadA_Offset = var32c;
			Polar1 &= ~0x04;
		}
		Flash_Write_all ();	
		Flag_DAC_OFF =0;
    }else if(step == 3){
		Modify_A_READ = Imon1_value;//
		Modify_C_READ = Contr_Laod;//
		Modify_A_ACT = inputvalue;
	}else if(step == 4){
		vu32 var16;
		vu32 var32a;
		vu32 var32b;
		
		vu32 var16a;
		vu32 var32c;
		vu32 var32d;
		
		Modify_B_READ = Imon1_value;
		Modify_D_READ = Contr_Laod;
		Modify_B_ACT = inputvalue;
		
		var32a = Modify_B_ACT;
		var32a = var32a - Modify_A_ACT;
		var32a = var32a << 12;
		var16 = Modify_B_READ - Modify_A_READ;
		var32a = var32a / var16;
		REG_Load_A1 = var32a;
		var32a = Modify_B_ACT;
		var32a = var32a << 12;
		var32b = Modify_B_READ;
		var32b = var32b * REG_Load_A1;
		if (var32a < var32b)
		{
			var32b = var32b - var32a;
			REG_LoadA_Offset1 = var32b;
			Polar8 |= 0x01;
		}
		else 
		{
			var32a = var32a - var32b;
			REG_LoadA_Offset1 = var32a;
			Polar8 &= ~0x01;					
		}
//---------------------------------------------------------------------------------//
		var32c = Modify_B_ACT; 
		var32c = var32c - Modify_A_ACT;
		var32c = var32c << 12;
		var16a=Modify_D_READ-Modify_C_READ;
		var16a=var16a*2;
		var32c=var32c/var16a;
		SET_LoadA1 = var32c;
		var32c = Modify_B_ACT;
		var32c = var32c << 12;
		var32d = SET_LoadA1;
		var32d = var32d * (Modify_D_READ*2);
		if (var32c < var32d)
		{
			var32d = var32d - var32c;
			SET_LoadA_Offset1 = var32d;
			Polar8 |= 0x04;
		}
		else 
		{
			var32c = var32c - var32d;
			SET_LoadA_Offset1 = var32c;
			Polar8 &= ~0x04;
		}
		Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
//			Flash_Write_all ();	
		Flag_DAC_OFF =0;
	}else if(step == 5){
		Modify_A_READ = Imon1_value;//
		Modify_C_READ = Contr_Laod;//
		Modify_A_ACT = inputvalue;
	}else if(step == 6){
		vu32 var16;
		vu32 var32a;
		vu32 var32b;
		
		vu32 var16a;
		vu32 var32c;
		vu32 var32d;
		
		Modify_B_READ = Imon1_value;
		Modify_D_READ = Contr_Laod;
		Modify_B_ACT = inputvalue;
		
		var32a = Modify_B_ACT;
		var32a = var32a - Modify_A_ACT;
		var32a = var32a << 12;
		var16 = Modify_B_READ - Modify_A_READ;
		var32a = var32a / var16;
		REG_Load_A2 = var32a;
		var32a = Modify_B_ACT;
		var32a = var32a << 12;
		var32b = Modify_B_READ;
		var32b = var32b * REG_Load_A2;
		if (var32a < var32b)
		{
			var32b = var32b - var32a;
			REG_LoadA_Offset2 = var32b;
			Polar9 |= 0x01;
		}
		else 
		{
			var32a = var32a - var32b;
			REG_LoadA_Offset2 = var32a;
			Polar9 &= ~0x01;					
		}
//---------------------------------------------------------------------------------//
		var32c = Modify_B_ACT; 
		var32c = var32c - Modify_A_ACT;
		var32c = var32c << 12;
		var16a=Modify_D_READ-Modify_C_READ;
		var16a=var16a*2;
		var32c=var32c/var16a;
		SET_LoadA2 = var32c;
		var32c = Modify_B_ACT;
		var32c = var32c << 12;
		var32d = SET_LoadA2;
		var32d = var32d * (Modify_D_READ*2);
		if (var32c < var32d)
		{
			var32d = var32d - var32c;
			SET_LoadA_Offset2 = var32d;
			Polar9 |= 0x04;
		}
		else 
		{
			var32c = var32c - var32d;
			SET_LoadA_Offset2 = var32c;
			Polar9 &= ~0x04;
		}
		Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
//			Flash_Write_all ();	
		Flag_DAC_OFF =0;
	}else if(step == 7){
		Modify_A_READ = Imon1_value;//
		Modify_C_READ = Contr_Laod;//
		Modify_A_ACT = inputvalue;
	}else if(step == 8){
		vu32 var16;
		vu32 var32a;
		vu32 var32b;
		
		vu32 var16a;
		vu32 var32c;
		vu32 var32d;
		
		Modify_B_READ = Imon1_value;
		Modify_D_READ = Contr_Laod;
		Modify_B_ACT = inputvalue;
		
		var32a = Modify_B_ACT;
		var32a = var32a - Modify_A_ACT;
		var32a = var32a << 12;
		var16 = Modify_B_READ - Modify_A_READ;
		var32a = var32a / var16;
		REG_Load_AH = var32a;
		var32a = Modify_B_ACT;
		var32a = var32a << 12;
		var32b = Modify_B_READ;
		var32b = var32b * REG_Load_AH;
		if (var32a < var32b)
		{
			var32b = var32b - var32a;
			REG_LoadA_OffsetH = var32b;
			Polar10 |= 0x01;
		}
		else 
		{
			var32a = var32a - var32b;
			REG_LoadA_OffsetH = var32a;
			Polar10 &= ~0x01;					
		}
//---------------------------------------------------------------------------------//
		var32c = Modify_B_ACT; 
		var32c = var32c - Modify_A_ACT;
		var32c = var32c << 12;
		var16a=Modify_D_READ-Modify_C_READ;
		var16a=var16a*2;
		var32c=var32c/var16a;
		SET_LoadAH = var32c;
		var32c = Modify_B_ACT;
		var32c = var32c << 12;
		var32d = SET_LoadAH;
		var32d = var32d * (Modify_D_READ*2);
		if (var32c < var32d)
		{
			var32d = var32d - var32c;
			SET_LoadA_OffsetH = var32d;
			Polar10 |= 0x04;
		}
		else 
		{
			var32c = var32c - var32d;
			SET_LoadA_OffsetH = var32c;
			Polar10 &= ~0x04;
		}
		Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
//			Flash_Write_all ();	
		Flag_DAC_OFF =0;
	}else if(step == 9){
		Modify_A_READ = Imon1_value;//
		Modify_C_READ = Contr_Laod;//
		Modify_A_ACT = inputvalue;
	}else if(step == 10){
		vu32 var16;
		vu32 var32a;
		vu32 var32b;
		
		vu32 var16a;
		vu32 var32c;
		vu32 var32d;
		
		Modify_B_READ = Imon1_value;
		Modify_D_READ = Contr_Laod;
		Modify_B_ACT = inputvalue;
		
		var32a = Modify_B_ACT;
		var32a = var32a - Modify_A_ACT;
		var32a = var32a << 12;
		var16 = Modify_B_READ - Modify_A_READ;
		var32a = var32a / var16;
		REG_Load_AH1 = var32a;
		var32a = Modify_B_ACT;
		var32a = var32a << 12;
		var32b = Modify_B_READ;
		var32b = var32b * REG_Load_AH1;
		if (var32a < var32b)
		{
			var32b = var32b - var32a;
			REG_LoadA_OffsetH1 = var32b;
			Polar11 |= 0x01;
		}
		else 
		{
			var32a = var32a - var32b;
			REG_LoadA_OffsetH1 = var32a;
			Polar11 &= ~0x01;					
		}
//---------------------------------------------------------------------------------//
		var32c = Modify_B_ACT; 
		var32c = var32c - Modify_A_ACT;
		var32c = var32c << 12;
		var16a=Modify_D_READ-Modify_C_READ;
		var16a=var16a*2;
		var32c=var32c/var16a;
		SET_LoadAH1 = var32c;
		var32c = Modify_B_ACT;
		var32c = var32c << 12;
		var32d = SET_LoadAH1;
		var32d = var32d * (Modify_D_READ*2);
		if (var32c < var32d)
		{
			var32d = var32d - var32c;
			SET_LoadA_OffsetH1 = var32d;
			Polar11 |= 0x04;
		}
		else 
		{
			var32c = var32c - var32d;
			SET_LoadA_OffsetH1 = var32c;
			Polar11 &= ~0x04;
		}
		Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
//			Flash_Write_all ();	
		Flag_DAC_OFF =0;
	}
}

void PowVCal(u8 step)
{
    if(step == 1)
    {
        Modify_A_READ = Vmon_value;//??d
		Modify_C_READ = Contr_Voltage;//???d
		Modify_A_ACT = inputvalue;
    }else if(step == 2){
        vu16 var16;
			vu32 var32a;
			vu32 var32b; 
			
			vu16 var16a;
			vu32 var32c;
			vu32 var32d;
			
			Modify_D_READ = Contr_Voltage;
			Modify_B_READ = Vmon_value;
			Modify_B_ACT = inputvalue;
			var32a = Modify_B_ACT;
			var32a = var32a - Modify_A_ACT;
			var32a = var32a << 14;
			var16 = Modify_B_READ - Modify_A_READ;
			var32a = var32a / var16;
			REG_POWERV = var32a;
			var32a = Modify_B_ACT;
			var32a = var32a << 14;
			var32b = Modify_B_READ;
			var32b = var32b * REG_POWERV;
			if (var32a < var32b)
			{
				var32b = var32b - var32a;
				REG_POWERV_Offset = var32b;
				Polar5 |= 0x01;
			}
			else 
			{
				var32a = var32a - var32b;
				REG_POWERV_Offset = var32a;
				Polar5 &= ~0x01;					
			}
	//---------------------------------------------------------------------------------//
			var32c = Modify_B_ACT; //????«µ?
			var32c = var32c - Modify_A_ACT;
			var32c = var32c << 14;
			var16a=Modify_D_READ-Modify_C_READ;
			var16a=var16a*2;
			var32c=var32c/var16a;
			SET_POWERV = var32c;
			var32c = Modify_B_ACT;
			var32c = var32c << 14;
			var32d = SET_POWERV;
			var32d = var32d * (Modify_D_READ*2);
			if (var32c < var32d)
			{
				var32d = var32d - var32c;
				SET_POWERV_Offset = var32d;
				Polar5 |= 0x04;
			}
			else 
			{
				var32c = var32c - var32d;
				SET_POWERV_Offset = var32c;
				Polar5 &= ~0x04;
			}
			Flash_Write_all ();	
			Flag_DAC_OFF=0;
    }else if(step == 3){
        Modify_A_READ = Vmon_value;//??d
		Modify_C_READ = Contr_Voltage;//???d
		Modify_A_ACT = inputvalue;
    }else if(step == 4){
        vu16 var16;
		vu32 var32a;
		vu32 var32b;
		
		vu16 var16a;
		vu32 var32c;
		vu32 var32d;
		
		Modify_D_READ = Contr_Voltage;
		Modify_B_READ = Vmon_value;
		Modify_B_ACT = inputvalue;
		var32a = Modify_B_ACT;
		var32a = var32a - Modify_A_ACT;
		var32a = var32a << 14;
		var16 = Modify_B_READ - Modify_A_READ;
		var32a = var32a / var16;
		REG_POWERV1 = var32a;
		var32a = Modify_B_ACT;
		var32a = var32a << 14;
		var32b = Modify_B_READ;
		var32b = var32b * REG_POWERV1;
		if (var32a < var32b)
		{
			var32b = var32b - var32a;
			REG_POWERV_Offset1 = var32b;
			Polar12 |= 0x01;
		}
		else 
		{
			var32a = var32a - var32b;
			REG_POWERV_Offset1 = var32a;
			Polar12 &= ~0x01;					
		}
//---------------------------------------------------------------------------------//
		var32c = Modify_B_ACT; //????ßµ?
		var32c = var32c - Modify_A_ACT;
		var32c = var32c << 14;
		var16a=Modify_D_READ-Modify_C_READ;
		var16a=var16a*2;
		var32c=var32c/var16a;
		SET_POWERV1 = var32c;
		var32c = Modify_B_ACT;
		var32c = var32c << 14;
		var32d = SET_POWERV1;
		var32d = var32d * (Modify_D_READ*2);
		if (var32c < var32d)
		{
			var32d = var32d - var32c;
			SET_POWERV_Offset1 = var32d;
			Polar12 |= 0x04;
		}
		else 
		{
			var32c = var32c - var32d;
			SET_POWERV_Offset1 = var32c;
			Polar12 &= ~0x04;
		}
		Flash_Write_all ();
		Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
		Flag_DAC_OFF=0;
    }else if(step == 5){
        Modify_A_READ = Vmon_value;//??d
		Modify_C_READ = Contr_Voltage;//???d
		Modify_A_ACT = inputvalue;
    }else if(step == 6){
        vu16 var16;
		vu32 var32a;
		vu32 var32b;
		
		vu16 var16a;
		vu32 var32c;
		vu32 var32d;
		
		Modify_D_READ = Contr_Voltage;
		Modify_B_READ = Vmon_value;
		Modify_B_ACT = inputvalue;
		var32a = Modify_B_ACT;
		var32a = var32a - Modify_A_ACT;
		var32a = var32a << 14;
		var16 = Modify_B_READ - Modify_A_READ;
		var32a = var32a / var16;
		REG_POWERV2 = var32a;
		var32a = Modify_B_ACT;
		var32a = var32a << 14;
		var32b = Modify_B_READ;
		var32b = var32b * REG_POWERV2;
		if (var32a < var32b)
		{
			var32b = var32b - var32a;
			REG_POWERV_Offset2 = var32b;
			Polar13 |= 0x01;
		}
		else 
		{
			var32a = var32a - var32b;
			REG_POWERV_Offset2 = var32a;
			Polar13 &= ~0x01;					
		}
//---------------------------------------------------------------------------------//
		var32c = Modify_B_ACT; //????ßµ?
		var32c = var32c - Modify_A_ACT;
		var32c = var32c << 14;
		var16a=Modify_D_READ-Modify_C_READ;
		var16a=var16a*2;
		var32c=var32c/var16a;
		SET_POWERV2 = var32c;
		var32c = Modify_B_ACT;
		var32c = var32c << 14;
		var32d = SET_POWERV2;
		var32d = var32d * (Modify_D_READ*2);
		if (var32c < var32d)
		{
			var32d = var32d - var32c;
			SET_POWERV_Offset2 = var32d;
			Polar13 |= 0x04;
		}
		else 
		{
			var32c = var32c - var32d;
			SET_POWERV_Offset2 = var32c;
			Polar13 &= ~0x04;
		}
		Flash_Write_all ();	
		Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
		Flag_DAC_OFF=0;
    }
}

void PowCCal(u8 step)
{
    if(step == 1)
    {
        Modify_A_READ = Imon_value;
		Modify_C_READ = Contr_Current;
		Modify_A_ACT = inputvalue;
    }else if(step == 2){
        vu16 var16;
			vu32 var32a;
			vu32 var32b;
			
			vu16 var16a;
			vu32 var32c;
			vu32 var32d;
			
			Modify_D_READ = Contr_Current;
			Modify_B_READ = Imon_value;
			Modify_B_ACT = inputvalue;
			var32a = Modify_B_ACT;
			var32a = var32a - Modify_A_ACT;
			var32a = var32a << 14;
			var16 = Modify_B_READ - Modify_A_READ;
			var32a = var32a / var16;
			REG_POWERA = var32a;
			var32a = Modify_B_ACT;
			var32a = var32a << 14;
			var32b = Modify_B_READ;
			var32b = var32b * REG_POWERA;
			if (var32a < var32b)
			{
				var32b = var32b - var32a;
				REG_POWERA_Offset = var32b;
				Polar4 |= 0x01;
			}
			else 
			{
				var32a = var32a - var32b;
				REG_POWERA_Offset = var32a;
				Polar4 &= ~0x01;					//?°§????°Í?ßµ???
			}
	//---------------------------------------------------------------------------------//
			var32c = Modify_B_ACT; //???°§ßµ?
			var32c = var32c - Modify_A_ACT;
			var32c = var32c << 14;
			var16a=Modify_D_READ-Modify_C_READ;
			var16a=var16a*2;
			var32c=var32c/var16a;
			SET_POWERA = var32c;
			var32c = Modify_B_ACT;
			var32c = var32c << 14;
			var32d = SET_POWERA;
			var32d = var32d * (Modify_D_READ*2);
			if (var32c < var32d)
			{
				var32d = var32d - var32c;
				SET_POWERA_Offset = var32d;
				Polar4 |= 0x04;
			}
			else 
			{
				var32c = var32c - var32d;
				SET_POWERA_Offset = var32c;
				Polar4 &= ~0x04;
			}
			Flash_Write_all ();	
			Flag_DAC_OFF=0;
    }else if (step == 3)			   //?d?«µ?
	{
		Modify_A_READ = Imon_value;//??d
		Modify_C_READ = Contr_Current;//???d
		Modify_A_ACT = inputvalue;
	}else if (step == 4)			   //?d?«µ???
	{
		vu16 var16;
		vu32 var32a;
		vu32 var32b;
		
		vu16 var16a;
		vu32 var32c;
		vu32 var32d;
		
		Modify_D_READ = Contr_Current;
		Modify_B_READ = Imon_value;
		Modify_B_ACT = inputvalue;
		var32a = Modify_B_ACT;
		var32a = var32a - Modify_A_ACT;
		var32a = var32a << 14;
		var16 = Modify_B_READ - Modify_A_READ;
		var32a = var32a / var16;
		REG_POWERA1 = var32a;
		var32a = Modify_B_ACT;
		var32a = var32a << 14;
		var32b = Modify_B_READ;
		var32b = var32b * REG_POWERA1;
		if (var32a < var32b)
		{
			var32b = var32b - var32a;
			REG_POWERA_Offset1 = var32b;
			Polar14 |= 0x01;
		}
		else 
		{
			var32a = var32a - var32b;
			REG_POWERA_Offset1 = var32a;
			Polar14 &= ~0x01;					//?d????¬™?«µ???
		}
//---------------------------------------------------------------------------------//
		var32c = Modify_B_ACT; //???d«µ?
		var32c = var32c - Modify_A_ACT;
		var32c = var32c << 14;
		var16a=Modify_D_READ-Modify_C_READ;
		var16a=var16a*2;
		var32c=var32c/var16a;
		SET_POWERA1 = var32c;
		var32c = Modify_B_ACT;
		var32c = var32c << 14;
		var32d = SET_POWERA1;
		var32d = var32d * (Modify_D_READ*2);
		if (var32c < var32d)
		{
			var32d = var32d - var32c;
			SET_POWERA_Offset1 = var32d;
			Polar14 |= 0x04;
		}
		else 
		{
			var32c = var32c - var32d;
			SET_POWERA_Offset1 = var32c;
			Polar14 &= ~0x04;
		}
		Flash_Write32BitDatas(FLASH_USER_START_ADDR,40, InFlashSave);
//			Flash_Write_all ();	
		Flag_DAC_OFF=0;
	}
}