#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"
#include "PCF8591.h"
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
    0x88,   //A
    0x8C,   //P
    0x86,   //E
    0xBF,   //-
    0xFF    //全灭
};

unsigned char Distrance_dat_arr[] = {10,14,14,14,14,14,14,14};   //测距
unsigned char Parameter1_dat_arr[] = {11,1,14,14,14,13,14,14};  //模式一
unsigned char Parameter2_dat_arr[] = {11,2,14,14,14,13,14,14};  //模式二
unsigned char Record_dat_arr[] = {12,14,14,14,14,14,14,0};  //记录
unsigned char LED_dat_arr[] = {14,14,14,14,14,14,14,14};

void Distrance_Display(){
    if(sound_value >= 100){
        Distrance_dat_arr[5] = sound_value / 100;
        Distrance_dat_arr[6] = sound_value % 100 / 10;
        Distrance_dat_arr[7] = sound_value % 10;
    }
    else if(sound_value >= 10 && sound_value < 100){
        Distrance_dat_arr[5] = 14;
        Distrance_dat_arr[6] = sound_value / 10;
        Distrance_dat_arr[7] = sound_value % 10;
    }
    else if(sound_value >= 0 && sound_value < 10){
        Distrance_dat_arr[5] = 14;
        Distrance_dat_arr[6] = 14;
        Distrance_dat_arr[7] = sound_value;
    }
}

void Parameter_Display(){
    Parameter1_dat_arr[3] = Parameter_min / 10;
    Parameter1_dat_arr[4] = Parameter_min % 10;
    Parameter1_dat_arr[6] = Parameter_max / 10;
    Parameter1_dat_arr[7] = Parameter_max % 10;

    Parameter2_dat_arr[3] = Parameter_min / 10;
    Parameter2_dat_arr[4] = Parameter_min % 10;
    Parameter2_dat_arr[6] = Parameter_max / 10;
    Parameter2_dat_arr[7] = Parameter_max % 10;
}

void Record_Display(){
    if(num <= 9){
        Record_dat_arr[7] = num;
    }
    else{
        Record_dat_arr[7] = 13;
    }
}

void LED_Display_Choose(){
    unsigned char i;
    switch(S4_cnt){
        case 0:
            Distrance_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Distrance_dat_arr[i];
            }
            break;
        case 1:
            Parameter_Display();
            switch(S5_cnt){
                case 0:
                    for(i = 0;i < 8;i++){
                        LED_dat_arr[i] = Parameter1_dat_arr[i];
                    }
                    break;
                case 1:
                    for(i = 0;i < 8;i++){
                        LED_dat_arr[i] = Parameter2_dat_arr[i];
                    }
                    break;
            }
            break;
        case 2:
            Record_Display();
            for(i = 0;i < 8;i++){
                LED_dat_arr[i] = Record_dat_arr[i];
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