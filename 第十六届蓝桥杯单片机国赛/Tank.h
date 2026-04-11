#ifndef Tank_H
#define Tank_H
extern float H1;
extern float H2;
extern unsigned char S;
extern float R;
extern float L;
extern float W;
extern float H;
extern unsigned int Wainning; //报警标志
extern bit Wainning_flag1; //报警状态标志
extern bit Wainning_flag2; //报警状态标志
extern bit Wainning_flag3; //报警状态标志
extern bit Wainning_flag4; //报警状态标志
extern bit Wainning_flag5; //报警状态标志
void S_Scan();
void Tank_login();
#endif // !Tank_H