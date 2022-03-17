/**********************************************************
    不建议更改此文档，相关函数功能请查看相关头文件定义
**********************************************************/
#include "PWM.h"

unsigned int PWM0_T; 
unsigned int PWM1_T; 
unsigned int PWM2_T; 
unsigned int PWM3_T; 
unsigned int PWM4_T; 
unsigned int PWM5_T; 
unsigned int PWM6_T; 
unsigned int PWM7_T; 
unsigned char STORE;

void PWM_init(int pin,long f,int pwm)  //PWM初始化函数
{
	switch(pin%10)
	{
		case 0:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //以下寄存器为扩展sfr,访问前需先将PSW2寄存器最高位置1
			
			PWMCKS = 0x0f;                              // PWM时钟为系统时钟/16 ,以适应不同PWM频率。   
			PWMCFG = 0x00;  											//PWM配置寄存器，PWM无中断，PWM不与ADC关联 
			if(pin==10) PWM0CR=0x08;
			if(pin==20) PWM0CR=0x00;
			if(pin==60) PWM0CR=0x10;
			PWM0_T = Main_Fosc16/f;                   //计算PWM一个周期总脉冲数
			PWMC = PWM0_T;                        //设置PWM周期时钟数
			PWM0T1= (long)pwm*PWM0_T/10000;              //PWM0在计数值为100H地方输出低电平
			PWM0T2= 0;                             //PWM0在计数值为700H地方输出高电平
			 
			PWM0CR|=0x80;                          //使能PWM输出
			P_SW2  &= ~0x80;                       //PSW2寄存器最高位清0   
			PWMCR  |= 0x80;   //使能PWM波形发生器，PWM计数器开始工作
			break;   //PWM0
		}
		case 1:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //以下寄存器为扩展sfr,访问前需先将PSW2寄存器最高位置1
			
			PWMCKS = 0x0f;                              // PWM时钟为系统时钟/16 ,以适应不同PWM频率。   
			PWMCFG = 0x00;  											//PWM配置寄存器，PWM无中断，PWM不与ADC关联 
			if(pin==11) PWM1CR=0x08;
			if(pin==21) PWM1CR=0x00;
			if(pin==61) PWM1CR=0x10;
			PWM1_T = Main_Fosc16/f;                   //计算PWM一个周期总脉冲数
			PWMC = PWM1_T;                        //设置PWM周期时钟数
			PWM1T1= (long)pwm*PWM1_T/10000;              //PWM0在计数值为100H地方输出低电平
			PWM1T2= 0;                             //PWM0在计数值为700H地方输出高电平
			 
			PWM1CR|=0x80;                          //使能PWM输出
			P_SW2  &= ~0x80;                       //PSW2寄存器最高位清0   
			PWMCR  |= 0x80;   //使能PWM波形发生器，PWM计数器开始工作
			break;   //PWM0
		}
		case 2:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //以下寄存器为扩展sfr,访问前需先将PSW2寄存器最高位置1
			
			PWMCKS = 0x0f;                              // PWM时钟为系统时钟/16 ,以适应不同PWM频率。   
			PWMCFG = 0x00;  											//PWM配置寄存器，PWM无中断，PWM不与ADC关联 
			if(pin==12) PWM2CR=0x08;
			if(pin==22) PWM2CR=0x00;
			if(pin==62) PWM2CR=0x10;
			PWM2_T = Main_Fosc16/f;                   //计算PWM一个周期总脉冲数
			PWMC = PWM2_T;                        //设置PWM周期时钟数
			PWM2T1= (long)pwm*PWM2_T/10000;              //PWM0在计数值为100H地方输出低电平
			PWM2T2= 0;                             //PWM0在计数值为700H地方输出高电平
			 
			PWM2CR|=0x80;                          //使能PWM输出
			P_SW2  &= ~0x80;                       //PSW2寄存器最高位清0   
			PWMCR  |= 0x80;   //使能PWM波形发生器，PWM计数器开始工作
			break;   //PWM0
		}
		case 3:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //以下寄存器为扩展sfr,访问前需先将PSW2寄存器最高位置1
			
			PWMCKS = 0x0f;                              // PWM时钟为系统时钟/16 ,以适应不同PWM频率。   
			PWMCFG = 0x00;  											//PWM配置寄存器，PWM无中断，PWM不与ADC关联 
			if(pin==13) PWM3CR=0x08;
			if(pin==23) PWM3CR=0x00;
			if(pin==63) PWM3CR=0x10;
			PWM3_T = Main_Fosc16/f;                   //计算PWM一个周期总脉冲数
			PWMC = PWM3_T;                        //设置PWM周期时钟数
			PWM3T1= (long)pwm*PWM3_T/10000;              //PWM0在计数值为100H地方输出低电平
			PWM3T2= 0;                             //PWM0在计数值为700H地方输出高电平
			 
			PWM3CR|=0x80;                          //使能PWM输出
			P_SW2  &= ~0x80;                       //PSW2寄存器最高位清0   
			PWMCR  |= 0x80;   //使能PWM波形发生器，PWM计数器开始工作
			break;   //PWM0
		}
		case 4:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //以下寄存器为扩展sfr,访问前需先将PSW2寄存器最高位置1
			
			PWMCKS = 0x0f;                              // PWM时钟为系统时钟/16 ,以适应不同PWM频率。   
			PWMCFG = 0x00;  											//PWM配置寄存器，PWM无中断，PWM不与ADC关联 
			if(pin==14) PWM4CR=0x08;
			if(pin==24) PWM4CR=0x00;
			if(pin==64) PWM4CR=0x10;
			PWM4_T = Main_Fosc16/f;                   //计算PWM一个周期总脉冲数
			PWMC = PWM4_T;                        //设置PWM周期时钟数
			PWM4T1= (long)pwm*PWM4_T/10000;              //PWM0在计数值为100H地方输出低电平
			PWM4T2= 0;                             //PWM0在计数值为700H地方输出高电平
			 
			PWM4CR|=0x80;                          //使能PWM输出
			P_SW2  &= ~0x80;                       //PSW2寄存器最高位清0   
			PWMCR  |= 0x80;   //使能PWM波形发生器，PWM计数器开始工作
			break;   //PWM0
		}
		case 5:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //以下寄存器为扩展sfr,访问前需先将PSW2寄存器最高位置1
			
			PWMCKS = 0x0f;                              // PWM时钟为系统时钟/16 ,以适应不同PWM频率。   
			PWMCFG = 0x00;  											//PWM配置寄存器，PWM无中断，PWM不与ADC关联 
			if(pin==15) PWM5CR=0x08;
			if(pin==25) PWM5CR=0x00;
			if(pin==65) PWM5CR=0x10;
			PWM5_T = Main_Fosc16/f;                   //计算PWM一个周期总脉冲数
			PWMC = PWM0_T;                        //设置PWM周期时钟数
			PWM5T1= (long)pwm*PWM5_T/10000;              //PWM0在计数值为100H地方输出低电平
			PWM5T2= 0;                             //PWM0在计数值为700H地方输出高电平
			 
			PWM5CR|=0x80;                          //使能PWM输出
			P_SW2  &= ~0x80;                       //PSW2寄存器最高位清0   
			PWMCR  |= 0x80;   //使能PWM波形发生器，PWM计数器开始工作
			break;   //PWM0
		}
		case 6:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //以下寄存器为扩展sfr,访问前需先将PSW2寄存器最高位置1
			
			PWMCKS = 0x0f;                              // PWM时钟为系统时钟/16 ,以适应不同PWM频率。   
			PWMCFG = 0x00;  											//PWM配置寄存器，PWM无中断，PWM不与ADC关联 
			if(pin==16) PWM6CR=0x08;
			if(pin==26) PWM6CR=0x00;
			if(pin==66) PWM6CR=0x10;
			PWM6_T = Main_Fosc16/f;                   //计算PWM一个周期总脉冲数
			PWMC = PWM6_T;                        //设置PWM周期时钟数
			PWM6T1= (long)pwm*PWM6_T/10000;              //PWM0在计数值为100H地方输出低电平
			PWM6T2= 0;                             //PWM0在计数值为700H地方输出高电平
			 
			PWM6CR|=0x80;                          //使能PWM输出
			P_SW2  &= ~0x80;                       //PSW2寄存器最高位清0   
			PWMCR  |= 0x80;   //使能PWM波形发生器，PWM计数器开始工作
			break;   //PWM0
		}
		case 7:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //以下寄存器为扩展sfr,访问前需先将PSW2寄存器最高位置1
			
			PWMCKS = 0x0f;                              // PWM时钟为系统时钟/16 ,以适应不同PWM频率。   
			PWMCFG = 0x00;  											//PWM配置寄存器，PWM无中断，PWM不与ADC关联 
			if(pin==17) PWM7CR=0x08;
			if(pin==27) PWM7CR=0x00;
			if(pin==67) PWM7CR=0x10;
			PWM7_T = Main_Fosc16/f;                   //计算PWM一个周期总脉冲数
			PWMC = PWM7_T;                        //设置PWM周期时钟数
			PWM7T1= (long)pwm*PWM7_T/10000;              //PWM0在计数值为100H地方输出低电平
			PWM7T2= 0;                             //PWM0在计数值为700H地方输出高电平
			 
			PWM7CR|=0x80;                          //使能PWM输出
			P_SW2  &= ~0x80;                       //PSW2寄存器最高位清0   
			PWMCR  |= 0x80;   //使能PWM波形发生器，PWM计数器开始工作
			break;   //PWM0
		}
	}

	
}

void PWM_change(int pin,int pwm)    //改变PWM模块占空比
{
	//STORE=P_SW2;
	P_SW2 |= 0x80;  //以下寄存器为扩展sfr,访问前需先将PSW2寄存器最高位置1
	switch(pin%10)
	{
		case 0:	PWM0T1= (long)pwm*PWM0_T/10000;        //PWM0在计数值为100H地方输出低电平
						break;
		case 1:	PWM1T1= (long)pwm*PWM1_T/10000;        //PWM0在计数值为100H地方输出低电平
						break;
		case 2:	PWM2T1= (long)pwm*PWM2_T/10000;        //PWM0在计数值为100H地方输出低电平
						break;
		case 3:	PWM3T1= (long)pwm*PWM3_T/10000;        //PWM0在计数值为100H地方输出低电平
						break;
		case 4:	PWM4T1= (long)pwm*PWM4_T/10000;        //PWM0在计数值为100H地方输出低电平
						break;
		case 5:	PWM5T1= (long)pwm*PWM5_T/10000;        //PWM0在计数值为100H地方输出低电平
						break;
		case 6:	PWM6T1= (long)pwm*PWM6_T/10000;        //PWM0在计数值为100H地方输出低电平
						break;
		case 7:	PWM7T1= (long)pwm*PWM7_T/10000;        //PWM0在计数值为100H地方输出低电平
						break;
	}
	P_SW2  &= ~0x80;  //以上寄存器为扩展sfr,访问后需将PSW2寄存器最高位置0
}