#ifndef Timer_H
#define Timer_H
extern unsigned int Temp_cnt;
extern unsigned int Time_cnt;
extern unsigned int Relay_cnt;
extern unsigned int LED1_cnt;
extern unsigned int LED3_cnt;
extern bit Relay_flag;
extern bit LED1_flag;
extern bit LED3_flag;
void Timer0_Init(void);
#endif // !Timer_H