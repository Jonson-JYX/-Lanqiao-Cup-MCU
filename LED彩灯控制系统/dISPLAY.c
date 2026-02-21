#include <stc15f2k60s2.h>
#include "DISPLAY.h"
#include "COMMON.h"

//数码管段码表
code unsigned char SEG_Value[2][8]={
	0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0x88,
	0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0x03
};

//数码管显示函数
void SEG_Display(unsigned char number){
	//初始化位选
	unsigned char com = 0;
	//数码管循环显示变量
	unsigned char i;
	//获取显示数据组函数
	unsigned char num = number;
	//定义存储缓冲区
	unsigned char dat;
	//消影
	SEG(0xFF);
	
	for(i = 0 ;i < 8 ;i++){
		//消影
		SEG(0xFF);
		//位选移动一位
		COM(1<<com);
		com++;
		//将数据放入缓冲区
		dat = SEG_Value[num][i];
		SEG(dat);
	}
	com = 0;
	COM(0x00);
	SEG(0xFF);
}