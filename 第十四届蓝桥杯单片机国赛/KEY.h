#ifndef KEY_H
#define KEY_H
extern unsigned char Unit_cnt;       //单位转化标志位
extern unsigned char Parameters_cnt; //参数界面转化标志位
extern unsigned char Setting_cnt;    //工厂界面转化标志位
extern unsigned char S4_cnt;
unsigned char Key_Scan();
void Key_login();
#endif // !KEY_H