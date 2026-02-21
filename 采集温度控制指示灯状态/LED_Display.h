#ifndef _LED_Display_H_
#define _LED_Display_H_
extern code unsigned char SEG_Value[];
extern unsigned char Temp_Show_Arr[];
extern unsigned char Temp_Dat_Arr[];
extern unsigned char Temp_Set_Value;
void Temp_Set(void);
void Temp_Change(void);
void LED_Display_Show(void);
#endif