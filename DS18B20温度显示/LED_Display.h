#ifndef _LED_Display_H_
#define _LED_Display_H_
extern code unsigned char LED_Display_Table[];
extern unsigned char Temp_modle1_Arr[];
extern unsigned char Temp_modle2_Arr[];
extern unsigned char Temp_dat[];
void Temp_Change();
void LED_Display_Show();
void LED_Display_Choose();
#endif