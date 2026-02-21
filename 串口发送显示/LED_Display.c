#include <stc15f2k60s2.h>
#include "Common.h"
#include "Delay.h"
#include "Uart.h"

code unsigned char SEG_Table[] = {
	0x88,	//A
	0x86,	//E
	0xFF	//全灭
};

//串口数据接收数组
unsigned char Uart_dat_arr[] = {2,2,2,2,2,2,2,2};
//串口数据显示数组
unsigned char Uart_show_arr[] = {2,2,2,2,2,2,2,2};

//数据转化函数
void Uart_dat_change(){
	unsigned char dat = *Arr_Value();
	unsigned char i;
	if(dat == 'A'){
		Uart_dat_arr[7] = 0;
	}
	else{
		Uart_dat_arr[7] = 1;
	}
	for(i = 0;i <8;i++){
		Uart_show_arr[i] = Uart_dat_arr[i];
	}
}
//数码管显示数组
void LED_Display_Show(){
	unsigned char i;
	unsigned char dat;
	unsigned char com = 0;
	for(i = 0;i < 8;i++){
		SEG(0xFF);
		COM(0xFF);
		COM(1<<com);
		dat = SEG_Table[Uart_show_arr[i]];
		SEG(dat);
		com++;
		Delay50us();
		Delay50us();
	}
	com = 0;
	SEG(0xFF);
	COM(0xFF);
}