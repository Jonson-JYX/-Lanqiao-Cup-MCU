#include <STC15F2K60S2.H>
#include "Timer.h"
#include "Common.h"

void LED_login(){
    unsigned char led_out = 0xFF;
    
    if(LED1 == 1){
        led_out &= 0xFE;  
    }
    // L2对应P0.1（0=亮，1=灭）
    if(LED2 == 1){
        led_out &= 0xFD;  
    }
    // L8对应P0.7（0=亮，1=灭）
    if(LED8 == 1){
        led_out &= 0x7F;  
    }

    LED(led_out);
}