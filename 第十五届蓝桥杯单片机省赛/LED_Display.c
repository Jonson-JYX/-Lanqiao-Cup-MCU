#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"
#include "Delay.h"
#include "DS1302.h"
#include "NE555.h"

code unsigned char SEG_Table[] ={
    0xC0,   //0
    0xF9,   //1
    0xA4,   //2
    0xB0,   //3
    0x99,   //4
    0X92,   //5
    0x82,   //6
    0xF8,   //7
    0x80,   //8
    0x90,   //9
    0x8E,   //F-10
    0x8C,   //P-11
    0x89,   //H-12
    0x88,   //A-13
    0xC7,   //L-14
    0xBF,   //- 15
    0xFF,   //全灭-16
};

//频率界面
unsigned char Frequency_dat_arr[] = {10,16,16,16,16,16,16,16};
//超限参数界面
unsigned char Excessive_Parameter_arr[] = {11,1,16,16,16,16,16,16};
//校准参数界面
unsigned char Calibrate_Parameter_arr[] = {11,2,16,16,16,16,16,16};
//时间界面
unsigned char Time_dat_arr[] = {16,16,15,16,16,15,16,16};
//频率回显界面
unsigned char Frequency_Echo_arr[] = {12,10,16,16,16,16,16,16};
//时间回显界面
unsigned char Time_Echo_arr[] = {12,13,16,16,16,16,16,16};
//数码管显示数组
unsigned char LED_Display_arr[] = {16,16,16,16,16,16,16,16};

void Frequency_Display(){
    if(NE555_now < 0){
        Frequency_dat_arr[3] = 16;
        Frequency_dat_arr[4] = 16;
        Frequency_dat_arr[5] = 16;
        Frequency_dat_arr[6] = 14;
        Frequency_dat_arr[7] = 14;
    }
    else{
        if(NE555_now >= 10000){
            Frequency_dat_arr[3] = NE555_now / 10000;
            Frequency_dat_arr[4] = NE555_now % 10000 / 1000;
            Frequency_dat_arr[5] = NE555_now % 1000 / 100;
            Frequency_dat_arr[6] = NE555_now % 100 / 10;
            Frequency_dat_arr[7] = NE555_now % 10;
        }
        else if(NE555_now>= 1000 && NE555_now < 10000){
            Frequency_dat_arr[3] = 16;
            Frequency_dat_arr[4] = NE555_now / 1000;
            Frequency_dat_arr[5] = NE555_now % 1000 / 100;
            Frequency_dat_arr[6] = NE555_now % 100 / 10;
            Frequency_dat_arr[7] = NE555_now % 10;
        }
        else if(NE555_now >= 100 && NE555_now < 1000){
            Frequency_dat_arr[3] = 16;
            Frequency_dat_arr[4] = 16;
            Frequency_dat_arr[5] = NE555_now / 100;
            Frequency_dat_arr[6] = NE555_now % 100 / 10;
            Frequency_dat_arr[7] = NE555_now % 10;
        }
        else if(NE555_now >= 10 && NE555_now < 100){
            Frequency_dat_arr[3] = 16;
            Frequency_dat_arr[4] = 16;
            Frequency_dat_arr[5] = 16;
            Frequency_dat_arr[6] = NE555_now / 10;
            Frequency_dat_arr[7] = NE555_now % 10;
        }
        else if(NE555_now >= 0 && NE555_now < 10){
            Frequency_dat_arr[3] = 16;
            Frequency_dat_arr[4] = 16;
            Frequency_dat_arr[5] = 16;
            Frequency_dat_arr[6] = 16;
            Frequency_dat_arr[7] = NE555_now;
        }
    }
}

void Excessive_Display(){
    Excessive_Parameter_arr[4] = NE555_Hyperparameter / 1000;
    Excessive_Parameter_arr[5] = NE555_Hyperparameter % 1000 / 100;
    Excessive_Parameter_arr[6] = NE555_Hyperparameter % 100 / 10;
    Excessive_Parameter_arr[7] = NE555_Hyperparameter % 100;
}

void Calibrate_Display(){
    if(NE555_Calibration == 0){
        Calibrate_Parameter_arr[4] = 16;
        Calibrate_Parameter_arr[5] = 16;
        Calibrate_Parameter_arr[6] = 16;
        Calibrate_Parameter_arr[7] = 0;
    }
    else{
        if(NE555_value > 0){
            Calibrate_Parameter_arr[4] = 16;
            Calibrate_Parameter_arr[5] = NE555_Calibration / 100;
            Calibrate_Parameter_arr[6] = NE555_Calibration % 100 / 10;
            Calibrate_Parameter_arr[7] = NE555_Calibration % 10;
        }
        else{
            Calibrate_Parameter_arr[4] = 15;
            Calibrate_Parameter_arr[5] = NE555_Calibration / 100;
            Calibrate_Parameter_arr[6] = NE555_Calibration % 100 / 10;
            Calibrate_Parameter_arr[7] = NE555_Calibration % 10;
        }
    }
}

void Time_Display(){
    Time_dat_arr[0] = Time_value[0];
    Time_dat_arr[1] = Time_value[1];
    Time_dat_arr[3] = Time_value[2];
    Time_dat_arr[4] = Time_value[3];
    Time_dat_arr[6] = Time_value[4];
    Time_dat_arr[7] = Time_value[5];
}

void Frequency_Echo_Display(){
    unsigned char i;
    if(NE555_max < NE555_now){
        NE555_max = NE555_value;
        for(i = 0;i < 8;i++){
            time_max[i] = Time_value[i];
        }
    }
    if(NE555_max >= 10000){
        Frequency_Echo_arr[3] = NE555_max / 10000;
        Frequency_Echo_arr[4] = NE555_max % 10000 / 1000;
        Frequency_Echo_arr[5] = NE555_max % 1000 / 100;
        Frequency_Echo_arr[6] = NE555_max % 100 / 10;
        Frequency_Echo_arr[7] = NE555_max % 10;
    }
    else if(NE555_max >= 1000 && NE555_max < 10000){
        Frequency_Echo_arr[3] = 16;
        Frequency_Echo_arr[4] = NE555_max / 1000;
        Frequency_Echo_arr[5] = NE555_max % 1000 / 100;
        Frequency_Echo_arr[6] = NE555_max % 100 / 10;
        Frequency_Echo_arr[7] = NE555_max % 10;
    }
    else if(NE555_max >= 100 && NE555_max < 1000){
        Frequency_Echo_arr[3] = 16;
        Frequency_Echo_arr[4] = 16;
        Frequency_Echo_arr[5] = NE555_max / 100;
        Frequency_Echo_arr[6] = NE555_max % 100 / 10;
        Frequency_Echo_arr[7] = NE555_max % 10;
    }
    else if(NE555_max >= 10 && NE555_max < 100){
        Frequency_Echo_arr[3] = 16;
        Frequency_Echo_arr[4] = 16;
        Frequency_Echo_arr[5] = 16;
        Frequency_Echo_arr[6] = NE555_max / 10;
        Frequency_Echo_arr[7] = NE555_max % 10;
    }
    else if(NE555_max >= 0 && NE555_max < 10){
        Frequency_Echo_arr[3] = 16;
        Frequency_Echo_arr[4] = 16;
        Frequency_Echo_arr[5] = 16;
        Frequency_Echo_arr[6] = 16;
        Frequency_Echo_arr[7] = NE555_max;
    }
}

void Time_Echo_Display(){
    Time_Echo_arr[2] = time_max[0];
    Time_Echo_arr[3] = time_max[1];
    Time_Echo_arr[4] = time_max[2];
    Time_Echo_arr[5] = time_max[3];
    Time_Echo_arr[6] = time_max[4];
    Time_Echo_arr[7] = time_max[5];
}

void LED_Display_Choose(){
    unsigned char i;
    unsigned char S4 = S4_cnt % 4;
    unsigned char S5 = S5_cnt % 2;
    switch(S4){
        case 0:
            Frequency_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Frequency_dat_arr[i];
            }
            break;
        case 1:
            switch(S5){
                case 0:
                    Excessive_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Excessive_Parameter_arr[i];
                    }
                    break;
                case 1:
                    Calibrate_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Calibrate_Parameter_arr[i];
                    }
                    break;
            }
            break;
        case 2:
            Time_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Time_dat_arr[i];
            }
            break;
        case 3:
            switch(S5){
                case 0:
                    Frequency_Echo_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Frequency_Echo_arr[i];
                    }
                    break;
                case 1:
                    Time_Echo_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Time_Echo_arr[i];
                    }
                    break;
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
        dat = SEG_Table[LED_Display_arr[com]];
        SEG(dat);
        Delay50us();
    }
}