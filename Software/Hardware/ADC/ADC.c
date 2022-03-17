/**********************************************************
    ��������Ĵ��ĵ�����غ���������鿴���ͷ�ļ�����
**********************************************************/
#include "ADC.h"

void ADC_init(int pin, int speed) //ADC��ʼ������
{
	switch (pin)
	{
	case 0:
		P1M0 &= ~0x01;
		P1M1 |= 0x01;
		break; //ADCͨ��0
	case 1:
		P1M0 &= ~0x02;
		P1M1 |= 0x02;
		break; //ADCͨ��1
	case 2:
		P1M0 &= ~0x04;
		P1M1 |= 0x04;
		break; //ADCͨ��2
	case 3:
		P1M0 &= ~0x08;
		P1M1 |= 0x08;
		break; //ADCͨ��3
	case 4:
		P1M0 &= ~0x10;
		P1M1 |= 0x10;
		break; //ADCͨ��4
	case 5:
		P1M0 &= ~0x20;
		P1M1 |= 0x20;
		break; //ADCͨ��5
	case 6:
		P1M0 &= ~0x40;
		P1M1 |= 0x40;
		break; //ADCͨ��6
	case 7:
		P1M0 &= ~0x80;
		P1M1 |= 0x80;
		break; //ADCͨ��7
	}
	ADC_RES = 0;				  //��ս���Ĵ�����8λ
	ADC_RESL = 0;				  //��ս���Ĵ�����8λ
	ADC_CONTR |= 0x80;			  //ʹ��ADCģ��
	ADCCFG = 0x20 | (16 - speed); //ѡ�����������ʽΪ��8λ+��4λ��ѡ��ADC�ٶ�
}

int ADC_get(int pin) //ȡ��ADCת��ֵ
{
	int u;

	switch (pin) //ADͨ��ѡ��
	{
	case 0:
		ADC_CONTR = 0xC0;
		break; //ͨ��P10
	case 1:
		ADC_CONTR = 0xC1;
		break; //ͨ��P11
	case 2:
		ADC_CONTR = 0xC2;
		break; //ͨ��P12
	case 3:
		ADC_CONTR = 0xC3;
		break; //ͨ��P13
	case 4:
		ADC_CONTR = 0xC4;
		break; //ͨ��P14
	case 5:
		ADC_CONTR = 0xC5;
		break; //ͨ��P15
	case 6:
		ADC_CONTR = 0xC6;
		break; //ͨ��P16
	case 7:
		ADC_CONTR = 0xC7;
		break; //ͨ��P17
	}
	_nop_(); //�ȴ�4��ָ��
	_nop_();
	_nop_();
	_nop_();
	while (!(ADC_CONTR & 0x20))
		;						  //�ȴ�ADCת�����
	ADC_CONTR &= ~0x20;			  //���ADC��־
	u = ADC_RES * 256 + ADC_RESL; //���ת��
	return u;
}
