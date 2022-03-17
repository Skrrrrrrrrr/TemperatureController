#ifndef __UART_H
#define __UART_H

// #include "sys.h"
#include "config.h"

#define Timer(x) (x)
#define UART(x) (x)

#define S1_IO_P30P31 (0 << 6)
#define S1_IO_P36P36 (1 << 6)
#define S1_IO_P16P17 (2 << 6)
#define S1_IO_P43P44 (3 << 6)

#define S2_IO_P10P11 (0 << 0)
#define S2_IO_P46P47 (1 << 0)
#define S3_IO_P00P01 (0 << 1)
#define S3_IO_P50P51 (1 << 1)
#define S4_IO_P02P03 (0 << 2)
#define S4_IO_P52P453 (1 << 2)
// extern DataStateEnum dataState;
extern u8 localAddr;

void UARTInit(u8 UARTx, u8 Timer, u8 serialport, bool enable); //UARTģ���ʼ������
/*
     ����1 Ϊ ����ģ��ͨ��1	����ΪRXD=P3.0��TXD=P3.1��
		2 Ϊ ����ģ��ͨ��2 ����ΪRXD=P4.0��TXD=P4.2��
		3 Ϊ ����ģ��ͨ��3	����ΪRXD=P5.0��TXD=P5.1��
		4 Ϊ ����ģ��ͨ��4 ����ΪRXD=P5.2��TXD=P5.3��
Timer���󶨵Ķ�ʱ��		UARTx=1:TImer=0/1/2,
						UARTx=2:TImer=2,
						UARTx=3:TImer=2/3,
						UARTx=4:TImer=2/4,

ȡֵ��enable:�Ƿ�򿪴����ж� ����0 Ϊ ���򿪽����ж�
														   1 Ϊ �򿪽����ж� 
*/

void UARTSendString(int UARTx, u8 *pt, u8 len); //UARTģ�鷢��һ���ַ���
/*	
ȡֵ��UARTx:Ҫʹ�õĴ���      ����1 Ϊ ����ģ��ͨ��1
														    2 Ϊ ����ģ��ͨ��2 
																3 Ϊ ����ģ��ͨ��3	
														    4 Ϊ ����ģ��ͨ��4 
ȡֵ��*pt:									Ҫ���͵��ַ�����Ϣ 
len�������ַ��ĳ��ȡ�modbus��Ҫ����0x00�����ʹ��*pt!=0���ᵼ�����ݷ���ʧ��
*/

void UARTSendByte(int UARTx, u8 c); //UARTģ�鷢��һ���ַ�
									/*
ȡֵ��UARTx:Ҫʹ�õĴ���     ����1 Ϊ ����ģ��ͨ��1
														   2 Ϊ ����ģ��ͨ��2 
															 3 Ϊ ����ģ��ͨ��3	
														   4 Ϊ ����ģ��ͨ��4 
ȡֵ��c:									 Ҫ���͵��ַ���Ϣ 
*/
#endif