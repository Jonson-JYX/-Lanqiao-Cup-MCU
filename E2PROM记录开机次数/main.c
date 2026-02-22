#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "EEPROM.h"
#include "KEY.h"
#include "Uart.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    LED(0xFF);
    BUZ(0x00);
    REY(0x00);
    Uart1_Init();
}

void main(){
    Read_EEPROM(EEPROM_value,0,1);
    num = EEPROM_value[0];
    Reset_Count_Inc();
    Init_MCU();
    while(1){
        Key_login();
    }
}