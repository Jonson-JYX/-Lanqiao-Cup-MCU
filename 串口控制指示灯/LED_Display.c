#include <stc15f2k60s2.h>
#include "Common.h"
#include "Delay.h"
#include "Uart.h"

//数码管数组
code unsigned char SEG_Table[] = {
	0xC0,	//0
	0xF9,	//1
	0xFF	//全灭
};

//LED接收数组
unsigned char LED_dat_arr[] = {2,2,2,2,2,2,2,2};

//LED转化函数
void LED_Change(){
	unsigned char *value = Arr_Value();
	unsigned char i;
	for(i = 0;i < 8;i++){
		if(value[i] == '1'){
			LED_dat_arr[i] = 1;
		}
		else{
			LED_dat_arr[i] = 0;
		}
	}
}	
	
//数码管显示数组
void LED_Display_Show(){
	unsigned char dat;
	unsigned char i;
	unsigned char com;
	for(i = 0;i < 8;i++){
		SEG(0xFF);
		COM(0xFF);
		COM(1<<com);
		dat = SEG_Table[LED_dat_arr[i]];
		SEG(dat);
		com++;
		Delay100us();
	}
	com = 0;
	SEG(0xFF);
	COM(0xFF);
}