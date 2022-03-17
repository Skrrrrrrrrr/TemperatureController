/**********************************************************
    不建议更改此文档，相关函数功能请查看相关头文件定义
**********************************************************/
#include "GPIO.h"

void IO_init()
{
	P0M1 = 0x00;
	P0M0 = 0x00; //设置为准双向口
	P1M1 = 0x00;
	P1M0 = 0x00; //设置为准双向口
	P2M1 = 0x00;
	P2M0 = 0x00; //设置为准双向口
	P3M1 = 0x00;
	P3M0 = 0x00; //设置为准双向口
	P4M1 = 0x00;
	P4M0 = 0x00; //设置为准双向口
	P5M1 = 0x00;
	P5M0 = 0x00; //设置为准双向口
	P6M1 = 0x00;
	P6M0 = 0x00; //设置为准双向口
	P7M1 = 0x00;
	P7M0 = 0x00; //设置为准双向口
}

// void GPIO_init_pin(int pin, int mode) //初始化单个IO引脚函数
// {
// 	int a, b;
// 	u8 c[8] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
// 	a = pin / 10; //取得端口号
// 	b = pin % 10; //取得引脚号
// 	switch (a)
// 	{
// 	case 0:
// 		switch (mode)
// 		{
// 		case 0:
// 			P0M0 &= c[b];
// 			P0M1 &= c[b];
// 			break;
// 		case 1:
// 			P0M0 |= ~c[b];
// 			P0M1 &= c[b];
// 			break;
// 		case 2:
// 			P0M0 &= c[b];
// 			P0M1 |= ~c[b];
// 			break;
// 		case 3:
// 			P0M0 |= ~c[b];
// 			P0M1 |= ~c[b];
// 			break;
// 		}
// 		break;
// 	case 1:
// 		switch (mode)
// 		{
// 		case 0:
// 			P1M0 &= c[b];
// 			P1M1 &= c[b];
// 			break;
// 		case 1:
// 			P1M0 |= ~c[b];
// 			P1M1 &= c[b];
// 			break;
// 		case 2:
// 			P1M0 &= c[b];
// 			P1M1 |= ~c[b];
// 			break;
// 		case 3:
// 			P1M0 |= ~c[b];
// 			P1M1 |= ~c[b];
// 			break;
// 		}
// 		break;
// 	case 2:
// 		switch (mode)
// 		{
// 		case 0:
// 			P2M0 &= c[b];
// 			P2M1 &= c[b];
// 			break;
// 		case 1:
// 			P2M0 |= ~c[b];
// 			P2M1 &= c[b];
// 			break;
// 		case 2:
// 			P2M0 &= c[b];
// 			P2M1 |= ~c[b];
// 			break;
// 		case 3:
// 			P2M0 |= ~c[b];
// 			P2M1 |= ~c[b];
// 			break;
// 		}
// 		break;
// 	case 3:
// 		switch (mode)
// 		{
// 		case 0:
// 			P3M0 &= c[b];
// 			P3M1 &= c[b];
// 			break;
// 		case 1:
// 			P3M0 |= ~c[b];
// 			P3M1 &= c[b];
// 			break;
// 		case 2:
// 			P3M0 &= c[b];
// 			P3M1 |= ~c[b];
// 			break;
// 		case 3:
// 			P3M0 |= ~c[b];
// 			P3M1 |= ~c[b];
// 			break;
// 		}
// 		break;
// 	case 4:
// 		switch (mode)
// 		{
// 		case 0:
// 			P4M0 &= c[b];
// 			P4M1 &= c[b];
// 			break;
// 		case 1:
// 			P4M0 |= ~c[b];
// 			P4M1 &= c[b];
// 			break;
// 		case 2:
// 			P4M0 &= c[b];
// 			P4M1 |= ~c[b];
// 			break;
// 		case 3:
// 			P4M0 |= ~c[b];
// 			P4M1 |= ~c[b];
// 			break;
// 		}
// 		break;
// 	case 5:
// 		switch (mode)
// 		{
// 		case 0:
// 			P5M0 &= c[b];
// 			P5M1 &= c[b];
// 			break;
// 		case 1:
// 			P5M0 |= ~c[b];
// 			P5M1 &= c[b];
// 			break;
// 		case 2:
// 			P5M0 &= c[b];
// 			P5M1 |= ~c[b];
// 			break;
// 		case 3:
// 			P5M0 |= ~c[b];
// 			P5M1 |= ~c[b];
// 			break;
// 		}
// 		break;
// 	case 6:
// 		switch (mode)
// 		{
// 		case 0:
// 			P6M0 &= c[b];
// 			P6M1 &= c[b];
// 			break;
// 		case 1:
// 			P6M0 |= ~c[b];
// 			P6M1 &= c[b];
// 			break;
// 		case 2:
// 			P6M0 &= c[b];
// 			P6M1 |= ~c[b];
// 			break;
// 		case 3:
// 			P6M0 |= ~c[b];
// 			P6M1 |= ~c[b];
// 			break;
// 		}
// 		break;
// 	case 7:
// 		switch (mode)
// 		{
// 		case 0:
// 			P7M0 &= c[b];
// 			P7M1 &= c[b];
// 			break;
// 		case 1:
// 			P7M0 |= ~c[b];
// 			P7M1 &= c[b];
// 			break;
// 		case 2:
// 			P7M0 &= c[b];
// 			P7M1 |= ~c[b];
// 			break;
// 		case 3:
// 			P7M0 |= ~c[b];
// 			P7M1 |= ~c[b];
// 			break;
// 		}
// 		break;
// 	}
// }

// bit Get_IO(int IO)
// {
// 	bit status;
// 	switch (IO)
// 	{
// 	case 00:
// 		status = P00;
// 		break;
// 	case 01:
// 		status = P01;
// 		break;
// 	case 02:
// 		status = P02;
// 		break;
// 	case 03:
// 		status = P03;
// 		break;
// 	case 04:
// 		status = P04;
// 		break;
// 	case 05:
// 		status = P05;
// 		break;
// 	case 06:
// 		status = P06;
// 		break;
// 	case 07:
// 		status = P07;
// 		break;

// 	case 10:
// 		status = P10;
// 		break;
// 	case 11:
// 		status = P11;
// 		break;
// 	case 12:
// 		status = P12;
// 		break;
// 	case 13:
// 		status = P13;
// 		break;
// 	case 14:
// 		status = P14;
// 		break;
// 	case 15:
// 		status = P15;
// 		break;
// 	case 16:
// 		status = P16;
// 		break;
// 	case 17:
// 		status = P17;
// 		break;

// 	case 20:
// 		status = P20;
// 		break;
// 	case 21:
// 		status = P21;
// 		break;
// 	case 22:
// 		status = P22;
// 		break;
// 	case 23:
// 		status = P23;
// 		break;
// 	case 24:
// 		status = P24;
// 		break;
// 	case 25:
// 		status = P25;
// 		break;
// 	case 26:
// 		status = P26;
// 		break;
// 	case 27:
// 		status = P27;
// 		break;

// 	case 30:
// 		status = P30;
// 		break;
// 	case 31:
// 		status = P31;
// 		break;
// 	case 32:
// 		status = P32;
// 		break;
// 	case 33:
// 		status = P33;
// 		break;
// 	case 34:
// 		status = P34;
// 		break;
// 	case 35:
// 		status = P35;
// 		break;
// 	case 36:
// 		status = P36;
// 		break;
// 	case 37:
// 		status = P37;
// 		break;

// 	case 40:
// 		status = P40;
// 		break;
// 	case 41:
// 		status = P41;
// 		break;
// 	case 42:
// 		status = P42;
// 		break;
// 	case 43:
// 		status = P43;
// 		break;
// 	case 44:
// 		status = P44;
// 		break;

// 	case 50:
// 		status = P50;
// 		break;
// 	case 51:
// 		status = P51;
// 		break;
// 	case 52:
// 		status = P52;
// 		break;
// 	case 53:
// 		status = P53;
// 		break;
// 	case 54:
// 		status = P54;
// 		break;
// 	case 55:
// 		status = P55;
// 		break;

// case 60:
// 	status = P60;
// 	break;
// case 61:
// 	status = P61;
// 	break;
// case 62:
// 	status = P62;
// 	break;
// case 63:
// 	status = P63;
// 	break;
// case 64:
// 	status = P64;
// 	break;
// case 65:
// 	status = P65;
// 	break;
// case 66:
// 	status = P66;
// 	break;
// case 67:
// 	status = P67;
// 	break;

// case 70:
// 	status = P70;
// 	break;
// case 71:
// 	status = P71;
// 	break;
// case 72:
// 	status = P72;
// 	break;
// case 73:
// 	status = P73;
// 	break;
// case 74:
// 	status = P74;
// 	break;
// case 75:
// 	status = P75;
// 	break;
// case 76:
// 	status = P76;
// 	break;
// case 77:
// 	status = P77;
// 	break;
// 	default:
// 		status = 1;
// 		break; //其他情况
// 	}
// 	return status;
// }

// void Out_IO(unsigned char IO, bit status)
// {
// 	switch (IO)
// 	{
// 	case 00:
// 		P00 = status;
// 		break;
// 	case 01:
// 		P01 = status;
// 		break;
// 	case 02:
// 		P02 = status;
// 		break;
// 	case 03:
// 		P03 = status;
// 		break;
// 	case 04:
// 		P04 = status;
// 		break;
// 	case 05:
// 		P05 = status;
// 		break;
// 	case 06:
// 		P06 = status;
// 		break;
// 	case 07:
// 		P07 = status;
// 		break;

// 	case 10:
// 		P10 = status;
// 		break;
// 	case 11:
// 		P11 = status;
// 		break;
// 	case 12:
// 		P12 = status;
// 		break;
// 	case 13:
// 		P13 = status;
// 		break;
// 	case 14:
// 		P14 = status;
// 		break;
// 	case 15:
// 		P15 = status;
// 		break;
// 	case 16:
// 		P16 = status;
// 		break;
// 	case 17:
// 		P17 = status;
// 		break;

// 	case 20:
// 		P20 = status;
// 		break;
// 	case 21:
// 		P21 = status;
// 		break;
// 	case 22:
// 		P22 = status;
// 		break;
// 	case 23:
// 		P23 = status;
// 		break;
// 	case 24:
// 		P24 = status;
// 		break;
// 	case 25:
// 		P25 = status;
// 		break;
// 	case 26:
// 		P26 = status;
// 		break;
// 	case 27:
// 		P27 = status;
// 		break;

// 	case 30:
// 		P30 = status;
// 		break;
// 	case 31:
// 		P31 = status;
// 		break;
// 	case 32:
// 		P32 = status;
// 		break;
// 	case 33:
// 		P33 = status;
// 		break;
// 	case 34:
// 		P34 = status;
// 		break;
// 	case 35:
// 		P35 = status;
// 		break;
// 	case 36:
// 		P36 = status;
// 		break;
// 	case 37:
// 		P37 = status;
// 		break;

// 	case 40:
// 		P40 = status;
// 		break;
// 	case 41:
// 		P41 = status;
// 		break;
// 	case 42:
// 		P42 = status;
// 		break;
// 	case 43:
// 		P43 = status;
// 		break;
// 	case 44:
// 		P44 = status;
// 		break;

// 	case 50:
// 		P50 = status;
// 		break;
// 	case 51:
// 		P51 = status;
// 		break;
// 	case 52:
// 		P52 = status;
// 		break;
// 	case 53:
// 		P53 = status;
// 		break;
// 	case 54:
// 		P54 = status;
// 		break;
// 	case 55:
// 		P55 = status;
// 		break;

// case 60: P60=status;break;
// case 61: P61=status;break;
// case 62: P62=status;break;
// case 63: P63=status;break;
// case 64: P64=status;break;
// case 65: P65=status;break;
// case 66: P66=status;break;
// case 67: P67=status;break;

// case 70: P70=status;break;
// case 71: P71=status;break;
// case 72: P72=status;break;
// case 73: P73=status;break;
// case 74: P74=status;break;
// case 75: P75=status;break;
// case 76: P76=status;break;
// case 77: P77=status;break;
// 	default:
// 		break; //其他情况
// 	}
// }
