#ifndef _DS1302_H_
#define _DS1302_H_
void SetRTC(void);
unsigned char* ReadRTC(void);
void Time_login();
extern unsigned char *Time_value;   //时间值
#endif