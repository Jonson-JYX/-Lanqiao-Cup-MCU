#ifndef Timer_H
#define Timer_H
void Timer1_Init(void);
extern unsigned int xdata NE555_cnt;
extern unsigned int xdata S7_cnt;
extern bit S7_flag;
#endif // !Timer_H