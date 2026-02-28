#ifndef _DS1302_H_
#define _DS1302_H_
extern unsigned char *Time_value;
extern unsigned char time_max[6];
void SetRTC(void);
unsigned char* ReadRTC(void);
void Time_login();
#endif