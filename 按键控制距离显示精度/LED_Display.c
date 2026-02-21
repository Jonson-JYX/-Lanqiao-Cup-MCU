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
    0x92,   //S
    0xFF    //全灭
};

unsigned char Num1_dat_arr[] = {10,11,11,11,11,11,11,11};
unsigned char Num2_dat_arr[] = {10,11,11,11,11,11,11,11};
unsigned char LED_dat_arr[] = {10,11,11,11,11,11,11,11};

void Num1_Display(){
    if(sound_value >= 100){
        Num1_dat_arr[5] = sound_value / 100;
        Num1_dat_arr[6] = sound_value % 100 / 10;
        Num1_dat_arr[7] = sound_value % 10;
    }
    if(sound_value >= 10 && sound_value < 100){
        Num1_dat_arr[5] = 0;
        Num1_dat_arr[6] = sound_value / 10;
        Num1_dat_arr[7] = sound_value % 10;
    }
    if(sound_value >= 0 && sound_value < 10){
        Num1_dat_arr[5] = 0;
        Num1_dat_arr[6] = 0;
        Num1_dat_arr[7] = sound_value;
    }
}

void Num2_Display(){
    if(sound_value >= 100){
        Num2_dat_arr[6] = sound_value / 100;
        Num2_dat_arr[7] = sound_value % 100 / 10;
    }
    if(sound_value >= 10 && sound_value < 100){
        Num2_dat_arr[6] = 0;
        Num2_dat_arr[7] = sound_value / 10;
    }
}

void LED_Display_Choose(){
    unsigned char i;
    if(S4_cnt % 2 == 0){
        Num1_Display();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Num1_dat_arr[i];
        }
    }
    if(S4_cnt % 2 == 1){
        Num2_Display();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Num2_dat_arr[i];
        }
    }
}

void LED_Display_Show(){
    unsigned char com;
    unsigned char dat;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[LED_dat_arr[com]];
        if(S4_cnt % 2 == 0 && com == 5){
            dat &= 0x7F;
        }
        if(S4_cnt % 2 == 1 && com == 6){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}