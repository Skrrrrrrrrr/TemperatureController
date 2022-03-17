#ifndef __KalmanFilter_H
#define __KalmanFilter_H

#include "config.h"

//1. 结构体类型定义
typedef struct
{
    float LastP; //上次估算协方差 初始化值为0.02
    float Now_P; //当前估算协方差 初始化值为0
    float out;   //卡尔曼滤波器输出 初始化值为0
    float Kg;    //卡尔曼增益 初始化值为0
    float Q;     //过程噪声协方差 初始化值为0.001
    float R;     //观测噪声协方差 初始化值为0.543
} KFP;           //Kalman Filter parameter

typedef struct
{
    KFP k0;
    KFP k1;
    KFP k2;
    KFP k3;
    KFP k4;
    KFP k5;
    KFP k6;
    KFP k7;

} KFPs;

extern KFP code _InitialKFP;

/*
//2. 以高度为例 定义卡尔曼结构体并初始化参数
KFP _InitialKFP={0.02,0,0,0,0.001,0.543};
*/

/**
 *卡尔曼滤波器
 *@param KFP *kfp 卡尔曼结构体参数
 *   float input 需要滤波的参数的测量值（即传感器的采集值）
 *@return 滤波后的参数（最优值）
 */
float kalmanFilter(KFP *kfp, float input);

#endif
