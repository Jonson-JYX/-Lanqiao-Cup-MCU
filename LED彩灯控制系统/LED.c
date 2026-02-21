#include <stc15f2k60s2.h>
#include "LED.h"
#include "DELAY.h"
#include "COMMON.h"

//模式一：LED闪烁表
code unsigned char LED_NUM1[8]={
	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80
};

//模式二：LED闪烁表
code unsigned char LED_NUM2[8]={
	0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
};

//模式三：LED闪烁表
code unsigned char LED_NUM3[4]={
	0x81,0x42,0x24,0x18
};

//模式四：LED闪烁表
code unsigned char LED_NUM4[4]={
	0x18,0x24,0x42,0x81
};

//LED显示函数
void LED_Show(unsigned char number){
	//获取模式几
	unsigned char num = number;
	//数据缓冲区
	unsigned char dat;
	//循环变量
	unsigned char i;
	//初始化
	LED(0xFF);
	switch(num){
		case 1:
			for(i = 0 ;i < 8 ;i++){
				dat = LED_NUM1[i];
				LED(dat);
				Delay(80000);
				LED(0xFF);
				Delay(80000);
			}
			break;
		case 2:
			for(i = 0 ;i < 8 ;i++){
				dat = LED_NUM2[i];
				LED(dat);
				Delay(80000);
				LED(0xFF);
				Delay(80000);
			}
			break;
		case 3:
			for(i = 0 ;i < 4 ;i++){
				dat = LED_NUM3[i];
				LED(dat);
				Delay(90000);
				LED(0xFF);
				Delay(90000);
			}
			break;
		case 4:
			for(i = 0 ;i < 4 ;i++){
				dat = LED_NUM4[i];
				LED(dat);
				Delay(90000);
				LED(0xFF);
				Delay(90000);
			}
			break;
	}
}
