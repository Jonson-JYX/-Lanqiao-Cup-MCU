#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"

unsigned char LED_value = 0xFF;

void LED_login(){
    unsigned char dat = S12_cnt % 2;
    switch(dat){
        case 0:
            LED_value = 0xFE;
            break;
        case 1:
            LED_value = 0xFD;
            break;
    }
    LED(LED_value);
}