#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "EEPROM.h"
#include "KEY.h"
#include "LED.h"
#include "Relay.h"
#include "Timer.h"
#include "LED_Display.h"

void Init_MCU(){
    unsigned char i;
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer0_Init();
    key_down = 1;    
    S16_flag = 0;    
    S12_flag = 0;    
    password = 0;   
    first_flag = 0;  // 显式初始化，避免随机值
    Key_flag = 0;    // 定时器按键计数标志清零
    LED_flag = 0;    // LED计数标志清零
    key_num = 0;     // 密码对比计数清零
    num = 0;         // 密码输入位数清零
    key_value = 0;   // 按键值清零
    // 密码数组重置
    for(i = 0;i < 6;i++){
        key_password[i] = 16;
        read_password[i] = 16;
    }
}

void main(){
    unsigned char i;
    Read_EEPROM(EEPROM_value,0,6);
    for(i = 0;i < 6;i++){
        read_password[i] = EEPROM_value[i];
    }
    Init_MCU();
    while(1){
        Key_login();
        LED_login();
        Relay_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}