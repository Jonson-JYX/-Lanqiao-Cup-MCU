#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "Timer.h"
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
    0xBF,   //-
    0xC0,   //O
    0x8C,   //P
    0x86,   //E
    0xC8,   //n
    0xC6,   //C
    0xFF    //全灭
};

unsigned char Key_Cin_arr[] = {10,16,16,16,16,16,16,16};
unsigned char Key_Open_arr[] = {11,16,16,16,11,12,13,14};
unsigned char Key_Change_arr[] = {15,16,16,16,16,16,16,16};
unsigned char LED_Display_arr[] = {16,16,16,16,16,16,16,16};

void Key_Cin_Display(){
    unsigned char i;
    unsigned char cnt = 0;
    for(i = 1;i < 8;i++){
        Key_Cin_arr[i] = 16;
    }
    for(i = 8 - num;i < 8;i++){
        Key_Cin_arr[i] = key_password[cnt];
        cnt++;
    }
}

void Key_Change_Display(){
    unsigned char i;
    unsigned char cnt = 0;
    for(i = 1;i < 8;i++){
        Key_Change_arr[i] = 16;
    }
    for(i = 8 - num;i < 8;i++){
        Key_Change_arr[i] = key_password[cnt];
        cnt++;
    } 
}

void LED_Display_Choose(){
    unsigned char i;
    if(S16_flag){
        Key_Cin_Display();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Key_Cin_arr[i];
        }
    }
    if(S12_flag){
        Key_Change_Display();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Key_Change_arr[i];
        }
    }
    if(key_down == 0 && password){
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Key_Open_arr[i];
        }
    }
    if(key_down == 1 && S16_flag == 0 && S12_flag == 0){
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = 16;
        }
    }
}

void LED_Display_Show(){
    unsigned char dat;
    unsigned char com;
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