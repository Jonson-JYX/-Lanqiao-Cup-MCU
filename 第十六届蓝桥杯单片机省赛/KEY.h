#ifndef KEY_H
#define KEY_H
extern unsigned char key_value;    //按键值
extern unsigned char S4_cnt;      //S4计数值
extern unsigned char S5_cnt;      //S5计数值
extern bit key_flag;                 //按键标志位
void Key_Scan();
void Key_login();
#endif // !KEY_H