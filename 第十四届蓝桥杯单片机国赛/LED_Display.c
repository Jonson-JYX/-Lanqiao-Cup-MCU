#include <STC15F2K60S2.H>
#include "Delay.h"
#include "DS18B20.h"
#include "KEY.h"
#include "Ultrasound.h"
#include "PCF8591.h"
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
    0xBF,   //- 10
    0x8C,   //P 11
    0x8E,   //F 12
    0xFF    //全灭 13
};

unsigned char Distance_dat_arr[] = {13,13,13,10,13,13,13,13};        //测距界面数组
unsigned char Distance_parameter_arr[] = {11,1,13,13,13,13,13,13};   //距离参数界面数组
unsigned char Temp_parameter_arr[] = {11,2,13,13,13,13,13,13};       //温度参数界面数组
unsigned char Calibration_setting_arr[] = {12,1,13,13,13,13,13,13};  // 校准值设置界面
unsigned char Medium_setting_arr[] = {12,2,13,13,13,13,13,13};       //介质值设置界面
unsigned char DAC_setting_arr[] = {12,3,13,13,13,13,13,13};          //DAC输出设置界面
unsigned char LED_Display_arr[] = {13,13,13,13,13,13,13,13};

void Distance_dat_Display(){
    if(Unit_cnt == 0){
        if(Sound_value >= 100){
            Distance_dat_arr[5] = Sound_value / 100;
            Distance_dat_arr[6] = Sound_value % 100 / 10;
            Distance_dat_arr[7] = Sound_value % 10;
        }
        else if(Sound_value >= 10 && Sound_value < 100){
            Distance_dat_arr[5] = 13;
            Distance_dat_arr[6] = Sound_value / 10;
            Distance_dat_arr[7] = Sound_value % 10;
        }
        else if(Sound_value >= 0 && Sound_value < 10){
            Distance_dat_arr[5] = 13;
            Distance_dat_arr[6] = 13;
            Distance_dat_arr[7] = Sound_value;
        }
    }
    else{
        Distance_dat_arr[5] = Sound_value / 100;
        Distance_dat_arr[6] = Sound_value % 100 / 10;
        Distance_dat_arr[7] = Sound_value % 10;
    }
    if(Temp_value >= 100){
        Distance_dat_arr[0] = Temp_value / 100;
        Distance_dat_arr[1] = Temp_value % 100 / 10;
        Distance_dat_arr[2] = Temp_value % 10;
    }
    else{
        Distance_dat_arr[0] = 13;
        Distance_dat_arr[1] = Temp_value / 10;
        Distance_dat_arr[2] = Temp_value % 10;
    }
}

void Distance_parameter_Display(){
    Distance_parameter_arr[6] = Sound_dat / 10;
    Distance_parameter_arr[7] = Sound_dat % 10;
}

void Temp_parameter_Display(){
    if(Temp_dat >= 10){
        Temp_parameter_arr[6] = Temp_dat / 10;
        Temp_parameter_arr[7] = Temp_dat % 10;
    }
    else{
        Temp_parameter_arr[6] = 13;
        Temp_parameter_arr[7] = Temp_dat;
    }
}

void Calibration_setting_Display(){
    if(Sound_Calib >= 10){
        Calibration_setting_arr[5] = 13;
        Calibration_setting_arr[6] = Sound_Calib / 10;
        Calibration_setting_arr[7] = Sound_Calib % 10;
    }
    else if(Sound_Calib >= 0 && Sound_Calib < 10){
        Calibration_setting_arr[5] = 13;
        Calibration_setting_arr[6] = 13;
        Calibration_setting_arr[7] = Sound_Calib;
    }
    else if(Sound_Calib < 0 && Sound_Calib > -10){
        Calibration_setting_arr[5] = 13;
        Calibration_setting_arr[6] = 10;
        Calibration_setting_arr[7] = -Sound_Calib;
    }
    else if(Sound_Calib <= -10){
        Calibration_setting_arr[5] = 10;
        Calibration_setting_arr[6] = -Sound_Calib / 10;
        Calibration_setting_arr[7] = -Sound_Calib % 10;
    }
}

void Medium_setting_Display(){
    if(Sound_speed >= 1000){
        Medium_setting_arr[4] = Sound_speed / 1000;
        Medium_setting_arr[5] = Sound_speed % 1000 / 100;
        Medium_setting_arr[6] = Sound_speed % 100 / 10;
        Medium_setting_arr[7] = Sound_speed % 10;
    }
    else if(Sound_speed >= 100 && Sound_speed < 1000){
        Medium_setting_arr[4] = 13;
        Medium_setting_arr[5] = Sound_speed / 100;
        Medium_setting_arr[6] = Sound_speed % 100 / 10;
        Medium_setting_arr[7] = Sound_speed % 10;
    }
    else if(Sound_speed >= 10 && Sound_speed < 100){
        Medium_setting_arr[4] = 13;
        Medium_setting_arr[5] = 13;
        Medium_setting_arr[6] = Sound_speed / 10;
        Medium_setting_arr[7] = Sound_speed % 10;
    }
}

void DAC_setting_Display(){
    DAC_setting_arr[6] = DAC_dat / 10;
    DAC_setting_arr[7] = DAC_dat % 10;
}

void LED_Display_Choose(){
    unsigned char i;
    switch(S4_cnt){
        case 0:
            Distance_dat_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Distance_dat_arr[i];
            }
            break;
        case 1:
            switch(Parameters_cnt){
                case 0:
                    Distance_parameter_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Distance_parameter_arr[i];
                    }
                    break;
                case 1:
                    Temp_parameter_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Temp_parameter_arr[i];
                    }
                    break;
            }
            break;
        case 2:
            switch(Setting_cnt){
                case 0:
                    Calibration_setting_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Calibration_setting_arr[i];
                    }
                    break;
                case 1:
                    Medium_setting_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Medium_setting_arr[i];
                    }
                    break;
                case 2:
                    DAC_setting_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = DAC_setting_arr[i];
                    }
                    break;
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
        dat = SEG_Table[LED_Display_arr[com]];
        if((S4_cnt == 0 && Unit_cnt == 1 && com == 5) || (S4_cnt == 0 && com == 1) || (S4_cnt == 2 && Setting_cnt == 2 && com == 6)){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
}