#ifndef Timer_H
#define Timer_H
extern unsigned int Time_cnt;
extern unsigned int Light_cnt;
extern unsigned int NE555_cnt;
extern unsigned int S9_cnt;
extern unsigned int LED_cnt;
extern unsigned int LED_Display_cnt;
extern bit Time_flag;
extern bit light_flag;
extern bit NE555_flag;
extern bit Temp_flag;
extern bit S9_flag;
extern bit LED_flag;
extern bit LED_Display_flag;
extern bit Collect_Flag;
void Timer1_Init(void);
#endif // !Timer_H