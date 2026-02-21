#ifndef _Uart_H_
#define _Uart_H_
void Uart1_Init(void);
void Uart_Isr(void);
unsigned char *Arr_Value();
extern bit rx_complete_flag;
extern unsigned char rx_cnt;
#endif