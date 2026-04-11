#ifndef Timer_H
#define Timer_H
extern unsigned int temp_cnt;    //温度计数值
extern unsigned int light_cnt;   //光照计数值
extern unsigned int sound_cnt;   //声音计数值
extern unsigned int sound_status1_cnt;   //声音状态1计数值
extern unsigned int sound_status2_cnt;   //声音状态2计数值
extern unsigned int sound_status3_cnt;   //声音状态3计数值
extern unsigned int LED_cnt;     //LED计数值
extern bit LED_flag;             //LED标志位
extern bit sound_status1_flag;       //声音状态1标志位
extern bit sound_status2_flag;       //声音状态2标志位
extern bit sound_status3_flag;       //声音状态3标志位
void Timer0_Init(void);
#endif // !Timer_H