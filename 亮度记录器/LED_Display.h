#ifndef _LED_Display_H_
#define _LED_Display_H_
extern code unsigned char SEG_Table[];
extern unsigned char dat_value;
extern unsigned char dat_max;
extern unsigned char dat_min;
extern unsigned char dat_value_arr[];
extern unsigned char dat_show_arr[];
void Lighting_Change();
void LED_Display_Show();
#endif