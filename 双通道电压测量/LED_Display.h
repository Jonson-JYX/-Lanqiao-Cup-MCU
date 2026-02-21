#ifndef _LED_Display_H_
#define _LED_Display_H_
extern code unsigned char SEG_Table[];
extern unsigned char Lighting_dat_Arr[];
extern unsigned char RB2_dat_Arr[];
extern unsigned char dat_arr[];
void Lighting_Change();
void RB2_Change();
void dat_arr_change();
void LED_Display_Show();
#endif