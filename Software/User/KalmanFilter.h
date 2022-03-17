#ifndef __KalmanFilter_H
#define __KalmanFilter_H

#include "config.h"

//1. �ṹ�����Ͷ���
typedef struct
{
    float LastP; //�ϴι���Э���� ��ʼ��ֵΪ0.02
    float Now_P; //��ǰ����Э���� ��ʼ��ֵΪ0
    float out;   //�������˲������ ��ʼ��ֵΪ0
    float Kg;    //���������� ��ʼ��ֵΪ0
    float Q;     //��������Э���� ��ʼ��ֵΪ0.001
    float R;     //�۲�����Э���� ��ʼ��ֵΪ0.543
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
//2. �Ը߶�Ϊ�� ���忨�����ṹ�岢��ʼ������
KFP _InitialKFP={0.02,0,0,0,0.001,0.543};
*/

/**
 *�������˲���
 *@param KFP *kfp �������ṹ�����
 *   float input ��Ҫ�˲��Ĳ����Ĳ���ֵ�����������Ĳɼ�ֵ��
 *@return �˲���Ĳ���������ֵ��
 */
float kalmanFilter(KFP *kfp, float input);

#endif
