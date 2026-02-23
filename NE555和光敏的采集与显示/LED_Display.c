#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"
#include "PCF8591.h"
#include "NE555.h"
#include "Delay.h"

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
    0x8E,   //F
    0x86,   //E
    0xFF    //全灭
};

unsigned char NE555_dat_arr[] = {10,12,12,12,12,12,12,12};
unsigned char Light_dat_arr[] = {11,12,12,12,12,12,12,12};
unsigned char LED_Display_arr[] = {12,12,12,12,12,12,12,12};

void NE555_Display(){
    if(key_value > 10){
        NE555_dat_arr[1] = key_value / 10;
        NE555_dat_arr[2] = key_value % 10;
    } 
    else if(key_value > 0 && key_value < 10){
        NE555_dat_arr[1] = 12;
        NE555_dat_arr[2] = key_value;
    }
	else if(key_value == 0){
		NE555_dat_arr[1] = 12;
        NE555_dat_arr[2] = 12;
	}
    if(NE555_value >= 10000){
        NE555_dat_arr[3] = NE555_value / 10000;
        NE555_dat_arr[4] = NE555_value % 10000 / 1000;
        NE555_dat_arr[5] = NE555_value % 1000 / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 1000 && NE555_value < 10000){
        NE555_dat_arr[3] = 12;
        NE555_dat_arr[4] = NE555_value / 1000;
        NE555_dat_arr[5] = NE555_value % 1000 / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 100 && NE555_value < 1000){
        NE555_dat_arr[3] = 12;
        NE555_dat_arr[4] = 12;
        NE555_dat_arr[5] = NE555_value / 100;
        NE555_dat_arr[6] = NE555_value % 100 / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 10 && NE555_value < 100){
        NE555_dat_arr[3] = 12;
        NE555_dat_arr[4] = 12;
        NE555_dat_arr[5] = 12;
        NE555_dat_arr[6] = NE555_value / 10;
        NE555_dat_arr[7] = NE555_value % 10;
    }
    else if(NE555_value >= 0 && NE555_value < 10){
        NE555_dat_arr[3] = 12;
        NE555_dat_arr[4] = 12;
        NE555_dat_arr[5] = 12;
        NE555_dat_arr[6] = 12;
        NE555_dat_arr[7] = NE555_value;
    }
}

void Light_Display(){
    if(key_value > 10){
        Light_dat_arr[1] = key_value / 10;
        Light_dat_arr[2] = key_value % 10;
    }
    else if(key_value > 0 && key_value < 10){
        Light_dat_arr[1] = 12;
        Light_dat_arr[2] = key_value;
    }
	else if(key_value == 0){
		Light_dat_arr[1] = 12;
        Light_dat_arr[2] = 12;
	}
    Light_dat_arr[6] = Light_value / 10;
    Light_dat_arr[7] = Light_value % 10;
}

void LED_Display_Choose(){
    unsigned char dat = S12_cnt % 2;
    unsigned char i;
    switch(dat){
        case 0:
            NE555_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = NE555_dat_arr[i];
            }
            break;
        case 1:
            Light_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Light_dat_arr[i];
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
        if(S12_cnt % 2 == 1 && com == 6){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
}