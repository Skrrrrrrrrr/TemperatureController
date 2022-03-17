/**********************************************************
    不建议更改此文档，相关函数功能请查看相关头文件定义
**********************************************************/
#include "ADC.h"

void ADC_init(int pin, int speed) //ADC初始化函数
{
	switch (pin)
	{
	case 0:
		P1M0 &= ~0x01;
		P1M1 |= 0x01;
		break; //ADC通道0
	case 1:
		P1M0 &= ~0x02;
		P1M1 |= 0x02;
		break; //ADC通道1
	case 2:
		P1M0 &= ~0x04;
		P1M1 |= 0x04;
		break; //ADC通道2
	case 3:
		P1M0 &= ~0x08;
		P1M1 |= 0x08;
		break; //ADC通道3
	case 4:
		P1M0 &= ~0x10;
		P1M1 |= 0x10;
		break; //ADC通道4
	case 5:
		P1M0 &= ~0x20;
		P1M1 |= 0x20;
		break; //ADC通道5
	case 6:
		P1M0 &= ~0x40;
		P1M1 |= 0x40;
		break; //ADC通道6
	case 7:
		P1M0 &= ~0x80;
		P1M1 |= 0x80;
		break; //ADC通道7
	}
	ADC_RES = 0;				  //清空结果寄存器高8位
	ADC_RESL = 0;				  //清空结果寄存器低8位
	ADC_CONTR |= 0x80;			  //使能ADC模块
	ADCCFG = 0x20 | (16 - speed); //选择数据输出格式为低8位+高4位，选择ADC速度
}

int ADC_get(int pin) //取得ADC转换值
{
	int u;

	switch (pin) //AD通道选择
	{
	case 0:
		ADC_CONTR = 0xC0;
		break; //通道P10
	case 1:
		ADC_CONTR = 0xC1;
		break; //通道P11
	case 2:
		ADC_CONTR = 0xC2;
		break; //通道P12
	case 3:
		ADC_CONTR = 0xC3;
		break; //通道P13
	case 4:
		ADC_CONTR = 0xC4;
		break; //通道P14
	case 5:
		ADC_CONTR = 0xC5;
		break; //通道P15
	case 6:
		ADC_CONTR = 0xC6;
		break; //通道P16
	case 7:
		ADC_CONTR = 0xC7;
		break; //通道P17
	}
	_nop_(); //等待4空指令
	_nop_();
	_nop_();
	_nop_();
	while (!(ADC_CONTR & 0x20))
		;						  //等待ADC转换完成
	ADC_CONTR &= ~0x20;			  //清除ADC标志
	u = ADC_RES * 256 + ADC_RESL; //结果转换
	return u;
}
