#ifndef _LED_Display_H_
#define _LED_Display_H_
extern code unsigned char SEG_Table[];
extern unsigned char RB2_dat_arr1[];
extern unsigned char RB2_dat_arr2[];
extern unsigned char RB2_dat_arr3[];
extern unsigned char RB2_dat[];
extern unsigned char LED_Display_flag;
unsigned char Uart_Choose();
void LED_Display_Choose();
void LED_Display_Show();
#endif