#include <STC15F2K60S2.H>
#include "Timer.h"
#include "KEY.h"
#include "DS18B20.h"
#include "NE555.h"
#include "Common.h"

unsigned char LED_value = 0xFF;
bit LED = 0;

void LED_login(){
    if(S4_cnt % 3 == 0){
        LED_value = 0xFE;
    }
    if(S4_cnt % 3 == 1){
        LED_value = 0xFD;
    }
    if(Temp_value > Temp_dat){
        LED_flag = 1;
        if(LED_cnt >= 100){
            LED = !LED;
        }
        if(LED){
            LED_value &= 0xFB;
        }
        else{
            LED_value |= 0xEC;
        }
    }
    if(NE555_value < 200 || NE555_value > 2000){
        LED_value &= 0xEF;
    }
    else{
        LED_value |= 0xF8;
    }
    LED(LED_value);
}