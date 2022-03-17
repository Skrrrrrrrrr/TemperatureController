#include "UART.h"

u8 wptr = 0;
u8 rxBuffer[MAXMODBUSDATALENGTH] = 0;
u8 *pRxBuffer = rxBuffer;
bool tx1Busy = false; //发送完毕标志
u8 txTimeout = 0xff;
DataStateEnum dataState = IS_ADDR;

void UARTInit(u8 UARTx, u8 Timer, u8 serialport, bool enable)
{
	switch (UARTx)
	{
	case UART(1):			 //串口1
		P_SW1 |= serialport; //串口1引脚切换到 P30.P31
		SCON = 0x50;		 //串口1工作模式为0，8位数据模式
		switch (Timer)
		{
		case Timer(1):
			AUXR &= 0xFE; //串口1选择定时器1作为波特率发生器
			break;
		case Timer(2):
			AUXR &= 0xFF; //串口1选择定时器2作为波特率发生器
			break;
		default:
			break;
		}

		// Timer1_init(DISABLE, baud, 0x00, true, DISABLE);

		if (enable)
		{
			ES = 1;
		} //使能串口1中断
		break;
	case UART(2):
		P_SW2 |= serialport; //串口2引脚切换到 P40.P42
		switch (Timer)
		{
		case Timer(2):
			S2CON = 0x10; //串口2选择定时器2作为波特率发生器
			break;
		default:
			break;
		}

		if (enable)
		{
			// IE2 |= ES2;
			UART2_INT_ENABLE();
		} //使能串口2中断
		break;
	case UART(3):
		P_SW2 |= serialport; //串口3引脚切换到 P50.P51
		switch (Timer)
		{
		case Timer(3):
			S3CON = 0x50; //串口3选择定时器3作为波特率发生器
			break;
		case Timer(2):
			S3CON = 0x10; //串口3选择定时器2作为波特率发生器
			break;
		default:
			break;
		}
		T4T3M |= 0x0a; //启动定时器3，1T模式
		if (enable == 1)
		{
			// IE2 |= ES3;
			UART3_INT_ENABLE();
		} //使能串口3中断
		break;
	case UART(4):
		P_SW2 |= serialport; //串口4引脚切换到 P52.P53
		switch (Timer)
		{
		case Timer(4):
			S4CON = 0x50; //串口4选择定时器4作为波特率发生器
			break;
		case Timer(2):
			S4CON = 0x10; //串口3选择定时器2作为波特率发生器
			break;
		default:
			break;
		}
		T4T3M |= 0xa0; //启动定时器4，1T模式
		if (enable == 1)
		{
			// IE2 |= ES4;
			UART4_INT_ENABLE();
		} //使能串口4中断
		break;
	default:
		break;
	}
	// EA = 1; //允许所有中断
}

void UARTSendByte(int UARTx, u8 c) //调用串口模块发送单个字符
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

void UARTSendString(int UARTx, u8 *pt, u8 len) //调用串口模块发送字符串
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
