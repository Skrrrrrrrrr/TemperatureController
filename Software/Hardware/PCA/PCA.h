#include "config.h"          //ͨ������ͷ�ļ�

extern unsigned char PCA_MODE;  //PCAģʽ
extern unsigned int PCA0_n;     //PCA0ͨ������ֵ
extern unsigned int PCA1_n;     //PCA1ͨ������ֵ
extern unsigned int PCA2_n;     //PCA2ͨ������ֵ
extern unsigned int PCA3_n;     //PCA3ͨ������ֵ

extern int PCA0_count;
extern int PCA1_count;
extern int PCA2_count;
extern int PCA3_count;

extern unsigned int PCA0_HZ;
extern unsigned int PCA1_HZ;
extern unsigned int PCA2_HZ;
extern unsigned int PCA3_HZ;

extern unsigned char PCA0_IO;
extern unsigned char PCA1_IO;
extern unsigned char PCA2_IO;
extern unsigned char PCA3_IO;

extern unsigned int PCA0_FallTime;
extern unsigned int PCA1_FallTime;
extern unsigned int PCA2_FallTime;
extern unsigned int PCA3_FallTime;

extern void PCA_Pwm_init(int pin,int freq,int pwm); //��ʼ��PWM���
extern void PCA_Pwm_change(int pin,int pwm);        //�ı�PWMռ��
extern void PCA_Pulse_init(int pin,unsigned long freq);       //��ʼ�������������
extern void PCA_Count_init(int pin,char dirIO);     //��ʼ���������
extern int PCA_Count_get(int n);                    //��ȡĳͨ���������ֵ
extern void PCA_Width_init(int pin);                //��ʼ�������Ȳ���
extern unsigned int PCA_Width_get(int pin);                  //��ȡ������

