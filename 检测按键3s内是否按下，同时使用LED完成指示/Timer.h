#ifndef Timer_H
#define Timer_H
extern unsigned int L1_cnt;  // L1计时（3秒）
extern bit L1_flag;          // L1点亮标志
extern unsigned int L2_cnt;  // L2计时（3秒）
extern bit L2_flag;          // L2点亮标志
extern unsigned int L4_cnt;  // L4计时（3秒）
extern bit L4_flag;          // L4闪烁标志
extern unsigned int L5_cnt;  // L5计时（3秒）
extern bit L5_flag;          // L5闪烁标志
extern unsigned int blink4_cnt; // L4闪烁计时（0.1秒）
extern unsigned int blink5_cnt; // L5闪烁计时（0.1秒）
void Timer0_Init(void);
#endif // !Timer_H