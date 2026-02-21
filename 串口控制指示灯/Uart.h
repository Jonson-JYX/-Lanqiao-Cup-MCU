#ifndef _Uart_H_
#define _Uart_H_
extern bit rece_flag;
extern unsigned char recv_dat[8];
extern unsigned char rece_cnt;
void Uart_Init(void);
void Uart_Isr(void);
unsigned char *Arr_Value();
#endif