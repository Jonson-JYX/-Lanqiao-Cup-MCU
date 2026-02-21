#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "DS18B20.h"
#include "PCF8591.h"
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
    0xFF    //全灭
};

unsigned char Temp_dat_arr[] = {10,1,11,11,11,11,11,11};
unsigned char ADC_dat_arr[] = {10,2,11,11,11,11,11,11};
unsigned char LED_dat_arr[] = {11,11,11,11,11,11,11,11};

void Temp_Display(){
    if(Temp_value >= 100){
        Temp_dat_arr[5] = Temp_value / 100;
        Temp_dat_arr[6] = Temp_value % 100 / 10;
        Temp_dat_arr[7] = Temp_value % 10;
    }
    else if(Temp_value >= 10 && Temp_value < 100){
        Temp_dat_arr[5] = 11;
        Temp_dat_arr[6] = Temp_value / 10;
        Temp_dat_arr[7] = Temp_value % 10;
    }
    else if(Temp_value >= 0 && Temp_value < 10){
        Temp_dat_arr[5] = 11;
        Temp_dat_arr[6] = 0;
        Temp_dat_arr[7] = Temp_value;
    }
}

void ADC_Display(){
    if(ADC_value >= 1000){
        ADC_dat_arr[4] = ADC_value / 1000;
        ADC_dat_arr[5] = ADC_value % 1000 / 100;
        ADC_dat_arr[6] = ADC_value % 100 / 10;
        ADC_dat_arr[7] = ADC_value % 10;
    }
    else if(ADC_value >= 100 && ADC_value < 1000){
        ADC_dat_arr[4] = 11;
        ADC_dat_arr[5] = ADC_value / 100;
        ADC_dat_arr[6] = ADC_value % 100 / 10;
        ADC_dat_arr[7] = ADC_value % 10;
    }
    else if(ADC_value >= 10 && ADC_value < 100){
        ADC_dat_arr[4] = 11;
        ADC_dat_arr[5] = 0;
        ADC_dat_arr[6] = ADC_value / 10;
        ADC_dat_arr[7] = ADC_value % 10;
    }
    else if(ADC_value >= 0 && ADC_value < 10){
        ADC_dat_arr[4] = 11;
        ADC_dat_arr[5] = 0;
        ADC_dat_arr[6] = 0;
        ADC_dat_arr[7] = ADC_value;
    }
}

void LED_Display_Choose(){
    unsigned char i;
    unsigned char dat = S5_cnt % 2;
    switch(dat){
        case 0:
            Temp_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Temp_dat_arr[i];
            }
            break;
        case 1:
            ADC_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = ADC_dat_arr[i];
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
        if(S5_cnt % 2 == 0 && com == 6){
            dat &= 0x7F;
        }
        if(S5_cnt % 2 == 1 && com == 5){
            dat &= 0x7F;
        }
        if(S4_flag){
            SEG(dat);
        }
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}