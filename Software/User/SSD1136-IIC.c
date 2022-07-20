/**********************************************************************************
 * 程序名:    SSD1306驱动程序	
 * 作者:      DaveoCKII			
 * 日期:      2020.3.12			
 * 版本:      STC12C5A60S2 		
 **********************************************************************************/

#ifndef _SSD1306_H_
#define _SSD1306_H_

#include <STC12C5A60S3.H>
//------------------------------------定义列表------------------------------------//
sbit SCL = P3^4;	// 时钟线
sbit SDA = P3^3;	// 数据线
//------------------------------------函数列表------------------------------------//
void OLED_Init(void);						// OLED 初始化
void OLED_Clear(void);						// OLED 清屏
void OLED_WriteCmd(unsigned char cmd);		// OLED 单次写命令
void OLED_WriteDat(unsigned char dat);		// OLED 单次写数据
void OLED_WriteC(unsigned char cmd);		// OLED 连续写命令	在结尾要加上IIC_STOP();
void OLED_WriteD(unsigned char dat);		// OLED 连续写数据	在结尾要加上IIC_STOP();
void OLED_Frame(unsigned char P[8][128]);	// OLED 一帧图像写入
//------------------------------------内部函数------------------------------------//
static void IIC_START(void);				// IIC_开始信号	(重开始信号用此替代)
static void IIC_STOP(void); 				// IIC_结束信号
static unsigned char IIC_WaitACK(void);		// IIC_等待应答		返回值: 0:NACK 1:ACK 
static void IIC_Write(unsigned char dat);	// IIC_写数据函数	参数:要写入的数据
static unsigned char IIC_Read(void);		// IIC_读数据函数	返回值:读到的数据
static void delay1us(void);					// 延时1us    
//------------------------------------函数内容------------------------------------//

void OLED_WriteD(unsigned char dat)
{
	IIC_START();		// 通信开始
	IIC_Write(0X78);	// 写从机地址'0111 100' 读写符号'0'
	IIC_WaitACK();
	IIC_Write(0X40);	// 写数据 Co='0' C/D='100 0000'
	IIC_WaitACK();
	IIC_Write(dat);		// 写入数据
	IIC_WaitACK();
}

void OLED_WriteC(unsigned char cmd)
{
	IIC_START();		// 通信开始
	IIC_Write(0X78);	// 写从机地址'0111 100' 读写符号'0'
	IIC_WaitACK();
	IIC_Write(0X00);	// 写命令 Co='0' C/D='000 0000'
	IIC_WaitACK();
	IIC_Write(cmd);		// 写入命令
	IIC_WaitACK();
}

void OLED_WriteDat(unsigned char dat)
{
	OLED_WriteD(dat);
	IIC_STOP();			// 通信结束
}

void OLED_WriteCmd(unsigned char cmd)
{
	OLED_WriteC(cmd);
	IIC_STOP();			// 通信结束
}

void OLED_Init(void)
{	
	OLED_WriteC(0XAE);		// 关OLED显示
	// 基础设置
	OLED_WriteC(0XA4);		// 输出GDDRAM内容	
	OLED_WriteC(0XA6);		// 正常显示(1亮0灭)	
	OLED_WriteC(0X81);		// 设置对比度		
	OLED_WriteC(0X7F);		// 第127级对比度	
	// COM和SEG输出设置
	OLED_WriteC(0XD3);		// 设置垂直显示偏移(向上)
	OLED_WriteC(0X00);		// 偏移0行					
	OLED_WriteC(0X40);		// 设置GDDRAM起始行 0		
	OLED_WriteC(0XA8);		// 设置MUX数 (显示行数)		
	OLED_WriteC(0X3F);		//  MUX=63	 (显示63行)			
	OLED_WriteC(0XA1);		// 左右反置关(段重映射)		
	OLED_WriteC(0XC8);		// 上下反置关(行重映射)		
	OLED_WriteC(0XDA);		// 设置COM引脚配置		
	OLED_WriteC(0X02);		// 序列COM配置,禁用左右反置
	// 时钟设置
	OLED_WriteC(0XD5);		// 设置DCLK分频和OSC频率
	OLED_WriteC(0X80);		// 无分频,第8级OSC频率	
	// 开OLED
	OLED_WriteC(0X8D);		// 启用电荷泵
	OLED_WriteC(0X14);		// 启用电荷泵
	OLED_WriteC(0XAF);		// 开OLED显示
	
	IIC_STOP();
}

void OLED_Clear(void)
{
	unsigned char i,j;
	
	OLED_WriteC(0X00);		// 水平寻址模式 
	OLED_WriteC(0X21);		// 设置列起始和结束地址
	OLED_WriteC(0X00);		// 列起始地址 0
	OLED_WriteC(0X7F);		// 列终止地址 127
	OLED_WriteC(0X22);		// 设置页起始和结束地址
	OLED_WriteC(0X00);		// 页起始地址 0
	OLED_WriteC(0X07);		// 页终止地址 7
	
	for(i=0; i<8; i++)		// 写入一帧'0'
		for(j=0; j<128; j++)
			OLED_WriteD(0X00);
	
	IIC_STOP();
}

void OLED_Frame(unsigned char P[8][128])
{
	unsigned char i,j;
	
	OLED_WriteC(0X20);	// 设置GDDRAM模式
	OLED_WriteC(0X00);	// 水平寻址模式 
	OLED_WriteC(0X21);	// 设置列起始和结束地址
	OLED_WriteC(0X00);	// 列起始地址 0
	OLED_WriteC(0X7F);	// 列终止地址 127
	OLED_WriteC(0X22);	// 设置页起始和结束地址
	OLED_WriteC(0X00);	// 页起始地址 0
	OLED_WriteC(0X07);	// 页终止地址 7
	
	for(i=0; i<8; i++)		// 写入一帧数据
		for(j=0; j<128; j++)
			OLED_WriteDat(P[i][j]);
	
	IIC_STOP();
}

//----------------------------------内部函数内容-----------------------------------//

static void IIC_START(void)
{
	SCL = 0;		// SCL拉低 防止可能出现的各种误动作
	delay1us();
	SDA = 1;		// SDA拉高 
	SCL = 1;		// SCL拉高 准备发出起始信号
	delay1us();		
	SDA = 0;		// SDA拉低 发出起始信号
	SCL = 0;		// SCL拉低 开始传输
}

static void IIC_STOP(void)
{
	SCL = 0;		// SCL拉低 防止可能出现的各种误动作
	SDA = 0;		// SDA拉低
	SCL = 1;		// SCL拉高 准备发出结束信号
	delay1us();		
	SDA = 1;		// SDA拉高 发出结束信号
}

static unsigned char IIC_WaitACK(void)
{
	bit s;
	SCL = 0;		// 拉低SCL
	delay1us();
	SDA = 1;		// 拉高SDA 主机释放总线
	delay1us();
	SCL = 1;		// 拉高SCL 
	delay1us();		
	s = SDA;		// 采集SDA信号线状态
	delay1us();		
	SCL = 0;		// 拉低SCL 结束询问ACK
	if(s)
		return 0;	// 无应答(ACK)
	else
		return 1;	// 有应答(ACK)	
}

static void IIC_Write(unsigned char dat)
{
	unsigned char i;
	for(i=0; i<8; i++) 
	{
		SCL = 0; 			// 拉低SCL 准备写数据
		SDA = dat & 0X80;	// 写数据
		dat <<= 1;			// 数据格式:高位在前
		SCL = 1;			// 拉高SCL 发送数据
		delay1us();
		SCL = 0;			// 拉低SCL 结束发送
	}
}

static void delay1us(void)
{	

}

//---------------------------------------------------------------------------------//
//------------------------------------定义结束--------------------------------------//
//---------------------------------------------------------------------------------//

#endif
