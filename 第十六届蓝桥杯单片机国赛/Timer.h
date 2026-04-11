#ifndef Timer_H
#define Timer_H
void Timer1_Init(void);
extern unsigned int Sound_cnt;   //声音测量计数器
extern unsigned int Temp_cnt;    //温度测量计数器
extern unsigned int RB2_cnt;     //RB2测量计数器
extern unsigned int Time_cnt;    //时间计数器
extern unsigned int NE555_cnt;   //NE555测量计数器
extern unsigned int Tank_cnt;    //容器测量计数器
#endif // !Timer_H