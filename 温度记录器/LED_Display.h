#ifndef _LED_Display_H_
#define _LED_Display_H_
extern code unsigned char SEG_Table[];
extern unsigned char Temp_Now;
extern unsigned char Temp_Min;
extern unsigned char Temp_Max;
extern unsigned char Temp_Value_Arr[];
extern unsigned char Temp_Dat_Arr[];
void Temp_Change();
void LED_Display_Show();
#endif