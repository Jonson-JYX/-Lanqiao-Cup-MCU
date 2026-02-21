#ifndef _DS1302_H_
#define _DS1302_H_

#include "stc15f2k60s2.h"
#include "intrins.h"

sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST = P1^3;   

void SetRTC(void);
unsigned char* ReadRTC(void);

#endif