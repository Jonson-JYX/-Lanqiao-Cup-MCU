#ifndef _Uart_H_
#define _Uart_H_
extern bit recv_flag;
extern unsigned int recv_cnt;
extern unsigned char recv_dat[6];
void Uart_Init(void);
void Uart_Isr(void);
unsigned char *Recv_dat_arr();
#endif