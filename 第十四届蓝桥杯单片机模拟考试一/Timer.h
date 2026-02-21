#ifndef Timer_H
#define Timer_H
void Timer_Init(void);  
extern unsigned int LED_cnt1;
extern unsigned int LED_cnt2;
extern unsigned int Sound_cnt;
void Timer_Isr(void);
#endif // !Timer_H