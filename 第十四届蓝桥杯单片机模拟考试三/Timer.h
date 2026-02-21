#ifndef Timer_H
#define Timer_H
extern unsigned int Temp_cnt;
extern unsigned int ADC_cnt;
extern unsigned int Uart_cnt;
extern unsigned int LED_cnt;
extern bit Uart_flag;
void Timer0_Init(void);
#endif // !Timer_H