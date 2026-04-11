#ifndef KEY_H
#define KEY_H
extern bit Sound_flag;
extern bit NE555_flag;
extern unsigned char S4_cnt;
extern unsigned char S5_cnt;
unsigned char Key_Scan();
void Key_login();
#endif // !KEY_H