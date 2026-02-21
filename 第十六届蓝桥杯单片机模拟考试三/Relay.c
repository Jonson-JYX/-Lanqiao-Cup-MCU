#include <STC15F2K60S2.H>
#include "Timer.h"
#include "Common.h"
#include "KEY.h"
#include "PCF8591.h"
bit relay_done_flag = 0;
void Relay_login(){
    if(S5_flag == 0){
        relay_delay_flag = 0; // 停止计时
        time_cnt = 0;         // 清空计时数
        relay_done_flag = 0;  // 重置完成标志
        REY(0x00);            // 继电器断开
    }
    else{
        if(ADC_value < ADC_dat){
            if(!relay_done_flag){ // 未计时完成时，保持吸合
                REY(0xBF);
                relay_delay_flag = 1; // 启动计时
                // 仅当计时达到设定值时，执行断开
                if(time_cnt >= (int)time * 1000){
                    REY(0x00);            // 继电器断开
                    relay_delay_flag = 0; // 停止计时
                    time_cnt = 0;         // 清空计时
                    relay_done_flag = 1;  // 标记计时完成
                }
            }
        }
        else{
            // 采集值超过阈值，强制断开并重置所有标志
            relay_delay_flag = 0;
            time_cnt = 0;
            relay_done_flag = 0;
            REY(0x00);
        }
    }
}