#include <STC15F2K60S2.H>
#include "Timer.h"
#include "Common.h"
#include "NE555.h"
#include "PCF8591.h"
#include "Ultrasound.h"
#include "Uart.h"
#include "KEY.h"
#include "Relay.h"
#include "LED_Display.h"
#include "LED.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    LED(0xFF);
    Timer1_Init();
    Timer0_Init();
    Uart1_Init();
}

void main(){
    Init_MCU();
    while(1){
        Key_Scan();
        Key_login();
        Uart_login();
        Sound_login();
        Light_login();
        Relay_login();
        NE555_login();
        LED_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}