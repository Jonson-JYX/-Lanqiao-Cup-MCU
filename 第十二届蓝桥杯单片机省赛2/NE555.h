#ifndef NE555_H
#define NE555_H
extern unsigned int xdata NE555_value;
extern unsigned int xdata NE555_dat;
extern unsigned int xdata NE555_f;
void Timer0_Init(void);
void NE555_login();
#endif // !NE555_H