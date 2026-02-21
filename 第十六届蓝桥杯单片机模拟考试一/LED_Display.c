#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "DS18B20.h"
#include "KEY.h"

code unsigned char SEG_Table[] = {
    0xC0,   
    0xF9,
    0xA4,
    0xB0,   
    0x99,
    0x92,
    0x82,
    0xF8,
    0x80,   
    0x90,
    0xBF,   //-
    0xC6,   //C
    0x86,   //E
    0x89,   //H
    0xFF    //全灭
};

unsigned char Num1_dat_arr[] = {11,14,14,14,14,14,14,14};
unsigned char Num2_dat_arr[] = {12,14,14,14,14,14,14,14};
unsigned char Num3_dat_arr[] = {13,14,14,14,14,14,14,14};
unsigned char LED_Display_arr[] = {14,14,14,14,14,14,14,14};

void Num1_Change(){
    int dat = temp_now + cali_dat * 10;
    if(dat >=100){
        Num1_dat_arr[5] = dat / 100;
        Num1_dat_arr[6] = dat % 100 / 10;
        Num1_dat_arr[7] = dat % 10;
    }
    if(dat >=10 && dat < 100){
        Num1_dat_arr[5] = 14;
        Num1_dat_arr[6] = dat / 10;
        Num1_dat_arr[7] = dat % 10;
    }
    if(dat >=0 && dat < 10){
        Num1_dat_arr[5] = 14;
        Num1_dat_arr[6] = 0;
        Num1_dat_arr[7] = dat % 10;
    }
}

void Num2_Change(){
    int dat = (-1) * cali_dat;
    if(cali_dat >= 0){
        if(cali_dat >= 10){
            Num2_dat_arr[6] = cali_dat / 10;
            Num2_dat_arr[7] = cali_dat % 10;
        }
        if(cali_dat < 10){
            Num2_dat_arr[6] = 14;
            Num2_dat_arr[7] = cali_dat % 10;
        }
    }
    if(cali_dat < 0){
        if(dat >= 10){
            Num2_dat_arr[5] = 10;
            Num2_dat_arr[6] = dat / 10;
            Num2_dat_arr[7] = dat % 10;
        }
        if(dat < 10){
            Num2_dat_arr[5] = 14;
            Num2_dat_arr[6] = 10;
            Num2_dat_arr[7] = dat % 10;
        }
    }
}

void Num3_Change(){
    int dat = (-1) * temp_dat;
    if(temp_dat >= 0){
        if(temp_dat >= 10){
            Num3_dat_arr[6] = temp_dat / 10;
            Num3_dat_arr[7] = temp_dat % 10;
        }
        if(temp_dat < 10){
            Num3_dat_arr[6] = 14;
            Num3_dat_arr[7] = temp_dat % 10;
        }
    }
    if(temp_dat < 0){
        if(dat >= 10){
            Num3_dat_arr[5] = 10;
            Num3_dat_arr[6] = dat / 10;
            Num3_dat_arr[7] = dat % 10;
        }
        if(dat < 10){
            Num3_dat_arr[5] = 14;
            Num3_dat_arr[6] = 10;
            Num3_dat_arr[7] = dat % 10;
        }
    }
}

void LED_Dislay_Choose(){
    unsigned char i;
    if(S4_cnt % 3 == 0){
        Num1_Change();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Num1_dat_arr[i];
        }
    }
    if(S4_cnt % 3 == 1){
        Num2_Change();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Num2_dat_arr[i];
        }
    }
    if(S4_cnt % 3 == 2){
        Num3_Change();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Num3_dat_arr[i];
        }
    }
}

//数码管显示函数
void LED_Display_Show(){
    unsigned char com;
    unsigned char dat;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[LED_Display_arr[com]];
        if(S4_cnt % 3 == 0 && com == 6){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}