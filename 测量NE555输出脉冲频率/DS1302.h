#ifndef _DS1302_H_
#define _DS1302_H_
void SetRTC(void);
unsigned char* ReadRTC(void);
void Time_login();
extern unsigned char *time_max;
extern unsigned char *time_value;
#endif