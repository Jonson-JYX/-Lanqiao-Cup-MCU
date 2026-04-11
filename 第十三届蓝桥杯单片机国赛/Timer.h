#ifndef Timer_H
#define Timer_H
extern unsigned int NE555_cnt;
extern unsigned int Sound_cnt;
extern unsigned int DAC_cnt;
extern unsigned int ADC_cnt;
extern unsigned int LED1_cnt;
extern unsigned int LED2_cnt;
extern unsigned int LED3_cnt;
extern bit LED1_flag;
extern bit LED2_flag;
extern bit LED3_flag;
void Timer1_Init(void);
#endif // !Timer_H