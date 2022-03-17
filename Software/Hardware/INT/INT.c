/**********************************************************
    ��������Ĵ��ĵ�����غ���������鿴���ͷ�ļ�����
**********************************************************/
#include "INT.h"

u8 psw2_st;
extern AD7124_REG *pChnReg; //����ָ��
extern KFP *pKfp;
extern float fRes[MAXAD7124CHNS];
extern float fKpfTemp;
extern int fTemp;
extern int chnValues[MAXAD7124CHNS]; //�洢ͨ��ת������¶�ֵ��10���Ŵ�BipolarDivisor��
extern Setup setup[MAXAD7124SETUPS];
extern bool adcAvailable;

void INT_init(int n, int mode)
{
	switch (n)
	{
	case 0:
	{
		if (mode == 0)
		{
			IT0 = 1;
			EX0 = 1;
		}
		else
		{
			IT0 = 0;
			EX0 = 1;
		}
		break;
	}
	case 1:
	{
		if (mode == 0)
		{
			IT1 = 1;
			EX1 = 1;
		}
		else
		{
			IT1 = 0;
			EX1 = 1;
		}
		break;
	}
	case 2:
	{
		INT_CLKO |= EX2;
		break;
	}
	case 3:
	{
		INT_CLKO |= EX3;
		break;
	}
	case 4:
	{
		INT_CLKO |= EX4;
		break;
	}
	}
	// EA=1;            //���������ж�
}

void int1_isr() interrupt INT1_VECTOR
{
	EX1 = 0; //INT1�жϹ�
	// IT1 = 0; //��ʹ���½���
	IE1 = 0; //��INT1��־λ
			 // // P16 = ~P16;
			 // P10 = 0;
			 // N_NOP(5);
			 // P10 = 1;
			 // N_NOP(5);
			 // P10 = 0;
			 // delay_X_us(1);

	adcAvailable = true;
	timer4Cnt = 0;
	// EX1 = 1; //INT1�жϿ�
}

// void int3_isr() interrupt INT3_VECTOR
// {
// 	P10 = ~P10;
// }

// void common_isr() interrupt COMMON_VECTOR
// {
// 	u8 intf;

// 	// SPISS = 0;
// 	psw2_st = P_SW2;
// 	P_SW2 |= 0x80;
// 	intf = P1INTF;
// 	P1INTE = 0x00;

// 	if (intf)
// 	{
// 		P1INTF = 0x00;
// 		if (intf & 0x01) //P1.0���ж�
// 		{
// 			P16 = ~P16;
// 			// pChnReg->value &= 0x00000000; //uTempΪ32λ��ֻ��3�����ƣ���Ҫ������λ8bit
// 			// SpiWrite&Read(AD7124_COMM_REG_RD | AD7124_DATA_REG);
// 			// pChnReg->value |= (u32)SpiWrite&Read(0x00);
// 			// pChnReg->value <<= 8;
// 			// pChnReg->value |= (u32)SpiWrite&Read(0x00);
// 			// pChnReg->value <<= 8;
// 			// pChnReg->value |= (u32)SpiWrite&Read(0x00);
// 			// // SpiWrite&Read(AD7124_COMM_REG_RD | AD7124_COMM_REG);
// 			// pChnReg->addr = SpiWrite&Read(0x00);
// 			// // SPISS = 1;

// 			// if (pChnReg->addr <= MAXAD7124CHNS)
// 			// {
// 			// 	fRes[pChnReg->addr] = (float)((pChnReg->value - 0x800000) >> setup[pChnReg->addr].pga) * BipolarDivisor; ////�����λΪ����������Ҫ55us
// 			// 	// fRes[pChnReg->addr] = (float)((pChnReg->value - 0x800000) >> setup[pChnReg->addr].pga) * 2127 * BipolarDivisor; //��ֵδת��Ϊ�¶ȣ�������Ҫ55us��
// 			// 	fKpfTemp = kalmanFilter(pKfp + pChnReg->addr, fRes[pChnReg->addr]);
// 			// 	if (fRes >= 100)
// 			// 	{
// 			// 		fTemp = 10 * Res2Temp_Pt100_ResLagrgerThan100(fKpfTemp); //BipolarDivisorΪe-13����Ҫ800us
// 			// 	}
// 			// 	else
// 			// 	{
// 			// 		fTemp = 10 * Res2Temp_Pt100_ResLessThan100(fKpfTemp); //BipolarDivisorΪe-13����Ҫ800us
// 			// 	}
// 			// 	chnValues[pChnReg->addr] = (int)(fTemp); //5us
// 			// }
// 			// // adcAvailable = true;
// 		}
// 		if (intf & 0x02) //P1.0���ж�
// 		{
// 		}
// 		if (intf & 0x04) //P1.0���ж�
// 		{
// 		}
// 		if (intf & 0x08) //P1.0���ж�
// 		{
// 		}
// 		if (intf & 0x10) //P1.0���ж�
// 		{
// 		}
// 		if (intf & 0x20) //P1.0���ж�
// 		{
// 		}
// 		if (intf & 0x40) //P1.0���ж�
// 		{
// 		}
// 		if (intf & 0x80) //P1.0���ж�
// 		{
// 		}
// 	}
// 	P1INTE = 0x00;
// 	P_SW2 = psw2_st;
// 	// SPISS = 1;
// }