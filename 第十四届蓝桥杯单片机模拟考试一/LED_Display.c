#include <STC15F2K60S2.H>
#include "Common.h" 
#include "KEY.h"
#include "PCF8591.h"
#include "Timer.h"
#include "Delay.h"

code unsigned char SEG_Table[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xC1, 0xFF
};

unsigned char Num1_dat_arr[] = {10,1,11,11,11,11,11,11};
unsigned char Num2_dat_arr[] = {10,2,11,11,11,11,11,11};
unsigned char LED_dat_arr[] = {11,11,11,11,11,11,11,11};

void Num1_Change(){
    if(Sound_value >= 100){
        Num1_dat_arr[5] = Sound_value / 100;
        Num1_dat_arr[6] = (Sound_value % 100) / 10;
        Num1_dat_arr[7] = Sound_value % 10;
    }
    if(Sound_value < 100 && Sound_value >= 10){
        Num1_dat_arr[5] = 11;
        Num1_dat_arr[6] = Sound_value / 10;
        Num1_dat_arr[7] = Sound_value % 10;
    }
    if(Sound_value < 10){
        Num1_dat_arr[5] = 11;
        Num1_dat_arr[6] = 0;
        Num1_dat_arr[7] = Sound_value;
    }
    
}

void Num2_Change(){
    if(Decibel_value >= 10){
        Num2_dat_arr[6] = Decibel_value / 10;
        Num2_dat_arr[7] = Decibel_value % 10;
    }
    if(Decibel_value < 10){
        Num2_dat_arr[6] = 11;
        Num2_dat_arr[7] = Decibel_value;
    }
}

void LED_Choose(){
    unsigned char i;
    if(S12_cnt % 2 == 0){
        Num1_Change();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Num1_dat_arr[i];
        }
    }
    if(S12_cnt % 2 == 1){
        Num2_Change();
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
        if(S12_cnt % 2 == 0 && com == 6){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
    COM(0xFF);
    SEG(0xFF);
}