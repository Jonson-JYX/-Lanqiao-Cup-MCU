#include <stc15f2k60s2.h>
#include "LED_Display.h"
#include "Common.h"
#include "DS1302.h"
#include "Delay.h"
#include "Key.h"

// 创建数码管段码表数组
code unsigned char LED_Display_NUM [11]= {
	0xC0,//0
	0xF9,//1
	0xA4,//2
	0xB0,//3
	0x99,//4
	0x92,//5
	0x82,//6
	0xF8,//7
	0x80,//8
	0x90,//9
	0xBF //-
};

//数码管显示函数
void LED_Dispaly_Show(){
	unsigned char com = 0;//位选移动变量
	unsigned char i = 0;  //数码管循环显示变量
	unsigned char j = 0;  //存储时间循环变量
	unsigned char *p_rtc = ReadRTC(); //接收参数
	unsigned char dat[8]; //定义缓冲区
	unsigned char dat1;	  //临时存储区
	
	for(j = 0;j < 8;j++){
		dat[j] = p_rtc[j];
	}
	
	//按键工作函数
	Key_Change(dat);
	
	SEG(0xFF);
	//循环显示8位数码管
	for(i = 0;i < 8;i++){
		SEG(0xFF);
		COM(1<<com);	//位选移动一位
		dat1 = LED_Display_NUM[dat[i]];
		SEG(dat1);//将缓冲区数据放入SEG显示函数
		Delay500us();
		com++;	//	位选加一	
	}
	com = 0;	//	循环结束后位选归零
	COM(0x00);  //  关闭位选
	SEG(0xFF);
}