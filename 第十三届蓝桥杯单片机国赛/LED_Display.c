#include <STC15F2K60S2.H>
#include "NE555.h"
#include "Common.h"
#include "Ultrasound.h"
#include "PCF8591.h"
#include "Delay.h"
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
    0x8E,   //F 10
    0x89,   //H 11
    0x88,   //A 12
    0x8C,   //P 13
    0xFF    //全灭 14
};

unsigned char NE555_dat_arr[] = {10,14,14,14,14,14,14,14};
unsigned char Humidity_dat_arr[] = {11,14,14,14,14,14,14,14};
unsigned char Sound_dat_arr[] = {12,14,14,14,14,14,14,14};
unsigned char NE555_Parameter_arr[] = {13,1,14,14,14,14,14,14};
unsigned char Humidity_Parameter_arr[] = {13,2,14,14,14,14,14,14};
unsigned char Sound_Parameter_arr[] = {13,3,14,14,14,14,14,14};
unsigned char LED_Display_arr[] = {14,14,14,14,14,14,14,14};

void NE555_dat_Diplay(){
    if(NE555_value >= 100000){
        NE555_dat_arr[2] = NE555_value / 100000;
        NE555_dat_arr[3] = NE555_value % 100000 / 10000;
        NE555_dat_arr[4] = NE555_value % 10000 / 1000;
        NE555_dat_arr[5] = NE555_value % 1000 / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 10000 && NE555_value < 100000){
        NE555_dat_arr[2] = 14;
        NE555_dat_arr[3] = NE555_value / 10000;
        NE555_dat_arr[4] = NE555_value % 10000 / 1000;
        NE555_dat_arr[5] = NE555_value % 1000 / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 1000 && NE555_value < 10000){
        NE555_dat_arr[2] = 14;
        NE555_dat_arr[3] = 14;
        NE555_dat_arr[4] = NE555_value / 1000;
        NE555_dat_arr[5] = NE555_value % 1000 / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 100 && NE555_value < 1000){
        NE555_dat_arr[2] = 14;
        NE555_dat_arr[3] = 14;
        NE555_dat_arr[4] = 14;
        NE555_dat_arr[5] = NE555_value / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 10 && NE555_value < 100){
        NE555_dat_arr[2] = 14;
        NE555_dat_arr[3] = 14;
        NE555_dat_arr[4] = 14;
        NE555_dat_arr[5] = 14;
        NE555_dat_arr[6] = NE555_value / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 0 && NE555_value < 10){
        NE555_dat_arr[2] = 14;
        NE555_dat_arr[3] = 14;
        NE555_dat_arr[4] = 14;
        NE555_dat_arr[5] = 14;
        NE555_dat_arr[6] = 14;
        NE555_dat_arr[7] = NE555_value;
    }
}

void Humidity_dat_Display(){
    if(Humidity_value >= 100){
        Humidity_dat_arr[5] = 1;  // 百位显示1
        Humidity_dat_arr[6] = 0;  // 十位显示0
        Humidity_dat_arr[7] = 0;  // 个位显示0
    }else if(Humidity_value >= 10){
        Humidity_dat_arr[5] = 14; // 百位灭
        Humidity_dat_arr[6] = Humidity_value / 10;
        Humidity_dat_arr[7] = Humidity_value % 10;
    }
    else{
        Humidity_dat_arr[5] = 14; // 百位灭
        Humidity_dat_arr[6] = 14; // 十位灭
        Humidity_dat_arr[7] = Humidity_value;
    }
}

void Sound_dat_Display(){
    if(!Sound_flag){
        if(Sound_value >= 100){
            Sound_dat_arr[5] = Sound_value / 100;
            Sound_dat_arr[6] = Sound_value % 100 / 10;
            Sound_dat_arr[7] = Sound_value % 10;
        }
        else if(Sound_value >= 10 && Sound_value < 100){
            Sound_dat_arr[5] = 14;
            Sound_dat_arr[6] = Sound_value / 10;
            Sound_dat_arr[7] = Sound_value % 10;
        }
        else if(Sound_value >= 0 && Sound_value < 10){
            Sound_dat_arr[5] = 14;
            Sound_dat_arr[6] = 14;
            Sound_dat_arr[7] = Sound_value;
        }
    }
    if(Sound_flag){
        Sound_dat_arr[5] = Sound_value / 100;
        Sound_dat_arr[6] = Sound_value % 100 / 10;
        Sound_dat_arr[7] = Sound_value % 10;
    }
}

void NE555_Parameter_Display(){
    if(NE555_dat >= 100){
        NE555_Parameter_arr[5] = NE555_dat / 100;
        NE555_Parameter_arr[6] = NE555_dat % 100 / 10;
        NE555_Parameter_arr[7] = NE555_dat % 10;
    }
    else{
        NE555_Parameter_arr[5] = 14;
        NE555_Parameter_arr[6] = NE555_dat / 10;
        NE555_Parameter_arr[7] = NE555_dat % 10;
    }
}

void Humidity_Parameter_Display(){
    Humidity_Parameter_arr[6] = Humidity_dat / 10;
    Humidity_Parameter_arr[7] = Humidity_dat % 10;
}

void Sound_Parameter_Display(){
    Sound_Parameter_arr[6] = Sound_dat / 10;
    Sound_Parameter_arr[7] = Sound_dat % 10;
}

void LED_Display_Choose(){
    unsigned char i;
    switch(S4_cnt){
        case 0:
            NE555_dat_Diplay();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = NE555_dat_arr[i];
            }
            break;
        case 1:
            Humidity_dat_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Humidity_dat_arr[i];
            }
            break;
        case 2:
            Sound_dat_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Sound_dat_arr[i];
            }
            break;
        case 3:
            switch(S5_cnt){
                case 0:
                    NE555_Parameter_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = NE555_Parameter_arr[i];
                    }
                    break;
                case 1:
                    Humidity_Parameter_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Humidity_Parameter_arr[i];
                    }
                    break;
                case 2:
                    Sound_Parameter_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Sound_Parameter_arr[i];
                    }
                    break;
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
        if((NE555_flag && com == 6 && S4_cnt % 4 == 0) || (Sound_flag && com == 5 && S4_cnt % 4 == 2) || (S4_cnt == 3 && S5_cnt == 0 && com == 6) || (S4_cnt == 3 && S5_cnt == 2 && com == 6)){
            dat &= 0x7F;
        }
        else{
            dat |= 0x80;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}