#ifndef __CONFIG_H
#define __CONFIG_H

/**************************************************************/

//	ѡ��MCU�ͺ�
#define MCU_Type STC8X3K64 //STC8X1K08, STC8X1K16, STC8XxK32, STC8XxK32, STC8XxK60

/***************************���ͷ�ļ�******************************/
#include <intrins.h> //������ͷ�ļ�
#include <math.h>    //��ѧ���ͷ�ļ�
#include <string.h>  //�ڴ����
#include <stdio.h>
#include <stdlib.h>

#include "STC8xxxx.h" //STC8H��Ƭ��ͷ�ļ�

#include "myMath.h"
#include "sys.h"   //��������������
#include "delay.h" //��ʱģ��ͷ�ļ�

#include "crc.h"
#include "fifoqueue.h"
#include "modbus.h"
#include "AD7124_8.h"
#include "DAC7611.h"
#include "KalmanFilter.h"

#include "GPIO.h" //GPIOģ��ͷ�ļ�
#include "INT.h"  //�ⲿ�ж�ģ��ͷ�ļ�
// #include "PCA.h"    //PCA�ɱ�̼���������ģ��ͷ�ļ�
#include "SPI.h" //ADCģ��ת��ģ��ͷ�ļ�
// #include "ADC.h"    //ADCģ��ת��ģ��ͷ�ļ�
#include "EEPROM.h" //EEPROM��дģ��ͷ�ļ�
// #include "PIT.h"    //PIT��ʱ��ģ��ͷ�ļ�
// #include "PWM.h"    //PWM�������ģ��ͷ�ļ�
#include "UART.h" //UART����ģ��ͷ�ļ�
#include "timer.h"
#include "WDT.h"

/*************************ѡ����ʱ��*******************************/
//#define Main_Fosc		22118400L	//������ʱ��
//#define Main_Fosc		12000000L	//������ʱ��
#define Main_Fosc 11059200L //������ʱ��
//#define Main_Fosc		 5529600L	//������ʱ��
// #define Main_Fosc 24000000L //������ʱ��

// #define Main_Fosc2 (Main_Fosc / 2)          //��ʱ��/2
// #define Main_Fosc4 (Main_Fosc / 4)          //��ʱ��/4
// #define Main_Fosc8 (Main_Fosc / 8)          //��ʱ��/8
// #define Main_Fosc16 (Main_Fosc / 16)        //��ʱ��/16
#define Main_Fosc_KHZ (Main_Fosc / 1000)    //��ʱ��kHZ
#define Main_Fosc_MHZ (Main_Fosc / 1000000) //��ʱ��MHZ
// #define BAUD (256 - Main_Fosc / 32 / 115200)
#define DacFosc 115200
#define BAUD 115200

#define MAXAD7124CHNS 8               //�������У�˫�����£����ֵΪ8.�����ͨ��ʱ������ѡ16��>8���У���
#define MAXAD7124SETUPS MAXAD7124CHNS //���ݲ����źŵĲ�ͬѡ�����ȵ�ż���ȵ��裨3�߻���4�ߣ����¶ȴ�������ѹ���������ȣ�������ѡ5�֣���Ӧ5��chns
#define MAXINPUTREGNUM 8
#define MAXHOLDREGNUM MAXAD7124CHNS
// #define AD7124_8MAINCLK_Khz 614
// #define ADCSETUPTIMEx(x) ((u16)((setup[x].fs << 5 + 94) / 614)) //���õ�ͨ����0-8
#define ADCSETUPTIME (64) //1����0.625ms
// u16 adcSetupTime;

//-50��450����Ч
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
/***************��������ֵ�ж�*************************/
#define EPSINON 0.00001;
/****************�ɼ����ݵ��ݲ��ж�***********************/
#define TOLERANCE 0x000
/*****************************************/
/****************�������ݱ������***********************/
// #define BipolarDivisor 31924774E-14;//
// #define SinglepolarDivisor 15962124E-14;
#define Rref 5600.0
// #define BipolarDivisor (Rref / 2 ^ 23)//�����λΪ��
#define BipolarDivisor (667.572e-6) //�����λΪ��

/*****************************************/
extern u8 localAddr;
/*****************************************/

sbit SPISS = P3 ^ 5; //ADƬѡ
sbit DOUT = P3 ^ 3;  //ADоƬ����ready

sbit DacCS = P1 ^ 1;  //DACƬѡ
sbit DacCLK = P1 ^ 2; //DACʱ��
sbit DacSDI = P3 ^ 7; //DAC����
sbit DacLD = P3 ^ 6;  //DAC
extern u8 dacChn;     //��ӦMAXAD7124CHNS��������ʾ���ϱ�ģ����4-20ma��0-4.0V��������һ��ѭ����dacFlag��timer4�ж���λ

/*****************************************/
extern u8 chnActive; //������ȡģʽ�£���ǰת����ɵ�ͨ����
/*****************************************/

// extern u32 offset[8];
// extern u32 gain[8];
/****************************************/

#endif
