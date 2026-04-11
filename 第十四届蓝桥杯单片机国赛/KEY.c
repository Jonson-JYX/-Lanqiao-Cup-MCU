#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "DS18B20.h"
#include "Ultrasound.h"
#include "PCF8591.h"
#include "Timer.h"

unsigned char Unit_cnt = 0;       //单位转化标志位
unsigned char Parameters_cnt = 0; //参数界面转化标志位
unsigned char Setting_cnt = 0;    //工厂界面转化标志位
unsigned char S4_cnt = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P44 = 0;P42 = 1;
    if(P33 == 0){   //s4
        Delay100ms();
        if(P33 == 0){
            key = 1;
            while(P33 == 0);
        }
    }
    else if(P32 == 0){   //s5
        Delay100ms();
        if(P32 == 0){
            key = 2;
            while(P32 == 0);
        }
    }
    P44 = 1;P42 = 0;
    if(P32 == 0 && P33 == 0){   //S8 && S9
        Delay100ms();
        if(P32 == 0 && P33 == 0){
            key = 3;
            while(P32 == 0 && P33 == 0);
        }
    }
    else if(P33 == 0){   //S8
        Delay100ms();
        if(P33 == 0){
            key = 4;
            while(P33 == 0);
        }
    }
    else if(P32 == 0){   //S9
        Delay100ms();
        if(P32 == 0){
            key = 5;
            while(P32 == 0);
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    if(!Record_flag){
        switch(key){    //判断哪个按键按下
            case 1: //S4
                S4_cnt = (S4_cnt + 1) % 3;
                if(S4_cnt != 0){ //不在测距界面
                    Unit_cnt = 0;
                }
                if(S4_cnt != 1){ //不在参数界面
                    Parameters_cnt = 0;
                }
                if(S4_cnt != 2){ //不在工厂界面
                    Setting_cnt = 0;
                }
                break;
            case 2: //S5
                switch(S4_cnt){ //判断界面
                    case 0: //测距界面
                    Unit_cnt = (Unit_cnt + 1) % 2;
                    break;
                    case 1: //参数界面
                        Parameters_cnt = (Parameters_cnt + 1) % 2;
                        break;
                    case 2: //工厂界面
                        Setting_cnt = (Setting_cnt + 1) % 3;
                        break;
                }
                break;
            case 3: //S8 && S9同时按下
                S4_cnt = 0; //处于测距界面
                Unit_cnt = 0;   //显示单位为cm
                Sound_dat = 40; //距离参数
                Temp_dat = 30;  //温度参数
                Sound_speed = 340;  //传输速度
                DAC_dat = 10;   //DAC输出下限值
                break;
            case 4: //S8
                switch(S4_cnt){ //判断界面
                    case 0: //测距界面
                        Record_flag = 1;
                        break;
                    case 1: //参数界面
                        switch(Parameters_cnt){ //参数的子界面
                            case 0: //距离参数界面
                                if(Sound_dat < 90){
                                    Sound_dat += 10;
                                }
                                break;
                            case 1: //温度参数界面
                                if(Temp_dat < 80){
                                    Temp_dat += 1;
                                }
                                break;
                        }
                        break;
                    case 2: //工厂界面
                        switch(Setting_cnt){ //工厂的子界面
                            case 0: //校准值设置界面
                                if(Sound_Calib < 90){
                                    Sound_Calib += 5;
                                }
                                break;
                            case 1: //介质设置界面
                                if(Sound_speed < 9990){
                                    Sound_speed += 10;
                                }
                                break;
                            case 2: //DAC输出设置界面
                                if(DAC_dat < 20){
                                    DAC_dat += 1;
                                }
                                break;
                        }
                        break;
                }
                break;  
            case 5: //S9
                switch(S4_cnt){ //判断界面
                    case 0: //测距界面
                        Output_flag = 1;
                        break;
                    case 1: //参数界面
                        switch(Parameters_cnt){ //参数的子界面
                            case 0: //距离参数界面
                                if(Sound_dat > 10){
                                    Sound_dat -= 10;
                                }
                                break;
                            case 1: //温度参数界面
                                if(Temp_dat > 0){
                                    Temp_dat -= 1;
                                }
                                break;
                        }
                        break;
                    case 2: //工厂界面
                        switch(Setting_cnt){ //工厂的子界面
                            case 0: //校准值设置界面
                                if(Sound_Calib > -90){
                                    Sound_Calib -= 5;
                                }
                                break;
                            case 1: //介质设置界面
                                if(Sound_speed > 10){
                                    Sound_speed -= 10;
                                }
                                break;
                            case 2: //DAC输出设置界面
                                if(DAC_dat > 1){
                                    DAC_dat -= 1;
                                }
                                break;
                        }
                        break;
                }
                break;
        }
    }
}