#ifndef NE555_H
#define NE555_H
extern unsigned int NE555_value;
extern unsigned int NE555_max;
extern unsigned int xdata NE555_Average;
void Timer0_Init(void);
void NE555_login();
#endif // !NE555_H