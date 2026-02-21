#ifndef __DISPLAYS_H__
#define __DISPLAYS_H__

//声明一个数组
extern code unsigned char Seg_Table[17][8];

//数码管显示函数
void Seg_Display(unsigned char number);
#endif