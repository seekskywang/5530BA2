#ifndef _TM1650_H
#define _TM1650_H

#include "my_register.h"

#define IIC_WR	0		/* д࠘׆bit */
#define IIC_RD	1		/* ׁ࠘׆bit */

void IIc_Start(void);
void IIc_Stop(void);
void IIc_SendByte(vu8 _ucByte);
vu8 IIc_ReadByte(void);
vu8 IIc_WaitAck(void);
void IIc_Ack(void);
void IIc_NAck(void);
vu8 IIc_CheckDevice(vu8 _Address);
void TM1650_GPIO_INT(void);
vu8 TM1650_Read_KEY(void);
void TM1650_SET_LED(vu8 addr,vu8 dat);
void TM1650_SystemCmd(vu8 light,vu8 segMod, vu8 WorkMod, vu8 Onoff);
void TM1650Disp(vu8 sdate1, vu8 sdate2, vu8 sdate3, vu8 sdate4);
#endif
