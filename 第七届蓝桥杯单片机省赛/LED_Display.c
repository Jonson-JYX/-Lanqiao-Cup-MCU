#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "DS1302.h"
#include "DS18B20.h"
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
    0xBF,   //- 10
    0xFF    //全灭
};

unsigned char Setting_dat_arr[] = {11,11,11,11,11,10,11,11};
unsigned char Timeing_dat_arr[] = {11,11,10,11,11,10,11,11};
unsigned char Collect_dat_arr[] = {10,11,11,11,11,10,11,11};
unsigned char LED_Display_arr[] = {11,11,11,11,11,11,11,11};

void Setting_Display(){
    Setting_dat_arr[6] = Time_dat[S4_cnt] / 10;
    Setting_dat_arr[7] = Time_dat[S4_cnt] % 10;
}

void Timeing_Display(){
    Timeing_dat_arr[0] = Time_value[0];
    Timeing_dat_arr[1] = Time_value[1];
    Timeing_dat_arr[3] = Time_value[2];
    Timeing_dat_arr[4] = Time_value[3];
    Timeing_dat_arr[6] = Time_value[4];
    Timeing_dat_arr[7] = Time_value[5];
}

void Collect_Display(){
    Collect_dat_arr[1] = S6_cnt / 10;
    Collect_dat_arr[2] = S6_cnt % 10;
    Collect_dat_arr[6] = Temp_dat[S6_cnt] / 10;
    Collect_dat_arr[7] = Temp_dat[S6_cnt] % 10;
}

void LED_Display_Choose(){
    unsigned char i;
    if(Setting_flag){
        Setting_Display();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Setting_dat_arr[i];
        }
    }
    if(Timeing_flag){
        Timeing_Display();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Timeing_dat_arr[i];
        }
    }
    if(Collect_flag){
        Collect_Display();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Collect_dat_arr[i];
        }
    }
}

void LED_Display_Show(){
    unsigned char com;
    unsigned char dat;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[LED_Display_arr[com]];
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}