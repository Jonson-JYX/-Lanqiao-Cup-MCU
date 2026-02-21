#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Uart.h"

bit password = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P33 = 0;P32 = 1;
    if(P44 == 0){   //S4
        Delay100ms();
        while(P44 == 0){
            key = 1;
        }
    }
    if(P35 == 0){   //S12
        Delay100ms();
        while(P35 == 0){
            key = 2;
        }
    }
    P33 = 1;P32 = 0;
    if(P44 == 0){ //s5
        Delay100ms();
        while(P44 == 0){
            key = 3;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    switch(key){
        case 1:
            password = 1;
            break;
        case 2:
            if(recv_value == 'A'){
                Send_Temp_login();
            }
            if(recv_value == 'B'){
                Send_Voltage_login();
            }
            break;
        case 3:
            password = 0;
            break;
    }
}