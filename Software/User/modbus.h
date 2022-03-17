#ifndef __MODBUS_H
#define __MODBUS_H

#include "config.h"

// #define MODBUS_T1_5_Timer_1T (u32)(1.5 * 11 * Main_Fosc / BAUD)       //modbus t1.5
// #define MODBUS_T1_5_Timer_12T (u32)(1.5 * 11 * Main_Fosc / 12 / BAUD) //modbus t1.5
// #define MODBUS_T2_Timer_1T (u32)(2 * 11 * Main_Fosc / BAUD)           //modbus t2
// #define MODBUS_T2_Timer_12T (u32)(2 * 11 * Main_Fosc / 12 / BAUD)     //modbus t2
// #define MODBUS_T3_5_Timer_1T (u32)(3.5 * 11 * Main_Fosc / BAUD)       //modbus t3.5
// #define MODBUS_T3_5_Timer_12T (u32)(3.5 * 11 * Main_Fosc / 12 / BAUD) //modbus t3.5
// #define MODBUS_T_x_Timer_yT(x, y) (u32)(x * 11 * Main_Fosc / y / BAUD) //modbus 数据有效性判定：单位为个机器周期，x为字符数，y为timer工作方式：1或者12T
#define MODBUS_T_x_CNT(x) (u16)(x * 11e5 / BAUD) //modbus 数据有效性判定：单位为个10us，x为字符数，建议主站发送帧间隔为5字符以上（从站最长接收准备时间间隔为5=1.5+3.5）

#define ModbusTimerRunningMachineCycle 12 //modbus检测帧和字符有效性的相关定时器机器周期

#define ReadCoilSta 0x01     //读线圈量
#define ReadInputDis 0x02    //读输入离散量
#define ReadHoldReg 0x03     //读保持寄存器
#define ReadInputReg 0x04    //读输入寄存器
#define ForceSingleCoil 0x05 //写位
#define WriteSinReg 0x06     //写单个寄存器
#define ForceMulCoils 0x0F   //写多位
#define WriteMulRegs 0x10    //写多个寄存器

// #define OFFSETREG 40000
// #define DOOFFSETREG 00001
// #define DIOFFSETREG 10001
// #define AIOFFSETREG 30001
// #define AOOFFSETREG 40001

//线圈0-7
#define MAXCOILNUM 8
#define Coilx(x) (x)
// #define Coilx_y(x, y) (x >> 3 + y)
// #define Coil0_0 0000
// #define Coil0_1 0001
// #define Coil0_2 0002
// #define Coil0_3 0003
// #define Coil0_4 0004
// #define Coil0_5 0005
// #define Coil0_6 0006
// #define Coil0_7 0007

//保持寄存器(地址寄存器)
#define LOCALADDRREG 0x2000
//保持寄存器(MAC寄存器)
#define MacReg 0x2100 //32Byte版本号,从0x2100~21FF
//保持寄存器(版本号寄存器)
#define VersionReg 0x2200 //32Byte版本号,从0x2200~0x22FF

//保持寄存器(温度寄存器)
#define CHNxReg(x) (x) //和16个通道数据对应
// #define CHN0Reg 0x3000            //
// #define CHN1Reg 0x3001  //
// #define CHN2Reg 0x3002  //
// #define CHN3Reg 0x3003  //
// #define CHN4Reg 0x3004  //
// #define CHN5Reg 0x3005  //
// #define CHN6Reg 0x3006  //
// #define CHN7Reg 0x3007  //
// #define CHN8Reg 0x3008  //
// #define CHN9Reg 0x3009  //
// #define CHN10Reg 0x300a //
// #define CHN11Reg 0x300b //
// #define CHN12Reg 0x300c //
// #define CHN13Reg 0x300d //
// #define CHN14Reg 0x300e //
// #define CHN15Reg 0x300f //
//输入寄存器(测试用)
#define InputRegx(x) (x) //
//保持寄存器(测试用)
#define HoldxReg(x) (x) //本地程序中保持寄存器为CHNxReg(x)

#define InputRegNum MAXINPUTREGNUM
#define HoldRegNUm MAXHOLDREGNUM

#define MAXMODBUSDATALENGTH 256
// #define MAXMODBUS_TX_DATALENGTH ((MAXINPUTREGNUM + MAXHOLDREGNUM) * 2 + 5) //可以省下一定的xdata空间;如有其它保持或输入寄存器，应再加上这些寄存器的数量
#define MAXMODBUS_TX_DATALENGTH MAXMODBUSDATALENGTH
// #define CRC_BYTES_LENGTH 2
// #define CRC16_POLYN 0xa001

typedef enum
{
    IS_INVALID_FUNCTION_CODE = 0x01,   //非法功能码
    IS_INVALID_DATA_ADDR = 0x02,       //非法数据地址
    IS_INVALID_DATA_VALUE = 0x03,      //非法数据值
    IS_SLAVE_FAILURE = 0x04,           //从站设备故障
    IS_CONFIRMED = 0x05,               //确认
    IS_SLAVE_BUSY = 0x06,              //从站设备忙
    IS_STORAGE_PARITY_ERROR = 0x08,    //存储奇偶性差错
    IS_GATEWAY_UNVAILABLE = 0x0A,      //网关路径不可用
    IS_GATEWAY_REPONSE_FAILURED = 0x0B //网关目标设备响应失败

} ErrorCode;

typedef enum
{
    // IS_READY = 0,	 //准备发送或接收数据
    IS_IDLE = 0,              //T3.5状态
    IS_ADDR,                  //确认开始接收从站地址
    IS_FunctionCode,          //已接收到起始符号，准备接收长度
    IS_START_ADDR,            //确认起始地址
    IS_DataLen,               //已经接收到长度，准备接收数据
    IS_DATA,                  //已经接收到长度，准备或正在接收数据
    IS_CRC,                   //已经接收到数据，准备计算校验和
    IS_FunctionCode_ABNORMAL, //功能码异常
    IS_VALID                  //数据字节正常
} DataStateEnum;

typedef struct
{
    DataStateEnum state;
    u8 addr;
    u8 functionCode;
    u16 startAddr;
    u16 dataLen;
    u8 nBytes;
    u16 dat[MAXMODBUSDATALENGTH];
} ModbusData;

extern u16 modbusDataGapCnt;

void ModbusDataParse(void);
u8 ModbusDataCheck(ModbusData *pModbusData);
// u16 CRC16(u8 *frame, u8 len);
void ErrorSend(u8 Cmd, u8 errorCode);
void ModbusReadVersion(ModbusData *pModbusData);
void ModbusReadMac(ModbusData *pModbusData);
void ReadCoils(ModbusData *pModbusData);
void ReadHoldRegs(ModbusData *pModbusData);
void ReadInputRegs(ModbusData *pModbusData);
void WriteSingleCoil(ModbusData *pModbusData);
void WriteMuilCoils(ModbusData *pModbusData);
void WriteSingleReg(ModbusData *pModbusData);
void WriteMuilRegs(ModbusData *pModbusData);
u8 GetCoilData(u16 coilAddr, u8 functionCode);
void SetCoilData(u16 coilAddr, u8 dat, u8 functionCode);
void WriteRegData(u16 regAddr, u16 regValue, u8 functionCode);
u16 GetRegData(u16 regAddr, u8 functionCode);
#endif