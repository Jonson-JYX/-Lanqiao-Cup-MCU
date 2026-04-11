#ifndef _DS1302_H_
#define _DS1302_H_
extern unsigned char *Time_value;
extern unsigned char Time_dat[4];
extern unsigned int Time_num;
void Time_login();
void SetRTC(void);
unsigned char* ReadRTC(void);
void Time_login(); 
#endif