#include <STC15F2K60S2.H>
#include "Common.h"
#include "Timer.h"
#include "DS18B20.h"
#include "DS1302.h"
#include "KEY.h"
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
    0xBF,   //- 10
    0xC6,   //C 11
    0x89,   //H 12
    0x8E,   //F 13
    0x8C,   //P 14
    0x87,   //E 15
    0x88,   //A 16
    0xFF    //全灭 17
};

unsigned char Time_dat_arr[] = {17,17,10,17,17,10,17,17};       //时间界面
unsigned char Temp_Echo_arr[] = {11,17,17,17,10,17,17,17};      //温度回显
unsigned char Humidity_Echo_arr[] = {12,17,17,17,10,17,17,17};  //湿度回显
unsigned char Time_Echo_arr[] = {13,17,17,17,17,10,17,17};      //时间回显
unsigned char Parameter_dat_arr[] = {14,17,17,17,17,17,17,17};  //参数界面
unsigned char Temp_Humidity_arr[] = {15,17,17,17,17,10,17,17};  //温湿度界面
unsigned char LED_Display_arr[] = {17,17,17,17,17,17,17,17};

void Time_Display(){
    Time_dat_arr[0] = Time_value[0];
    Time_dat_arr[1] = Time_value[1];
    Time_dat_arr[3] = Time_value[2];
    Time_dat_arr[4] = Time_value[3];
    Time_dat_arr[6] = Time_value[4];
    Time_dat_arr[7] = Time_value[5];
}

void Temp_Echo_Display(){
    if(Temp_max >= 10){
        Temp_Echo_arr[2] = Temp_max / 10;
        Temp_Echo_arr[3] = Temp_max % 10;
    }
    else{
        Temp_Echo_arr[2] = 17;
        Temp_Echo_arr[3] = Temp_max;
    }
    
    if(Temp_Average >= 100){
        Temp_Echo_arr[5] = Temp_Average / 100;
        Temp_Echo_arr[6] = Temp_Average % 100 / 10;
        Temp_Echo_arr[7] = Temp_Average % 10;
    }
    else if(Temp_Average >= 10 && Temp_Average < 100){
        Temp_Echo_arr[5] = 17;
        Temp_Echo_arr[6] = Temp_Average / 10;
        Temp_Echo_arr[7] = Temp_Average % 10;
    }
    else{
        Temp_Echo_arr[5] = 17;
        Temp_Echo_arr[6] = 0;
        Temp_Echo_arr[7] = Temp_Average;
    }
}

void Humidity_Echo_Display(){
    if(NE555_max >= 10){
        Humidity_Echo_arr[2] = NE555_max / 10;
        Humidity_Echo_arr[3] = NE555_max % 10;
    }
    else{
        Humidity_Echo_arr[2] = 17;
        Humidity_Echo_arr[3] = NE555_max;
    }

    if(NE555_Average >= 100){
        Humidity_Echo_arr[5] = NE555_Average / 100;
        Humidity_Echo_arr[6] = NE555_Average % 100 / 10;
        Humidity_Echo_arr[7] = NE555_Average % 10;
    }
    else if(NE555_Average >= 10 && NE555_Average < 100){
        Humidity_Echo_arr[5] = 17;
        Humidity_Echo_arr[6] = NE555_Average / 10;
        Humidity_Echo_arr[7] = NE555_Average % 10;
    }
    else{
        Humidity_Echo_arr[5] = 17;
        Humidity_Echo_arr[6] = 0;
        Humidity_Echo_arr[7] = NE555_Average;
    }
}

void Time_Echo_Display(){
    Time_Echo_arr[1] = Time_num / 10;
    Time_Echo_arr[2] = Time_num % 10;
    Time_Echo_arr[3] = Time_dat[0];
    Time_Echo_arr[4] = Time_dat[1];
    Time_Echo_arr[6] = Time_dat[2];
    Time_Echo_arr[7] = Time_dat[3];
}

void Parameter_Display(){
    if(Temp_dat >= 10){
        Parameter_dat_arr[6] = Temp_dat / 10;
        Parameter_dat_arr[7] = Temp_dat % 10;
    }
    else{
        Parameter_dat_arr[6] = 17;
        Parameter_dat_arr[7] = Temp_dat;
    }
}

void Temp_Humidity_Display(){
    Temp_Humidity_arr[3] = Temp_value / 100;
    Temp_Humidity_arr[4] = Temp_value % 100 / 10;
    Temp_Humidity_arr[6] = NE555_value / 100;
    Temp_Humidity_arr[7] = NE555_value % 100 / 10;
    if(NE555_value < 200 || NE555_value > 2000){
        Temp_Humidity_arr[6] = 16;
        Temp_Humidity_arr[7] = 16;
    }
}

void LED_Display_Choose(){
    unsigned int S4 = S4_cnt % 3;
    unsigned int S5 = S5_cnt % 3;
    unsigned char i;
    
    if(Collect_Flag == 1){  
        LED_Display_flag = 1;
        LED_Display_cnt = 0;  
        Collect_Flag = 0;   
    }
    
    if(LED_Display_flag){
        Temp_Humidity_Display();
        for(i = 0;i < 8;i++){
            LED_Display_arr[i] = Temp_Humidity_arr[i];
        }
        if(LED_Display_cnt >= 3000){
            LED_Display_flag = 0;
            LED_Display_cnt = 0;
        } 
    }
    switch(S4){
        case 0:
            Time_Display();
            for(i = 0;i < 8;i++){
                LED_Display_arr[i] = Time_dat_arr[i];
            }
            break;
        case 1:
            switch(S5){
                case 0:
                    Temp_Echo_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Temp_Echo_arr[i];
                    }
                    break;
                case 1:
                    Humidity_Echo_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Humidity_Echo_arr[i];
                    }
                    break;
                case 2:
                    Time_Echo_Display();
                    for(i = 0;i < 8;i++){
                        LED_Display_arr[i] = Time_Echo_arr[i];
                    }
                    break;
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
    unsigned char com;
    unsigned char dat;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[LED_Display_arr[com]];
        if(S4_cnt % 3 == 1 && com == 6){
            if(S5_cnt % 3 == 0 || S5_cnt % 3 == 1){
                dat &= 0x7F;
            }
        }
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}