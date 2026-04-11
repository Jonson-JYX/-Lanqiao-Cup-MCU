#include <STC15F2K60S2.H>
#include "Timer.h"
#include "math.h"

unsigned int NE555_value = 0;   //NE555测量的值
unsigned int NE555_dat = 2000;	//NE555参数
unsigned int NE555_waining_value[5] = {0}; //NE555异常报警值
unsigned char NE555_waining_flag = 0; //NE555报警标志
unsigned int NE555_change_value[2] = {0}; //NE555变化异常值
unsigned int NE555_change_dat = 0; //NE555变化异常差值

void Timer0_Init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x05;			//设置定时器模式
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0x00;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}

void NE555_login(){
	unsigned char i;
	int dat;
	unsigned char num1 = 0;
	unsigned char num2 = 0;
    if(NE555_cnt >= 1000){
        NE555_value = (TH0 << 8) | TL0;   //读取计数器的值
		// 频率趋势异常判断
		for(i = 0;i < 4;i++){
			NE555_waining_value[i] = NE555_waining_value[i+1]; //更新报警值
		}
		NE555_waining_value[4] = NE555_value; //保存当前测量值
		for(i = 0;i < 4;i++){
			dat = NE555_waining_value[i] - NE555_waining_value[i+1];
			if(dat >= 0){
				num1++;
			}
			if(dat <= 0){
				num2++;
			}
		}
		if(num1 == 4){
			NE555_waining_flag = 1; //设置报警标志下降异常
		}
		if(num2 == 4){
			NE555_waining_flag = 2; //设置报警标志上升异常
		}
		if(num1 != 4 && num2 != 4){
			NE555_waining_flag = 0; //设置报警标志正常
		}

		// 频率变化异常判断
		NE555_change_value[0] = NE555_change_value[1]; //更新
		NE555_change_value[1] = NE555_value; //保存当前测量值
		NE555_change_dat = abs(NE555_change_value[1] - NE555_change_value[0]); //计算变化差值
		
		TH0 = 0x00;
		TL0 = 0x00;
        NE555_cnt = 0;   //重置计数器
    }
}