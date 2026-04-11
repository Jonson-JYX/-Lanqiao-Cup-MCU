#include <STC15F2K60S2.H>
#include "Delay.h"
#include "NE555.h"
#include "PCF8591.h"
#include "Ultrasound.h"
#include "Relay.h"
#include "EEPROM.h"

sbit S4 = P3^3;
sbit S5 = P3^2;
sbit S6 = P3^1;
sbit S7 = P3^0;

bit Sound_flag = 0;
bit NE555_flag = 0;

unsigned char S4_cnt = 0;
unsigned char S5_cnt = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    if(S4 == 0){
        Delay100ms();
        if(S4 == 0){
            key = 1;
            while(S4 == 0);
        }
    }
    if(S5 == 0){
        Delay100ms();
        if(S5 == 0){
            key = 2;
            while(S5 == 0);
        }
    }
    if(S6 == 0){
        Delay100ms();
        if(S6 == 0){
            key = 3;
            while(S6 == 0);
        }
    }
    if(S7 == 0){
        Delay100ms();
        if(S7 == 0){
            key = 4;
            while(S7 == 0);
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    switch(key){    //按键判断
        case 1: //S4按下
            S4_cnt = (S4_cnt + 1) % 4;
            break;
        case 2: //S5按下
            if(S4_cnt == 3){
                S5_cnt = (S5_cnt + 1) % 3;
            }
            break;
        case 3: //S6按下
            switch(S4_cnt){ //判断S4的位置
                case 2:
                    Sound_flag = !Sound_flag;
                    break;
                case 3:
                    switch(S5_cnt){ //判断S5的位置
                        case 0:
                            NE555_dat += 5;
                            if(NE555_dat > 120){
                                NE555_dat = 10;
                            }
                            break;
                        case 1:
                            Humidity_dat += 10;
                            if(Humidity_dat > 60){
                                Humidity_dat = 10;
                                }
                            break;
                        case 2:
                            Sound_dat += 1;
                            if(Sound_dat > 12){
                                Sound_dat = 1;
                            }
                            break;
                    }
            }
            break;
        case 4: //S7按下
            switch(S4_cnt){
                case 0:
                    NE555_flag = !NE555_flag;
                    break;
                case 1:
                    Relay_num = 0;
                    EEPROM_value[0] = Relay_num;
                    Write_EEPROM(EEPROM_value,0,1);
                    break;
                case 3:
                    switch(S5_cnt){
                        case 0:
                            NE555_dat -= 5;
                            if(NE555_dat < 10){
                                NE555_dat = 120;
                            }
                            break;
                        case 1:
                            Humidity_dat -= 10;
                            if(Humidity_dat < 10){
                                Humidity_dat = 60;
                                }
                            break;
                        case 2:
                            Sound_dat -= 1;
                            if(Sound_dat < 1){
                                Sound_dat = 12;
                            }
                            break;
                    }
            }
            break;
    }
}