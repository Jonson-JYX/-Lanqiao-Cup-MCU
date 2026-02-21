#ifndef DS1302_H
#define DS1302_H
extern unsigned char *time_value;
extern unsigned char time_now[6];
void Time_login();
void SetRTC(void);
#endif // !DS1302_H