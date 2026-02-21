#include <STC15F2K60S2.H>
#include "KEY.h"
#include "Delay.h"
#include "PCF8591.h"
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
    0xC6,   //C
    0x86,   //E
    0x89,   //H
    0xFF    //全灭
};

unsigned char Num1_dat_arr[] = {10,13,13,13,13,13,13,13};
unsigned char Num2_dat_arr[] = {11,13,13,13,13,13,13,13};
unsigned char Num3_dat_arr[] = {12,13,13,13,13,13,13,13};
unsigned char LED_dat_arr[] = {13,13,13,13,13,13,13,13};

void Num1_Display(){
    Num1_dat_arr[6] = ADC_value / 10;
    Num1_dat_arr[7] = ADC_value % 10;
}

void Num2_Display(){
    Num2_dat_arr[6] = ADC_dat / 10;
    Num2_dat_arr[7] = ADC_dat % 10;
}

void Num3_Display(){
    if(time == 10){
        Num3_dat_arr[6] = 1;
        Num3_dat_arr[7] = 0;
    }
    else{
        Num3_dat_arr[6] = 13;
        Num3_dat_arr[7] = time;
    }
}

void LED_Display_Choose(){
    unsigned char dat = S4_cnt % 3;
    unsigned char i;
    switch(dat){
        case 0:
            Num1_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Num1_dat_arr[i];
            }
            break;
        case 1:
            Num2_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Num2_dat_arr[i];
            }
            break;
        case 2:
            Num3_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Num3_dat_arr[i];
            }
            break;
    }
}

void LED_Display_Show(){
    unsigned char dat;
    unsigned char com;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[LED_dat_arr[com]];
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}