#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
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
    0xC6,   //C
    0x8C,   //P
    0xFF    //全灭
};

//数据界面数组
unsigned char Data_Interface_Arr[] = {10,12,12,12,12,12,12,12};
//参数界面数组
unsigned char Parameter_Interface_Arr[] = {11,12,12,12,12,12,12,12};
//数码管显示数组
unsigned char LED_Display_Arr[] = {12,12,12,12,12,12,12,12};

//数据界面转化数组
void Data_Interface_Change(){
    float temp_value = Temp_Value();
    unsigned int temp = (unsigned int)temp_value;
    if(temp >= 10){
        Data_Interface_Arr[6] = temp / 10;
        Data_Interface_Arr[7] = temp % 10;
    }
    if(temp < 10 && temp >=0){
        Data_Interface_Arr[6] = 12;
        Data_Interface_Arr[7] = temp % 10;
    }
}

//参数界面转化函数
void Parameter_Interface_Change(){
    if(Temporarily_max >= 10){
        Parameter_Interface_Arr[3] = Temporarily_max / 10;
        Parameter_Interface_Arr[4] = Temporarily_max % 10; 
    }
    else if(Temporarily_max >= 0 && Temporarily_max < 10){
        Parameter_Interface_Arr[3] = 12;
        Parameter_Interface_Arr[4] = Temporarily_max % 10; 
    }
    if(Temporarily_min >= 10){
        Parameter_Interface_Arr[6] = Temporarily_min / 10;
        Parameter_Interface_Arr[7] = Temporarily_min % 10; 
    }
    else if(Temporarily_min >= 0 && Temporarily_min < 10){
        Parameter_Interface_Arr[6] = 12;
        Parameter_Interface_Arr[7] = Temporarily_min % 10; 
    }
}

//数码管选择函数
void LED_Display_Choose(){
    unsigned char i;
    if(S4_cnt % 2 == 0){
        Data_Interface_Change();
        for(i = 0;i < 8;i++){
            LED_Display_Arr[i] = Data_Interface_Arr[i];
        }
    }
    if(S4_cnt % 2 == 1){
        Parameter_Interface_Change();
        for(i = 0;i < 8;i++){
            LED_Display_Arr[i] = Parameter_Interface_Arr[i];
        }
    }
}

//数码管显示数组
void LED_Display_Show(){
    unsigned char com;
    unsigned char dat;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[LED_Display_Arr[com]];
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}