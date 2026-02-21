#include <STC15F2K60S2.H>
#include "KEY.h"
#include "DS18B20.h"
#include "Common.h"

//LED逻辑函数
void LED_login(){
    if(S4_cnt % 3 == 0){
        if(S5_cnt % 2 == 0 && temp_now + cali_dat * 10 > temp_dat * 10){
            LED(0x76);
        }
        if(S5_cnt % 2 == 0 && temp_now + cali_dat * 10 <= temp_dat * 10){
            LED(0xF6);
        }
        if(S5_cnt % 2 == 1 && temp_now + cali_dat * 10 >= temp_dat * 10){
            LED(0xEE);
        }
        if(S5_cnt % 2 == 1 && temp_now + cali_dat * 10 < temp_dat * 10){
            LED(0x6E);
        }
    }
    if(S4_cnt % 3 == 1){
        if(S5_cnt % 2 == 0 && temp_now + cali_dat * 10 > temp_dat * 10){
            LED(0x75);
        }
        if(S5_cnt % 2 == 0 && temp_now + cali_dat * 10 <= temp_dat * 10){
            LED(0xF5);
        }
        if(S5_cnt % 2 == 1 && temp_now + cali_dat * 10 >= temp_dat * 10){
            LED(0xED);
        }
        if(S5_cnt % 2 == 1 && temp_now + cali_dat * 10 < temp_dat * 10){
            LED(0x6D);
        }
    }
    if(S4_cnt % 3 == 2){
        if(S5_cnt % 2 == 0 && temp_now + cali_dat * 10 > temp_dat * 10){
            LED(0x73);
        }
        if(S5_cnt % 2 == 0 && temp_now + cali_dat * 10 <= temp_dat * 10){
            LED(0xF3);
        }
        if(S5_cnt % 2 == 1 && temp_now + cali_dat * 10 >= temp_dat * 10){
            LED(0xEB);
        }
        if(S5_cnt % 2 == 1 && temp_now + cali_dat * 10 < temp_dat * 10){
            LED(0x6B);
        }
    }
}