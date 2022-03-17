#ifndef __CONFIG_H
#define __CONFIG_H

/**************************************************************/

//	选择MCU型号
#define MCU_Type STC8X3K64 //STC8X1K08, STC8X1K16, STC8XxK32, STC8XxK32, STC8XxK60

/***************************添加头文件******************************/
#include <intrins.h> //汇编相关头文件
#include <math.h>    //数学相关头文件
#include <string.h>  //内存操作
#include <stdio.h>
#include <stdlib.h>

#include "STC8xxxx.h" //STC8H单片机头文件

#include "myMath.h"
#include "sys.h"   //定义了数据类型
#include "delay.h" //延时模块头文件

#include "crc.h"
#include "fifoqueue.h"
#include "modbus.h"
#include "AD7124_8.h"
#include "DAC7611.h"
#include "KalmanFilter.h"

#include "GPIO.h" //GPIO模块头文件
#include "INT.h"  //外部中断模块头文件
// #include "PCA.h"    //PCA可编程计数器阵列模块头文件
#include "SPI.h" //ADC模数转换模块头文件
// #include "ADC.h"    //ADC模数转换模块头文件
#include "EEPROM.h" //EEPROM读写模块头文件
// #include "PIT.h"    //PIT定时器模块头文件
// #include "PWM.h"    //PWM脉宽调制模块头文件
#include "UART.h" //UART串口模块头文件
#include "timer.h"
#include "WDT.h"

/*************************选择主时钟*******************************/
//#define Main_Fosc		22118400L	//定义主时钟
//#define Main_Fosc		12000000L	//定义主时钟
#define Main_Fosc 11059200L //定义主时钟
//#define Main_Fosc		 5529600L	//定义主时钟
// #define Main_Fosc 24000000L //定义主时钟

// #define Main_Fosc2 (Main_Fosc / 2)          //主时钟/2
// #define Main_Fosc4 (Main_Fosc / 4)          //主时钟/4
// #define Main_Fosc8 (Main_Fosc / 8)          //主时钟/8
// #define Main_Fosc16 (Main_Fosc / 16)        //主时钟/16
#define Main_Fosc_KHZ (Main_Fosc / 1000)    //主时钟kHZ
#define Main_Fosc_MHZ (Main_Fosc / 1000000) //主时钟MHZ
// #define BAUD (256 - Main_Fosc / 32 / 115200)
#define DacFosc 115200
#define BAUD 115200

#define MAXAD7124CHNS 8               //本方案中，双极性下，最大值为8.（混合通道时，可以选16（>8就行））
#define MAXAD7124SETUPS MAXAD7124CHNS //根据测量信号的不同选择，如热电偶、热电阻（3线或者4线）、温度传感器、压力传感器等，本方案选5种，对应5个chns
#define MAXINPUTREGNUM 8
#define MAXHOLDREGNUM MAXAD7124CHNS
// #define AD7124_8MAINCLK_Khz 614
// #define ADCSETUPTIMEx(x) ((u16)((setup[x].fs << 5 + 94) / 614)) //配置的通道号0-8
#define ADCSETUPTIME (64) //1代表0.625ms
// u16 adcSetupTime;

//-50到450℃有效
// #define LinerRegreseeionFormula(x) (2.7181 * x - 274.7)
// #define PolynomialRegreseeionFormula(x) (0.0012 * x * x + 2.3162 * x - 243.21)

#define a0 -242.02
#define a1 222.28e-2
#define a2 25.859e-4
#define a3 -4.8260e-6
#define a4 -2.8183e-8
#define a5 1.5243e-10
#define Res2Temp_Pt100_ResLessThan100(r) (a0 + a1 * r + a2 * r * r + a3 * r * r * r + a4 * r * r * r * r + a5 * r * r * r * r * r)
#define a6 3.9083e-3
#define a7 -5.775e-7
// #define a8 -4.23225e-12
#define R0 100.0
#define Res2Temp_Pt100_ResLagrgerThan100(r) ((-a6 + Q_rsqrt(a6 * a6 - 4 * a7 * (1 - r / R0))) / (2 * a7))
/***************浮点型零值判断*************************/
#define EPSINON 0.00001;
/****************采集数据的容差判断***********************/
#define TOLERANCE 0x000
/*****************************************/
/****************计算数据编码输出***********************/
// #define BipolarDivisor 31924774E-14;//
// #define SinglepolarDivisor 15962124E-14;
#define Rref 5600.0
// #define BipolarDivisor (Rref / 2 ^ 23)//换算后单位为Ω
#define BipolarDivisor (667.572e-6) //换算后单位为Ω

/*****************************************/
extern u8 localAddr;
/*****************************************/

sbit SPISS = P3 ^ 5; //AD片选
sbit DOUT = P3 ^ 3;  //AD芯片数据ready

sbit DacCS = P1 ^ 1;  //DAC片选
sbit DacCLK = P1 ^ 2; //DAC时钟
sbit DacSDI = P3 ^ 7; //DAC数据
sbit DacLD = P3 ^ 6;  //DAC
extern u8 dacChn;     //对应MAXAD7124CHNS次主动显示（上报模拟量4-20ma和0-4.0V），构成一个循环；dacFlag在timer4中断置位

/*****************************************/
extern u8 chnActive; //连续读取模式下，当前转换完成的通道号
/*****************************************/

// extern u32 offset[8];
// extern u32 gain[8];
/****************************************/

#endif
