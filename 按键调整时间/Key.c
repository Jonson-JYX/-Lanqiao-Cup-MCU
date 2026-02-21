#include <stc15f2k60s2.h>
#include "Key.h"
#include "Delay.h"
#include "DS1302.h"

sbit S7  = P3 ^ 0;
sbit S6  = P3 ^ 1;
sbit S5  = P3 ^ 2;

//定义键值数组
code unsigned char Key_Value[3] = {1,2,3};

//按键扫描函数
unsigned char Key_Scan(){
	if(S7 == 0){
		Delay500ms();
		while(S7 == 0){
			return Key_Value[2];
		}
	}
	
	if(S6 == 0){
		Delay500ms();
		while(S6 == 0){
			return Key_Value[1];
		}
	}	
	
	if(S5 == 0){
		Delay500ms();
		while(S5 == 0){
			return Key_Value[0];
		}
	}
	return 0;
}

//按键工作函数
void Key_Change(unsigned char *dat){
	unsigned char hour;
	unsigned char minute;
	unsigned char key;	  //获取按键键值
	
	key = Key_Scan();
	if(key == 1){ // S5：时加1
		// 组合十位+个位为完整的“时”值
		hour = dat[0] * 10 + dat[1];
		hour++;
		if(hour >= 24){ // 时满24清零
			hour = 0;
		}
		// 拆分回十位和个位
		dat[0] = hour / 10;
		dat[1] = hour % 10;
		// 同步到DS1302
		SyncRTCToDS1302(dat);
	}
	if(key == 2){ // S6：分加1
		// 组合十位+个位为完整的“分”值
		minute = dat[3] * 10 + dat[4];
		minute++;
		if(minute >= 60){ // 分满60清零，时进位
			minute = 0;
			// 时进位处理
			hour = dat[0] * 10 + dat[1];
			hour++;
			if(hour >= 24){
				hour = 0;
			}
			dat[0] = hour / 10;
			dat[1] = hour % 10;
		}
		// 拆分分的十位和个位
		dat[3] = minute / 10;
		dat[4] = minute % 10;
		// 同步到DS1302
		SyncRTCToDS1302(dat);
	}
	if(key == 3){ // S7：秒清零
		dat[6] = 0;
		dat[7] = 0;
		// 同步到DS1302
		SyncRTCToDS1302(dat);
	}
}