#ifndef NE555_H
#define NE555_H
extern int NE555_value; 
extern int NE555_max;
extern int NE555_PF;    //  超限
extern int NE555_cali;  //  校正
extern int NE555_now;
void Timer0_Init(void);
#endif // !NE555_H