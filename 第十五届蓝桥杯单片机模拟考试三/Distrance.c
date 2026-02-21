#include <STC15F2K60S2.H>
#include "Timer.h"
#include "Delay.h"
#include "KEY.h"

sbit TX = P1^0;
sbit RX = P1^1;

unsigned int sound_value = 0;
bit sound_flag = 1;

unsigned char Read_Distrance(){
    unsigned int dat = 0;
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
    dat = (CH << 8) | CL;
    return (unsigned int)(dat * 0.0172);
}

void Sound_login(){
    unsigned int dat = Read_Distrance();
    if(sound_cnt == 0){
        sound_value = dat;
    }
    if((sound_value > Parameter_max || sound_value < Parameter_min) && sound_flag == 1){
        num++;
        sound_flag = 0;
    }
    else if(sound_value <= Parameter_max && sound_value >= Parameter_min){
        sound_flag = 1;
    }
}