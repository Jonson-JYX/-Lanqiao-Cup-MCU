#include <STC15F2K60S2.H>
#include "Dealy.h"
#include "DS18B20.h"
#include "NE555.h"
#include "KEY.h"
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
    0x8C,   //P 10
    0xC6,   //C 11
    0xC1,   //U 12
    0xFF    //全灭 13
};

unsigned char NE555_dat_arr[] = {10,13,13,13,13,13,13,13};
unsigned char Temp_dat_arr[] = {11,13,13,13,13,13,13,13};
unsigned char Parameter_dat_arr[] = {12,13,13,13,13,13,13,13};
unsigned char LED_Display_arr[] = {13,13,13,13,13,13,13,13};

void NE555_Display(){
    if(NE555_value >= 100000){
        NE555_dat_arr[2] = NE555_value / 100000;
        NE555_dat_arr[3] = NE555_value % 100000 / 10000;
        NE555_dat_arr[4] = NE555_value % 10000 / 1000;
        NE555_dat_arr[5] = NE555_value % 1000 / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 10000 && NE555_value < 100000){
        NE555_dat_arr[2] = 13;
        NE555_dat_arr[3] = NE555_value / 10000;
        NE555_dat_arr[4] = NE555_value % 10000 / 1000;
        NE555_dat_arr[5] = NE555_value % 1000 / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 1000 && NE555_value < 10000){
        NE555_dat_arr[2] = 13;
        NE555_dat_arr[3] = 13;
        NE555_dat_arr[4] = NE555_value / 1000;
        NE555_dat_arr[5] = NE555_value % 1000 / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 100 && NE555_value < 1000){
        NE555_dat_arr[2] = 13;
        NE555_dat_arr[3] = 13;
        NE555_dat_arr[4] = 13;
        NE555_dat_arr[5] = NE555_value / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 10 && NE555_value < 100){
        NE555_dat_arr[2] = 13;
        NE555_dat_arr[3] = 13;
        NE555_dat_arr[4] = 13;
        NE555_dat_arr[5] = 13;
        NE555_dat_arr[6] = NE555_value / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 0 && NE555_value < 10){
        NE555_dat_arr[2] = 13;
        NE555_dat_arr[3] = 13;
        NE555_dat_arr[4] = 13;
        NE555_dat_arr[5] = 13;
        NE555_dat_arr[6] = 13;
        NE555_dat_arr[7] = NE555_value;
    }
}

void Temp_Display(){
    if(Temp_value >= 100){
        Temp_dat_arr[5] = Temp_value / 100;
        Temp_dat_arr[6] = Temp_value % 100 / 10;
        Temp_dat_arr[7] = Temp_value % 10;
    }
    else if(Temp_value >= 10 && Temp_value < 100){
        Temp_dat_arr[5] = 13;
        Temp_dat_arr[6] = Temp_value / 10;
        Temp_dat_arr[7] = Temp_value % 10;
    }
    else if(Temp_value >= 0 && Temp_value < 10){
        Temp_dat_arr[5] = 13;
        Temp_dat_arr[6] = 0;
        Temp_dat_arr[7] = Temp_value;
    }
}

void Parameter_Display(){
    if(Temp_dat >= 100){
        Parameter_dat_arr[5] = Temp_dat / 100;
        Parameter_dat_arr[6] = Temp_dat % 100 / 10;
        Parameter_dat_arr[7] = Temp_dat % 10;
    }
    else if(Temp_dat >= 10 && Temp_dat < 100){
        Parameter_dat_arr[5] = 13;
        Parameter_dat_arr[6] = Temp_dat / 10;
        Parameter_dat_arr[7] = Temp_dat % 10;
    }
    else if(Temp_dat >= 0 && Temp_dat < 10){
        Parameter_dat_arr[5] = 13;
        Parameter_dat_arr[6] = 13;
        Parameter_dat_arr[7] = Temp_dat;
    }
}

void LED_Display_Choose(){
    unsigned char i;
    unsigned char S4 = S4_cnt % 3;
    switch(S4){
        case 0:
            NE555_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = NE555_dat_arr[i];
            }
            break;
        case 1:
            Temp_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Temp_dat_arr[i];
            }
            break;
        case 2:
            Parameter_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Parameter_dat_arr[i];
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
        if(S4_cnt % 3 == 1 && com == 6){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}