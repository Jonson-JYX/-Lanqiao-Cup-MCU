#ifndef NE555_H
#define NE555_H
extern unsigned int NE555_value;   //NE555测量的值
extern unsigned int NE555_dat;	//NE555参数
extern unsigned int NE555_waining_value[5]; //NE555异常报警值
extern unsigned char NE555_waining_flag; //NE555报警标志
extern unsigned int NE555_change_value[2]; //NE555变化异常值
extern unsigned int NE555_change_dat; //NE555变化异常差值
void Timer0_Init(void);		//1毫秒@12.000MHz
void NE555_login();
#endif // !NE555_H