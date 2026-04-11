#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Timer.h"
#include "math.h"

sbit TX = P1^0;
sbit RX = P1^1;

unsigned char sound_value = 0;    //声音强度值
unsigned char sound_dat = 30;     //声音参数
unsigned char sound_status = 0;   //声音状态值
unsigned char sound_storage1 = 0; //声音存储值1
unsigned char sound_storage2 = 0; //声音存储值2
bit sound_flag = 0;               //声音标志位

unsigned char Read_Sound(){
    unsigned char i;
    unsigned int sound = 0;
    CMOD = 0x01;
    CCON = 0x00;
    CL = 0x00;
    CH = 0x00;
    for(i = 0; i < 8;i++){
        TX = 1;
        Delay12us();
        TX = 0;
        Delay12us();
    }
    CR = 1;
    while((RX == 1)&&(CH <= 0x40));
    CR = 0;
    if(CH > 0x40){
        CF = 0;
        return 0;
    }
    sound = (CH << 8) | CL;
    return sound * 0.0172f; 
}

void Sound_login(){
    if(sound_cnt >= 1000){
        sound_cnt = 0;
        sound_value = Read_Sound();
        if(sound_value > sound_dat){
            sound_flag = 1;
        }
        else{
            sound_flag = 0;
        }
        sound_storage1 = sound_storage2;
        sound_storage2 = sound_value;
        if(abs(sound_storage1 - sound_storage2) < 5){
            sound_status = 1;   //静止
            sound_status1_flag = 1;
        }
        else if(abs(sound_storage1 - sound_storage2) >= 5 && abs(sound_storage1 - sound_storage2) < 10){
            sound_status = 2;   //徘徊
            sound_status2_flag = 1;

        }
        else if(abs(sound_storage1 - sound_storage2) >= 10){
            sound_status = 3;   //移动
            sound_status3_flag = 1;
        }
    }
}