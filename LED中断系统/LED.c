#include <stc15f2k60s2.h>
#include "common.h"
#include "delay.h"

//模式一数组
code unsigned char LED1[5] = {
	0x01,0x02,0x04,0x08,0x10
};

//模式二数组
code unsigned char LED2[3] = {
	0x11,0x0A,0x04
};

//模式一实现代码
void LED1_Show(){
	unsigned char i;
	unsigned dat;
	LED(0xFF);
	for(i = 0 ;i < 5;i++){
		dat = LED1[i];
		LED(dat);
		Delayms(8000);
		LED(0xFF);
		Delayms(8000);
	}
	LED(0xFF);
}

//模式二实现代码
void LED2_Show(){
	unsigned char i;
	unsigned dat;
	LED(0xFF);
	for(i = 0 ;i < 3;i++){
		dat = LED2[i];
		LED(dat);
		Delayms(8000);
		LED(0xFF);
		Delayms(8000);
	}
	LED(0xFF);
}