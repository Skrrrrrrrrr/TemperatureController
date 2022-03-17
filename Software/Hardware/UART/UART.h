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

void UARTInit(u8 UARTx, u8 Timer, u8 serialport, bool enable); //UART模块初始化函数
/*
     例：1 为 串口模块通道1	引脚为RXD=P3.0和TXD=P3.1等
		2 为 串口模块通道2 引脚为RXD=P4.0和TXD=P4.2等
		3 为 串口模块通道3	引脚为RXD=P5.0和TXD=P5.1等
		4 为 串口模块通道4 引脚为RXD=P5.2和TXD=P5.3等
Timer：绑定的定时器		UARTx=1:TImer=0/1/2,
						UARTx=2:TImer=2,
						UARTx=3:TImer=2/3,
						UARTx=4:TImer=2/4,

取值：enable:是否打开串口中断 例：0 为 不打开接收中断
														   1 为 打开接收中断 
*/

void UARTSendString(int UARTx, u8 *pt, u8 len); //UART模块发送一个字符串
/*	
取值：UARTx:要使用的串口      例：1 为 串口模块通道1
														    2 为 串口模块通道2 
																3 为 串口模块通道3	
														    4 为 串口模块通道4 
取值：*pt:									要发送的字符串信息 
len：发送字符的长度。modbus需要发送0x00，如果使用*pt!=0，会导致数据发送失真
*/

void UARTSendByte(int UARTx, u8 c); //UART模块发送一个字符
									/*
取值：UARTx:要使用的串口     例：1 为 串口模块通道1
														   2 为 串口模块通道2 
															 3 为 串口模块通道3	
														   4 为 串口模块通道4 
取值：c:									 要发送的字符信息 
*/
#endif