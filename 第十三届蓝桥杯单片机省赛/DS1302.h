#ifndef _DS1302_H_
#define _DS1302_H_   
void SetRTC(void);
unsigned char* ReadRTC(void);
extern unsigned char Time_value[6];
void Time_login();
#endif