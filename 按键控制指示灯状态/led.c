#include <stc15f2k60s2.h>
#include "led.h"
#include "delay.h"
#include "common.h"

//单个LED反转函数
unsigned char LED_Reverse(unsigned char num, unsigned char value){
	//获取第几个LED控制变量
	unsigned char number = num;
	//获取当前LED的状态
	unsigned char LED_Value = value;
	//先判断要反转的LED处于的状态
	unsigned char status = (LED_Value >> num) & 1;
	//判断LED为亮则进行灭操作
	if(status == 1){
		//返回反转后的LED状态
		return LED_Value & ~(1 << num);
	}
	//判断LED为灭则进行亮操作
	if(status == 0){
		return LED_Value | (1 << num);
	}
	return 0;
}

//单个LED闪烁函数
unsigned char LED_Flash(unsigned char num, unsigned char value){
	//获取第几个LED控制变量
	unsigned char number = num;
	//获取当前LED的状态
	unsigned char LED_Value = value;
	//先判断要反转的LED处于的状态
	unsigned char status = (LED_Value >> num) & 1;
	//判断LED为亮则进行灭操作
	if(status == 1){
		LED_Value &= ~(1 << num);
	}
	//判断LED为灭则进行亮操作
	if(status == 0){
		LED_Value |= (1 << num); 
	}
	LED(LED_Value);
	Delay100ms();
	return LED_Value;
}