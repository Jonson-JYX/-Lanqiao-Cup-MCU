#include <STC15F2K60S2.H>
#include "DS1302.h"
#include "KEY.h"
#include "NE555.h"
#include "Delay.h"
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
    0xBF,   //-
    0x8E,   //F
    0x8C,   //P
    0x89,   //H
    0x88,   //A
    0xFF,   //全灭
    0xC7    //L
};
unsigned char Freq_dat_arr[] = {11,15,15,15,15,15,15,15};   //频率
unsigned char Para_dat_arr[] = {12,1,15,15,15,15,15,15};    //参数
unsigned char Cali_dat_arr[] = {12,2,15,15,15,15,15,15};    //校准
unsigned char Time_dat_arr[] = {15,15,10,15,15,10,15,15};   //时间
unsigned char Freq_max_arr[] = {13,11,15,15,15,15,15,15};   //HF
unsigned char Time_max_arr[] = {13,14,15,15,15,15,15,15};   //HA
unsigned char LED_dat_arr[] = {15,15,15,15,15,15,15,15};   
unsigned char time_max_cache[6];

void Freq_dat_Display(){
    if(NE555_now >= 10000){
        Freq_dat_arr[3] = NE555_now / 10000;
        Freq_dat_arr[4] = NE555_now % 10000 / 1000;
        Freq_dat_arr[5] = NE555_now % 1000 / 100;
        Freq_dat_arr[6] = NE555_now % 100 / 10;
        Freq_dat_arr[7] = NE555_now % 10;
    }
    else if(NE555_now >= 1000 && NE555_now < 10000){
        Freq_dat_arr[3] = 15;
        Freq_dat_arr[4] = NE555_now / 1000;
        Freq_dat_arr[5] = NE555_now % 1000 / 100;
        Freq_dat_arr[6] = NE555_now % 100 / 10;
        Freq_dat_arr[7] = NE555_now % 10;
    }
    else if(NE555_now >= 100 && NE555_now < 1000){
        Freq_dat_arr[3] = 15;
        Freq_dat_arr[4] = 15;
        Freq_dat_arr[5] = NE555_now / 100;
        Freq_dat_arr[6] = NE555_now % 100 / 10;
        Freq_dat_arr[7] = NE555_now % 10;
    }
    else if(NE555_now >= 10 && NE555_now < 100){
        Freq_dat_arr[3] = 15;
        Freq_dat_arr[4] = 15;
        Freq_dat_arr[5] = 15;
        Freq_dat_arr[6] = NE555_now / 10;
        Freq_dat_arr[7] = NE555_now % 10;
    }
    else if(NE555_now >= 0 && NE555_now < 10){
        Freq_dat_arr[3] = 15;
        Freq_dat_arr[4] = 15;
        Freq_dat_arr[5] = 15;
        Freq_dat_arr[6] = 15;
        Freq_dat_arr[7] = NE555_now;
    }
    else if(NE555_now < 0){
        Freq_dat_arr[3] = 15;
        Freq_dat_arr[4] = 15;
        Freq_dat_arr[5] = 15;
        Freq_dat_arr[6] = 16;
        Freq_dat_arr[7] = 16;
    }
}

void Para_dat_Display(){
    Para_dat_arr[4] = NE555_PF / 1000;
    Para_dat_arr[5] = NE555_PF % 1000 / 100;
    Para_dat_arr[6] = NE555_PF % 100 / 10;
    Para_dat_arr[7] = NE555_PF % 10;
}

void Cali_dat_Display(){
    int dat = (-1) * NE555_cali;
    if(NE555_cali > 0){
        Cali_dat_arr[4] = 15;
        Cali_dat_arr[5] = NE555_cali / 100;
        Cali_dat_arr[6] = NE555_cali % 100 / 10;
        Cali_dat_arr[7] = NE555_cali % 10;
    }
    else if(NE555_cali == 0){
        Cali_dat_arr[4] = 15;
        Cali_dat_arr[5] = 15;
        Cali_dat_arr[6] = 15;
        Cali_dat_arr[7] = 0;
    }
    else{
        Cali_dat_arr[4] = 10;
        Cali_dat_arr[5] = dat / 100;
        Cali_dat_arr[6] = dat % 100 / 10;
        Cali_dat_arr[7] = dat % 10;
    }
}

void Time_dat_Display(){
    Time_dat_arr[0] = time_value[0];
    Time_dat_arr[1] = time_value[1];
    Time_dat_arr[2] = 10;
    Time_dat_arr[3] = time_value[2];
    Time_dat_arr[4] = time_value[3];
    Time_dat_arr[5] = 10;
    Time_dat_arr[6] = time_value[4];
    Time_dat_arr[7] = time_value[5];
}

void Freq_max_Display(){
    if(NE555_now > NE555_max && NE555_now >= 0){
		unsigned char *rtc_ptr = ReadRTC();
        NE555_max = NE555_now;
        time_max_cache[0] = rtc_ptr[0];
        time_max_cache[1] = rtc_ptr[1];
        time_max_cache[2] = rtc_ptr[2];
        time_max_cache[3] = rtc_ptr[3];
        time_max_cache[4] = rtc_ptr[4];
        time_max_cache[5] = rtc_ptr[5];
        time_max = time_max_cache;
    }
    if(NE555_max >= 10000){
        Freq_max_arr[3] = NE555_max / 10000;
        Freq_max_arr[4] = NE555_max % 10000 / 1000;
        Freq_max_arr[5] = NE555_max % 1000 / 100;
        Freq_max_arr[6] = NE555_max % 100 / 10;
        Freq_max_arr[7] = NE555_max % 10;
    }
    else if(NE555_max >= 1000 && NE555_max < 10000){
        Freq_max_arr[3] = 15;
        Freq_max_arr[4] = NE555_max / 1000;
        Freq_max_arr[5] = NE555_max % 1000 / 100;
        Freq_max_arr[6] = NE555_max % 100 / 10;
        Freq_max_arr[7] = NE555_max % 10;
    }
    else if(NE555_max >= 100 && NE555_max < 1000){
        Freq_max_arr[3] = 15;
        Freq_max_arr[4] = 15;
        Freq_max_arr[5] = NE555_max / 100;
        Freq_max_arr[6] = NE555_max % 100 / 10;
        Freq_max_arr[7] = NE555_max % 10;
    }
    else if(NE555_max >= 10 && NE555_max < 100){
        Freq_max_arr[3] = 15;
        Freq_max_arr[4] = 15;
        Freq_max_arr[5] = 15;
        Freq_max_arr[6] = NE555_max / 10;
        Freq_max_arr[7] = NE555_max % 10;
    }
    else if(NE555_max >= 0 && NE555_max < 10){
        Freq_max_arr[3] = 15;
        Freq_max_arr[4] = 15;
        Freq_max_arr[5] = 15;
        Freq_max_arr[6] = 15;
        Freq_max_arr[7] = NE555_max;
    }
}

void Time_max_Display(){
    Time_max_arr[2] = time_max[0];
    Time_max_arr[3] = time_max[1];
    Time_max_arr[4] = time_max[2];
    Time_max_arr[5] = time_max[3];
    Time_max_arr[6] = time_max[4];
    Time_max_arr[7] = time_max[5];
}

void LED_Display_Choose(){
    unsigned char i;
    if(S4_cnt % 4 == 0){
        Freq_dat_Display();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Freq_dat_arr[i];
        }
    }
    if(S4_cnt % 4 == 1 && S5_para_cnt % 2 == 0){
        Para_dat_Display();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Para_dat_arr[i];
        }
    }
    if(S4_cnt % 4 == 1 && S5_para_cnt % 2 == 1){
        Cali_dat_Display();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Cali_dat_arr[i];
        }
    }
    if(S4_cnt % 4 == 2){
        Time_dat_Display();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Time_dat_arr[i];
        }
    }
    if(S4_cnt % 4 == 3 && S5_echo_cnt % 2 == 0){
        Freq_max_Display();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Freq_max_arr[i];
        }
    }
    if(S4_cnt % 4 == 3 && S5_echo_cnt % 2 == 1){
        Time_max_Display();
        for(i = 0;i < 8;i++){
            LED_dat_arr[i] = Time_max_arr[i];
        }
    }
}

void LED_Display_Show(){
    unsigned char com;
    unsigned char dat;
    for(com = 0;com < 8;com++){
        SEG(0xFF);
        COM(1<<com);
        dat = SEG_Table[LED_dat_arr[com]];
        SEG(dat);
        Delay50us();
    }
    SEG(0xFF);
    COM(0xFF);
}