#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"

unsigned char LED_value = 0xFF;

void LED_login(){
    if(prepare_flag){
        LED_value = 0xFE;
    }
    if(setting_flag){
        LED_value = 0xFD;
    }
    if(competition_flag){
        LED_value = 0xFB;
    }
    if(result_flag){
        LED_value = 0xF7;
    }
    LED(LED_value);
}