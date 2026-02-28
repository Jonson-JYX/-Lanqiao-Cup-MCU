#ifndef Timer_H
#define Timer_H
extern unsigned int Time_cnt;
extern unsigned int NE555_cnt;
extern unsigned int LED1_cnt;
extern unsigned int LED2_cnt;
extern bit LED1_flag;
extern bit LED2_flag;
void Timer1_Init(void);
#endif // !Timer_H