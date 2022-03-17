#include "config.h"          //通用配置头文件

extern unsigned char PCA_MODE;  //PCA模式
extern unsigned int PCA0_n;     //PCA0通道计数值
extern unsigned int PCA1_n;     //PCA1通道计数值
extern unsigned int PCA2_n;     //PCA2通道计数值
extern unsigned int PCA3_n;     //PCA3通道计数值

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

extern void PCA_Pwm_init(int pin,int freq,int pwm); //初始化PWM输出
extern void PCA_Pwm_change(int pin,int pwm);        //改变PWM占空
extern void PCA_Pulse_init(int pin,unsigned long freq);       //初始化高速脉冲输出
extern void PCA_Count_init(int pin,char dirIO);     //初始化脉冲计数
extern int PCA_Count_get(int n);                    //获取某通道脉冲计数值
extern void PCA_Width_init(int pin);                //初始化脉冲宽度测量
extern unsigned int PCA_Width_get(int pin);                  //获取脉冲宽度

