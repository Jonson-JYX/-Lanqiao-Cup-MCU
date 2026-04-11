#ifndef KEY_H
#define KEY_H
extern unsigned char Key_value;   //按键值
extern unsigned char S4_cnt;     //S4按键计数器 
extern unsigned char S5_cnt1;     //S5按键计数器
extern unsigned char S5_cnt2;     //S5按键计数器
extern unsigned char S5_cnt3;     //S5按键计数器
void Key_Scan();
void Key_login();
#endif // !KEY_H