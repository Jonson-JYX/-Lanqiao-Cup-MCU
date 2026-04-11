#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Timer.h"

sbit TX = P1^0;   //声音传感器连接到P1.0口
sbit RX = P1^1;   //声音传感器连接到P1.1口

unsigned int Sound_value = 0;   //测量的高度
unsigned int Sound_speed = 0;   //测量的校准声音速度

unsigned int Read_Sound(){
    unsigned char i;
    unsigned int value = 0;
    CMOD = 0X01;
    CCON = 0X00;
    CL = 0x00;
    CH = 0x00;
    for(i = 0;i < 8;i++){
        TX = 1;
        Delay12us();
        TX = 0;
        Delay12us();
    }
    CR = 1;
    while((RX == 1) && (CH <= 0x40));
    CR = 0;
    if(CH > 0x40){
        CF = 0;
        return 0;
    }
    value = (CH << 8) | CL;

    return (float)value * (float)Sound_speed / 20000.0f;
}

void Sound_login(){
    if(Sound_cnt >= 200){
        Sound_value = Read_Sound();
        Sound_cnt = 0;
    }
}