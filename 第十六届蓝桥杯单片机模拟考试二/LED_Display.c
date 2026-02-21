#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Common.h"
#include "PCF8591.h"
#include "Timer.h"
#include "KEY.h"
#include "DS1302.h"

bit Trigger_flag = 1;
bit History_flag = 1;

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
    0x8C,   //P 10
    0x88,   //R 11
    0xC6,   //C 12
    0xC1,   //U 13
    0xBF,   //- 14
    0xFF    //全灭 15
};

unsigned char Time_dat_arr[] = {15,15,14,15,15,14,15,15};
unsigned char Figures_dat_arr[] = {10,15,15,15,13,15,15,15};
unsigned char History_dat_arr1[] = {11,1,14,14,14,14,14,14};
unsigned char History_dat_arr2[] = {11,2,14,14,14,14,14,14};
unsigned char History_dat_arr3[] = {11,3,14,14,14,14,14,14};
unsigned char Trigger_dat_arr[] = {12,12,15,15,15,15,15,15};
unsigned char LED_Display_dat_arr[] = {15,15,15,15,15,15,15,15};

void Time_Display(){
    Time_dat_arr[0] = time_value[0];
    Time_dat_arr[1] = time_value[1];
    Time_dat_arr[3] = time_value[2];
    Time_dat_arr[4] = time_value[3];
    Time_dat_arr[6] = time_value[4];
    Time_dat_arr[7] = time_value[5];
}

void Figures_Display(){
    Figures_dat_arr[1] = light_value / 100;
    Figures_dat_arr[2] = light_value % 100 / 10;
    Figures_dat_arr[3] = light_value % 10;

    Figures_dat_arr[5] = ADC_value / 100;
    Figures_dat_arr[6] = ADC_value % 100 / 10;
    Figures_dat_arr[7] = ADC_value % 10;
}

void History_Display(){
    unsigned char i;
    unsigned char time[6] = {0};
    if(ADC_value > light_value){
        if(History_flag){
            for(i = 2;i < 8;i++){
                History_dat_arr3[i] = History_dat_arr2[i];
                History_dat_arr2[i] = History_dat_arr1[i];
            }
            for(i = 0;i < 6;i++){
                time[i] = time_value[i];
            }
            for(i = 2;i < 8;i++){
                History_dat_arr1[i] = time[i - 2];
            }
        }
        History_flag = 0;
    }
    else{
        History_flag = 1;
        Trigger_flag = 1;
    }
}

void Trigger_Display(){
    unsigned char i;
    for(i = 2;i < 8;i++){
        Trigger_dat_arr[i] = History_dat_arr1[i];
    }
}

void LED_Display_Choose(){
    unsigned char S4_dat = S4_cnt % 3;
    unsigned char S5_dat = S5_cnt % 3;
    unsigned char i;
    History_Display();
    if(ADC_value > light_value){
        Trigger_Display();
        if(Trigger_flag == 1){
            for(i = 0;i < 8;i++){
                LED_Display_dat_arr[i] = Trigger_dat_arr[i];
            }
            if(LED_Display_cnt >= 3000){
                Trigger_flag = 0;
                LED_Display_cnt = 0;
            }
        }
    }
    else{
        switch(S4_dat){
            case 0:
                Time_Display();
                for(i = 0;i < 8;i++){
                    LED_Display_dat_arr[i] = Time_dat_arr[i];
                }
                break;
            case 1:
                Figures_Display();
                for(i = 0;i < 8;i++){
                    LED_Display_dat_arr[i] = Figures_dat_arr[i];
                }
                break;
            case 2:
                switch(S5_dat){
                    case 0:
                        for(i = 0;i < 8;i++){
                            LED_Display_dat_arr[i] = History_dat_arr1[i];
                        }
                        break;
                    case 1:
                        for(i = 0;i < 8;i++){
                            LED_Display_dat_arr[i] = History_dat_arr2[i];
                        }
                        break;
                    case 2:
                        for(i = 0;i < 8;i++){
                            LED_Display_dat_arr[i] = History_dat_arr3[i];
                        }
                        break;
                }
                break;
        }
    }
}

void LED_Display_Show(){
    unsigned char dat = 0;
    unsigned char com = 0;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[LED_Display_dat_arr[com]];
        if(S4_cnt % 3 == 1 && (com == 1 || com == 5)){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}