#ifndef Timer_H
#define Timer_H
extern unsigned int Temp_cnt;
extern unsigned int Sound_cnt;
extern unsigned int DAC_cnt;
extern unsigned int LED_cnt;
extern bit Record_flag;  
extern bit LED_flag;
void Timer0_Init(void);
#endif // !Timer_H