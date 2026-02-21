#include <stc15f2k60s2.h>
#include "Common.h"
#include "Delay.h"
#include "DS18B20.h"
#include "PCF8591.h"
#include "KEY.h"
#include "LED.h"

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
    0x8C,   //P
    0x89,   //H
    0xFF    //全灭
};

//检测界面数组
unsigned char Detection_Interface_Arr[] = {10,13,13,13,12,13,13,13};
//温度阈值界面数组
unsigned char Temp_Threshold_Interface_Arr[] = {11,10,13,13,13,13,13,13};
//光照阈值界面数组
unsigned char Light_Threshold_Interface_Arr[] = {11,12,13,13,13,13,13,13};
//数码管显示数组
unsigned char LED_Display_Show_Arr[] = {13,13,13,13,13,13,13,13};

//检测界面转化函数
void Detection_Change(){
    float Temp_value = Temp_Value();
    float Light_value = RB2_Value();
    unsigned int temp_dat = (unsigned int)(Temp_value);
    unsigned int light_dat = (unsigned int)(Light_value * 50);
    unsigned int dat = (unsigned int)(Light_value * 4900.0 / 47.0 + 1000.0 / 47.0);
    //温度转化
    if(temp_dat >= 10){
        Detection_Interface_Arr[1] = temp_dat / 10;
        Detection_Interface_Arr[2] = temp_dat % 10;
    }
    else if(temp_dat < 10){
        Detection_Interface_Arr[1] = 13;
        Detection_Interface_Arr[2] = temp_dat % 10;
    }
    //光照转化
    if(light_dat <= 3){
        Detection_Interface_Arr[5] = 13;
        Detection_Interface_Arr[6] = 1;
        Detection_Interface_Arr[7] = 0;
    }
    else if(light_dat < 50 && light_dat > 3){
        if(dat > 10 && dat < 100){
            Detection_Interface_Arr[5] = 13;
            Detection_Interface_Arr[6] = dat / 10;
            Detection_Interface_Arr[7] = dat % 10;
        }
        if(dat >= 100){
            Detection_Interface_Arr[5] = dat / 100;
            Detection_Interface_Arr[6] = dat % 100 / 10;
            Detection_Interface_Arr[7] = dat % 10;
        }
    }
    else if(light_dat >= 50){
        Detection_Interface_Arr[5] = 5;
        Detection_Interface_Arr[6] = 0;
        Detection_Interface_Arr[7] = 0;
    }
}

//温度阈值界面转化函数
void Temp_Change(){
    Temp_Threshold_Interface_Arr[6] = Temp_dat / 10;
    Temp_Threshold_Interface_Arr[7] = Temp_dat % 10;
}

//光照阈值界面转化函数
void Light_Change(){
    Light_Threshold_Interface_Arr[5] = Light_dat / 100;
    Light_Threshold_Interface_Arr[6] = Light_dat % 100 / 10;
    Light_Threshold_Interface_Arr[7] = Light_dat % 10;
}

//数码管选择显示函数
void LED_Display_Choose(){
    unsigned char i;
    if(S4_cnt % 2 == 0){
        for(i = 0;i < 8;i++){
            LED_Display_Show_Arr[i] = Detection_Interface_Arr[i];
        }
    }
    if(S4_cnt % 2 != 0){
        if(S5_cnt % 2 == 0){
            for(i = 0;i < 8;i++){
                LED_Display_Show_Arr[i] = Temp_Threshold_Interface_Arr[i];
            }
        }
        if(S5_cnt % 2 != 0){
            for(i = 0;i < 8;i++){
                LED_Display_Show_Arr[i] = Light_Threshold_Interface_Arr[i];
            }
        }
    }
}

//数码管显示函数
void LED_Display_Show(){
    unsigned char dat;
    unsigned char com;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[LED_Display_Show_Arr[com]];
        SEG(dat);
        Delay15us();
    }
    SEG(0xFF);
    COM(0xFF);
}