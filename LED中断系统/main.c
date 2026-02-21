#include "reg52.h"  //定义51单片机特殊功能寄存器

sbit LED1 = P0 ^ 0;
sbit LED2 = P0 ^ 1;
sbit LED3 = P0 ^ 2;
sbit LED4 = P0 ^ 3;
sbit LED5 = P0 ^ 4;

void Delayms(unsigned char time)		//@12.000MHz
{
	unsigned char i, j;

	while(time--){
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

void cls_buzz()
{
    P2 = ((P2 & 0x1f) | 0xA0);
    P0 = 0x00;
    P2 &= 0x1f;
}
void cls_led()
{
    P2 = ((P2 & 0x1f) | 0x80);
    P0 = 0xFF;
    P2 &= 0x1f;
}

void main(void)
{
    cls_buzz();
    cls_led();
    EX0 = 1;
    IT0 = 1;  //边沿触发方式(下降沿)
    EX1 = 1;
    IT1 = 1;  //边沿触发方式(下降沿)
    EA = 1;  //开启总中断
    while(1);
}

//外部中断0中断服务函数
void isr_intr_0(void) interrupt 0
{
	unsigned char time = 5;
    P2 = ((P2 & 0x1f) | 0x80);
	while(time --){
		LED1 = ~LED1;
		Delayms(1000);
		LED2 = ~LED2;
		Delayms(1000);
		LED3 = ~LED3;
		Delayms(1000);
		LED4 = ~LED4;
		Delayms(1000);
		LED5 = ~LED5;
		Delayms(1000);
		P2 = P2 & 0x1f;
	}
}

//外部中断1中断服务函数
void isr_intr_1(void) interrupt 2
{
	unsigned char time = 5;
    P2 = ((P2 & 0x1f) | 0x80);
    while(time --){
		LED1 = ~LED1;
		LED5 = ~LED5;
		Delayms(1000);
		LED2 = ~LED2;
		LED4 = ~LED4;
		Delayms(1000);
		LED5 = ~LED5;
		Delayms(1000);
		P2 = P2 & 0x1f;
	}
    P2 = P2 & 0x1f;
}
