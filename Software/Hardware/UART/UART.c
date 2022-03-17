#include "UART.h"

u8 wptr = 0;
u8 rxBuffer[MAXMODBUSDATALENGTH] = 0;
u8 *pRxBuffer = rxBuffer;
bool tx1Busy = false; //������ϱ�־
u8 txTimeout = 0xff;
DataStateEnum dataState = IS_ADDR;

void UARTInit(u8 UARTx, u8 Timer, u8 serialport, bool enable)
{
	switch (UARTx)
	{
	case UART(1):			 //����1
		P_SW1 |= serialport; //����1�����л��� P30.P31
		SCON = 0x50;		 //����1����ģʽΪ0��8λ����ģʽ
		switch (Timer)
		{
		case Timer(1):
			AUXR &= 0xFE; //����1ѡ��ʱ��1��Ϊ�����ʷ�����
			break;
		case Timer(2):
			AUXR &= 0xFF; //����1ѡ��ʱ��2��Ϊ�����ʷ�����
			break;
		default:
			break;
		}

		// Timer1_init(DISABLE, baud, 0x00, true, DISABLE);

		if (enable)
		{
			ES = 1;
		} //ʹ�ܴ���1�ж�
		break;
	case UART(2):
		P_SW2 |= serialport; //����2�����л��� P40.P42
		switch (Timer)
		{
		case Timer(2):
			S2CON = 0x10; //����2ѡ��ʱ��2��Ϊ�����ʷ�����
			break;
		default:
			break;
		}

		if (enable)
		{
			// IE2 |= ES2;
			UART2_INT_ENABLE();
		} //ʹ�ܴ���2�ж�
		break;
	case UART(3):
		P_SW2 |= serialport; //����3�����л��� P50.P51
		switch (Timer)
		{
		case Timer(3):
			S3CON = 0x50; //����3ѡ��ʱ��3��Ϊ�����ʷ�����
			break;
		case Timer(2):
			S3CON = 0x10; //����3ѡ��ʱ��2��Ϊ�����ʷ�����
			break;
		default:
			break;
		}
		T4T3M |= 0x0a; //������ʱ��3��1Tģʽ
		if (enable == 1)
		{
			// IE2 |= ES3;
			UART3_INT_ENABLE();
		} //ʹ�ܴ���3�ж�
		break;
	case UART(4):
		P_SW2 |= serialport; //����4�����л��� P52.P53
		switch (Timer)
		{
		case Timer(4):
			S4CON = 0x50; //����4ѡ��ʱ��4��Ϊ�����ʷ�����
			break;
		case Timer(2):
			S4CON = 0x10; //����3ѡ��ʱ��2��Ϊ�����ʷ�����
			break;
		default:
			break;
		}
		T4T3M |= 0xa0; //������ʱ��4��1Tģʽ
		if (enable == 1)
		{
			// IE2 |= ES4;
			UART4_INT_ENABLE();
		} //ʹ�ܴ���4�ж�
		break;
	default:
		break;
	}
	// EA = 1; //���������ж�
}

void UARTSendByte(int UARTx, u8 c) //���ô���ģ�鷢�͵����ַ�
{
	if (UARTx == 1)
	{
		// TI = 0;
		SBUF = c;
		while (!TI)
			;
	}
	if (UARTx == 2)
	{
		S2CON &= ~0x02;
		S2BUF = c;
		while (!(S2CON & 0x02))
			;
	}
	if (UARTx == 3)
	{
		S3CON &= ~0x02;
		S3BUF = c;
		while (!(S3CON & 0x02))
			;
	}
	if (UARTx == 4)
	{
		S4CON &= ~0x02;
		S4BUF = c;
		while (!(S4CON & 0x02))
			;
	}
}

void UARTSendString(int UARTx, u8 *pt, u8 len) //���ô���ģ�鷢���ַ���
{
	while (len-- > 0)
	{
		UARTSendByte(UARTx, *pt++);
	}
}

void UART1Isr(void) interrupt UART1_VECTOR
{
	if (TI)
	{
		TI = 0;
		tx1Busy = false;
		// spi_write_read(SBUF);
	}
	else if (RI)
	{
		RI = 0;
		switch (dataState)
		{
		case IS_IDLE:
			modbusDataGapCnt = 0;
			break;
		case IS_ADDR:
			modbusDataGapCnt = 0;
			Timer3_start();
			if (SBUF == 0 || SBUF == localAddr)
			{
				dataState = IS_VALID;
				*pRxBuffer = SBUF;
				pRxBuffer++;
				wptr++;
			}
			else
			{
				dataState = IS_IDLE;
				if (wptr)
				{
					pRxBuffer = rxBuffer;
					memset(pRxBuffer, 0, wptr);
					wptr = 0;
				}
			}
			break;
		case IS_VALID:
			modbusDataGapCnt = 0;
			*pRxBuffer = SBUF;
			pRxBuffer++;
			wptr++;
			break;
		default:
			Timer3_stop();
			dataState = IS_IDLE;
			break;
		}
	}
}
