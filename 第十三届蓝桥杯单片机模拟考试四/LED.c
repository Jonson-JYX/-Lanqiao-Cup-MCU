#include <STC15F2K60S2.H>
#include "PCF8591.h"
#include "Common.h"
#include "Timer.h"

bit LED_flag = 0;

void LED_login(){
    if(Vol_value1 >= 200 && Vol_value1 <= 300){
        LED(0xFE);
    }
    else{
        if(LED_cnt == 99){
            if(LED_flag == 0){
                LED(0xFE);
                LED_flag = 1;
            }
            else{
                LED(0xFF);
                LED_flag = 0;
            }
        } 
    }
}