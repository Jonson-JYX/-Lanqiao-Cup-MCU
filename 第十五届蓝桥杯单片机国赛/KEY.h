#ifndef KEY_H
#define KEY_H
extern bit Free_flag;       //空闲标志位
extern bit Wait_flag;       //等待标志位
extern bit Run_flag;        //运行标志位
extern bit coordinate_flag; //坐标接受标志位
extern bit Obstacle_flag;   //障碍物标志物
extern unsigned char key_value;
extern unsigned int Position_value[]; //坐标
extern unsigned char S8_cnt;
extern unsigned char S9_cnt;
extern unsigned int R_Parameter;
extern int B_Parameter;
void Key_Scan();
void Key_login();
#endif // !KEY_H