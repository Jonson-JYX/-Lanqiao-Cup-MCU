#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "Relay.h"
#include "LED.h"
#include "LED_Display.h"
#include "KEY.h"
#include "Timer.h"
#include "DS18B20.h"
#include "Ultrasound.h"
#include "PCF8591.h"

void Init_MCU(){
    LED(0xFF);
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer0_Init();
    S4_cnt = 0; //处于测距界面
    Unit_cnt = 0;   //显示单位为cm
    Sound_dat = 40; //距离参数
    Temp_dat = 30;  //温度参数
    Sound_speed = 340;  //传输速度
    Sound_Calib = 0;
    DAC_dat = 10;   //DAC输出下限值
    Unit_cnt = 0;       //单位转化标志位
    Parameters_cnt = 0; //参数界面转化标志位
    Setting_cnt = 0;    //工厂界面转化标志位
    S4_cnt = 0;
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        Sound_login();
        Temp_login();
        Relay_login();
        LED_login();
        DAC_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}