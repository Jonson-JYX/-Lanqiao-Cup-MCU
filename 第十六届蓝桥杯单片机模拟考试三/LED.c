#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"

unsigned char LED_value = 0xFF;
void LED_login(){
    unsigned char dat = S4_cnt % 3;
    switch(dat){
        case 0:
            LED_value = 0xFE;
            break;
        case 1:
            LED_value = 0xFD;
            break;
        case 2:
            LED_value = 0xFB;
            break;
    }
    if(S5_flag){
        LED_value &= 0x7F;
    }
    else{
        LED_value |= 0x80;
    }
    LED(LED_value);
}