
#include "pid.h"

/*
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
*/
 
/*************************************************
 *函数名称:void PID_Arg_Init(PID* sptr)                              
 *功    能:参数初始化                                     
 *参    数:PID* sptr                                     
 *返 回 值:void                                       
 *************************************************/
void PID_Arg_Init(PID* sptr)
{
	sptr->SumError = 0;         //误差累计 
	sptr->LastError = 0;        //上次偏差值
	sptr->PrevError = 0;        //上上次偏差值
	                            
	sptr->P = 0;                //比例常数
	sptr->I = 0;                //积分常数
	sptr->D = 0;                //微分常数
	                            
	sptr->SetPoint = 0;			//目标值
}
/*************************************************
 *函数名称:int PID_Contrl(PID* sptr,int NextPoint)                             
 *功    能:PID控制                                   
 *参    数:PID* sptr：上次参数  int NextPoint：当前实际值                                   
 *返 回 值:void                                       
 *************************************************/
int PID_Contrl(PID* sptr,int NextPoint)
{
	register int iError,iIncPid;
	
	iError = sptr->SetPoint - NextPoint;	//当前误差  设定的目标值和实际值的偏差
	
	iIncPid = sptr->P * iError				//增量计算
			  - sptr->I * sptr->LastError
			  + sptr->D * sptr->PrevError;
	
	/*存储误差  用于下次计算*/
	sptr->PrevError = sptr->LastError;
	sptr->LastError = iError;
	
	return iIncPid;							//返回增量值
}

