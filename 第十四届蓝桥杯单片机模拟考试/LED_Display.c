#include <STC15F2K60S2.H>
#include "Common.h"
#include "Distance.h"
#include "KEY.h"
#include "Delay.h"

code unsigned char SGE_Table[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xC1, 0xFF
};

unsigned char Num1_dat_arr[] = {10,1,11,11,11,11,11,11};
unsigned char Num2_dat_arr[] = {10,2,11,11,11,11,11,11};
unsigned char LED_dat_arr[] = {11,11,11,11,11,11,11,11};

void Num1_Display(){
    if(sound_dat >= 0 && sound_dat < 10){
        Num1_dat_arr[5] = 11;
        Num1_dat_arr[6] = 11;
        Num1_dat_arr[7] = sound_dat;
    }
    if(sound_dat >= 10 && sound_dat < 100){
        Num1_dat_arr[5] = 11;
        Num1_dat_arr[6] = sound_dat / 10;
        Num1_dat_arr[7] = sound_dat % 10;
    }
    if(sound_dat >= 100){
        Num1_dat_arr[5] = sound_dat / 100;
        Num1_dat_arr[6] = sound_dat % 100 / 10;
        Num1_dat_arr[7] = sound_dat % 10;
    }
}

void Num2_Display(){
    if(sound_value >= 0 && sound_value < 10){
        Num2_dat_arr[5] = 11;
        Num2_dat_arr[6] = 11;
        Num2_dat_arr[7] = sound_value;
    }
    if(sound_value >= 10 && sound_value < 100){
        Num2_dat_arr[5] = 11;
        Num2_dat_arr[6] = sound_value / 10;
        Num2_dat_arr[7] = sound_value % 10;
    }
    if(sound_value >= 100){
        Num2_dat_arr[5] = sound_value / 100;
        Num2_dat_arr[6] = sound_value % 100 / 10;
        Num2_dat_arr[7] = sound_value % 10;
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
        dat = SGE_Table[LED_dat_arr[com]];
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}