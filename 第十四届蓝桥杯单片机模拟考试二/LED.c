#include <STC15F2K60S2.H>
#include "Uart.h"
#include "Common.h"
#include "KEY.h"
#include "Timer.h"

unsigned char LED_value = 0xFF;
bit LED_flag = 0;
void LED_login(){
    if(recv_value == 'A' && password == 0){
        LED_value = 0xFE;
    }
    else if(recv_value == 'B' && password == 0){
        LED_value = 0xFD;
    }
    if(password == 1){
        if(LED_cnt >= 100){
            LED_flag = !LED_flag;
            LED_cnt = 0;
        }
        if(LED_flag == 0){
            LED_value &= 0xFB;
        }
        if(LED_flag == 1){
            LED_value |= 0x04;
        }
    }
    LED(LED_value);
}