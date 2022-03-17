#include "AD7124_8.h"

AD7124_REG code ad7124Regs[AD7124_REG_NO] = {
    {0x00, 0x00, 1, 2},     /* AD7124_Status */
    {0x01, 0x0000, 2, 1},   /* AD7124_ADC_Control */
    {0x02, 0x0000, 3, 2},   /* AD7124_Data */
    {0x03, 0x0000, 3, 1},   /* AD7124_IOCon1 */
    {0x04, 0x0000, 2, 1},   /* AD7124_IOCon2 */
    {0x05, 0x12, 1, 2},     /* AD7124_ID */
    {0x06, 0x0000, 3, 2},   /* AD7124_Error */
    {0x07, 0x0040, 3, 1},   /* AD7124_Error_En */
    {0x08, 0x00, 1, 2},     /* AD7124_Mclk_Count */
    {0x09, 0x8001, 2, 1},   /* AD7124_Channel_0 */
    {0x0A, 0x0001, 2, 1},   /* AD7124_Channel_1 */
    {0x0B, 0x0001, 2, 1},   /* AD7124_Channel_2 */
    {0x0C, 0x0001, 2, 1},   /* AD7124_Channel_3 */
    {0x0D, 0x0001, 2, 1},   /* AD7124_Channel_4 */
    {0x0E, 0x0001, 2, 1},   /* AD7124_Channel_5 */
    {0x0F, 0x0001, 2, 1},   /* AD7124_Channel_6 */
    {0x10, 0x0001, 2, 1},   /* AD7124_Channel_7 */
    {0x11, 0x0001, 2, 1},   /* AD7124_Channel_8 */
    {0x12, 0x0001, 2, 1},   /* AD7124_Channel_9 */
    {0x13, 0x0001, 2, 1},   /* AD7124_Channel_10 */
    {0x14, 0x0001, 2, 1},   /* AD7124_Channel_11 */
    {0x15, 0x0001, 2, 1},   /* AD7124_Channel_12 */
    {0x16, 0x0001, 2, 1},   /* AD7124_Channel_13 */
    {0x17, 0x0001, 2, 1},   /* AD7124_Channel_14 */
    {0x18, 0x0001, 2, 1},   /* AD7124_Channel_15 */
    {0x19, 0x0860, 2, 1},   /* AD7124_Config_0 */
    {0x1A, 0x0860, 2, 1},   /* AD7124_Config_1 */
    {0x1B, 0x0860, 2, 1},   /* AD7124_Config_2 */
    {0x1C, 0x0860, 2, 1},   /* AD7124_Config_3 */
    {0x1D, 0x0860, 2, 1},   /* AD7124_Config_4 */
    {0x1E, 0x0860, 2, 1},   /* AD7124_Config_5 */
    {0x1F, 0x0860, 2, 1},   /* AD7124_Config_6 */
    {0x20, 0x0860, 2, 1},   /* AD7124_Config_7 */
    {0x21, 0x060180, 3, 1}, /* AD7124_Filter_0 */
    {0x22, 0x060180, 3, 1}, /* AD7124_Filter_1 */
    {0x23, 0x060180, 3, 1}, /* AD7124_Filter_2 */
    {0x24, 0x060180, 3, 1}, /* AD7124_Filter_3 */
    {0x25, 0x060180, 3, 1}, /* AD7124_Filter_4 */
    {0x26, 0x060180, 3, 1}, /* AD7124_Filter_5 */
    {0x27, 0x060180, 3, 1}, /* AD7124_Filter_6 */
    {0x28, 0x060180, 3, 1}, /* AD7124_Filter_7 */
    {0x29, 0x800000, 3, 1}, /* AD7124_Offset_0 */
    {0x2A, 0x800000, 3, 1}, /* AD7124_Offset_1 */
    {0x2B, 0x800000, 3, 1}, /* AD7124_Offset_2 */
    {0x2C, 0x800000, 3, 1}, /* AD7124_Offset_3 */
    {0x2D, 0x800000, 3, 1}, /* AD7124_Offset_4 */
    {0x2E, 0x800000, 3, 1}, /* AD7124_Offset_5 */
    {0x2F, 0x800000, 3, 1}, /* AD7124_Offset_6 */
    {0x30, 0x800000, 3, 1}, /* AD7124_Offset_7 */
    {0x31, 0x500000, 3, 1}, /* AD7124_Gain_0 */
    {0x32, 0x500000, 3, 1}, /* AD7124_Gain_1 */
    {0x33, 0x500000, 3, 1}, /* AD7124_Gain_2 */
    {0x34, 0x500000, 3, 1}, /* AD7124_Gain_3 */
    {0x35, 0x500000, 3, 1}, /* AD7124_Gain_4 */
    {0x36, 0x500000, 3, 1}, /* AD7124_Gain_5 */
    {0x37, 0x500000, 3, 1}, /* AD7124_Gain_6 */
    {0x38, 0x500000, 3, 1}, /* AD7124_Gain_7 */
};

Channel AD7124_8_ChannelPreConfig(u16 AD7124_Channel, u16 enable, u16 setup, u16 AINP, u16 AINM)
{
    Channel chn;
    chn.reg = (u8)AD7124_Channel & 0xff;
    chn.enable = enable;
    chn.setup = setup;
    chn.AINP = AINP;
    chn.AINM = AINM;

    return chn;
}

Setup AD7124_8_SetupPreConfig(u8 configReg, u16 bipolar, u16 burnout, u8 ref_bufp, u8 ref_bufm, u8 ain_bufp, u8 ain_bufm, u8 ref_sel, u8 pga,
                              u8 filterReg, u8 filter, u8 rej60, u8 post_filter, u8 single_cycle, u16 fs,
                              u8 offsetReg, u32 offset,
                              u8 gainReg, u32 gain)
{
    Setup st;

    st.configReg = configReg;
    st.bipolar = bipolar;
    st.burnout = burnout;
    st.ref_bufp = ref_bufp;
    st.ref_bufm = ref_bufm;
    st.ain_bufp = ain_bufp;
    st.ain_bufm = ain_bufm;
    st.ref_sel = ref_sel;
    st.pga = pga;
    st.filterReg = filterReg;
    st.filter = filter;
    st.rej60 = rej60;
    st.post_filter = post_filter;
    st.single_cycle = single_cycle;
    st.fs = fs;
    st.offsetReg = offsetReg;
    st.offset = offset;
    st.gainReg = gainReg;
    st.gain = gain;

    return st;
}

AdcControl AD7124_8_AdcControlPreConfig(u8 control, u16 dout_rdy_del, u16 cont_read, u16 data_status, u16 cs_en, u16 ref_en, u8 power_mode, u8 mode, u8 clk_sel)
{
    AdcControl adcControl;

    adcControl.control = control;
    adcControl.dout_rdy_del = dout_rdy_del;
    adcControl.cont_read = cont_read,
    adcControl.data_status = data_status;
    adcControl.cs_en = cs_en;
    adcControl.ref_en = ref_en;
    adcControl.power_mode = power_mode;
    adcControl.mode = mode;
    adcControl.clk_sel = clk_sel;

    return adcControl;
}

Ad7124_8_IO AD7124_8_ioPreConfig(u8 gpio_dat, u8 gpio_ctrl, u16 pdsw, u16 gpio_iout, u8 gpio_iout_ch, u16 gpio_vbias)
{
    Ad7124_8_IO ad7124_8_io;
    ad7124_8_io.gpio_dat = gpio_dat;
    ad7124_8_io.gpio_ctrl = gpio_ctrl;
    ad7124_8_io.pdsw = pdsw;
    ad7124_8_io.gpio_iout = gpio_iout;
    ad7124_8_io.gpio_iout_ch = gpio_iout_ch;
    ad7124_8_io.gpio_vbias = gpio_vbias;

    return ad7124_8_io;
}

void AD7124_8_init_SingleChannelConfiguraton(Channel channel)
{
    spi_write_read(channel.reg);
    spi_write_read((channel.enable | channel.setup | channel.AINP) >> 8 & 0xff);
    spi_write_read(channel.AINP | channel.AINM);
    delay_X_ms(5);
}

//未配置gain和offset
void AD7124_8_init_Setup(Setup setup)
{
    spi_write_read(setup.configReg);
    spi_write_read((setup.bipolar | setup.burnout | setup.ref_bufp) >> 8 & 0xff);
    spi_write_read(setup.ref_bufm | setup.ain_bufp | setup.ain_bufm | setup.ref_sel | setup.pga);
    delay_X_ms(5);
    spi_write_read(setup.filterReg);
    spi_write_read(setup.filter | setup.rej60 | setup.post_filter | setup.single_cycle);
    spi_write_read(setup.fs >> 8 & 0x07);
    spi_write_read(setup.fs & 0xff);
    delay_X_ms(5);
}
// void AD7124_8_init_Diagnostics(Diagnostics diagnostics)
// {
// }
void AD7124_8_init_AdcControl(AdcControl adcControl)
{
    spi_write_read(adcControl.control);
    spi_write_read((adcControl.dout_rdy_del | adcControl.cont_read | adcControl.data_status | adcControl.cs_en | adcControl.ref_en) >> 8 & 0xff);
    spi_write_read(adcControl.power_mode | adcControl.mode | adcControl.clk_sel);
    delay_X_ms(5);
}

void Ad7124_8_init_io(Ad7124_8_IO ad7124_8_io)
{
    spi_write_read(AD7124_COMM_REG_WR | AD7124_IO_CTRL1_REG);
    spi_write_read(ad7124_8_io.gpio_dat | ad7124_8_io.gpio_ctrl);
    spi_write_read((ad7124_8_io.pdsw | ad7124_8_io.gpio_iout) >> 8);
    spi_write_read(ad7124_8_io.gpio_iout_ch);
    delay_X_ms(5);
    if (ad7124_8_io.gpio_vbias)
    {
        spi_write_read(AD7124_COMM_REG_WR | AD7124_IO_CTRL2_REG);
        spi_write_read(ad7124_8_io.gpio_vbias >> 8 & 0xff);
        spi_write_read(ad7124_8_io.gpio_vbias & 0xff);
    }
    delay_X_ms(5);
}

// void Ad7124_8_read(AD7124_REG reg);
// void Ad7124_8_write(AD7124_REG reg);

void ADC(AD7124_REG *pChnReg)
{

    pChnReg->value &= 0x00000000; //uTemp为32位，只有3次右移，需要消除高位8bit
    spi_write_read(AD7124_COMM_REG_RD | AD7124_DATA_REG);
    pChnReg->value |= (u32)spi_write_read(0xff);
    pChnReg->value <<= 8;
    pChnReg->value |= (u32)spi_write_read(0xff);
    pChnReg->value <<= 8;
    pChnReg->value |= (u32)spi_write_read(0xff);
    // spi_write_read(AD7124_COMM_REG_RD | AD7124_COMM_REG);
    pChnReg->addr = spi_write_read(0xff);
}

// void ADCTrig(AD7124_REG *pChnReg)
// {
//     SPISS = 0;
//     pChnReg->value &= 0x00000000; //uTemp为32位，只有3次右移，需要消除高位8bit
//                                   // spi_write_read(pChnReg->rw | pChnReg->addr);

//     // EX1 = 1; //INT1中断开
//     psw2_st = P_SW2;
//     P_SW2 |= 0x80;
//     P1INTE = 0x01;
//     P_SW2 = psw2_st;
// }

// void ADCCalibrate(Setup * Setup)
// {
//     void InternalFullScaleCalibrate(Setup * Setup);
//     void InternalZeroScaleCalibrate(Setup * Setup);
//     void SystemZeroScaleCalibrate(void);
//     void SystemFullScaleCalibrate(void);
// }

void InternalFullScaleCalibrate(Setup *setup)
{

    //校准前写入失调寄存器0x800000，保障校准精度
    spi_write_read(AD7124_COMM_REG_WR | (setup->offsetReg));
    spi_write_read(0x80);
    spi_write_read(0x00);
    spi_write_read(0x00);
    //较低的输出速率获得较高的失调校准精度，此精度一次校准，多速率共用
    spi_write_read(AD7124_COMM_REG_WR | setup->filterReg);
    spi_write_read(0x06); //默认值
    spi_write_read(0x00); //低速率输出
    spi_write_read(0x01); //低速率输出

    //启动校准:内部满量程校准需在非全功率模式，其他校准随意
    spi_write_read(AD7124_COMM_REG_WR | AD7124_ADC_CTRL_REG);
    spi_write_read(0x10);
    spi_write_read(AD7124_ADC_CTRL_REG_POWER_MODE(1) | AD7124_ADC_CTRL_REG_MODE(6));
    delay_X_ms(100);
    // delay_X_ms(1600); //增益大于1时，为4个滤波器建立时间
    while (DOUT)
        ;
    //获得校准参数
    spi_write_read(AD7124_COMM_REG_RD | setup->gainReg);
    // delay_X_ms(1);
    setup->gain = spi_write_read(0xff);
    setup->gain <<= 8;
    setup->gain |= spi_write_read(0xff);
    setup->gain <<= 8;
    setup->gain |= spi_write_read(0xff);
    delay_X_ms(1);
}

void InternalZeroScaleCalibrate(Setup *setup)
{
    // 启动校准
    spi_write_read(AD7124_COMM_REG_WR | AD7124_ADC_CTRL_REG);
    spi_write_read(0x10);
    spi_write_read(AD7124_ADC_CTRL_REG_POWER_MODE(1) | AD7124_ADC_CTRL_REG_MODE(5));
    delay_X_ms(100);
    while (DOUT)
        ;

    //获得校准参数
    spi_write_read(AD7124_COMM_REG_RD | setup->offsetReg);
    delay_X_ms(1);
    setup->offset = spi_write_read(0xff);
    setup->offset <<= 8;
    setup->offset |= spi_write_read(0xff);
    setup->offset <<= 8;
    setup->offset |= spi_write_read(0xff);
    delay_X_ms(1);
}
