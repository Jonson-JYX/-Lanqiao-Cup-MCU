#ifndef _KEY_H_
#define _KEY_H_
extern bit KEY_Password;
extern unsigned char S4_Cnt;
extern unsigned char S4;
extern unsigned char S5;
extern code unsigned char KEY_Value[12];
unsigned char KEY_Scan();
unsigned char KEY_S4();
unsigned char KEY_S5();
unsigned char KEY_ALL();
#endif