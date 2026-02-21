#include <STC15F2K60S2.H>
#include "Delay.h"
#include "NE555.h"
#include "Common.h"

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
    0x8C,   //P
    0xFF    //全灭
};

unsigned char NE555_dat_arr[] = {10,11,11,11,11,11,11,11};

void NE555_Display(){
    if(NE555_dat >= 100000){
        NE555_dat_arr[2] = NE555_dat / 100000;
        NE555_dat_arr[3] = NE555_dat % 100000 / 10000;
        NE555_dat_arr[4] = NE555_dat % 10000 / 1000;
        NE555_dat_arr[5] = NE555_dat % 1000 / 100;
        NE555_dat_arr[6] = NE555_dat % 100 / 10;
        NE555_dat_arr[7] = NE555_dat % 10;
    }
    if(NE555_dat >= 10000 && NE555_dat < 100000){
        NE555_dat_arr[2] = 11;
        NE555_dat_arr[3] = NE555_dat / 10000;
        NE555_dat_arr[4] = NE555_dat % 10000 / 1000;
        NE555_dat_arr[5] = NE555_dat % 1000 / 100;
        NE555_dat_arr[6] = NE555_dat % 100 / 10;
        NE555_dat_arr[7] = NE555_dat % 10;
    }
    if(NE555_dat >= 1000 && NE555_dat <10000){
        NE555_dat_arr[2] = 11;
        NE555_dat_arr[3] = 11;
        NE555_dat_arr[4] = NE555_dat / 1000;
        NE555_dat_arr[5] = NE555_dat % 1000 / 100;
        NE555_dat_arr[6] = NE555_dat % 100 / 10;
        NE555_dat_arr[7] = NE555_dat % 10;
    }
    if(NE555_dat >= 100 && NE555_dat <1000){
        NE555_dat_arr[2] = 11;
        NE555_dat_arr[3] = 11;
        NE555_dat_arr[4] = 11;
        NE555_dat_arr[5] = NE555_dat / 100;
        NE555_dat_arr[6] = NE555_dat % 100 / 10;
        NE555_dat_arr[7] = NE555_dat % 10;
    }
    if(NE555_dat >= 10 && NE555_dat <100){
        NE555_dat_arr[2] = 11;
        NE555_dat_arr[3] = 11;
        NE555_dat_arr[4] = 11;
        NE555_dat_arr[5] = 11;
        NE555_dat_arr[6] = NE555_dat / 10;
        NE555_dat_arr[7] = NE555_dat % 10;
    }
    if(NE555_dat >= 0 && NE555_dat <10){
        NE555_dat_arr[2] = 11;
        NE555_dat_arr[3] = 11;
        NE555_dat_arr[4] = 11;
        NE555_dat_arr[5] = 11;
        NE555_dat_arr[6] = 11;
        NE555_dat_arr[7] = NE555_dat;
    }
}

void LED_Display_Show(){
    unsigned char com;
    unsigned char dat;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[NE555_dat_arr[com]];
        SEG(dat);
        Delay50us();
    }
    COM(0xFF);
    SEG(0xFF);
}