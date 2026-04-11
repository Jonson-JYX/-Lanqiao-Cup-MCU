#ifndef PCF8591_H
#define PCF8591_H
extern unsigned int RB2_value;   //RB2测量的值
extern unsigned int RB2_VC;     //RB2测量的校准值
extern unsigned int RB2_dat;    //RB2参数
unsigned int Read_RB2();
void RB2_login();
#endif // !PCF8591_H