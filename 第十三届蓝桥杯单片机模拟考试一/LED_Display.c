#include <STC15F2K60S2.H>
#include "Common.h"
#include "DS1302.h"
#include "DS18B20.h"
#include "KEY.h"
#include "Delay.h"

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
    0xBF,   //-
    0xFF    //全灭
};

unsigned char Time_dat_arr[] = {12,12,11,12,12,11,12,12};
unsigned char Temp_dat_arr[] = {10,12,12,12,12,12,12,12};
unsigned char LED_dat_arr[] = {12,12,12,12,12,12,12,12};

void Time_Display(){
    Time_dat_arr[0] = time_now[0];
    Time_dat_arr[1] = time_now[1];
    Time_dat_arr[3] = time_now[2];
    Time_dat_arr[4] = time_now[3];
    Time_dat_arr[6] = time_now[4];
    Time_dat_arr[7] = time_now[5];
}

void Temp_Display(){
    if(temp_value >= 100){
        Temp_dat_arr[5] = temp_value / 100;
        Temp_dat_arr[6] = temp_value % 100 / 10;
        Temp_dat_arr[7] = temp_value % 10;
    }
    else if(temp_value >= 10 && temp_value < 100){
        Temp_dat_arr[5] = 12;
        Temp_dat_arr[6] = temp_value / 10;
        Temp_dat_arr[7] = temp_value % 10;
    }
    else if(temp_value >= 0 && temp_value < 10){
        Temp_dat_arr[5] = 12;
        Temp_dat_arr[6] = 0;
        Temp_dat_arr[7] = temp_value;
    }
}

void LED_Display_Choose(){
    unsigned char dat = S4_cnt % 2;
    unsigned char i;
    switch(dat){
        case 0:
            Time_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Time_dat_arr[i];
            }
            break;
        case 1:
            Temp_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Temp_dat_arr[i];
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
        if(S4_cnt % 2 == 1 && com == 6){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}