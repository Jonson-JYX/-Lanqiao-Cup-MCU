#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "DS18B20.h"
#include "PCF8591.h"
#include "Sound.h"
#include "Timer.h"
#include "Relay.h"

unsigned char key_value = 0;    //按键值
unsigned char S4_cnt = 0;      //S4计数值
unsigned char S5_cnt = 0;      //S5计数值

void Key_Scan(){
    P44 = 0;P42 = 1;
    if(P33 == 0){   //S4
        Delay50us();
        if(P33 == 0){
            key_value = 1;
            while(P33 == 0);
        }
    }
    else if(P32 == 0){   //S5
        Delay50us();
        if(P32 == 0){
            key_value = 2;
            while(P32 == 0);
        }
    }
    P44 = 1;P42 = 0;
    if(P33 == 0 && P32 == 0){   //S8和S9同时按下
        Delay50us();
        if(P33 == 0 && P32 == 0){
            key_value = 5;
            while(P33 == 0 || P32 == 0);
        }
    }
    else if(P33 == 0){   //S8
        Delay50us();
        if(P33 == 0){
            key_value = 3;
            while(P33 == 0);
        }
    }
    else if(P32 == 0){   //S9
        Delay50us();
        if(P32 == 0){
            key_value = 4;
            while(P32 == 0);
        }
    }
}

void Key_login(){
    Key_Scan();
    switch(key_value){
        case 1:
            S4_cnt = (S4_cnt + 1) % 4;
            break;
        case 2:
            if(S4_cnt == 2){
                S5_cnt = (S5_cnt + 1) % 2;
            }
            break;
        case 3:
            if(S4_cnt == 2){
                switch(S5_cnt){
                    case 0:
                        if(temp_dat < 80){
                            temp_dat += 1;
                        }
                        break;
                    case 1:
                        if(sound_dat < 80){
                            sound_dat += 5;
                        }
                        break;
                }
            }
            break;
        case 4:
            if(S4_cnt == 2){
                switch(S5_cnt){
                    case 0:
                        if(temp_dat > 10){
                            temp_dat -= 1;
                        }
                        break;
                    case 1:
                        if(sound_dat > 10){
                            sound_dat -= 5;
                        }
                        break;
                }
            }
            break;
        case 5:
            relay_cnt = 0;
            break;
    }
    key_value = 0;
}