#include "config.h"

/****************************************/
u8 localAddr = 0x01;
u8 code mac[16] = "DC_TT_0_001_0001";     //Ӳ����ַ
u8 code version[16] = "C51_LPD_TT0_0001"; //����汾

/****************************************/

///////////////////////////////////////////////////////////
//��Ҫ����ʱ�жϣ�Ҫ���ӳ���³����
//////////////////////////////////////////////////////////

// #define CodeToFloat(code) ((float)((code - 0x800000) >> (int)setup.pga) * BipolarDivide)
// #define CodeToFloat(code) ((float)(code >> (int)setup.pga) * SinglepolarDivide)
///////////////////////////////////////////////////////////
//���ڽ��յ�MODBUS
SqQueue sq;         //�洢������������
SqQueue nDataCntSq; //�洢ÿ�ε�������Ч���ݣ�����CRC������CRC��2�ֽ�����

//////////////////////////////////////////////
//AD7124���ã�ȫ�ֱ�����������λ���޸����ú�ͨ��
Channel chn[MAXAD7124CHNS];
Setup setup[MAXAD7124SETUPS];

AdcControl adcControl;
Ad7124_8_IO ad7124_8_io;
//////////////////////////////////////////////
// //����У׼
// u32 offset[8] = {0};
// u32 gain[8] = {0};
/////////////////////////////////////////////
int chnValues[MAXAD7124CHNS] = {0};       //�洢ͨ��ת������¶�ֵ��10���Ŵ�BipolarDivisor��
u16 inputRegValues[MAXINPUTREGNUM] = {0}; //Modbusд�����
u8 coilValues[MAXCOILNUM] = {0};          //��ɢ�����飬һ���ֽڴ�һ��״̬
AD7124_REG chnReg;                        //����
AD7124_REG *pChnReg = &chnReg;            //����ָ��

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
u8 dacChn = 0; //��ӦMAXAD7124CHNS��������ʾ���ϱ�ģ����4-20ma��0-4.0V��������һ��ѭ����dacFlag��timer4�ж���λ
//////////////////////////////////////////////
WDT_InitTypeDef *wdt; //���Ź�
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

    //��ʼ���Ĵ���ֵΪ������ֵ
    {
        // for (i = 0; i <= 16; i++)
        // {
        //     ADC(pChnReg);                                                                                            // FS=2047ʱ��Ҫ80msһ��ת��
        //     fRes[pChnReg->addr] = (float)((pChnReg->value - 0x800000) >> setup[pChnReg->addr].pga) * BipolarDivisor; ////�����λΪ����������Ҫ55us
        //     if (fRes >= 100)
        //     {
        //         fTemp = 10 * Res2Temp_Pt100_ResLagrgerThan100(kalmanFilter(pKfp + pChnReg->addr, fRes[pChnReg->addr])); //BipolarDivisorΪe-13����Ҫ800us
        //     }
        //     else
        //     {
        //         fTemp = 10 * Res2Temp_Pt100_ResLessThan100(kalmanFilter(pKfp + pChnReg->addr, fRes[pChnReg->addr])); //BipolarDivisorΪe-13����Ҫ800us
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
            ADC(pChnReg); // FS=2047ʱ��Ҫ80msһ��ת��
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
                fRes[pChnReg->addr] = (float)((pChnReg->value - 0x800000) >> setup[pChnReg->addr].pga) * BipolarDivisor; ////�����λΪ����������Ҫ55us
                                                                                                                         // fRes[pChnReg->addr] = (float)((pChnReg->value - 0x800000) >> setup[pChnReg->addr].pga) * 2127 * BipolarDivisor; //��ֵδת��Ϊ�¶ȣ�������Ҫ55us��
                fKpfTemp[pChnReg->addr] = kalmanFilter(pKfp + pChnReg->addr, fRes[pChnReg->addr]);
                if (fRes >= 100)
                {
                    fTemp[pChnReg->addr] = 10 * Res2Temp_Pt100_ResLagrgerThan100(fKpfTemp[pChnReg->addr]); //BipolarDivisorΪe-13����Ҫ800us
                }
                else
                {
                    fTemp[pChnReg->addr] = 10 * Res2Temp_Pt100_ResLessThan100(fKpfTemp[pChnReg->addr]); //BipolarDivisorΪe-13����Ҫ800us
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

        if (dacFlag) //ѭ����ʾ��ͨ����ʵ�ʲ���Ҫ
        {
            DAC((u16)(5 * (fKpfTemp[dacChn] + 200))); //��ʱ1ms
            // UARTSendByte(UART(1), dacChn);
            // DAC((u16)(5 * (fKpfTemp[0] + 200))); //��ʱ1ms
            // DAC(0); //��ʱ1ms
        }
        if (GetQueueLength(&sq))
        {
            ModbusDataParse(); //��ʱ2ms
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

    u8 i = 0; //��ʼ��chn��setup��

    IO_init();

    QueueInit(&sq);
    QueueInit(&nDataCntSq);
    SpiInit(); //initial SPI

    // P_SW2 = 0x80;
    // CKSEL = 0x00;   //ѡ���ڲ�IRC����ѡ���ⲿʱ�ӣ���Ҫ�ȴ��ⲿʱ���ȶ���
    // CLKDIV = 0x00;  //ʱ�Ӳ���Ƶ
    // MCLKOCR = 0x82; //ϵͳʱ�����
    // P_SW2 = 0x00;

    // IE2 |= ESPI;

    for (i = 0; i < MAXAD7124CHNS; i++)
    {
        chn[i] = AD7124_8_ChannelPreConfig(AD7124_CH0_MAP_REG + i, AD7124_CH_MAP_REG_CH_ENABLE, AD7124_CH_MAP_REG_SETUP(i), AD7124_CH_MAP_REG_AINP(i + 1), AD7124_CH_MAP_REG_AINM(i)); //�˿ڴ�С�˿�ʼ����
    }

    for (i = 0; i < MAXAD7124SETUPS; i++)
    {
        setup[i] = AD7124_8_SetupPreConfig(AD7124_CFG0_REG + i, AD7124_CFG_REG_BIPOLAR, AD7124_CFG_REG_BURNOUT(0), AD7124_CFG_REG_REF_BUFP, AD7124_CFG_REG_REF_BUFM, AD7124_CFG_REG_AIN_BUFP, AD7124_CFG_REG_AIN_BUFM, AD7124_CFG_REG_REF_SEL(0), AD7124_CFG_REG_PGA(4),
                                           AD7124_FILT0_REG + i, AD7124_FILT_REG_FILTER(0), AD7124_FILT_REG_REJ60, AD7124_FILT_REG_POST_FILTER(0), AD7124_FILT_REG_SINGLE_CYCLE, AD7124_FILT_REG_FS(480),
                                           AD7124_OFFS0_REG + i, 0x800000,
                                           AD7124_GAIN0_REG + i, 0x5fffff);
    }

    adcControl = AD7124_8_AdcControlPreConfig(AD7124_ADC_CTRL_REG, AD7124_ADC_CTRL_REG_DOUT_RDY_DEL, !AD7124_ADC_CTRL_REG_CONT_READ, AD7124_ADC_CTRL_REG_DATA_STATUS, !AD7124_ADC_CTRL_REG_CS_EN, !AD7124_ADC_CTRL_REG_REF_EN, AD7124_ADC_CTRL_REG_POWER_MODE(3), AD7124_ADC_CTRL_REG_MODE(0), AD7124_ADC_CTRL_REG_CLK_SEL(0));
    //io�������·ͼ���
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

    // EA = 1; //ʹ��spi��Ҫ�������꼴�ء�
    delay_X_us(50);

    for (i = 0; i < 64; i++)
    {
        spi_write_read(0xff);
    }

    spi_write_read(AD7124_COMM_REG_RD | AD7124_COMM_REG); //��POR_FLAG��־λ
    spi_write_read(0xff);
    delay_X_ms(30);

    //AD7124_8_init_Setup()δ����gain��offset���˴�����
    //ʧ���Ĵ���д��ʱ�����뱣֤ADC���ڴ��������
    spi_write_read(AD7124_COMM_REG_WR | AD7124_ADC_CTRL_REG);
    spi_write_read(0x10);
    spi_write_read(AD7124_ADC_CTRL_REG_POWER_MODE(1) | AD7124_ADC_CTRL_REG_MODE(4));
    delay_X_ms(30);

    spi_write_read(AD7124_COMM_REG_RD | AD7124_COMM_REG); //���к���POR_FLAG��־λ
    spi_write_read(0xff);
    for (i = 0; i < MAXAD7124CHNS; i++)
    {
        if (setup[i].pga >= 1) //����ı���У׼��Ĭ������Ϊ1
        {
            InternalFullScaleCalibrate(&setup[i]);
            spi_write_read(AD7124_COMM_REG_RD | AD7124_COMM_REG); //У׼����POR_FLAG��־λ
            spi_write_read(0xff);
        }
        InternalZeroScaleCalibrate(&setup[i]);
        spi_write_read(AD7124_COMM_REG_RD | AD7124_COMM_REG); //У׼����POR_FLAG��־λ
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

    //ʹ��INT1�ж�
    // IT1 = 1;
    // EX1 = 1;
    INT_init(1, 0); //�ܽ���DOUT�غ�

    //ʹ��INT3�ж�
    // INT_CLKO = EX3;

    // //ʹ��P1.6���ж�
    // P_SW2 |= 0x80;
    // P1IM0 = 0x00;
    // P1IM1 = 0xff;
    // P1INTE = 0x00;
    // P_SW2 &= ~0x80;
    /************************************/
    EEPROMInit();
    /************************************/
    TimerInit();
    //���Ź�
    wdt->WDT_Enable = ENABLE;
    wdt->WDT_IDLE_Mode = 1;
    wdt->WDT_PS = D_WDT_SCALE_256;
    WDT_Inilize(wdt);
    EA = 1;
    //ͳһ���������￪�ж�
}

void TimerInit(void)
{
    Timer1_init(DISABLE, BAUD, 0x00, true, DISABLE);
    Timer2_init(ENABLE, 598, 0x00, true, DISABLE);           //15ms,15ms*100*2 =3s dac
    Timer3_init(ENABLE, Timer_xUs_yT(10, 1), true, DISABLE); //������T3.5��T1.5��Timer3��1T��12T��20us������1T��5us��������;
    Timer4_init(ENABLE, 9550, true, DISABLE);                //Լ625usһ���жϣ������ɼ�adc����
    UARTInit(UART(1), Timer(1), S1_IO_P30P31, ENABLE);       //initial UART��
}

//3��������1.AD7124�ֲ�Ĭ�ϲ�������дҲ�У�code����ad7124Regs����2.�豸������AD7124У׼������3.��������ʱУ׼��AD7124����
//����д����ʱ����Ҫѡ��2��������1k��
//�����ж�����1�����豸������AD7124������û����д�룻
void EEPROMInit(void)
{
    u8 nRegs = 0;          //����ļĴ�������
    u16 regShift = 0x6400; //����ƫ��
    u8 eeDataBuff[3] = {0};

    IapRead(regShift, eeDataBuff, 3);
    // eeDataBuff[0] = IapRead(regShift++);
    // eeDataBuff[1] = IapRead(regShift++);
    // eeDataBuff[2] = IapRead(regShift);
    // regShift = 0x0000;
    //�յ�Ƭ������
    if ((eeDataBuff[0] != 0x00) || (eeDataBuff[1] != 0x00) || (eeDataBuff[2] != 0x80))
    {
        IapErase(regShift); //������һ������

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
    //д���豸����У׼����
    regShift += 0x0200;
    IapErase(regShift); //������2������
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
