#include <STC15F2K60S2.H>
#include "Common.h"
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
    0x88,   //A
    0x89,   //H
    0xFF    //全灭
};

unsigned char Num1_dat_arr[] = {10,12,12,12,12,12,12,12};
unsigned char Num2_dat_arr[] = {11,12,12,12,12,12,12,12};
unsigned char LED_dat_arr[] = {12,12,12,12,12,12,12,12};

void Num1_Display(){
    if(count >= 100){
        Num1_dat_arr[5] = count / 100;
        Num1_dat_arr[6] = count % 100 / 10;
        Num1_dat_arr[7] = count % 10;
    }
    else if(count >= 10 && count < 100){
        Num1_dat_arr[5] = 12;
        Num1_dat_arr[6] = count / 10;
        Num1_dat_arr[7] = count % 10;
    }
    else if(count >= 0 && count < 10){
        Num1_dat_arr[5] = 12;
        Num1_dat_arr[6] = 12;
        Num1_dat_arr[7] = count;
    }
}

void Num2_Display(){
    if(num >= 100){
        Num2_dat_arr[5] = num / 100;
        Num2_dat_arr[6] = num % 100 / 10;
        Num2_dat_arr[7] = num % 10;
    }
    else if(num >= 10 && num < 100){
        Num2_dat_arr[5] = 12;
        Num2_dat_arr[6] = num / 10;
        Num2_dat_arr[7] = num % 10;
    }
    else if(num >= 0 && num < 10){
        Num2_dat_arr[5] = 12;
        Num2_dat_arr[6] = 12;
        Num2_dat_arr[7] = num;
    }
}

void LED_Display_Choose(){
    unsigned char dat = S9_cnt % 2;
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