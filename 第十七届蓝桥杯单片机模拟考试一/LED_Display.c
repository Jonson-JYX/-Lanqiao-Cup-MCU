#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "KEY.h"
#include "Distance.h"
#include "DS1302.h"

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
    0x88,   //R
    0xBF,   //-
    0xC7,   //L
    0xFF    //全灭
};

unsigned char time1_dat_arr[] = {10,1,11,11,11,11,11,11};
unsigned char time2_dat_arr[] = {10,2,11,11,11,11,11,11};
unsigned char time3_dat_arr[] = {10,3,11,11,11,11,11,11};
unsigned char Clear_dat_arr[] = {11,11,11,11,11,11,11,11};

unsigned char Num1_dat_arr[] = {12,13,13,13,13,13,13,13};
unsigned char Num2_dat_arr[] = {13,13,11,13,13,11,13,13};
unsigned char LED_dat_arr[] = {13,13,13,13,13,13,13,13};

void Num1_Display(){
    if(sound_dat >= 100){
        Num1_dat_arr[5] = sound_dat / 100;
        Num1_dat_arr[6] = sound_dat % 100 / 10;
        Num1_dat_arr[7] = sound_dat % 10;
    }
    if(sound_dat >= 10 && sound_dat < 100){
        Num1_dat_arr[5] = 13;
        Num1_dat_arr[6] = sound_dat / 10;
        Num1_dat_arr[7] = sound_dat % 10;
    }
    if(sound_dat >= 0 && sound_dat < 10){
        Num1_dat_arr[5] = 13;
        Num1_dat_arr[6] = 13;
        Num1_dat_arr[7] = sound_dat % 10;
    }
}

void Num2_Display(){
    Num2_dat_arr[0] = time_dat[0];
    Num2_dat_arr[1] = time_dat[1];
    Num2_dat_arr[3] = time_dat[2];
    Num2_dat_arr[4] = time_dat[3];
    Num2_dat_arr[6] = time_dat[4];
    Num2_dat_arr[7] = time_dat[5];
}

void Num3_Display(){
    unsigned char i;
    if(sound_dat < 30 && num_flag == 1){
        for(i = 2;i < 8;i++){
            time3_dat_arr[i] = time2_dat_arr[i];
            time2_dat_arr[i] = time1_dat_arr[i];
        }
        for(i = 2;i < 8;i++){
            time1_dat_arr[i] = time_dat[i-2];
        }
        num_flag = 0;
    }
    if(sound_dat >= 30){
        num_flag = 1;
    }
}

void LED_Display_Choose(){
    unsigned char i;
    unsigned char num1 = S4_cnt % 3;
    unsigned char num2 = S5_cnt % 3;
    Num3_Display();
    switch(num1){
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
            switch(num2){
                case 0:
                    for(i = 0;i < 8;i++){
                        LED_dat_arr[i] = time1_dat_arr[i];
                    }
                    break;
                case 1:
                    for(i = 0;i < 8;i++){
                        LED_dat_arr[i] = time2_dat_arr[i];
                    }
                    break;
                case 2:
                    for(i = 0;i < 8;i++){
                        LED_dat_arr[i] = time3_dat_arr[i];
                    }
                    break;
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
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}