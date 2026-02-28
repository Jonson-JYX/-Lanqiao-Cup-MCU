#ifndef NE555_H
#define NE555_H
extern int NE555_value;
extern int NE555_Hyperparameter;        //超限
extern int NE555_Calibration;           //校准
extern int NE555_now;
extern int NE555_max;
void Timer0_Init(void);
void NE555_login();
#endif // !NE555_H