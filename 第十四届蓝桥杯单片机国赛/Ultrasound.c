#include <STC15F2K60S2.H>
#include "Timer.h"
#include "Delay.h"

sbit TX = P1^0;
sbit RX = P1^1;

int Sound_value = 0;            //距离实际值
unsigned int Sound_speed = 340; //传播速度
unsigned int Sound_dat = 40;    //距离参数
int Sound_Calib = 0;            //距离校准值

unsigned char Read_Sound(){
    unsigned int sound = 0;
    unsigned char i;
    CMOD = 0x01;
    CCON = 0x00;
    CH = 0x00;
    CL = 0x00;
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
    sound = (CH << 8) | CL;
    return (unsigned char)((float)sound * (float)Sound_speed / 20000.0 + (float)Sound_Calib);
}

void Sound_login(){
    if(Sound_cnt >= 200){
        Sound_value = (int)Read_Sound();
        Sound_cnt = 0;
    }
}