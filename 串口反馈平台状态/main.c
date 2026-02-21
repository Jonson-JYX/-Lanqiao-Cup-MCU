#include <STC15F2K60S2.H>
#include "Common.h"
#include "LED.h"
#include "Uart.h"
#include "KEY.h"

void Init_MCU(){
    LED(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    SEG(0xFF);
    Uart_Init();
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        LED_login();
    }
}