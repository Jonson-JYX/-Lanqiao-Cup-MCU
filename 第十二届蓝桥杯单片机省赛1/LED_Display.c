#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "PCF8591.h"
#include "KEY.h"
#include "DS18B20.h"

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
    0x88,   //R
    0xFF    //熄灭
};

//温度显示界面数组
unsigned char Temp_Show_Arr[] = {10,13,13,13,13,13,13,13};
//参数设置界面数组
unsigned char Parameter_Show_Arr[] = {11,13,13,13,13,13,13,13};
//DAC输出界面数组
unsigned char DAC_Show_Arr[] = {12,13,13,13,13,13,13,13};
//数码管显示数组
unsigned char LED_Display_Show_Arr[] = {13,13,13,13,13,13,13,13};

//温度显示界面转化函数
void Temp_Show_Change(){
    float temp_value = Temp_Value();
    unsigned int temp = (unsigned int)(temp_value * 100);
    if(temp >= 1000){
        Temp_Show_Arr[4] = temp / 1000;
        Temp_Show_Arr[5] = temp % 1000 / 100;
        Temp_Show_Arr[6] = temp % 100 / 10;
        Temp_Show_Arr[7] = temp % 10;
    }
    if(temp >= 100 && temp < 1000){
        Temp_Show_Arr[4] = 13;
        Temp_Show_Arr[5] = temp / 100;
        Temp_Show_Arr[6] = temp % 100 / 10;
        Temp_Show_Arr[7] = temp % 10;
    }
    if(temp >= 10 && temp < 100){
        Temp_Show_Arr[4] = 13;
        Temp_Show_Arr[5] = 0;
        Temp_Show_Arr[6] = temp / 10;
        Temp_Show_Arr[7] = temp % 10;
    }
    if(temp >= 0 && temp < 10){
        Temp_Show_Arr[4] = 13;
        Temp_Show_Arr[5] = 0;
        Temp_Show_Arr[6] = 0;
        Temp_Show_Arr[7] = temp % 10;
    }
}

//参数设置界面转化函数
void Parameter_Show_Change(){
    if(Temporary_dat >= 10){
        Parameter_Show_Arr[6] = Temporary_dat / 10;
        Parameter_Show_Arr[7] = Temporary_dat % 10;
    }
    if(Temporary_dat >= 1 && Temporary_dat < 10){
        Parameter_Show_Arr[6] = 13;
        Parameter_Show_Arr[7] = Temporary_dat % 10;
    }
}

//DAC输出界面转化数组
void DAC_Show_Change(){
    float temp_value = Temp_Value();
    unsigned int temp1 = (unsigned int)(temp_value);
    unsigned int temp2 = (unsigned int)((temp_value * 3.0 / 20.0 - 2.0) * 100);
    if(S5_cnt % 2 == 0){
        if(temp1 < Temp_dat){
            DAC_Show_Arr[5] = 0;
            DAC_Show_Arr[6] = 0;
            DAC_Show_Arr[7] = 0;
            DAC_Value(0);
        }
        else{
            DAC_Show_Arr[5] = 5;
            DAC_Show_Arr[6] = 0;
            DAC_Show_Arr[7] = 0;
            DAC_Value(255);
        }
    }
    if(S5_cnt % 2 == 1){
        if(temp1 <= 20){
            DAC_Show_Arr[5] = 1;
            DAC_Show_Arr[6] = 0;
            DAC_Show_Arr[7] = 0;
            DAC_Value(1);
        }
        else if(temp1 > 20 && temp1 < 40){
            if(temp2 >= 100){
                DAC_Show_Arr[5] = temp2 / 100;
                DAC_Show_Arr[6] = temp2 % 100 / 10;
                DAC_Show_Arr[7] = temp2 % 10;
            }
            if(temp2 >= 10 && temp2 < 100){
                DAC_Show_Arr[5] = 0;
                DAC_Show_Arr[6] = temp2 / 10;
                DAC_Show_Arr[7] = temp2 % 10;
            }
            if(temp2 >= 0 && temp2 < 10){
                DAC_Show_Arr[5] = 0;
                DAC_Show_Arr[6] = 0;
                DAC_Show_Arr[7] = temp2 % 10;
            }
        }
        else if(temp1 >= 40){
            DAC_Show_Arr[5] = 5;
            DAC_Show_Arr[6] = 0;
            DAC_Show_Arr[7] = 0;
            DAC_Value(255);
        }
    }
}

//数码管选择函数
void LED_Display_Choose(){
    unsigned char i;
    if(S4_cnt % 3 == 0){
        Temp_Show_Change();
        for(i = 0;i < 8;i++){
            LED_Display_Show_Arr[i] = Temp_Show_Arr[i];
        }
    }
    if(S4_cnt % 3 == 1){
        Parameter_Show_Change();
        for(i = 0;i < 8;i++){
            LED_Display_Show_Arr[i] = Parameter_Show_Arr[i];
        }
    }
    if(S4_cnt % 3 == 2){
        DAC_Show_Change();
        for(i = 0;i < 8;i++){
            LED_Display_Show_Arr[i] = DAC_Show_Arr[i];
        }
    }
}

//数码管显示函数
void LED_Display_Show(){
    unsigned char com;
    unsigned char dat;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[LED_Display_Show_Arr[com]];
        if(S4_cnt % 3 == 0 && com == 5){
            dat = dat & 0x7F;
        }
        if(S4_cnt % 3 == 2 && com == 5){
            dat = dat & 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}