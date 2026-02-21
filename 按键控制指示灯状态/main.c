#include <stc15f2k60s2.h>
#include <intrins.h>

// L长按标志
unsigned char L_flag = 0x00;
// 长按倒计时
bit Time_down_flag=0,Press_flag=0;
unsigned char Count_200=200;
// 100ms循环
unsigned char Count_20;
// 按键检测
bit key_flag;

void Timer0_Init(void)		//5毫秒@12.000MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x78;				//设置定时初始值
	TH0 = 0xEC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
}

void Turn_L(unsigned char pos){
	switch(pos){
		case 0: P00 = ~P00;
			break;
		case 1: P01 = ~P01;
			break;
		case 2: P02 = ~P02;
			break;
		case 3: P03 = ~P03;
			break;
		case 4: P04 = ~P04;
			break;
		case 5: P05 = ~P05;
			break;
		case 6: P06 = ~P06;
			break;
		case 7: P07 = ~P07;
			break;
		default:
			break;
	}
}

void L_flag_Pro(unsigned char pos)
{
	L_flag &= ~(0x01 << pos); 
	if(Press_flag) {
		Press_flag = 0;
		L_flag |= 0x01 << pos;
	}
	else {
		Turn_L(pos);
	}
		
}
void Key_scanf()
{
	unsigned char pos=8;
	P30=P31=P32=P33=0;
	P44=P42=1;
	if(!(P44&&P42))
	{
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		if(!(P44&&P42))
		{
			// 检测长按
			Time_down_flag = 1;
			P30=P31=P32=P33=1;
			P44=P42=0;
			if(!P33){pos=0;}
			else if(!P32) {pos=1;}
			else if(!P31) {pos=2;}
			else if(!P30) {pos=3;}
			else ;;
			P30=P31=P32=P33=0;
			P44=P42=1;
			if(!P42) {pos+=4;}
			while(!(P44&&P42));
			// 关闭检测
			Time_down_flag = 0; Count_200 = 200;
			L_flag_Pro(pos);
		}
	}
}

void Turn_L_Port(){
	unsigned char i = 0;
	for(;i<8;i++)
	{
		if((L_flag >> i)&0x01) Turn_L(i);
	}
}

void Timer0_Isr(void) interrupt 1
{
	key_flag = 1;
	
	if(Time_down_flag){
		if(--Count_200 == 0){
			Time_down_flag = 0;
			Press_flag = 1;
			Count_200 = 200;
		}
	}
	
	if(++Count_20==20) {Count_20 = 0; Turn_L_Port();}
}

void main()
{
	Timer0_Init();
	EA = 1;
	P0 = 0xff;
	P2 = P2&0x1f|0x80;
	while(1)
	{
		Key_scanf();
	}
}