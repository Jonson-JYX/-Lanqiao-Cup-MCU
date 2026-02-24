#include <STC15F2K60S2.H>
#include "Common.h"
#include "DS1302.h"
#include "DS18B20.h"
#include "Delay.h"
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
    0xBF,   //-
    0xFF    //全灭
};

unsigned char Temp_dat_arr[] = {10,1,12,12,12,12,12,12};
unsigned char Time_dat_arr[] = {10,2,12,12,12,11,12,12};
unsigned char Para_dat_arr[] = {10,3,12,12,12,12,12,12};
unsigned char LED_dat_arr[] = {12,12,12,12,12,12,12,12};

void Temp_Display(){
    if(Temp_value >= 100){
        Temp_dat_arr[5] = Temp_value / 100;
        Temp_dat_arr[6] = Temp_value % 100 / 10;
        Temp_dat_arr[7] = Temp_value % 10;
    }
    else if(Temp_value >= 10 && Temp_value < 100){
        Temp_dat_arr[5] = 12;
        Temp_dat_arr[6] = Temp_value / 10;
        Temp_dat_arr[7] = Temp_value % 10;
    }
    else if(Temp_value >= 0 && Temp_value < 10){
        Temp_dat_arr[5] = 12;
        Temp_dat_arr[6] = 12;
        Temp_dat_arr[7] = Temp_value % 10;
    }
}

void Time_Display(){
    if(Time_flag){
        Time_dat_arr[3] = Time_value[2];
        Time_dat_arr[4] = Time_value[3];
        Time_dat_arr[6] = Time_value[4];
        Time_dat_arr[7] = Time_value[5];
    }
    else{
        Time_dat_arr[3] = Time_value[0];
        Time_dat_arr[4] = Time_value[1];
        Time_dat_arr[6] = Time_value[2];
        Time_dat_arr[7] = Time_value[3];
    }
}

void Para_Display(){
    Para_dat_arr[6] = Temp_dat / 10;
    Para_dat_arr[7] = Temp_dat % 10;
}

void LED_Display_Choose(){
    unsigned char dat = S12_cnt % 3;
    unsigned char i;
    switch(dat){
        case 0:
            Temp_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Temp_dat_arr[i];
            }
            break;
        case 1:
            Time_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Time_dat_arr[i];
            }
            break;
        case 2:
            Para_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Para_dat_arr[i];
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
        if(S12_cnt % 3 == 0 && com == 6){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}