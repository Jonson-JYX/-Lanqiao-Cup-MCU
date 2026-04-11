#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "DS18B20.h"
#include "PCF8591.h"
#include "Sound.h"
#include "Timer.h"
#include "KEY.h"
#include "Relay.h"

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
    0xC6,   //C 10
    0xC7,   //L 11
    0x8C,   //P 12
    0xC8,   //N 13
    0xFF    //灭14
};

unsigned char Environmental_status_arr[] = {10,14,14,14,14,14,13,14};    //环境状态数组
unsigned char Runing_status_arr[] = {11,14,14,14,14,14,14,14};           //运行状态数组
unsigned char Temp_setting_arr[] = {12,10,14,14,14,14,14,14};            //温度设定数组
unsigned char Sound_setting_arr[] = {12,11,14,14,14,14,14,14};           //声音设定数组
unsigned char Relay_count_arr[] = {13,10,14,14,14,14,14,14};             //继电器计数数组
unsigned char LED_Display_arr[] = {14,14,14,14,14,14,14,14};             //数码管显示数组

void Environmental_status_Display(){
    Environmental_status_arr[1] = temp_value / 10;
    Environmental_status_arr[2] = temp_value % 10;
    Environmental_status_arr[7] = light_level;
}

void Runing_status_Display(){
    Runing_status_arr[1] = sound_status;
    Runing_status_arr[5] = sound_value / 100;
    Runing_status_arr[6] = sound_value % 100 / 10;
    Runing_status_arr[7] = sound_value % 10;
}

void Temp_setting_Display(){
    Temp_setting_arr[6] = temp_dat / 10;
    Temp_setting_arr[7] = temp_dat % 10;
}

void Sound_setting_Display(){
    Sound_setting_arr[6] = sound_dat / 10;
    Sound_setting_arr[7] = sound_dat % 10;
}

void Relay_count_Display(){
    Relay_count_arr[4] = relay_cnt / 1000;
    Relay_count_arr[5] = relay_cnt % 1000 / 100;
    Relay_count_arr[6] = relay_cnt % 100 / 10;
    Relay_count_arr[7] = relay_cnt % 10;
}

void LED_Display_Choose(){
    unsigned char i;
    switch(S4_cnt){
        case 0:
            Environmental_status_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Environmental_status_arr[i];
            }
            break;
        case 1:
            Runing_status_Display();
            if(sound_status1_flag){
                for(i = 0;i < 8;i++){
                    LED_Display_arr[i] = Runing_status_arr[i];
                }
                if(sound_status1_cnt >= 3000){
                    sound_status1_flag = 0;
                    sound_status1_cnt = 0;
                } 
            }
            if(sound_status2_flag){
                for(i = 0;i < 8;i++){
                    LED_Display_arr[i] = Runing_status_arr[i];
                }
                if(sound_status2_cnt >= 3000){
                    sound_status2_flag = 0;
                    sound_status2_cnt = 0;
                } 
            }
            if(sound_status3_flag){
                for(i = 0;i < 8;i++){
                    LED_Display_arr[i] = Runing_status_arr[i];
                }
                if(sound_status3_cnt >= 3000){
                    sound_status3_flag = 0;
                    sound_status3_cnt = 0;
                } 
            }
            break;
        case 2:
            switch(S5_cnt){
                case 0:
                    Temp_setting_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Temp_setting_arr[i];
                    }
                    break;
                case 1:
                    Sound_setting_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Sound_setting_arr[i];
                    }
                    break;
            }
            break;
        case 3:
            Relay_count_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Relay_count_arr[i];
            }
            break;
    }
}

void LED_Display_Show(){
    unsigned char com;
    unsigned char dat;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1 << com);
        dat = SEG_Table[LED_Display_arr[com]];
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}