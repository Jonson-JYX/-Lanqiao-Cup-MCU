#include <STC15F2K60S2.H>
#include "Common.h"
#include "PCF8591.h"
#include "Delay.h"
#include "KEY.h"

code unsigned char SEG_Table[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xC1, 0xFF
};

unsigned char Num1_dat_arr[] = {10,11,11,11,11,11,11,11};
unsigned char Num2_dat_arr[] = {10,11,11,11,11,11,11,11};
unsigned char Num3_dat_arr[] = {11,11,11,11,11,11,11,11};
unsigned char LED_dat_arr[] = {11,11,11,11,11,11,11,11};

void Num1_Display(){
    Num1_dat_arr[5] = Vol_value1 / 100;
    Num1_dat_arr[6] = Vol_value1 % 100 / 10;
    Num1_dat_arr[7] = Vol_value1 % 10;
}

void Num2_Display(){
    Num2_dat_arr[6] = Vol_value2 / 10;
    Num2_dat_arr[7] = Vol_value2 % 10;
}

void Num3_Display(){
    if(ADC_value >= 100){
        Num3_dat_arr[5] = ADC_value / 100;
        Num3_dat_arr[6] = ADC_value % 100 / 10;
        Num3_dat_arr[7] = ADC_value % 10;
    }
    if(ADC_value < 100 && ADC_value >= 10){
        Num3_dat_arr[5] = 11;
        Num3_dat_arr[6] = ADC_value / 10;
        Num3_dat_arr[7] = ADC_value % 10;
    }
    if(ADC_value < 10){
        Num3_dat_arr[5] = 11;
        Num3_dat_arr[6] = 11;
        Num3_dat_arr[7] = ADC_value;
    }
}

void LED_Display_Choose(){
    unsigned char i;
    if(S5_cnt % 3 == 0){
        Num1_Display();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Num1_dat_arr[i];
        }
    }
    if(S5_cnt % 3 == 1){
        Num2_Display();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Num2_dat_arr[i];
        }
    }
    if(S5_cnt % 3 == 2){
        Num3_Display();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Num3_dat_arr[i];
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
        if(S5_cnt % 3 == 0 && com == 5){
            dat = dat & 0x7F;
        }
        if(S5_cnt % 3 == 1 && com == 6){
            dat = dat & 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}