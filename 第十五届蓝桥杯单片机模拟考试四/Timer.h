#ifndef Timer_H
extern unsigned int Temp_cnt;
extern unsigned int NE555_cnt;
extern unsigned int DAC_cnt;
extern unsigned int LED_cnt;
extern bit LED_flag;
void Timer1_Init(void);
#endif // !Timer_H