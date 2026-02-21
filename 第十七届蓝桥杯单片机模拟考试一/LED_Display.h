#ifndef LED_Display_H
#define LED_Display_H
extern code unsigned char SEG_Table[];
extern unsigned char time1_dat_arr[];
extern unsigned char time2_dat_arr[];
extern unsigned char time3_dat_arr[];
extern unsigned char Clear_dat_arr[];
void LED_Display_Choose();
void LED_Display_Show();
#endif