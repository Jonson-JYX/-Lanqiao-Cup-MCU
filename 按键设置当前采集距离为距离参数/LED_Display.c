#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"
#include "Delay.h"
#include "Distrance.h"

code unsigned char SEG_Table[] = {
    0xC0,   //0
    0xF9,   //1
    0xA4,   //2
    0xB0,   //3
    0x99,   //4
    0x92,   //5
    0x82,   //6
    0xF8,   //7
    0x80,   //8
    0x90,   //9
    0xC1,   //U
    0xFF    //全灭
};

unsigned char Sound_dat_arr[] = {10,11,11,11,11,11,11,11};

void Sound_Display(){
    Sound_dat_arr[5] = sound_value / 100;
    Sound_dat_arr[6] = sound_value % 100 / 10;
    Sound_dat_arr[7] = sound_value % 10;
}

void LED_Display_Show(){
    unsigned char com;
    unsigned char dat;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[Sound_dat_arr[com]];
        if(com == 5){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}