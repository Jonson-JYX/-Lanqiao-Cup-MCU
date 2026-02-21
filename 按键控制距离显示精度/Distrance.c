#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Timer.h"

sbit TX = P1^0;
sbit RX = P1^1;
unsigned int sound_value = 0;

unsigned char Read_Distrance(){
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
    sound = (CH<<8) | CL;
    return sound * 0.0172 + 2;
}

void Sound_login(){
    if(sound_cnt == 199){
        sound_value = Read_Distrance();
    }
}