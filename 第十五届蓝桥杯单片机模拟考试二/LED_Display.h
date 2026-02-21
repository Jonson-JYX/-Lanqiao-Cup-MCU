#ifndef _LED_Display_H_
#define _LED_Display_H_

extern code unsigned char Seg_Table[];
void LED_Display_Show();
void Temperature_dat_Receive();
void Lighting_dat_Receive();
void Temperature_DAC_Receive();
void Lighting_DAC_Receive();
void LED_Display_Arr();
#endif