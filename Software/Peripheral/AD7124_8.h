
#ifndef __AD7124_8_H
#define __AD7124_8_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
// #include "sys.h"
// #include "delay.h"
#include "config.h"

/******************************************************************************/
/*********************** CRC8_POLYNOMIAL_REPRESENTATION ***********************/
/******************************************************************************/
#define AD7124_CRC8_POLYNOMIAL_REPRESENTATION 0x07 /* x8 + x2 + x + 1 */
#define AD7124_DISABLE_CRC 0
#define AD7124_USE_CRC 1
/******************************************************************************/
/******************* Register map and register definitions ********************/
/******************************************************************************/

#define AD7124_RW 1 /* Read and Write */
#define AD7124_R 2  /* Read only */
#define AD7124_W 3  /* Write only */

/* AD7124 Register Map */
#define AD7124_COMM_REG 0x00
#define AD7124_STATUS_REG 0x00
#define AD7124_ADC_CTRL_REG 0x01
#define AD7124_DATA_REG 0x02
#define AD7124_IO_CTRL1_REG 0x03
#define AD7124_IO_CTRL2_REG 0x04
#define AD7124_ID_REG 0x05
#define AD7124_ERR_REG 0x06
#define AD7124_ERREN_REG 0x07
#define AD7124_CH0_MAP_REG 0x09
#define AD7124_CH1_MAP_REG 0x0A
#define AD7124_CH2_MAP_REG 0x0B
#define AD7124_CH3_MAP_REG 0x0C
#define AD7124_CH4_MAP_REG 0x0D
#define AD7124_CH5_MAP_REG 0x0E
#define AD7124_CH6_MAP_REG 0x0F
#define AD7124_CH7_MAP_REG 0x10
#define AD7124_CH8_MAP_REG 0x11
#define AD7124_CH9_MAP_REG 0x12
#define AD7124_CH10_MAP_REG 0x13
#define AD7124_CH11_MAP_REG 0x14
#define AD7124_CH12_MAP_REG 0x15
#define AD7124_CH13_MAP_REG 0x16
#define AD7124_CH14_MAP_REG 0x17
#define AD7124_CH15_MAP_REG 0x18
#define AD7124_CFG0_REG 0x19
#define AD7124_CFG1_REG 0x1A
#define AD7124_CFG2_REG 0x1B
#define AD7124_CFG3_REG 0x1C
#define AD7124_CFG4_REG 0x1D
#define AD7124_CFG5_REG 0x1E
#define AD7124_CFG6_REG 0x1F
#define AD7124_CFG7_REG 0x20
#define AD7124_FILT0_REG 0x21
#define AD7124_FILT1_REG 0x22
#define AD7124_FILT2_REG 0x23
#define AD7124_FILT3_REG 0x24
#define AD7124_FILT4_REG 0x25
#define AD7124_FILT5_REG 0x26
#define AD7124_FILT6_REG 0x27
#define AD7124_FILT7_REG 0x28
#define AD7124_OFFS0_REG 0x29
#define AD7124_OFFS1_REG 0x2A
#define AD7124_OFFS2_REG 0x2B
#define AD7124_OFFS3_REG 0x2C
#define AD7124_OFFS4_REG 0x2D
#define AD7124_OFFS5_REG 0x2E
#define AD7124_OFFS6_REG 0x2F
#define AD7124_OFFS7_REG 0x30
#define AD7124_GAIN0_REG 0x31
#define AD7124_GAIN1_REG 0x32
#define AD7124_GAIN2_REG 0x33
#define AD7124_GAIN3_REG 0x34
#define AD7124_GAIN4_REG 0x35
#define AD7124_GAIN5_REG 0x36
#define AD7124_GAIN6_REG 0x37
#define AD7124_GAIN7_REG 0x38

/* Communication Register bits */
#define AD7124_COMM_REG_WEN (0 << 7)
#define AD7124_COMM_REG_WR (0 << 6)
#define AD7124_COMM_REG_RD (1 << 6)
#define AD7124_COMM_REG_RA(x) ((x)&0x3F)

/* Status Register bits */
#define AD7124_STATUS_REG_RDY (1 << 7)
#define AD7124_STATUS_REG_ERROR_FLAG (1 << 6)
#define AD7124_STATUS_REG_POR_FLAG (1 << 4)
#define AD7124_STATUS_REG_CH_ACTIVE(x) ((x)&0xF)

/* ADC_Control Register bits */
#define AD7124_ADC_CTRL_REG_DOUT_RDY_DEL (1 << 12)
#define AD7124_ADC_CTRL_REG_CONT_READ (1 << 11)
#define AD7124_ADC_CTRL_REG_DATA_STATUS (1 << 10)
#define AD7124_ADC_CTRL_REG_CS_EN (1 << 9)
#define AD7124_ADC_CTRL_REG_REF_EN (1 << 8)
#define AD7124_ADC_CTRL_REG_POWER_MODE(x) (((x)&0x3) << 6)
#define AD7124_ADC_CTRL_REG_MODE(x) (((x)&0xF) << 2)
#define AD7124_ADC_CTRL_REG_CLK_SEL(x) (((x)&0x3) << 0)

/* IO_Control_1 Register bits */
// #define AD7124_IO_CTRL1_REG_GPIO_DAT2 (1 << 23)
// #define AD7124_IO_CTRL1_REG_GPIO_DAT1 (1 << 22)
// #define AD7124_IO_CTRL1_REG_GPIO_CTRL2 (1 << 19)
// #define AD7124_IO_CTRL1_REG_GPIO_CTRL1 (1 << 18)
#define AD7124_IO_CTRL1_REG_PDSW (1 << 15)
#define AD7124_IO_CTRL1_REG_IOUT1(x) (((x)&0x7) << 11)
#define AD7124_IO_CTRL1_REG_IOUT0(x) (((x)&0x7) << 8)
#define AD7124_IO_CTRL1_REG_IOUT_CH1(x) (((x)&0xF) << 4)
#define AD7124_IO_CTRL1_REG_IOUT_CH0(x) (((x)&0xF) << 0)

/* IO_Control_1 AD7124-8 specific bits */
#define AD7124_8_IO_CTRL1_REG_GPIO_DAT4 (1 << 7)
#define AD7124_8_IO_CTRL1_REG_GPIO_DAT3 (1 << 6)
#define AD7124_8_IO_CTRL1_REG_GPIO_DAT2 (1 << 5)
#define AD7124_8_IO_CTRL1_REG_GPIO_DAT1 (1 << 4)
#define AD7124_8_IO_CTRL1_REG_GPIO_CTRL4 (1 << 3)
#define AD7124_8_IO_CTRL1_REG_GPIO_CTRL3 (1 << 2)
#define AD7124_8_IO_CTRL1_REG_GPIO_CTRL2 (1 << 1)
#define AD7124_8_IO_CTRL1_REG_GPIO_CTRL1 (1 << 0)
// #define AD7124_8_IO_CTRL1_REG_GPIO_DAT4 (1 << 23)  //51单片机32位左移有问题？选择8位，避免移位
// #define AD7124_8_IO_CTRL1_REG_GPIO_DAT3 (1 << 22)
// #define AD7124_8_IO_CTRL1_REG_GPIO_DAT2 (1 << 21)
// #define AD7124_8_IO_CTRL1_REG_GPIO_DAT1 (1 << 20)
// #define AD7124_8_IO_CTRL1_REG_GPIO_CTRL4 (1 << 19)
// #define AD7124_8_IO_CTRL1_REG_GPIO_CTRL3 (1 << 18)
// #define AD7124_8_IO_CTRL1_REG_GPIO_CTRL2 (1 << 17)
// #define AD7124_8_IO_CTRL1_REG_GPIO_CTRL1 (1 << 16)

// /* IO_Control_2 Register bits */
// #define AD7124_IO_CTRL2_REG_GPIO_VBIAS7 (1 << 15)
// #define AD7124_IO_CTRL2_REG_GPIO_VBIAS6 (1 << 14)
// #define AD7124_IO_CTRL2_REG_GPIO_VBIAS5 (1 << 11)
// #define AD7124_IO_CTRL2_REG_GPIO_VBIAS4 (1 << 10)
// #define AD7124_IO_CTRL2_REG_GPIO_VBIAS3 (1 << 5)
// #define AD7124_IO_CTRL2_REG_GPIO_VBIAS2 (1 << 4)
// #define AD7124_IO_CTRL2_REG_GPIO_VBIAS1 (1 << 1)
// #define AD7124_IO_CTRL2_REG_GPIO_VBIAS0 (1 << 0)

/* IO_Control_2 AD7124-8 specific bits */
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS15 (1 << 15)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS14 (1 << 14)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS13 (1 << 13)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS12 (1 << 12)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS11 (1 << 11)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS10 (1 << 10)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS9 (1 << 9)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS8 (1 << 8)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS7 (1 << 7)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS6 (1 << 6)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS5 (1 << 5)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS4 (1 << 4)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS3 (1 << 3)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS2 (1 << 2)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS1 (1 << 1)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS0 (1 << 0)

/* ID Register bits */
#define AD7124_ID_REG_DEVICE_ID(x) (((x)&0xF) << 4)
#define AD7124_ID_REG_SILICON_REV(x) (((x)&0xF) << 0)

/* Error Register bits */
#define AD7124_ERR_REG_LDO_CAP_ERR (1 << 19)
#define AD7124_ERR_REG_ADC_CAL_ERR (1 << 18)
#define AD7124_ERR_REG_ADC_CONV_ERR (1 << 17)
#define AD7124_ERR_REG_ADC_SAT_ERR (1 << 16)
#define AD7124_ERR_REG_AINP_OV_ERR (1 << 15)
#define AD7124_ERR_REG_AINP_UV_ERR (1 << 14)
#define AD7124_ERR_REG_AINM_OV_ERR (1 << 13)
#define AD7124_ERR_REG_AINM_UV_ERR (1 << 12)
#define AD7124_ERR_REG_REF_DET_ERR (1 << 11)
#define AD7124_ERR_REG_DLDO_PSM_ERR (1 << 9)
#define AD7124_ERR_REG_ALDO_PSM_ERR (1 << 7)
#define AD7124_ERR_REG_SPI_IGNORE_ERR (1 << 6)
#define AD7124_ERR_REG_SPI_SLCK_CNT_ERR (1 << 5)
#define AD7124_ERR_REG_SPI_READ_ERR (1 << 4)
#define AD7124_ERR_REG_SPI_WRITE_ERR (1 << 3)
#define AD7124_ERR_REG_SPI_CRC_ERR (1 << 2)
#define AD7124_ERR_REG_MM_CRC_ERR (1 << 1)
#define AD7124_ERR_REG_ROM_CRC_ERR (1 << 0)

/* Error_En Register bits */
#define AD7124_ERREN_REG_MCLK_CNT_EN (1 << 22)
#define AD7124_ERREN_REG_LDO_CAP_CHK_TEST_EN (1 << 21)
#define AD7124_ERREN_REG_LDO_CAP_CHK(x) (((x)&0x3) << 19)
#define AD7124_ERREN_REG_ADC_CAL_ERR_EN (1 << 18)
#define AD7124_ERREN_REG_ADC_CONV_ERR_EN (1 << 17)
#define AD7124_ERREN_REG_ADC_SAT_ERR_EN (1 << 16)
#define AD7124_ERREN_REG_AINP_OV_ERR_EN (1 << 15)
#define AD7124_ERREN_REG_AINP_UV_ERR_EN (1 << 14)
#define AD7124_ERREN_REG_AINM_OV_ERR_EN (1 << 13)
#define AD7124_ERREN_REG_AINM_UV_ERR_EN (1 << 12)
#define AD7124_ERREN_REG_REF_DET_ERR_EN (1 << 11)
#define AD7124_ERREN_REG_DLDO_PSM_TRIP_TEST_EN (1 << 10)
#define AD7124_ERREN_REG_DLDO_PSM_ERR_ERR (1 << 9)
#define AD7124_ERREN_REG_ALDO_PSM_TRIP_TEST_EN (1 << 8)
#define AD7124_ERREN_REG_ALDO_PSM_ERR_EN (1 << 7)
#define AD7124_ERREN_REG_SPI_IGNORE_ERR_EN (1 << 6)
#define AD7124_ERREN_REG_SPI_SCLK_CNT_ERR_EN (1 << 5)
#define AD7124_ERREN_REG_SPI_READ_ERR_EN (1 << 4)
#define AD7124_ERREN_REG_SPI_WRITE_ERR_EN (1 << 3)
#define AD7124_ERREN_REG_SPI_CRC_ERR_EN (1 << 2)
#define AD7124_ERREN_REG_MM_CRC_ERR_EN (1 << 1)
#define AD7124_ERREN_REG_ROM_CRC_ERR_EN (1 << 0)

/* Channel Registers 0-15 bits */
#define AD7124_CH_MAP_REG_CH_ENABLE (1 << 15)
#define AD7124_CH_MAP_REG_SETUP(x) (((x)&0x7) << 12)
#define AD7124_CH_MAP_REG_AINP(x) (((x)&0x1F) << 5)
#define AD7124_CH_MAP_REG_AINM(x) (((x)&0x1F) << 0)

/* Configuration Registers 0-7 bits */
#define AD7124_CFG_REG_BIPOLAR (1 << 11)
#define AD7124_CFG_REG_BURNOUT(x) (((x)&0x3) << 9)
#define AD7124_CFG_REG_REF_BUFP (1 << 8)
#define AD7124_CFG_REG_REF_BUFM (1 << 7)
#define AD7124_CFG_REG_AIN_BUFP (1 << 6)
#define AD7124_CFG_REG_AIN_BUFM (1 << 5)
#define AD7124_CFG_REG_REF_SEL(x) ((x)&0x3) << 3
#define AD7124_CFG_REG_PGA(x) (((x)&0x7) << 0)

/* Filter Register 0-7 bits */
#define AD7124_FILT_REG_FILTER(x) (((x)&0x7) << 5) //51单片机32位左移有问题？选择8位，避免移位
#define AD7124_FILT_REG_REJ60 (1 << 4)
#define AD7124_FILT_REG_POST_FILTER(x) (((x)&0x7) << 1)
#define AD7124_FILT_REG_SINGLE_CYCLE (1 << 0)
// #define AD7124_FILT_REG_FILTER(x) (((x)&0x7) << 21)
// #define AD7124_FILT_REG_REJ60 (1 << 20)
// #define AD7124_FILT_REG_POST_FILTER(x) (((x)&0x7) << 17)
// #define AD7124_FILT_REG_SINGLE_CYCLE (1 << 16)
#define AD7124_FILT_REG_FS(x) (((x)&0x7FF) << 0)

/******************************************************************************/
/*************************** Types Declarations *******************************/
/******************************************************************************/

/*! Device register info */
typedef struct
{
    u8 addr;
    u32 value;
    u8 size;
    u8 rw;
} AD7124_REG;

/*! Device channel info */
typedef struct
{
    u8 reg;
    u16 enable;
    u16 setup;
    u16 AINP;
    u16 AINM;

} Channel;

//config/filter/gain/offset放在一个结构体里，方便chn配置setup;AD7124_8_init_Setup不初始化gain/offset，待校准以后初始化
typedef struct
{
    u8 configReg;
    u16 bipolar;
    u16 burnout;
    u8 ref_bufp;
    u8 ref_bufm;
    u8 ain_bufp;
    u8 ain_bufm;
    u8 ref_sel;
    u8 pga;
    u8 filterReg;
    u8 filter;
    u8 rej60;
    u8 post_filter;
    u8 single_cycle;
    u16 fs;
    u8 offsetReg;
    u32 offset;
    u8 gainReg;
    u32 gain;

} Setup;

typedef struct
{
    u8 control;
    u16 dout_rdy_del;
    u16 cont_read;
    u16 data_status;
    u16 cs_en;
    u16 ref_en;
    u8 power_mode;
    u8 mode;
    u8 clk_sel;
} AdcControl;

// typedef struct
// {

// } Diagnostics;

typedef struct
{
    u8 gpio_dat;
    u8 gpio_ctrl;
    u16 pdsw;
    u16 gpio_iout;
    u8 gpio_iout_ch;
    u16 gpio_vbias;
} Ad7124_8_IO;

/*! AD7124 registers list*/
enum ad7124_registers
{
    AD7124_Status = 0x00,
    AD7124_ADC_Control,
    AD7124_Data,
    AD7124_IOCon1,
    AD7124_IOCon2,
    AD7124_ID,
    AD7124_Error,
    AD7124_Error_En,
    AD7124_Mclk_Count,
    AD7124_Channel_0,
    AD7124_Channel_1,
    AD7124_Channel_2,
    AD7124_Channel_3,
    AD7124_Channel_4,
    AD7124_Channel_5,
    AD7124_Channel_6,
    AD7124_Channel_7,
    AD7124_Channel_8,
    AD7124_Channel_9,
    AD7124_Channel_10,
    AD7124_Channel_11,
    AD7124_Channel_12,
    AD7124_Channel_13,
    AD7124_Channel_14,
    AD7124_Channel_15,
    AD7124_Config_0,
    AD7124_Config_1,
    AD7124_Config_2,
    AD7124_Config_3,
    AD7124_Config_4,
    AD7124_Config_5,
    AD7124_Config_6,
    AD7124_Config_7,
    AD7124_Filter_0,
    AD7124_Filter_1,
    AD7124_Filter_2,
    AD7124_Filter_3,
    AD7124_Filter_4,
    AD7124_Filter_5,
    AD7124_Filter_6,
    AD7124_Filter_7,
    AD7124_Offset_0,
    AD7124_Offset_1,
    AD7124_Offset_2,
    AD7124_Offset_3,
    AD7124_Offset_4,
    AD7124_Offset_5,
    AD7124_Offset_6,
    AD7124_Offset_7,
    AD7124_Gain_0,
    AD7124_Gain_1,
    AD7124_Gain_2,
    AD7124_Gain_3,
    AD7124_Gain_4,
    AD7124_Gain_5,
    AD7124_Gain_6,
    AD7124_Gain_7,
    AD7124_REG_NO
};

extern AD7124_REG code ad7124Regs[AD7124_REG_NO];

// void AD7124_8_init_SingleChannel(u8 AD7124_Channel, u16 enable, u16 setup, u16 AINP, u16 AINM,
//                                  u8 config, u16 bipolar, u16 burnout, u8 ref_bufp, u8 ref_bufm, u8 ain_bufp, u8 ain_bufm, u8 ref_sel, u8 pga,
//                                  u8 filter, u8 flt, u8 rej60, u8 post_filter, u8 single_cycle, u16 fs,
//                                  //  u8 offset, u8 gain,
//                                  u8 control, u16 dout_rdy_del, u16 cont_read, u16 data_status, u16 cs_en, u16 ref_en, u8 power_mode, u8 mode, u8 clk_sel); //单通道配置

Channel AD7124_8_ChannelPreConfig(u16 AD7124_Channel, u16 enable, u16 setup, u16 AINP, u16 AINM);
Setup AD7124_8_SetupPreConfig(u8 config, u16 bipolar, u16 burnout, u8 ref_bufp, u8 ref_bufm, u8 ain_bufp, u8 ain_bufm, u8 ref_sel, u8 pga,
                              u8 filter, u8 flt, u8 rej60, u8 post_filter, u8 single_cycle, u16 fs,
                              u8 offsetReg, u32 offset,
                              u8 gainReg, u32 gain);
// Diagnostics AD7124_8_DiagnosticsPreConfig();
AdcControl AD7124_8_AdcControlPreConfig(u8 control, u16 dout_rdy_del, u16 cont_read, u16 data_status, u16 cs_en, u16 ref_en, u8 power_mode, u8 mode, u8 clk_sel);

Ad7124_8_IO AD7124_8_ioPreConfig(u8 gpio_dat, u8 gpio_ctrl, u16 pdsw, u16 gpio_iout, u8 gpio_iout_ch, u16 gpio_vbias);

void AD7124_8_init_SingleChannelConfiguraton(Channel channel); //SELECT POSITIVEAND NEGATIVE INPUT FOR EACH ADC CHANNEL, SELECT ONE OF 8 SETUPS FORADC CHANNEL
void AD7124_8_init_Setup(Setup setup);                         //8 POSSIBLE ADC SETUPS ,SELECT FILTER, OUTPUT DATA RATE, GAIN AND MORE
// void AD7124_8_init_Diagnostics(Diagnostics diagnostics);       //ENABLE CRC, SPI READ AND WRITE CHECKS,ENABLE LDO CHECKS, AND MORE
void AD7124_8_init_AdcControl(AdcControl adcControl); //SELECT ADC OPERATING MODE, CLOCK SOURCE,SELECT POWER MODE, DATA + STATUS, AND MORE

void Ad7124_8_init_io(Ad7124_8_IO Ad7124_8_io);

// void Ad7124_8_read(AD7124_REG reg);

// void Ad7124_8_write(AD7124_REG reg);

void ADC(AD7124_REG *pChnReg);

// void ADCTrig(AD7124_REG *pChnReg);

// //ADC校准
// void ADCCalibrate(Setup * Setup);
//内部满量程校准
void InternalFullScaleCalibrate(Setup *Setup);
//内部零电平校准
void InternalZeroScaleCalibrate(Setup *Setup);
//系统满量程校准
void SystemFullScaleCalibrate(void);
//系统零电平校准
void SystemZeroScaleCalibrate(void);

#endif