#include <STC15F2K60S2.H>
#include "Common.h"
#include "PCF8591.h"
#include "Uart.h"
#include "Ultrasound.h"
#include "NE555.h"
#include "KEY.h"
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
    0xC7,   //L 10
    0x86,   //E 11
    0x8C,   //P 12
    0xBF,   //- 13
    0xFF    //全灭 14
};

// 坐标界面
unsigned char L1_dat_arr[] = {10,14,14,14,13,14,14,14};
unsigned char L2_dat_arr[] = {10,14,14,14,13,14,14,14};
// 速度界面
unsigned char E1_dat_arr[] = {11,1,14,14,14,14,14,14};
unsigned char E2_dat_arr[] = {11,2,14,13,13,13,13,13};
unsigned char E3_dat_arr[] = {11,3,14,14,14,14,14,14};
// 参数界面
unsigned char P_dat_arr[] = {12,14,14,14,14,14,14,14};
// 显示数组
unsigned char LED_Display_arr[] = {14,14,14,14,14,14,14,14};

void L1_Display(){
    if(rx_dat[0] >= 100){
        L1_dat_arr[1] = rx_dat[0] / 100;
        L1_dat_arr[2] = rx_dat[0] % 100 / 10;
        L1_dat_arr[3] = rx_dat[0] % 10;
    }
    else if(rx_dat[0] >= 10 && rx_dat[0] < 100){
        L1_dat_arr[1] = 14;
        L1_dat_arr[2] = rx_dat[0] / 10;
        L1_dat_arr[3] = rx_dat[0] % 10;
    }
    else{
        L1_dat_arr[1] = 14;
        L1_dat_arr[2] = 14;
        L1_dat_arr[3] = rx_dat[0];
    }

    if(rx_dat[1] >= 100){
        L1_dat_arr[5] = rx_dat[1] / 100;
        L1_dat_arr[6] = rx_dat[1] % 100 / 10;
        L1_dat_arr[7] = rx_dat[1] % 10;
    }
    else if(rx_dat[1] >= 10 && rx_dat[1] < 100){
        L1_dat_arr[5] = 14;
        L1_dat_arr[6] = rx_dat[1] / 10;
        L1_dat_arr[7] = rx_dat[1] % 10;
    }
    else{
        L1_dat_arr[5] = 14;
        L1_dat_arr[6] = 14;
        L1_dat_arr[7] = rx_dat[1];
    }
}

void L2_Display(){
    if(Position_value[0] >= 100){
        L2_dat_arr[1] = Position_value[0] / 100;
        L2_dat_arr[2] = Position_value[0] % 100 / 10;
        L2_dat_arr[3] = Position_value[0] % 10;
    }
    else if(Position_value[0] >= 10 && Position_value[0] < 100){
        L2_dat_arr[1] = 14;
        L2_dat_arr[2] = Position_value[0] / 10;
        L2_dat_arr[3] = Position_value[0] % 10;
    }
    else{
        L2_dat_arr[1] = 14;
        L2_dat_arr[2] = 14;
        L2_dat_arr[3] = Position_value[0];
    }

    if(Position_value[1] >= 100){
        L2_dat_arr[5] = Position_value[1] / 100;
        L2_dat_arr[6] = Position_value[1] % 100 / 10;
        L2_dat_arr[7] = Position_value[1] % 10;
    }
    else if(Position_value[1] >= 10 && Position_value[1] < 100){
        L2_dat_arr[5] = 14;
        L2_dat_arr[6] = Position_value[1] / 10;
        L2_dat_arr[7] = Position_value[1] % 10;
    }
    else{
        L2_dat_arr[5] = 14;
        L2_dat_arr[6] = 14;
        L2_dat_arr[7] = Position_value[1];
    }
}

void E1_Display(){
    if(Speed_value >= 10000){
        E1_dat_arr[3] = Speed_value / 10000;
        E1_dat_arr[4] = Speed_value % 10000 / 1000;
        E1_dat_arr[5] = Speed_value % 1000 / 100;
        E1_dat_arr[6] = Speed_value % 100 / 10;
        E1_dat_arr[7] = Speed_value % 10;
    }
    else if(Speed_value >= 1000 && Speed_value < 10000){
        E1_dat_arr[3] = 14;
        E1_dat_arr[4] = Speed_value / 1000;
        E1_dat_arr[5] = Speed_value % 1000 / 100;
        E1_dat_arr[6] = Speed_value % 100 / 10;
        E1_dat_arr[7] = Speed_value % 10;
    }
    else if(Speed_value >= 100 && Speed_value < 1000){
        E1_dat_arr[3] = 14;
        E1_dat_arr[4] = 14;
        E1_dat_arr[5] = Speed_value / 100;
        E1_dat_arr[6] = Speed_value % 100 / 10;
        E1_dat_arr[7] = Speed_value % 10;
    }
    else{
        E1_dat_arr[3] = 14;
        E1_dat_arr[4] = 14;
        E1_dat_arr[5] = 14;
        E1_dat_arr[6] = Speed_value / 10;
        E1_dat_arr[7] = Speed_value % 10;
    }
}

void E3_Display(){
    if(Sound_value >= 10000){
        E3_dat_arr[3] = Sound_value / 10000;
        E3_dat_arr[4] = Sound_value % 10000 / 1000;
        E3_dat_arr[5] = Sound_value % 1000 / 100;
        E3_dat_arr[6] = Sound_value % 100 / 10;
        E3_dat_arr[7] = Sound_value % 10;
    }
    else if(Sound_value >= 1000 && Sound_value < 10000){
        E3_dat_arr[3] = 14;
        E3_dat_arr[4] = Sound_value / 1000;
        E3_dat_arr[5] = Sound_value % 1000 / 100;
        E3_dat_arr[6] = Sound_value % 100 / 10;
        E3_dat_arr[7] = Sound_value % 10;
    }
    else if(Sound_value >= 100 && Sound_value < 1000){
        E3_dat_arr[3] = 14;
        E3_dat_arr[4] = 14;
        E3_dat_arr[5] = Sound_value / 100;
        E3_dat_arr[6] = Sound_value % 100 / 10;
        E3_dat_arr[7] = Sound_value % 10;
    }
    else if(Sound_value >= 10 && Sound_value < 100){
        E3_dat_arr[3] = 14;
        E3_dat_arr[4] = 14;
        E3_dat_arr[5] = 14;
        E3_dat_arr[6] = Sound_value / 10;
        E3_dat_arr[7] = Sound_value % 10;
    }
    else{
        E3_dat_arr[3] = 14;
        E3_dat_arr[4] = 14;
        E3_dat_arr[5] = 14;
        E3_dat_arr[6] = 14;
        E3_dat_arr[7] = Sound_value;
    }
}

void P_Display(){
    P_dat_arr[2] = R_Parameter / 10;
    P_dat_arr[3] = R_Parameter % 10;
    if(B_Parameter >= 10){
        P_dat_arr[4] = 14;
        P_dat_arr[5] = B_Parameter / 10;
        P_dat_arr[6] = B_Parameter % 10;
    }
    else if(B_Parameter >= 0 && B_Parameter < 10){
        P_dat_arr[4] = 14;
        P_dat_arr[5] = 14;
        P_dat_arr[6] = B_Parameter;
    }
    else if(B_Parameter < 0 && B_Parameter > -10){
        P_dat_arr[4] = 14;
        P_dat_arr[5] = 13;
        P_dat_arr[6] = -B_Parameter;
    }
    else if(B_Parameter <= -10 && B_Parameter > -100){
        P_dat_arr[4] = 13;
        P_dat_arr[5] = -B_Parameter / 10;
        P_dat_arr[6] = -B_Parameter % 10;
    }
}

void LED_Display_Choose(){
    unsigned char i;
    switch(S8_cnt){
        case 0:
            if(Wait_flag || Run_flag){
                L1_Display();
                for(i = 0;i < 8;i++){
                    LED_Display_arr[i] = L1_dat_arr[i];
                }
            }
            else{
                L2_Display();
                for(i = 0;i < 8;i++){
                    LED_Display_arr[i] = L2_dat_arr[i];
                }
            }
            break;
        case 1:
            if(Run_flag){
                E1_Display();
                for(i = 0;i < 8;i++){
                    LED_Display_arr[i] = E1_dat_arr[i];
                }
            }
            if(Free_flag){
                for(i = 0;i < 8;i++){
                    LED_Display_arr[i] = E2_dat_arr[i];
                }
            }
            if(Wait_flag){
                E3_Display();
                for(i = 0;i < 8;i++){
                    LED_Display_arr[i] = E3_dat_arr[i];
                }
            }
            break;
        case 2:
            P_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = P_dat_arr[i];
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
        if((S8_cnt == 1 && com == 6 && Run_flag) || (S8_cnt == 2 && com == 2)){
            dat &= 0x7F;
        }
        SEG(dat);
        Delay50us();
    }
}