#include <STC15F2K60S2.H>
#include "Delay.h"
#include "PCF8591.h"
#include "DS18B20.h"
#include "Relay.h"
#include "Beep.h"
#include "Uart.h"
#include "LED.h"
#include "LED_Display.h"
#include "Timer.h"
#include "KEY.h"
#include "Common.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    LED(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer0_Init();
    Uart1_Init();
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        if(recv_flag == 1 && password == 0){
            Recv_login();
            recv_flag = 0;
        }
        ADC_login();
        Temp_login();
        LED_login();
        Beep_login();
        Relay_login();
        LED_Display_Choose();
        LED_Display_Show();
        LED_Display_Show();
        LED_Display_Show();
    }
}