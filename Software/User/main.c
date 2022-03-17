#include "config.h"

/****************************************/
u8 localAddr = 0x01;
u8 code mac[16] = "DC_TT_0_001_0001";     //硬件地址
u8 code version[16] = "C51_LPD_TT0_0001"; //程序版本

/****************************************/

///////////////////////////////////////////////////////////
//需要做超时判断，要增加程序鲁棒性
//////////////////////////////////////////////////////////

// #define CodeToFloat(code) ((float)((code - 0x800000) >> (int)setup.pga) * BipolarDivide)
// #define CodeToFloat(code) ((float)(code >> (int)setup.pga) * SinglepolarDivide)
///////////////////////////////////////////////////////////
//串口接收的MODBUS
SqQueue sq;         //存储大量到来数据
SqQueue nDataCntSq; //存储每次到来的有效数据（经过CRC），含CRC的2字节数量

//////////////////////////////////////////////
//AD7124配置，全局变量，方便上位机修改配置和通道
Channel chn[MAXAD7124CHNS];
Setup setup[MAXAD7124SETUPS];

AdcControl adcControl;
Ad7124_8_IO ad7124_8_io;
//////////////////////////////////////////////
// //用于校准
// u32 offset[8] = {0};
// u32 gain[8] = {0};
/////////////////////////////////////////////
int chnValues[MAXAD7124CHNS] = {0};       //存储通道转换后的温度值，10倍放大（BipolarDivisor）
u16 inputRegValues[MAXINPUTREGNUM] = {0}; //Modbus写入测试
u8 coilValues[MAXCOILNUM] = {0};          //离散量数组，一个字节存一个状态
AD7124_REG chnReg;                        //数据
AD7124_REG *pChnReg = &chnReg;            //数据指针

// pChnReg = &chnReg;
///////////////////////////////////////////
KFPs kfps;
KFP kfp[MAXAD7124CHNS];
KFP *pKfp;
// KFP *kfp = &_InitialKFP;
// rx_buffer_modbus.state = IS_ADDR;
////////////////////////////////////////////////
float fRes[MAXAD7124CHNS] = {0.0};
// MyFloat fTemp[MAXAD7124CHNS];
float fKpfTemp[MAXAD7124CHNS] = 0.0;
int fTemp[MAXAD7124CHNS] = 0;
/////////////////////////////////////////////
bool adcAvailable = false;
bool dacFlag = false;
u8 dacChn = 0; //对应MAXAD7124CHNS次主动显示（上报模拟量4-20ma和0-4.0V），构成一个循环；dacFlag在timer4中断置位
//////////////////////////////////////////////
WDT_InitTypeDef *wdt; //看门狗
/////////////////////////////////////////////
void TimerInit(void);
void EEPROMInit(void);
void SysInit(void);

void main()
{

    u8 i = 0;

    memset(pChnReg, 0, sizeof(chnReg));
    pChnReg->addr = AD7124_COMM_REG;

    pKfp = kfp;
    for (i = 0; i < MAXAD7124CHNS; i++)
    {
        *(pKfp + i) = _InitialKFP;
    }

    SysInit();

    {
        // SPISS = 1;
        // DacCS = 0;
        // DacCLK = 0;
        // DacSDI = 0;
        // DacLD = 0;
    }

    delay_X_ms(100);

    //初始化寄存器值为传感器值
    {
        // for (i = 0; i <= 16; i++)
        // {
        //     ADC(pChnReg);                                                                                            // FS=2047时需要80ms一次转换
        //     fRes[pChnReg->addr] = (float)((pChnReg->value - 0x800000) >> setup[pChnReg->addr].pga) * BipolarDivisor; ////换算后单位为Ω，跑完需要55us
        //     if (fRes >= 100)
        //     {
        //         fTemp = 10 * Res2Temp_Pt100_ResLagrgerThan100(kalmanFilter(pKfp + pChnReg->addr, fRes[pChnReg->addr])); //BipolarDivisor为e-13，需要800us
        //     }
        //     else
        //     {
        //         fTemp = 10 * Res2Temp_Pt100_ResLessThan100(kalmanFilter(pKfp + pChnReg->addr, fRes[pChnReg->addr])); //BipolarDivisor为e-13，需要800us
        //     }
        // }
        // chnValues[pChnReg->addr] = (int)(fTemp);
        adcAvailable = true;
        dacFlag = true;
        SPISS = 0;
        // Timer4_stop();
        // Timer4_start();
    }

    while (1)
    {
        // spi_write_read(AD7124_COMM_REG_RD | AD7124_ID_REG);
        // spi_write_read(0xff);

        delay_X_ms(1);
        if (adcAvailable)
        {
            adcAvailable = false;
            // ADCTrig(pChnReg);
            ADC(pChnReg); // FS=2047时需要80ms一次转换
            // pChnReg->value = 0x00000000;
            // spi_write_read(AD7124_COMM_REG_RD | AD7124_DATA_REG);
            // pChnReg->value |= (u32)spi_write_read(0x00);
            // pChnReg->value <<= 8;
            // pChnReg->value |= (u32)spi_write_read(0x00);
            // pChnReg->value <<= 8;
            // pChnReg->value |= (u32)spi_write_read(0x00);
            // // spi_write_read(AD7124_COMM_REG_RD | AD7124_COMM_REG);
            // pChnReg->addr = spi_write_read(0x00);
            // // SPISS = 1;

            if (pChnReg->addr <= MAXAD7124CHNS)
            {
                fRes[pChnReg->addr] = (float)((pChnReg->value - 0x800000) >> setup[pChnReg->addr].pga) * BipolarDivisor; ////换算后单位为Ω，跑完需要55us
                                                                                                                         // fRes[pChnReg->addr] = (float)((pChnReg->value - 0x800000) >> setup[pChnReg->addr].pga) * 2127 * BipolarDivisor; //阻值未转化为温度，跑完需要55us，
                fKpfTemp[pChnReg->addr] = kalmanFilter(pKfp + pChnReg->addr, fRes[pChnReg->addr]);
                if (fRes >= 100)
                {
                    fTemp[pChnReg->addr] = 10 * Res2Temp_Pt100_ResLagrgerThan100(fKpfTemp[pChnReg->addr]); //BipolarDivisor为e-13，需要800us
                }
                else
                {
                    fTemp[pChnReg->addr] = 10 * Res2Temp_Pt100_ResLessThan100(fKpfTemp[pChnReg->addr]); //BipolarDivisor为e-13，需要800us
                }
                chnValues[pChnReg->addr] = (int)(fTemp[pChnReg->addr]); //5us
            }
            // psw2_st = P_SW2;
            // P_SW2 |= 0x80;
            // P1INTE = 0x01;
            // P_SW2 = psw2_st;
            // delay_X_ms(5000);
            // spi_write_read(AD7124_COMM_REG_RD | AD7124_ERR_REG);
            // spi_write_read(0xff);
            // spi_write_read(0xff);
            // spi_write_read(0xff);
            // delay_X_ms(5000);
        }

        if (dacFlag) //循环显示各通道，实际不需要
        {
            DAC((u16)(5 * (fKpfTemp[dacChn] + 200))); //耗时1ms
            // UARTSendByte(UART(1), dacChn);
            // DAC((u16)(5 * (fKpfTemp[0] + 200))); //耗时1ms
            // DAC(0); //耗时1ms
        }
        if (GetQueueLength(&sq))
        {
            ModbusDataParse(); //耗时2ms
        }
        WDT_Clear();

        // UARTSendByte(UART(1), setup[0].offset >> 16 & 0xff);
        // UARTSendByte(UART(1), setup[0].offset >> 8 & 0xff);
        // UARTSendByte(UART(1), setup[0].offset & 0xff);
        // UARTSendByte(UART(1), 0xff);
        // UARTSendByte(UART(1), setup[0].gain >> 16 & 0xff);
        // UARTSendByte(UART(1), setup[0].gain >> 8 & 0xff);
        // UARTSendByte(UART(1), setup[0].gain & 0xff);
        // UARTSendByte(UART(1), 0xff);
        // UARTSendByte(UART(1), 0xff);
    }
}
void SysInit(void)
{

    u8 i = 0; //初始化chn，setup等

    IO_init();

    QueueInit(&sq);
    QueueInit(&nDataCntSq);
    SpiInit(); //initial SPI

    // P_SW2 = 0x80;
    // CKSEL = 0x00;   //选择内部IRC；如选择外部时钟，需要等待外部时钟稳定。
    // CLKDIV = 0x00;  //时钟不分频
    // MCLKOCR = 0x82; //系统时钟输出
    // P_SW2 = 0x00;

    // IE2 |= ESPI;

    for (i = 0; i < MAXAD7124CHNS; i++)
    {
        chn[i] = AD7124_8_ChannelPreConfig(AD7124_CH0_MAP_REG + i, AD7124_CH_MAP_REG_CH_ENABLE, AD7124_CH_MAP_REG_SETUP(i), AD7124_CH_MAP_REG_AINP(i + 1), AD7124_CH_MAP_REG_AINM(i)); //端口从小端开始配置
    }

    for (i = 0; i < MAXAD7124SETUPS; i++)
    {
        setup[i] = AD7124_8_SetupPreConfig(AD7124_CFG0_REG + i, AD7124_CFG_REG_BIPOLAR, AD7124_CFG_REG_BURNOUT(0), AD7124_CFG_REG_REF_BUFP, AD7124_CFG_REG_REF_BUFM, AD7124_CFG_REG_AIN_BUFP, AD7124_CFG_REG_AIN_BUFM, AD7124_CFG_REG_REF_SEL(0), AD7124_CFG_REG_PGA(4),
                                           AD7124_FILT0_REG + i, AD7124_FILT_REG_FILTER(0), AD7124_FILT_REG_REJ60, AD7124_FILT_REG_POST_FILTER(0), AD7124_FILT_REG_SINGLE_CYCLE, AD7124_FILT_REG_FS(480),
                                           AD7124_OFFS0_REG + i, 0x800000,
                                           AD7124_GAIN0_REG + i, 0x5fffff);
    }

    adcControl = AD7124_8_AdcControlPreConfig(AD7124_ADC_CTRL_REG, AD7124_ADC_CTRL_REG_DOUT_RDY_DEL, !AD7124_ADC_CTRL_REG_CONT_READ, AD7124_ADC_CTRL_REG_DATA_STATUS, !AD7124_ADC_CTRL_REG_CS_EN, !AD7124_ADC_CTRL_REG_REF_EN, AD7124_ADC_CTRL_REG_POWER_MODE(3), AD7124_ADC_CTRL_REG_MODE(0), AD7124_ADC_CTRL_REG_CLK_SEL(0));
    //io配置与电路图相关
    ad7124_8_io = AD7124_8_ioPreConfig(!AD7124_8_IO_CTRL1_REG_GPIO_DAT1 | !AD7124_8_IO_CTRL1_REG_GPIO_DAT2 | !AD7124_8_IO_CTRL1_REG_GPIO_DAT3 | !AD7124_8_IO_CTRL1_REG_GPIO_DAT4,
                                       !AD7124_8_IO_CTRL1_REG_GPIO_CTRL1 | !AD7124_8_IO_CTRL1_REG_GPIO_CTRL2 | !AD7124_8_IO_CTRL1_REG_GPIO_CTRL3 | !AD7124_8_IO_CTRL1_REG_GPIO_CTRL4,
                                       AD7124_IO_CTRL1_REG_PDSW, AD7124_IO_CTRL1_REG_IOUT1(4) | AD7124_IO_CTRL1_REG_IOUT0(4),
                                       AD7124_IO_CTRL1_REG_IOUT_CH1(11) | AD7124_IO_CTRL1_REG_IOUT_CH0(8),
                                       !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS0 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS1 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS2 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS3 |
                                           !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS4 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS5 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS6 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS7 |
                                           !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS8 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS9 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS10 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS11 |
                                           !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS12 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS13 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS14 | !AD7124_8_IO_CTRL2_REG_GPIO_VBIAS15);

    SPISS = 1;
    delay_X_ms(10);
    SPISS = 0;
    delay_X_ms(10);

    // EA = 1; //使用spi需要开，用完即关。
    delay_X_us(50);

    for (i = 0; i < 64; i++)
    {
        spi_write_read(0xff);
    }

    spi_write_read(AD7124_COMM_REG_RD | AD7124_COMM_REG); //清POR_FLAG标志位
    spi_write_read(0xff);
    delay_X_ms(30);

    //AD7124_8_init_Setup()未配置gain和offset，此处配置
    //失调寄存器写入时，必须保证ADC处于待机或空闲
    spi_write_read(AD7124_COMM_REG_WR | AD7124_ADC_CTRL_REG);
    spi_write_read(0x10);
    spi_write_read(AD7124_ADC_CTRL_REG_POWER_MODE(1) | AD7124_ADC_CTRL_REG_MODE(4));
    delay_X_ms(30);

    spi_write_read(AD7124_COMM_REG_RD | AD7124_COMM_REG); //空闲后，清POR_FLAG标志位
    spi_write_read(0xff);
    for (i = 0; i < MAXAD7124CHNS; i++)
    {
        if (setup[i].pga >= 1) //增益改变需校准，默认增益为1
        {
            InternalFullScaleCalibrate(&setup[i]);
            spi_write_read(AD7124_COMM_REG_RD | AD7124_COMM_REG); //校准后，清POR_FLAG标志位
            spi_write_read(0xff);
        }
        InternalZeroScaleCalibrate(&setup[i]);
        spi_write_read(AD7124_COMM_REG_RD | AD7124_COMM_REG); //校准后，清POR_FLAG标志位
        spi_write_read(0xff);
        delay_X_ms(30);
    }

    for (i = 0; i < MAXAD7124CHNS; i++)
    {
        AD7124_8_init_SingleChannelConfiguraton(chn[i]);
        delay_X_ms(30);
        AD7124_8_init_Setup(setup[i]);
        delay_X_ms(30);
    }

    Ad7124_8_init_io(ad7124_8_io);
    delay_X_ms(30);
    AD7124_8_init_AdcControl(adcControl);
    delay_X_ms(30);

    //使能INT1中断
    // IT1 = 1;
    // EX1 = 1;
    INT_init(1, 0); //管脚与DOUT重合

    //使能INT3中断
    // INT_CLKO = EX3;

    // //使能P1.6口中断
    // P_SW2 |= 0x80;
    // P1IM0 = 0x00;
    // P1IM1 = 0xff;
    // P1INTE = 0x00;
    // P_SW2 &= ~0x80;
    /************************************/
    EEPROMInit();
    /************************************/
    TimerInit();
    //看门狗
    wdt->WDT_Enable = ENABLE;
    wdt->WDT_IDLE_Mode = 1;
    wdt->WDT_PS = D_WDT_SCALE_256;
    WDT_Inilize(wdt);
    EA = 1;
    //统一在主函数里开中断
}

void TimerInit(void)
{
    Timer1_init(DISABLE, BAUD, 0x00, true, DISABLE);
    Timer2_init(ENABLE, 598, 0x00, true, DISABLE);           //15ms,15ms*100*2 =3s dac
    Timer3_init(ENABLE, Timer_xUs_yT(10, 1), true, DISABLE); //用来测T3.5和T1.5，Timer3用1T，12T在20us以下误差、1T在5us以下误差大;
    Timer4_init(ENABLE, 9550, true, DISABLE);                //约625us一次中断，用来采集adc数据
    UARTInit(UART(1), Timer(1), S1_IO_P30P31, ENABLE);       //initial UART。
}

//3个参数：1.AD7124手册默认参数（不写也行，code里有ad7124Regs）；2.设备出厂的AD7124校准参数；3.程序运行时校准的AD7124参数
//在烧写程序时，需要选择2个扇区（1k）
//首先判断扇区1有无设备出厂的AD7124参数，没有则写入；
void EEPROMInit(void)
{
    u8 nRegs = 0;          //保存的寄存器个数
    u16 regShift = 0x6400; //扇区偏移
    u8 eeDataBuff[3] = {0};

    IapRead(regShift, eeDataBuff, 3);
    // eeDataBuff[0] = IapRead(regShift++);
    // eeDataBuff[1] = IapRead(regShift++);
    // eeDataBuff[2] = IapRead(regShift);
    // regShift = 0x0000;
    //空单片机运行
    if ((eeDataBuff[0] != 0x00) || (eeDataBuff[1] != 0x00) || (eeDataBuff[2] != 0x80))
    {
        IapErase(regShift); //擦除第一个扇区

        for (nRegs = 0; nRegs < 8; nRegs++)
        {
            eeDataBuff[0] = ad7124Regs[AD7124_Offset_0 + nRegs].value & 0xff;
            eeDataBuff[1] = ad7124Regs[AD7124_Offset_0 + nRegs].value >> 8 & 0xff;
            eeDataBuff[2] = ad7124Regs[AD7124_Offset_0 + nRegs].value >> 16 & 0xff;
            // IapWrite(0x0000 + nRegs * 3 + regShift, eeDataBuff, 3);
            // IapRead(0x0000 + nRegs * 3 + regShift, eeDataBuff, 3);
            // IapWrite(0x0000 + nRegs * 3 + regShift, eeDataBuff[0]);
            // IapWrite(0x0000 + nRegs * 3 + regShift + 1, eeDataBuff[1]);
            // IapWrite(0x0000 + nRegs * 3 + regShift + 2, eeDataBuff[2]);
            // memset(eeDataBuff, 0xff, 3);
            // eeDataBuff[0] = IapRead(0x0000 + nRegs * 3 + regShift);
            // eeDataBuff[1] = IapRead(0x0000 + nRegs * 3 + regShift + 1);
            // eeDataBuff[2] = IapRead(0x0000 + nRegs * 3 + regShift + 2);
        }
        // memset(eeDataBuff, 0xff, 3);
        // IapRead(regShift + 0x0003, eeDataBuff, 3);

        for (nRegs = 0; nRegs < 8; nRegs++)
        {
            eeDataBuff[0] = ad7124Regs[AD7124_Gain_0 + nRegs].value & 0xff;
            eeDataBuff[1] = ad7124Regs[AD7124_Gain_0 + nRegs].value >> 8 & 0xff;
            eeDataBuff[2] = ad7124Regs[AD7124_Gain_0 + nRegs].value >> 16 & 0xff;
            // IapWrite(0x0018 + nRegs * 3 + regShift, eeDataBuff, 3);
            // IapRead(0x0018 + nRegs * 3 + regShift, eeDataBuff, 3);
            // IapWrite(0x0018 + nRegs * 3 + regShift, eeDataBuff[0]);
            // IapWrite(0x0018 + nRegs * 3 + regShift + 1, eeDataBuff[1]);
            // IapWrite(0x0018 + nRegs * 3 + regShift + 2, eeDataBuff[2]);
            // memset(eeDataBuff, 0xff, 3);
            // eeDataBuff[0] = IapRead(0x0018 + nRegs * 3 + regShift);
            // eeDataBuff[1] = IapRead(0x0018 + nRegs * 3 + regShift + 1);
            // eeDataBuff[2] = IapRead(0x0018 + nRegs * 3 + regShift + 2);
        }
        // memset(eeDataBuff, 0xff, 3);
        // IapRead(regShift + 0x0021, eeDataBuff, 3);
    }
    //写入设备出厂校准参数
    regShift += 0x0200;
    IapErase(regShift); //擦除第2个扇区
    // memset(eeDataBuff, 0xff, 3);
    // IapRead(0x6400, eeDataBuff, 3);
    // memset(eeDataBuff, 0xff, 3);
    // IapRead(0x6620, eeDataBuff, 3);
    for (nRegs = 0; nRegs < 8; nRegs++)
    {
        eeDataBuff[0] = setup[nRegs].offset & 0xff;
        eeDataBuff[1] = setup[nRegs].offset >> 8 & 0xff;
        eeDataBuff[2] = setup[nRegs].offset >> 16 & 0xff;
        // IapWrite(0x0000 + nRegs * 3 + regShift, eeDataBuff, 3);
        // IapRead(0x0000 + nRegs * 3 + regShift, eeDataBuff, 3);
        // IapWrite(0x0000 + nRegs * 3 + regShift, eeDataBuff[0]);
        // IapWrite(0x0000 + nRegs * 3 + regShift + 1, eeDataBuff[1]);
        // IapWrite(0x0000 + nRegs * 3 + regShift + 2, eeDataBuff[2]);
        // memset(eeDataBuff, 0xff, 3);
        // eeDataBuff[0] = IapRead(0x0000 + nRegs * 3 + regShift);
        // eeDataBuff[1] = IapRead(0x0000 + nRegs * 3 + regShift + 1);
        // eeDataBuff[2] = IapRead(0x0000 + nRegs * 3 + regShift + 2);
    }
    // memset(eeDataBuff, 0xff, 3);
    // IapRead(regShift + 0x0203, eeDataBuff, 3);

    for (nRegs = 0; nRegs < 8; nRegs++)
    {
        eeDataBuff[0] = setup[nRegs].gain & 0xff;
        eeDataBuff[1] = setup[nRegs].gain >> 8 & 0xff;
        eeDataBuff[2] = setup[nRegs].gain >> 16 & 0xff;
        // IapWrite(0x0018 + nRegs * 3 + regShift, eeDataBuff, 3);
        // IapRead(0x0018 + nRegs * 3 + regShift, eeDataBuff, 3);
        // IapWrite(0x0018 + nRegs * 3 + regShift, eeDataBuff[0]);
        // IapWrite(0x0018 + nRegs * 3 + regShift + 1, eeDataBuff[1]);
        // IapWrite(0x0018 + nRegs * 3 + regShift + 2, eeDataBuff[2]);
        // memset(eeDataBuff, 0xff, 3);
        // eeDataBuff[0] = IapRead(0x0018 + nRegs * 3 + regShift);
        // eeDataBuff[1] = IapRead(0x0018 + nRegs * 3 + regShift + 1);
        // eeDataBuff[2] = IapRead(0x0018 + nRegs * 3 + regShift + 2);
    }
    // memset(eeDataBuff, 0xff, 3);
    // IapRead(regShift + 0x0221, eeDataBuff, 3);
    // // IapRead(0x0000, eeDataBuff, 3);
    // // IapRead(0x0200, eeDataBuff, 3);
    // memset(eeDataBuff, 0xff, 3);
    // IapRead(0x6400, eeDataBuff, 3);
    // memset(eeDataBuff, 0xff, 3);
    // IapRead(0x6620, eeDataBuff, 3);
}
