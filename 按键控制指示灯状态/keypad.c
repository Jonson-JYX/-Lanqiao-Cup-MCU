#include <stc15f2k60s2.h>
#include "keypad.h"
#include "delay.h"
#include "common.h"

//按键事件类型定义
//无按键按下
#define Key_None 0;
//按键短按
#define Key_Short_Pressed 1;
//按键长按
#define Key_Long_Pressed 2;

//按键短按键值表
code unsigned char Key_Num[9] = {
	0,1,2,3,4,5,6,7,8
};

//检测按键是否按下函数
bit isKeyPressed (unsigned char row,unsigned char col){
	unsigned int PressTime = 0; //按键初始化按下时间为0
	
	//设置行
	P3 = (P3 & 0xF0) | 0x0F;	//将行线全部置高
	switch(row){
		case 1:P30 = 0;break;
		case 2:P31 = 0;break;
		case 3:P32 = 0;break;
		case 4:P33 = 0;break;
	}
	//消抖
	Delay100us();
	//设置列
	if((col == 0 && P44 == 0) || (col == 1 && P42 == 0)){
		
		//持续检测按键的状态
		while((col == 0 && P44 == 0) || (col == 1 && P42 == 0)){
			Delay10ms();	//10毫秒为一个计时单位
			PressTime++;
			
			//超过1秒则判定为长按
			if(PressTime > 100){
				//等待按键释放
				while((col == 0 && P44 == 0) || (col == 1 && P42 == 0));
				return Key_Long_Pressed;
			}
			
		}
		//否则判定为短按
		return Key_Short_Pressed;
	}
	//若都没有返回则返回无按键按下
	return Key_None;
}

//按键扫描函数
unsigned char Key_Scan(){
	unsigned char Key = 0xFF; 	//默认无按键按下
	unsigned char row = 0;		//记录按键按下的行
	unsigned char col = 0;		//记录按键按下的列
	//检测是否有按键按下
	for(row = 0;row < 4;row++){
		for(col = 0;col < 2;col++){
			if(isKeyPressed(row,col)){	//获取对应键值
				if(row == 0 && col == 0){
					Key = Key_Num[3];
				}
				if(row == 1 && col == 0){
					Key = Key_Num[2];
				}
				if(row == 2 && col == 0){
					Key = Key_Num[1];
				}
				if(row == 3 && col == 0){
					Key = Key_Num[0];
				}
				if(row == 0 && col == 1){
					Key = Key_Num[8];
				}
				if(row == 1 && col == 1){
					Key = Key_Num[7];
				}
				if(row == 2 && col == 1){
					Key = Key_Num[6];
				}
				if(row == 3 && col == 1){
					Key = Key_Num[5];
				}
				if(row == 4 && col == 1){
					Key = Key_Num[4];
				}
			}
		}
	}
	return Key_Num[9];
}
