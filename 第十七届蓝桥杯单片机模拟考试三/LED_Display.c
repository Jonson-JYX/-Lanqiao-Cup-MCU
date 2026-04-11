#include <STC15F2K60S2.H>
#include "KEY.h"
#include "Delay.h"
#include "Common.h"

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
    0x89,   //H 10
    0x86,   //E 11
    0xC7,   //L 12
    0xC0,   //O 13
    0xC1,   //U 14
    0x88,   //A 15
    0xFF    //全灭 16
};

//准备界面数组
unsigned char Prepare_dat_arr[] = {10,11,12,12,13,16,16,16};
//设置界面数组
unsigned char Setting_dat_arr[] = {14,16,16,16,16,16,16,16};
//比赛界面数组
unsigned char Competition_dat_arr[] = {15,16,16,16,16,16,16,16};
//结果界面数组
unsigned char Result_dat_arr[] = {11,16,16,16,16,16,16,16};
//数码管数组
unsigned char LED_Display_arr[] = {16,16,16,16,16,16,16,16};

void Setting_Display(){
    Setting_dat_arr[6] = Time_value / 10;
    Setting_dat_arr[7] = Time_value % 10;
}

void Competition_Display(){
    Competition_dat_arr[6] = Time_dat / 10;
    Competition_dat_arr[7] = Time_dat % 10;
}

void Result_Display(){
    if(contestant_num == 0){
        Result_dat_arr[6] = 11;
        Result_dat_arr[7] = 11;
    }
    else{
        Result_dat_arr[6] = 16;
        Result_dat_arr[7] = contestant_num;
    }
}

void LED_Display_Choose(){
    unsigned char i;
    if(prepare_flag){
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Prepare_dat_arr[i];
        }
    }
    if(setting_flag){
        Setting_Display();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Setting_dat_arr[i];
        }
    }
    if(competition_flag){
        Competition_Display();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Competition_dat_arr[i];
        }
    }
    if(result_flag){
        Result_Display();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Result_dat_arr[i];
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