#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "Distrance.h"
#include "KEY.h"

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
    0xC8,   //N
    0xFF    //全灭
};

unsigned char Distance_dat_arr[] = {12,12,12,12,12,12,12,12};
unsigned char Distance_max_arr[] = {10,12,12,12,12,12,12,12};
unsigned char Distance_min_arr[] = {11,12,12,12,12,12,12,12};
unsigned char LED_dat_arr[] = {12,12,12,12,12,12,12,12};

void Distance_Display(){
    Distance_dat_arr[5] = sound_value / 100;
    Distance_dat_arr[6] = sound_value % 100 / 10;
    Distance_dat_arr[7] = sound_value % 10;
}

void Distance_max_Display(){
    if(Distance_max == 0){
        Distance_max_arr[6] = 12;
        Distance_max_arr[7] = 0;
    }
    else{
        Distance_max_arr[6] = Distance_max / 10;
        Distance_max_arr[7] = Distance_max % 10;
    }
}

void Distance_min_Display(){
    if(Distance_min == 0){
        Distance_min_arr[6] = 12;
        Distance_min_arr[7] = 0;
    }
    else{
        Distance_min_arr[6] = Distance_min / 10;
        Distance_min_arr[7] = Distance_min % 10;
    }
}

void LED_Display_Choose(){
    unsigned char dat = S4_cnt % 3;
    unsigned char i;
    switch(dat){
        case 0:
            Distance_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Distance_dat_arr[i];
            }
            break;
        case 1:
            Distance_max_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Distance_max_arr[i];
            }
            break;
        case 2:
            Distance_min_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Distance_min_arr[i];
            }
            break;
    }
}

void LED_Display_Show(){
    unsigned char com;
    unsigned char dat;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[LED_dat_arr[com]];
        if(S4_cnt % 3 == 0 && com == 5){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}