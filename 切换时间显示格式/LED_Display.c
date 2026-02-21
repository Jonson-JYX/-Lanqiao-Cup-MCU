#include <stc15f2k60s2.h>
#include "LED_Display.h"
#include "Common.h"
#include "DS1302.h"
#include "Delay.h"
#include "KEY.h"

// 创建数码管段码表数组
code unsigned char LED_Display_NUM [12]= {
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
	0xBF,//-
	0xFF //全灭
};

unsigned char dat1[8];
unsigned char dat2[8];
unsigned char dat3[8];

//时间转化函数
void Time_Change(){
	unsigned char *p_rtc = ReadRTC(); //接收参数
	//模式一
	dat1[0] = p_rtc[0];
	dat1[1] = p_rtc[1];
	dat1[2] = p_rtc[2];
	dat1[3] = p_rtc[3];
	dat1[4] = p_rtc[4];
	dat1[5] = p_rtc[5];
	dat1[6] = p_rtc[6];
	dat1[7] = p_rtc[7];
	
	//模式二
	dat2[0] = 11;
	dat2[1] = 11;
	dat2[2] = 11;
	dat2[3] = p_rtc[0];
	dat2[4] = p_rtc[1];
	dat2[5] = p_rtc[2];
	dat2[6] = p_rtc[3];
	dat2[7] = p_rtc[4];
	
	//模式三
	dat3[0] = 11;
	dat3[1] = 11;
	dat3[2] = 11;
	dat3[3] = 11;
	dat3[4] = 11;
	dat3[5] = 11;
	dat3[6] = p_rtc[6];
	dat3[7] = p_rtc[7];
}


//数码管显示函数
void LED_Dispaly_Show(){
	unsigned char com = 0;//位选移动变量
	unsigned char i = 0;  //数码管循环显示变量
	unsigned char temp_dat;	  //临时存储区
	unsigned char dat[8];
	unsigned char j = 0;
	unsigned char num = Key_Scan();
	
	Time_Change();
	switch(num){
		case 1: // 时分秒
			for(j=0; j<8; j++) {
				dat[j] = dat1[j];
			}
			break;
		case 2: // 时分
			for(j=0; j<8; j++) {
				dat[j] = dat2[j];
			}
			break;
		case 3: // 秒
			for(j=0; j<8; j++) {
				dat[j] = dat3[j];
			}
			break;
		default: // 默认时分秒
			for(j=0; j<8; j++) {
				dat[j] = dat1[j];
			}
			break;
	}
	
	SEG(0xFF);
	//循环显示8位数码管
	for(i = 0;i < 8;i++){
		SEG(0xFF);
		COM(1<<com);	//位选移动一位
		temp_dat = LED_Display_NUM[dat[i]];
		SEG(temp_dat);//将缓冲区数据放入SEG显示函数
		Delay500us();
		com++;	//	位选加一	
	}
	com = 0;	//	循环结束后位选归零
	COM(0x00);  //  关闭位选
	SEG(0xFF);
}