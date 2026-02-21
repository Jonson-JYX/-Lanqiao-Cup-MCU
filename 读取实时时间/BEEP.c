#include <stc15f2k60s2.h>
#include "Common.h"
#include "DS1302.h"
#include "Delay.h"
#include "BEEP.h"
#include "Uart.h"

bit beep_flag = 0;        
bit beep_running = 0;     
#define BEEP_DURATION 20  
unsigned char beep_cnt = 0; // 计数器

// 定时器0相关1ms中断
unsigned int beep_timer = 0; // 毫秒级计时变量
bit beep_2s_flag = 0;        // 2秒计时完成标志

// 声明外部变量
extern bit timer_time_set;

// 定时器0初始化函数（1ms中断，12MHz晶振）
void Timer0_Init(void) {
    TMOD &= 0xF0;  // 清空定时器0模式位
    TMOD |= 0x01;  // 定时器0工作在模式1（16位）
    TL0 = 0x18;    // 1ms定时初值（12MHz）
    TH0 = 0xFC;    // 65536 - 1000 = 64536 → 0xFC18
    TF0 = 0;       // 清除溢出标志
    TR0 = 1;       // 启动定时器0
    ET0 = 1;       // 使能定时器0中断
    EA = 1;        // 开启总中断
}

// 定时器0中断服务函数（1ms触发一次）
void Timer0_ISR(void) interrupt 1 {
    TL0 = 0x18;    // 重新加载初值，保证计时精度
    TH0 = 0xFC;
    
    // 仅在蜂鸣器运行时累加计时
    if(beep_running) {
        beep_timer++;
        if(beep_timer >= 2000) { // 累计2000ms（2秒）
            beep_2s_flag = 1;    // 置2秒完成标志
            beep_timer = 0;      // 重置计时
        }
    }
}

void BEEP(){
    unsigned char *time_rtc = ReadRTC(); 
    unsigned char *timer_time = get_time_array(); 
    
    // 时间转换逻辑
    unsigned char curr_hour = time_rtc[0] * 10 + time_rtc[1];
    unsigned char curr_min = time_rtc[3] * 10 + time_rtc[4];
    unsigned char curr_sec = time_rtc[6] * 10 + time_rtc[7];
    
    unsigned char timer_hour = timer_time[0];
    unsigned char timer_min = timer_time[1];
    unsigned char timer_sec = timer_time[2];
    
    // 时间匹配触发逻辑
    if(timer_time_set && !beep_running && 
       (curr_hour == timer_hour) && (curr_min == timer_min) && (curr_sec == timer_sec))
    {
        beep_flag = 1;
        beep_running = 1;
        beep_cnt = 0;
        timer_time_set = 0;
    }
	   
    // 判断2秒完成标志
    if(beep_flag){
        BUZ(0xFF); //打开蜂鸣器
        
        // 检测2秒计时完成，而非阻塞延时
        if(beep_2s_flag) {
            beep_flag = 0;
            beep_running = 0;
            beep_2s_flag = 0; // 清空完成标志
            BUZ(0x00);       // 关闭蜂鸣器
            beep_cnt = 0;    // 重置计数器
        }
    }
}