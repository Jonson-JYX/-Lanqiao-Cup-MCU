#include <STC15F2K60S2.H>
#include "Delay.h"
#include "PCF8591.h"
#include "Timer.h"

sbit S4 = P3^3;
sbit S5 = P3^2;
sbit S6 = P3^1;
sbit S7 = P3^0;

bit S4_flag = 0;
bit S5_flag = 0;
bit S6_flag = 0;
bit S7_flag = 0;

bit prepare_flag = 1;
bit setting_flag = 0;
bit competition_flag = 0;
bit result_flag = 0;
unsigned int Time_value = 5;
unsigned int Time_dat = 5;
unsigned char contestant_num = 0;   //淘汰选手编号

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
    if(prepare_flag){   //准备界面逻辑
        if(S4_flag && S5_flag && S6_flag && S7_flag){
            prepare_flag = 0;
            competition_flag = 1;
        }
        if(Light_value < ADC_value){
            prepare_flag = 0;
            setting_flag = 1;
        }
    }
    if(setting_flag){   //设置界面逻辑
        if(Light_value >= ADC_value){
            prepare_flag = 1;
            setting_flag = 0;
        }
    }
    if(competition_flag){   //比赛界面逻辑
        Time_flag = 1;
        if(Time_cnt >= Time_value * 1000){
            Time_flag = 0;
            Time_cnt = 0;
            contestant_num = 0;
            competition_flag = 0;
            result_flag = 1;
            Time_dat = Time_value;
        }
        if(Time_cnt % 1000 == 0 && Time_cnt != 0){
            Time_dat--;
        }
        if(S4_flag == 0){
            Time_flag = 0;
            Time_cnt = 0;
            contestant_num = 1;
            competition_flag = 0;
            result_flag = 1;
            Time_dat = Time_value;
        }
        else if(S5_flag == 0){
            Time_flag = 0;
            Time_cnt = 0;
            contestant_num = 2;
            competition_flag = 0;
            result_flag = 1;
            Time_dat = Time_value;
        }
        else if(S6_flag == 0){
            Time_flag = 0;
            Time_cnt = 0;
            contestant_num = 3;
            competition_flag = 0;
            result_flag = 1;
            Time_dat = Time_value;
        }
        else if(S7_flag == 0){
            Time_flag = 0;
            Time_cnt = 0;
            contestant_num = 4;
            competition_flag = 0;
            result_flag = 1;
            Time_dat = Time_value;
        }
    }
    if(result_flag){    //结果界面逻辑
        if(!S4_flag && !S5_flag && !S6_flag && !S7_flag){
            result_flag = 0;
            prepare_flag = 1;
        }
    }
    switch(key){
        case 1:
            if(prepare_flag || competition_flag || result_flag){
                S4_flag = !S4_flag;
            }
            break;
        case 2:
            if(prepare_flag || competition_flag || result_flag){
                S5_flag = !S5_flag;
            }
            break;
        case 3:
            if(prepare_flag || competition_flag || result_flag){
                S6_flag = !S6_flag;
            }
            if(setting_flag){
                if(Time_value > 0){
                    Time_value--;
                    Time_dat = Time_value;
                }
            }
            break;
        case 4:
            if(prepare_flag || competition_flag || result_flag){
                S7_flag = !S7_flag;
            }
            if(setting_flag){
                if(Time_value < 99){
                    Time_value++;
                    Time_dat = Time_value;
                }
            }
            break;
    }
}