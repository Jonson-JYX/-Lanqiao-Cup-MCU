#include <STC15F2K60S2.H>
#include "Common.h"
#include "Timer.h"
#include "KEY.h"
#include "Ultrasound.h"

unsigned char LED_value = 0xFF;
bit LED1 = 0;

void LED_login(){
    LED_value = 0xFF;
    switch(S4_cnt){
        case 0:
            if(Sound_value > 255){
                LED_value = 0x00;
            }
            else{
                LED_value = (unsigned char)Sound_value;
            }
            LED_flag = 0;
            break;
        case 1:
            LED_value = 0x7F;
            LED_flag = 0;
            break;
        case 2:
            LED_flag = 1;
            if(LED_cnt >= 100){
                LED1 = !LED1;
                LED_cnt = 0;
            }
            LED_value = LED1 ? 0xFE : 0xFF;
            break;
    }
    LED(LED_value);
}