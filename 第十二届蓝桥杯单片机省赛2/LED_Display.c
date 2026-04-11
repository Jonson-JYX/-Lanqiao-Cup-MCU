#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "NE555.h"
#include "PCF8591.h"
#include "KEY.h"

code unsigned char SEG_Table[] = {
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
    0x8E,//F 10
    0xC8,//n 11
    0xC1,//U 12
    0xBF,//- 13
    0xFF //  14
};

unsigned char NE555_dat_arr[] = {10,14,14,14,14,14,14,14};
unsigned char Timer_dat_arr[] = {11,14,14,14,14,14,14,14};
unsigned char Light_dat_arr[] = {12,13,1,14,14,14,14,14};
unsigned char RB2_dat_arr[] = {12,13,3,14,14,14,14,14}; 
unsigned char LED_dat_arr[] = {14,14,14,14,14,14,14,14};

void NE555_Display(){
    if(NE555_value >= 10000){
        NE555_dat_arr[3] = NE555_value / 10000;
        NE555_dat_arr[4] = NE555_value % 10000 / 1000;
        NE555_dat_arr[5] = NE555_value % 1000 / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 1000){
        NE555_dat_arr[4] = NE555_value / 1000;
        NE555_dat_arr[5] = NE555_value % 1000 / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 100){
        NE555_dat_arr[5] = NE555_value / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 10){
        NE555_dat_arr[6] = NE555_value / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else{
        NE555_dat_arr[7] = NE555_value;
    }
}

void Timer_Display(){
    if(NE555_f >= 10000){
        Timer_dat_arr[3] = NE555_f / 10000;
        Timer_dat_arr[4] = NE555_f % 10000 / 1000;
        Timer_dat_arr[5] = NE555_f % 1000 / 100;
        Timer_dat_arr[6] = NE555_f % 100 / 10;
        Timer_dat_arr[7] = NE555_f % 10;
    }
    else if(NE555_f >= 1000){
        Timer_dat_arr[4] = NE555_f / 1000;
        Timer_dat_arr[5] = NE555_f % 1000 / 100;
        Timer_dat_arr[6] = NE555_f % 100 / 10;
        Timer_dat_arr[7] = NE555_f % 10;
    }
    else if(NE555_f >= 100){
        Timer_dat_arr[5] = NE555_f / 100;
        Timer_dat_arr[6] = NE555_f % 100 / 10;
        Timer_dat_arr[7] = NE555_f % 10;
    }
    else if(NE555_f >= 10){
        Timer_dat_arr[6] = NE555_f / 10;
        Timer_dat_arr[7] = NE555_f % 10;
    }
    else{
        Timer_dat_arr[7] = NE555_f;
    }
}

void Light_Display(){
    Light_dat_arr[5] = Light_value / 100;
    Light_dat_arr[6] = Light_value % 100 / 10;
    Light_dat_arr[7] = Light_value % 10;
}

void RB2_Display(){
    RB2_dat_arr[5] = RB2_value / 100;
    RB2_dat_arr[6] = RB2_value % 100 / 10;
    RB2_dat_arr[7] = RB2_value % 10;
}

void LED_Display_Choose(){
    unsigned char i;
    switch(S4_cnt){
        case 0:
            NE555_Display();
            for(i = 0; i < 8; i++){
                LED_dat_arr[i] = NE555_dat_arr[i];
            }
            break;
        case 1:
            Timer_Display();
            for(i = 0; i < 8; i++){
                LED_dat_arr[i] = Timer_dat_arr[i];
            }
            break;
        case 2:
            switch(S5_cnt){
                case 0:
                    Light_Display();
                    for(i = 0; i < 8; i++){
                        LED_dat_arr[i] = Light_dat_arr[i];
                    }
                    break;
                case 1:
                    RB2_Display();
                    for(i = 0; i < 8; i++){
                        LED_dat_arr[i] = RB2_dat_arr[i];
                    }
                    break;
            }
            break;
    }
}

void LED_Display_Show(){
    unsigned char com;
    unsigned char dat;
    for(com = 0; com < 8; com++){
        SEG(0xFF);
        COM(1 << com);
        dat = SEG_Table[LED_dat_arr[com]];
        if(S4_cnt == 2 && com == 5){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
}