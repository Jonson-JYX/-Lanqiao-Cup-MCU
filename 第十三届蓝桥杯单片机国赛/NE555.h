#ifndef NE555_H
#define NE555_H
extern unsigned int NE555_value;   //频率采集
extern unsigned int NE555_dat;     //频率参数
void Timer0_Init(void);
void NE555_login();
#endif // !NE555_H