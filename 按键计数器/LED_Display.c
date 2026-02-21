#include <stc15f2k60s2.h>
#include "Key.h"
#include "Delay.h"
#include "Common.h"

code unsigned char LED_Display_Value[11] = {
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
	0xFF //全灭
};

//数据转换函数
unsigned char num_dat[8];
void Num_Change(){
    unsigned char num = Number();
    unsigned char dat[8];
    unsigned char i = 0;
    unsigned char j = 0;
    // 初始化所有位为10（全灭）
    for(j = 0;j < 8;j++){
        dat[j] = 10;
    }
    // 拆分数字到dat[7-i]（从最低位开始填充）
    if(num == 0){
        dat[7] = 0; // 数字0显示在最后一位
    }else{
        while(num && i < 8){
            dat[7 - i] = num % 10; // 个位→dat[7]，十位→dat[6]...
            num /= 10;
            i++;
        }
    }
    // 赋值给num_dat
    for(j = 0;j < 8;j++){
        num_dat[j] = dat[j];
    }
}

//数码管显示函数
void LED_Display_Show(){
	unsigned char temp_dat;
	unsigned char com = 0;
	unsigned char i = 0;
	Num_Change();
	SEG(0xFF);
	COM(0x00);
	for(i = 0;i < 8;i++){
		COM(0x00);
		COM(1<<com);
		temp_dat = LED_Display_Value[num_dat[i]];
		SEG(temp_dat);
		Delay500us();
		com++;
	}
	com = 0;
	COM(0x00);
	SEG(0xFF);
}




