#ifndef __PID_H_
#define __PID_H_
#endif

//增量式PID
typedef struct{
	int SetPoint;		//目标值
	long SumError;		//误差累计
	
	float P;			//比例常数
	float I;			//积分常数
	float D;			//微分常数
	
	int LastError;		//上次偏差值
	int PrevError;		//上上次偏差值
}PID;

void PID_Arg_Init(PID* sptr);
int PID_Contrl(PID* sptr,int NextPoint);