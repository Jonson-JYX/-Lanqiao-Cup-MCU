#include <stc15f2k60s2.h>
#include "KEY.h"

unsigned int key1_cnt = 0;
bit key1_flag = 0;
unsigned int key2_cnt = 0;
bit key2_flag = 0;
unsigned int key3_cnt = 0;
bit key3_flag = 0;
unsigned int key4_cnt = 0;
bit key4_flag = 0;
unsigned int key5_cnt = 0;
bit key5_flag = 0;
unsigned int key6_cnt = 0;
bit key6_flag = 0;
unsigned int key7_cnt = 0;
bit key7_flag = 0;
unsigned int key8_cnt = 0;
bit key8_flag = 0;
unsigned int key9_cnt = 0;
bit key9_flag = 0;
unsigned int key10_cnt = 0;
bit key10_flag = 0;
unsigned int key11_cnt = 0;
bit key11_flag = 0;
unsigned int key12_cnt = 0;
bit key12_flag = 0;
unsigned int key13_cnt = 0;
bit key13_flag = 0;
unsigned int key14_cnt = 0;
bit key14_flag = 0;
unsigned int key15_cnt = 0;
bit key15_flag = 0;
unsigned int key16_cnt = 0;
bit key16_flag = 0;

unsigned int timer_cnt = 0;  // 10ms计数器

void Timer0_Isr(void) interrupt 1
{
	// 原有的按键计数代码
	if(key1_flag){
		key1_cnt++;
	}
	if(key2_flag){
		key2_cnt++;
	}
	if(key3_flag){
		key3_cnt++;
	}
	if(key4_flag){
		key4_cnt++;
	}
	if(key5_flag){
		key5_cnt++;
	}
	if(key6_flag){
		key6_cnt++;
	}
	if(key7_flag){
		key7_cnt++;
	}
	if(key8_flag){
		key8_cnt++;
	}
	if(key9_flag){
		key9_cnt++;
	}
	if(key10_flag){
		key10_cnt++;
	}
	if(key11_flag){
		key11_cnt++;
	}
	if(key12_flag){
		key12_cnt++;
	}
	if(key13_flag){
		key13_cnt++;
	}
	if(key14_flag){
		key14_cnt++;
	}
	if(key15_flag){
		key15_cnt++;
	}
	if(key16_flag){
		key16_cnt++;
	}
	
	// 每10ms调用一次按键扫描
	timer_cnt++;
	if(timer_cnt >= 10)
	{
		timer_cnt = 0;
		KEY_Scan();
	}
}

void Timer0_Init(void)		//1毫秒@12.000MHz
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x20;				//设置定时初始值
	TH0 = 0xD1;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
	EA = 1;
}