#include <STC15F2K60S2.H>
#include "Common.h"
#include "Ultrasound.h"
#include "EEPROM.h"

unsigned char Relay_value = 0x00;
unsigned int Relay_num = 0;
bit Relay_flag = 0;

void Relay_login(){
    if(Sound_value > Sound_dat * 10){
        Relay_flag = 1;
    }
    if(Relay_flag){
        Relay_value = 0xBF;
        if(Sound_value < Sound_dat){
            Relay_num++;
            EEPROM_value[0] = Relay_num;
            Write_EEPROM(EEPROM_value,0,1);
            Relay_value = 0x00;
            Relay_flag = 0;
        }
    }
    REY(Relay_value);
}