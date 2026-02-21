#include <stc15f2k60s2.h>
#include "keypad.h"
#include "common.h"
#include "delay.h"

//定义按键的编号
code unsigned char Key_Num[17] = {
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
};

//按键扫描函数
unsigned char Key_Scan(){
	//扫描第一行
	P30 = 0;P31 = 1;P32 = 1;P33 = 1;
	if(P44 == 0){
		//延时消抖
		Delay100us();
		//等待按键释放
		while(P44 == 0){
			return Key_Num[4];
		}
	}
	if(P42 == 0){
		Delay100us();
		while(P42 == 0){
			return Key_Num[8];
		}
	}
	if(P35 == 0){
		Delay100us();
		while(P35 == 0){
			return Key_Num[12];
		}
	}
	if(P34 == 0){
		Delay100us();
		while(P34 == 0){
			return Key_Num[16];
		}
	}
	//扫描第二行
	P30 = 1;P31 = 0;P32 = 1;P33 = 1;
	if(P44 == 0){
		Delay100us();
		while(P44 == 0){
			return Key_Num[3];
		}
	}
	if(P42 == 0){
		Delay100us();
		while(P42 == 0){
			return Key_Num[7];
		}
	}
	if(P35 == 0){
		Delay100us();
		while(P35 == 0){
			return Key_Num[11];
		}
	}
	if(P34 == 0){
		Delay100us();
		while(P34 == 0){
			return Key_Num[15];
		}
	}
	//扫描第三行
	P30 = 1;P31 = 1;P32 = 0;P33 = 1;
	if(P44 == 0){
		Delay100us();
		while(P44 == 0){
			return Key_Num[2];
		}
	}
	if(P42 == 0){
		Delay100us();
		while(P42 == 0){
			return Key_Num[6];
		}
	}
	if(P35 == 0){
		Delay100us();
		while(P35 == 0){
			return Key_Num[10];
		}
	}
	if(P34 == 0){
		Delay100us();
		while(P34 == 0){
			return Key_Num[14];
		}
	}
	//扫描第四行
	P30 = 1;P31 = 1;P32 = 1;P33 = 0;
	if(P44 == 0){
		Delay100us();
		while(P44 == 0){
			return Key_Num[1];
		}
	}
	if(P42 == 0){
		Delay100us();
		while(P42 == 0){
			return Key_Num[5];
		}
	}
	if(P35 == 0){
		Delay100us();
		while(P35 == 0){
			return Key_Num[9];
		}
	}
	if(P34 == 0){
		Delay100us();
		while(P34 == 0){
			return Key_Num[13];
		}
	}
	return Key_Num[0];
}