#include <stc15f2k60s2.h>

//LED控制程序
void LED(x){
	//P0口写入的数据
	P0 = x;
	
	//打开锁存器
	//实现Y4C锁存器LE=1 -> 打开指示灯锁存器
	//此时P0口数据同步到LED
	P2 = (P2&0x1F | 0X80);

	//关闭锁存器
	P2 &= 0x1F;
}