#include <STC15F2K60S2.H>
#include "DS18B20.h"
#include "Common.h"
#include "PCF8591.h"
#include "Delay.h"
#include "KEY.h"

code unsigned char SEG_Table[] = {
    0xC0,//0
	0xF9,//1
	0xA4,//2
	0xB0,//3
	0x99,//4
	0x92,//5
	0x82,//6
	0xF8,//7
	0x80,//8
	0x90,//9
	0xBF,//- 10
    0xC6,//C 11
    0xC8,//n 12
    0x88,//A 13
    0xFF
};

unsigned char Temp_dat_arr[] = {11,14,14,14,14,14,14,14};
unsigned char RB2_dat_arr[] = {12,10,1,14,14,14,14,14};
unsigned char Light_dat_arr[] = {12,10,3,14,14,14,14,14};
unsigned char DAC_dat_arr[] = {13,14,14,14,14,14,14,14};
unsigned char LED_Display_arr[] = {14,14,14,14,14,14,14,14};

void Temp_Display(){
    Temp_dat_arr[5] = Temp_value / 100;
    Temp_dat_arr[6] = Temp_value % 100 / 10;
    Temp_dat_arr[7] = Temp_value % 10;
}

void RB2_Display(){
    RB2_dat_arr[5] = RB2_value / 100;
    RB2_dat_arr[6] = RB2_value % 100 / 10;
    RB2_dat_arr[7] = RB2_value % 10;
}

void Light_Display(){
    Light_dat_arr[5] = Light_value / 100;
    Light_dat_arr[6] = Light_value % 100 / 10;
    Light_dat_arr[7] = Light_value % 10;
}

void DAC_Display(){
    DAC_dat_arr[5] = DAC_value / 100;
    DAC_dat_arr[6] = DAC_value % 100 / 10;
    DAC_dat_arr[7] = DAC_value % 10;
}

void LED_Display_Choose(){
    unsigned char i;
    switch(S4_cnt){
        case 0:
            Temp_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Temp_dat_arr[i];
            }
            break;
        case 1:
            if(S5_cnt == 0){
                RB2_Display();
                for(i = 0;i < 8;i++){
                    LED_Display_arr[i] = RB2_dat_arr[i];
                }
            }
            if(S5_cnt == 1){
                Light_Display();
                for(i = 0;i < 8;i++){
                    LED_Display_arr[i] = Light_dat_arr[i];
                }
            }
            break;
        case 2:
            DAC_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = DAC_dat_arr[i];
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
        if(S4_cnt == 0 && com ==6){
            dat &= 0x7F;
        }
        if(S4_cnt == 1 && com == 5){
            dat &= 0x7F;
        }
        if(S4_cnt == 2 && com == 5){
            dat &= 0X7F;
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0x00);
}