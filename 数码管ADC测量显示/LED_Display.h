#ifndef _LED_Display_H_
#define _LED_Display_H_
extern code unsigned char SEG_Table[];
extern unsigned char ADC_dat_arr[];
extern unsigned char ADC_show_arr[];
void ADC_Change();
void LED_Display_Show();
#endif