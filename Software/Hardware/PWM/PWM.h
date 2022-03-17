#include "config.h"

extern unsigned int PWM0_T; 
extern unsigned int PWM1_T; 
extern unsigned int PWM2_T; 
extern unsigned int PWM3_T; 
extern unsigned int PWM4_T; 
extern unsigned int PWM5_T; 
extern unsigned int PWM6_T; 
extern unsigned int PWM7_T; 
extern unsigned char STORE; 

extern void PWM_init(int pin,long f,int pwm); //PWM模块初始化函数
/*
取值：pin:要初始化的引脚端口 例：10 为 将对应的PWM通道初始化到P10口对应引脚
														     22 为 将对应的PWM通道初始化到P22口对应引脚 
																 64 为 将对应的PWM通道初始化到P64口对应引脚
													   注意：STC8单片机仅有P1,P2,P6口具有PWM功能，不能初始化成其他端口的引脚
取值：f:PWM输出频率        例：  取值范围：50Hz-100KHz   
													 注意：所有PWM通道必须保证频率一致。频率取值越大，PWM精度越不准确，100KHz时PWM调节精度为7.25%，误差较大
取值：pwm:PWM初始占空比    取值范围： 0-10000   对应 0%-100%
*/
extern void PWM_change(int pin,int pwm); //改变PWM模块的占空比
/*
取值：pin:要改变的通道     例：  10 为 将P10端口对应的PWM通道改变
														     22 为 将P22端口对应的PWM通道改变
																 64 为 将P64端口对应的PWM通道改变 
取值：pwm:新的PWM占空比    取值范围： 0-10000   对应 0%-100%
*/