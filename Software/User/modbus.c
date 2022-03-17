#include "modbus.h"

u8 txBuffer[MAXMODBUS_TX_DATALENGTH]; //发送的数据
u16 modbusDataGapCnt = 0;			  //modbus字符及帧间隔计数器,10us计数1次

extern u8 localAddr;
extern u8 code mac[128];
extern u8 code version[128];
extern SqQueue sq;		   //存储大量到来数据
extern SqQueue nDataCntSq; //存储每次到来的有效数据（经过CRC），含CRC的2字节数量
extern u16 chnValues[MAXAD7124CHNS];
extern u16 inputRegValues[MAXINPUTREGNUM]; //Modbus写入测试
extern u8 coilValues[MAXCOILNUM];		   //离散量数组，一个字节存一个状态

//////////////////功能码数组///////////////////////

// u32 code OffsetRegs[17] = {
// 	0, 0, 10000, 40000, 30000, 10000, 40000, 0,
// 	0, 0, 0, 0, 0, 0, 0, 10000,
// 	40000};

//////////////////////////////////////////

/**************************************
//函数功能：解析上位机发过来的modbus数据帧
//函数返回值：无
//函数形参：无
//时间：2020/06/22
//备注：无
*************************************/
void ModbusDataParse(void)
{
	ModbusData modbusData;

	if (ModbusDataCheck(&modbusData) == 0)
	{
		switch (modbusData.functionCode)
		{
		case ReadCoilSta:
		case ReadInputDis:
			ReadCoils(&modbusData);
			break;
		case ReadHoldReg:
			ReadHoldRegs(&modbusData);
			break;
		case ReadInputReg:
			ReadInputRegs(&modbusData);
			break;
		case ForceSingleCoil:
			WriteSingleCoil(&modbusData);
			break;
		case WriteSinReg:
			WriteSingleReg(&modbusData);
			break;
		case ForceMulCoils:
			WriteMuilCoils(&modbusData);
			break;
		case WriteMulRegs:
			WriteMuilRegs(&modbusData);
			break;
		default:
			ErrorSend(UART(1), IS_INVALID_FUNCTION_CODE);
			break;
		}
		memset(&modbusData, 0, sizeof(modbusData));
	}
}
/**************************************
//函数功能：对上位机发来的帧进行判断
//函数返回值：无
//函数形参：pRxBytes：队列首数据帧，length：接收到的长度，pModbusData：modbusdata结构指针
//时间：2020/06/22
//备注：无
*************************************/
u8 ModbusDataCheck(ModbusData *pModbusData)
{
	u16 validationCRC = 0;
	u16 i = 0;

	u8 nByte = 0;
	u8 *pNByte = &nByte; //u8不能满足多于256个数据值
	u8 rxBytes[MAXMODBUSDATALENGTH];
	u8 *pRxBytes = rxBytes; //存储队列拿出的数据帧，帧长度由DeQueue(nDataCntSq)控制
	memset(rxBytes, 0, MAXMODBUSDATALENGTH);

	// pNByte = (u16)DeQueue(&nDataCntSq);
	DeQueue(&nDataCntSq, &pNByte, 1);
	if (nByte < 8) //防空指针
	{
		return 4;
	}

	DeQueue(&sq, &pRxBytes, nByte);

	validationCRC = CRC16(pRxBytes, nByte - 2);

	if (validationCRC == (u16)(pRxBytes[nByte - 2] << 8 | pRxBytes[nByte - 1]))
	{
		pModbusData->addr = pRxBytes[0];
		pModbusData->functionCode = pRxBytes[1];
		if (pModbusData->addr == localAddr)
		{
			switch (pRxBytes[1])
			{
			case ReadCoilSta:
			case ReadInputDis:
			case ReadHoldReg:
			case ReadInputReg:
				pModbusData->startAddr = (u16)(pRxBytes[2] << 8 | pRxBytes[3]);
				pModbusData->dataLen = (u16)(pRxBytes[4] << 8 | pRxBytes[5]);
				break;
			case ForceSingleCoil:
			case WriteSinReg:
				//01 05 00 00 ff 00 crc1 crc2  8byte
				//01 06 00 01 aa bb crc1 crc2  8byte
				pModbusData->dataLen = 2;
				pModbusData->nBytes = 1;
				pModbusData->startAddr = (u16)(pRxBytes[2] << 8 | pRxBytes[3]);
				pModbusData->dat[0] = (u16)(pRxBytes[4] << 8 | pRxBytes[5]);
				break;
			case WriteMulRegs:
				//01 10 00 13 00 02 04 aa aa bb bb crc1 crc ---- 7+len+2字节
				pModbusData->startAddr = (u16)(pRxBytes[2] << 8 | pRxBytes[3]);
				pModbusData->dataLen = (u16)(pRxBytes[4] << 8 | pRxBytes[5]);
				pModbusData->nBytes = pRxBytes[6];
				for (i = 0; i < pModbusData->dataLen; i++)
				{
					pModbusData->dat[i] = (u16)(pRxBytes[7 + 2 * i] << 8 | pRxBytes[8 + 2 * i]);
				}
				break;
			case ForceMulCoils:
				pModbusData->startAddr = (u16)(pRxBytes[2] << 8 | pRxBytes[3]);
				pModbusData->dataLen = (u16)(pRxBytes[4] << 8 | pRxBytes[5]);
				pModbusData->nBytes = (pModbusData->dataLen / 8);
				if ((pModbusData->dataLen % 8) != 0)
				{
					pModbusData->nBytes++;
				}
				for (i = 0; i < pModbusData->nBytes; i++)
				{
					pModbusData->dat[i] = (u16)pRxBytes[7 + i];
				}
				break;
			default:
				ErrorSend(UART(1), IS_INVALID_FUNCTION_CODE);
				break;
			}
			return 0; //success
		}
		else
		{
			return 0xff;
		}
	}
	return 0xff;
}

/**************************************
//函数功能：Modbus异常码发送
//函数返回值：无
//函数形参：Cmd：命令码，Err：错误类型
//时间：2020/06/22
//备注：无
*************************************/
void ErrorSend(u8 Cmd, u8 errorCode)
{
	u16 validationCRC = 0;

	txBuffer[0] = localAddr;
	txBuffer[1] = 0x80 + Cmd;
	txBuffer[2] = errorCode;
	validationCRC = CRC16(txBuffer, 3);
	txBuffer[3] = (u8)((validationCRC >> 8) & 0xff);
	txBuffer[4] = (u8)(validationCRC & 0xff);
	UARTSendString(UART(1), txBuffer, 5);
	memset(txBuffer, 0, MAXMODBUS_TX_DATALENGTH);
}

/**************************************
//函数功能：Modbus读版本号
//函数返回值：无
//函数形参：pModbusData
//时间：2020/06/22
//备注：无
*************************************/
void ModbusReadVersion(ModbusData *pModbusData)
{
	u16 validationCRC = 0;
	u16 indexSend = 0;

	txBuffer[indexSend++] = pModbusData->addr;
	txBuffer[indexSend++] = pModbusData->functionCode;
	txBuffer[indexSend++] = pModbusData->dataLen * 2;

	memcpy((char *)txBuffer + indexSend, version, pModbusData->dataLen * 2);
	indexSend += pModbusData->dataLen * 2;
	validationCRC = CRC16(txBuffer, indexSend);
	txBuffer[indexSend++] = (u8)((validationCRC >> 8) & 0xff);
	txBuffer[indexSend++] = (u8)(validationCRC & 0xff);
	UARTSendString(UART(1), txBuffer, indexSend);
	memset(txBuffer, 0, MAXMODBUS_TX_DATALENGTH);
}

void ModbusReadMac(ModbusData *pModbusData)
{
	u16 validationCRC = 0;
	u16 indexSend = 0;

	txBuffer[indexSend++] = pModbusData->addr;
	txBuffer[indexSend++] = pModbusData->functionCode;
	txBuffer[indexSend++] = pModbusData->dataLen * 2;

	memcpy((char *)txBuffer + indexSend, mac, pModbusData->dataLen * 2);
	indexSend += pModbusData->dataLen * 2;
	validationCRC = CRC16(txBuffer, indexSend);
	txBuffer[indexSend++] = (u8)((validationCRC >> 8) & 0xff);
	txBuffer[indexSend++] = (u8)(validationCRC & 0xff);
	UARTSendString(UART(1), txBuffer, indexSend);
	memset(txBuffer, 0, MAXMODBUS_TX_DATALENGTH);
}

/**************************************
//函数功能：对上位机01/02命令处理
//函数返回值：无
//函数形参：无
//时间：2020/06/22
//备注：无
*************************************/
void ReadCoils(ModbusData *pModbusData)
{
	u16 validationCRC = 0;
	u16 i = 0;
	u16 j = 0;
	//u16 nOffset = 0;
	//u16 uStatus[16] = {0};
	u16 indexSend = 0;
	u8 coilValue = 0;
	u16 coilAddr = 0;
	bool readFlag = false;

	memset(txBuffer, 0, MAXMODBUS_TX_DATALENGTH);

	if (!((pModbusData->dataLen >= 0x0001) && (pModbusData->dataLen <= 0x07D0))) //非法数据值
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_VALUE);
		return;
	}
	if ((pModbusData->startAddr < Coilx(0)) || (pModbusData->startAddr > Coilx(MAXCOILNUM)) || pModbusData->dataLen > Coilx(MAXCOILNUM) - Coilx(0) + 1 || (pModbusData->startAddr + pModbusData->dataLen) > Coilx(MAXCOILNUM) + 1) //超出范围
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_ADDR);
		return;
	}

	coilAddr = pModbusData->startAddr;
	txBuffer[0] = pModbusData->addr;
	txBuffer[1] = pModbusData->functionCode;
	indexSend = pModbusData->dataLen >> 3; //字节数，开关量8位组成一个字节

	if (pModbusData->dataLen % 8)
	{ //有余数字节数加1
		indexSend++;
	}
	txBuffer[2] = (u8)indexSend;
	//小端模式，低位存放在低地址
	for (i = 0; i < indexSend; i++)
	{
		txBuffer[3 + i] = 0x00;

		for (j = 0; j < 8; j++)
		{
			//读线圈状态
			coilValue = GetCoilData(coilAddr, ReadCoilSta);
			txBuffer[3 + i] |= coilValue << j;
			coilAddr++;
			if (coilAddr >= pModbusData->dataLen + pModbusData->startAddr) //屏蔽indexSend++的影响
			{
				readFlag = true;
				break;
			}
		}
		if (readFlag)
		{
			break;
		}
	}

	validationCRC = CRC16(txBuffer, indexSend + 3);
	txBuffer[indexSend + 3] = (u8)((validationCRC >> 8) & 0xff);
	txBuffer[indexSend + 4] = (u8)(validationCRC & 0xff);
	UARTSendString(UART(1), txBuffer, indexSend + 5);
	memset(txBuffer, 0, MAXMODBUS_TX_DATALENGTH);
}

/**************************************
//函数功能：对上位机0命令处理
//函数返回值：无
//函数形参：无
//时间：2020/06/22
//备注：无
*************************************/
void ReadHoldRegs(ModbusData *pModbusData)
{

	u16 validationCRC = 0;
	u16 i = 0;
	// u16 regAddr = 0;
	u16 regValue = 0;
	u16 indexSend = 0;
	u8 readBuff[HoldRegNUm];
	memset(readBuff, 0, HoldRegNUm);

	if (!((pModbusData->dataLen >= 0x0001) && (pModbusData->dataLen <= 0x07D0))) //非法数据值
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_VALUE);
		return;
	}
	if (pModbusData->startAddr == VersionReg && pModbusData->dataLen != 0)
	{
		ModbusReadVersion(pModbusData);
		return;
	}
	if (pModbusData->startAddr == MacReg && pModbusData->dataLen != 0)
	{
		ModbusReadMac(pModbusData);
		return;
	}
	if ((pModbusData->startAddr > HoldxReg(HoldRegNUm)) || (pModbusData->startAddr < HoldxReg(0)) || pModbusData->dataLen > MAXAD7124CHNS || (pModbusData->startAddr + pModbusData->dataLen) > HoldxReg(HoldRegNUm)) //超出范围
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_ADDR);
		return;
	}
	for (i = 0; i < pModbusData->dataLen; i++)
	{
		regValue = GetRegData(pModbusData->startAddr + i, ReadHoldReg);
		// readBuff[2 * i] = chnValues[(u8)(pModbusData->startAddr + i)] >> 8 & 0xFF;
		// readBuff[2 * i + 1] = chnValues[(u8)(pModbusData->startAddr + i)] & 0xFF;
		readBuff[2 * i] = regValue >> 8 & 0xFF;
		readBuff[2 * i + 1] = regValue & 0xFF;
	}
	txBuffer[indexSend++] = pModbusData->addr;
	txBuffer[indexSend++] = pModbusData->functionCode;
	txBuffer[indexSend++] = pModbusData->dataLen * 2;
	memcpy(&txBuffer[indexSend], readBuff, (2 * i));
	indexSend += 2 * i;
	validationCRC = CRC16(txBuffer, indexSend);
	txBuffer[indexSend++] = (u8)((validationCRC >> 8) & 0xff);
	txBuffer[indexSend++] = (u8)(validationCRC & 0xff);
	UARTSendString(UART(1), txBuffer, indexSend);
	memset(txBuffer, 0, MAXMODBUS_TX_DATALENGTH);
}

/**************************************
//函数功能：对上位机04命令处理
//函数返回值：无
//函数形参：无
//时间：2020/06/22
//备注：无
*************************************/
void ReadInputRegs(ModbusData *pModbusData)
{

	u16 validationCRC = 0;
	u16 i = 0;
	// u16 regAddr = 0;
	u16 regValue = 0;
	u16 indexSend = 0;
	u8 readBuff[InputRegNum];
	memset(readBuff, 0, InputRegNum);

	if (!((pModbusData->dataLen >= 0x0001) && (pModbusData->dataLen <= 0x07D0))) //非法数据值
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_VALUE);
		return;
	}
	if (pModbusData->startAddr == VersionReg && pModbusData->dataLen != 0)
	{
		ModbusReadVersion(pModbusData);
		return;
	}
	if (pModbusData->startAddr == MacReg && pModbusData->dataLen != 0)
	{
		ModbusReadMac(pModbusData);
		return;
	}
	if ((pModbusData->startAddr > InputRegx(InputRegNum)) || (pModbusData->startAddr < InputRegx(0)) || pModbusData->dataLen > InputRegNum || (pModbusData->startAddr + pModbusData->dataLen) > InputRegx(InputRegNum)) //超出范围
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_ADDR);
		return;
	}
	for (i = 0; i < pModbusData->dataLen; i++)
	{
		regValue = GetRegData(pModbusData->startAddr + i, ReadInputReg);
		// readBuff[2 * i] = chnValues[(u8)(pModbusData->startAddr + i)] >> 8 & 0xFF;
		// readBuff[2 * i + 1] = chnValues[(u8)(pModbusData->startAddr + i)] & 0xFF;
		readBuff[2 * i] = regValue >> 8 & 0xFF;
		readBuff[2 * i + 1] = regValue & 0xFF;
	}
	txBuffer[indexSend++] = pModbusData->addr;
	txBuffer[indexSend++] = pModbusData->functionCode;
	txBuffer[indexSend++] = pModbusData->dataLen * 2;
	memcpy(&txBuffer[indexSend], readBuff, (2 * i));
	indexSend += 2 * i;
	validationCRC = CRC16(txBuffer, indexSend);
	txBuffer[indexSend++] = (u8)((validationCRC >> 8) & 0xff);
	txBuffer[indexSend++] = (u8)(validationCRC & 0xff);
	UARTSendString(UART(1), txBuffer, indexSend);
	memset(txBuffer, 0, MAXMODBUS_TX_DATALENGTH);
}
/**************************************
//函数功能：对上位机0x05写单个线圈处理
//函数返回值：无
//函数形参：无
//时间：2020/06/22
//备注：无
*************************************/
void WriteSingleCoil(ModbusData *pModbusData)
{
	u16 validationCRC = 0;
	u16 indexSend = 0;
	u8 coilValue = 0;
	// u16 coilAddr = 0;
	u16 coilStatus = 0;

	// coilAddr = pModbusData->startAddr;
	if (pModbusData->startAddr < Coilx(0) || pModbusData->startAddr > Coilx(MAXCOILNUM))
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_ADDR);
		return;
	}

	coilStatus = pModbusData->dat[0];
	if (coilStatus == 0xFF00)
	{
		coilValue = 1;
	}
	else if (coilStatus == 0x0000)
	{
		coilValue = 0;
	}
	SetCoilData(pModbusData->startAddr, coilValue, ForceSingleCoil);

	txBuffer[indexSend++] = pModbusData->addr;
	txBuffer[indexSend++] = pModbusData->functionCode;
	txBuffer[indexSend++] = (u8)((pModbusData->startAddr >> 8) & 0xff);
	txBuffer[indexSend++] = (u8)(pModbusData->startAddr & 0xff);
	txBuffer[indexSend++] = (u8)((pModbusData->dat[0] >> 8) & 0xff);
	txBuffer[indexSend++] = (u8)(pModbusData->dat[0] & 0xff);
	validationCRC = CRC16(txBuffer, indexSend);
	txBuffer[indexSend++] = (u8)((validationCRC >> 8) & 0xff);
	txBuffer[indexSend++] = (u8)(validationCRC & 0xff);
	UARTSendString(UART(1), txBuffer, indexSend);
	memset(txBuffer, 0, MAXMODBUS_TX_DATALENGTH);
}

/**************************************
//函数功能：对上位机0x0F写多个线圈处理
//函数返回值：无
//函数形参：无
//时间：2020/06/22
//备注：01 0F 10 03 00 0A 02 CD 01 61 9A
//100A 1009 1008 1007 1006 1005 1004 1003
//	1   1     0    0    1    1    0    1
// 	其余位补0					100C 100B
//								  0    1
*************************************/
void WriteMuilCoils(ModbusData *pModbusData)
{
	u16 validationCRC = 0;
	u16 i = 0;
	u16 j = 0;
	u16 indexSend = 0;
	u16 coilAddr = 0;
	u8 coilValue = 0;
	u8 nByte = 0;
	bool readFlag = false;

	coilAddr = pModbusData->startAddr;
	nByte = pModbusData->dataLen >> 3;
	if (pModbusData->dataLen % 8)
	{
		nByte++;
	}
	if (coilAddr < Coilx(0) || coilAddr > Coilx(MAXCOILNUM) || pModbusData->dataLen > Coilx(MAXCOILNUM) - Coilx(0) + 1 || (pModbusData->startAddr + pModbusData->dataLen) > Coilx(MAXCOILNUM) + 1)
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_ADDR);
		return;
	}
	for (i = 0; i < nByte; i++)
	{
		for (j = 0; j < 8; j++)
		{
			coilValue = (pModbusData->dat[i] >> j) & 0x01;
			SetCoilData(coilAddr, coilValue, ForceMulCoils);
			coilAddr++;
			if (coilAddr >= pModbusData->dataLen + pModbusData->startAddr)
			{
				readFlag = true;
				break;
			}
		}
		if (readFlag)
		{
			break;
		}
	}
	txBuffer[indexSend++] = pModbusData->addr;
	txBuffer[indexSend++] = pModbusData->functionCode;
	txBuffer[indexSend++] = (u8)((pModbusData->startAddr >> 8) & 0xff);
	txBuffer[indexSend++] = (u8)(pModbusData->startAddr & 0xff);
	txBuffer[indexSend++] = (u8)((pModbusData->dataLen >> 8) & 0xff);
	txBuffer[indexSend++] = (u8)(pModbusData->dataLen & 0xff);
	validationCRC = CRC16(txBuffer, indexSend);
	txBuffer[indexSend++] = (u8)((validationCRC >> 8) & 0xff);
	txBuffer[indexSend++] = (u8)(validationCRC & 0xff);
	UARTSendString(UART(1), txBuffer, indexSend);
	memset(txBuffer, 0, MAXMODBUS_TX_DATALENGTH);
}
/**************************************
//函数功能：对上位机06命令写单个寄存器处理
//函数返回值：无
//函数形参：无
//时间：2020/06/22
//备注：无
*************************************/
void WriteSingleReg(ModbusData *pModbusData)
{
	u16 validationCRC = 0;
	u16 indexSend = 0;
	//	u16 regValue = 0;
	// u16 regAddr = 0;

	// regAddr = pModbusData->startAddr;

	//从设备地址不可为0
	if (pModbusData->dat[0] < 0x0000 || pModbusData->dat[0] > 0xFFFF || ((pModbusData->startAddr == LOCALADDRREG) && (pModbusData->dat[0] == 0)))
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_VALUE);
		return;
	}

	if ((pModbusData->startAddr < CHNxReg(0) || pModbusData->startAddr > CHNxReg(MAXAD7124CHNS)) && (pModbusData->startAddr != LOCALADDRREG))
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_ADDR);
		return;
	}

	//业务处理
	WriteRegData(pModbusData->startAddr, pModbusData->dat[0], WriteSinReg);
	if (pModbusData->dat[0] == GetRegData(pModbusData->startAddr, WriteSinReg))
	{
		txBuffer[indexSend++] = pModbusData->addr;
		txBuffer[indexSend++] = pModbusData->functionCode;
		txBuffer[indexSend++] = (u8)((pModbusData->startAddr >> 8) & 0xff);
		txBuffer[indexSend++] = (u8)(pModbusData->startAddr & 0xff);
		txBuffer[indexSend++] = (u8)((pModbusData->dat[0] >> 8) & 0xff);
		txBuffer[indexSend++] = (u8)(pModbusData->dat[0] & 0xff);
		validationCRC = CRC16(txBuffer, indexSend);
		txBuffer[indexSend++] = (u8)((validationCRC >> 8) & 0xff);
		txBuffer[indexSend++] = (u8)(validationCRC & 0xff);
		UARTSendString(UART(1), txBuffer, indexSend);
		memset(txBuffer, 0, MAXMODBUS_TX_DATALENGTH);
	}
	else
	{
		ErrorSend(pModbusData->functionCode, IS_SLAVE_FAILURE);
		return;
	}
}

void WriteMuilRegs(ModbusData *pModbusData)
{
	u16 validationCRC = 0;
	u16 regValue = 0;
	u16 regAddr = 0;
	u8 i, j = 0;
	u8 writeFlag = 0;
	u8 indexSend = 0;

	regAddr = pModbusData->startAddr;
	if (pModbusData->dataLen < 0x0001 || pModbusData->dataLen > 0x007B || pModbusData->nBytes != pModbusData->dataLen << 1)
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_VALUE);
		return;
	}
	if (regAddr < InputRegx(0) || regAddr > InputRegx(MAXINPUTREGNUM) || regAddr + pModbusData->dataLen > InputRegx(MAXINPUTREGNUM))
	{
		ErrorSend(pModbusData->functionCode, IS_INVALID_DATA_ADDR);
		return;
	}
	//业务处理
	for (i = 1; i <= pModbusData->dataLen; i++)
	{

		regValue = pModbusData->dat[i];
		WriteRegData(regAddr, regValue, WriteMulRegs);
		if (regValue == GetRegData(regAddr, WriteMulRegs))
		{
			writeFlag += 1;
		}
		regAddr++;
	}
	if (writeFlag == pModbusData->dataLen)
	{
		txBuffer[indexSend++] = pModbusData->addr;
		txBuffer[indexSend++] = pModbusData->functionCode;
		txBuffer[indexSend++] = (u8)((pModbusData->startAddr >> 8) & 0xff);
		txBuffer[indexSend++] = (u8)(pModbusData->startAddr & 0xff);
		txBuffer[indexSend++] = (u8)((pModbusData->dataLen >> 8) & 0xff);
		txBuffer[indexSend++] = (u8)(pModbusData->dataLen & 0xff);
		validationCRC = CRC16(txBuffer, indexSend);
		txBuffer[indexSend++] = (u8)((validationCRC >> 8) & 0xff);
		txBuffer[indexSend++] = (u8)(validationCRC & 0xff);
		UARTSendString(UART(1), txBuffer, indexSend);
		memset(txBuffer, 0, MAXMODBUS_TX_DATALENGTH);
	}
	else
	{
		ErrorSend(pModbusData->functionCode, IS_SLAVE_FAILURE);
		return;
	}
}

u8 GetCoilData(u16 coilAddr, u8 functionCode)
{
	switch (functionCode)
	{
	case ReadCoilSta:
	case ReadInputDis:
		return coilValues[coilAddr];
	default:
		break;
	}
	return 0;
}

void SetCoilData(u16 coilAddr, u8 coilValue, u8 functionCode)
{
	switch (functionCode)
	{
	case WriteSinReg:
	case ForceMulCoils:
		coilValues[coilAddr] = coilValue;
	default:
		break;
	}
}
void WriteRegData(u16 regAddr, u16 regValue, u8 functionCode)
{
	switch (functionCode)
	{
	case WriteSinReg:
	case WriteMulRegs:
		if (regAddr == LOCALADDRREG)
		{
			localAddr = (u8)regValue;
		}
		else
		{
			inputRegValues[regAddr] = regValue;
		}
		break;
	default:
		break;
	}
}

u16 GetRegData(u16 regAddr, u8 functionCode)
{
	u16 regValue = 0;
	if (regAddr == LOCALADDRREG)
	{
		return (u8)localAddr;
	}
	switch (functionCode)
	{
	case ReadHoldReg:
		regValue = chnValues[(u8)(regAddr)];
		break;
	case ReadInputReg:
		regValue = inputRegValues[(u8)(regAddr)];
		break;
	case WriteSinReg:
	case WriteMulRegs:
		regValue = inputRegValues[regAddr];
		break;
	default:
		break;
	}
	// regValue = *(volatile u16 *)regAddr;
	return regValue;
}
