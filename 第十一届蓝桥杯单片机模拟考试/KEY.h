#ifndef KEY_H
#define KEY_H
extern unsigned char key_password[]; // 密码临时数组
extern unsigned char read_password[];
extern unsigned char key_value;
extern int num;
extern bit S12_flag;   //密码修改标志位
extern bit S16_flag;   //密码输入标志位
extern bit password;   //密码正确标志位
extern bit first_flag; //第一次输入密码
extern bit key_down;   //按键按下检测按键
extern unsigned char key_num;  //输入密码不同个数累加变量
void Key_login();
#endif // !KEY_H