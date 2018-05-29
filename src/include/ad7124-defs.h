/***************************************************************************//**
*   @file    AD7124-defs.h
*   @brief   AD7124 header file.
*   @devices AD7124-4, AD7124-8
*
********************************************************************************
* Copyright 2015(c) Analog Devices, Inc.
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*  - Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*  - Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
*  - Neither the name of Analog Devices, Inc. nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*  - The use of this software may or may not infringe the patent rights
*    of one or more patent holders.  This license does not release you
*    from the requirement that you obtain separate licenses from these
*    patent holders to use this software.
*  - Use of the software either in source or binary form, must be run
*    on or directly connected to an Analog Devices Inc. component.
*
* THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT, MERCHANTABILITY
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/
#ifndef __AD7124_DEFS_H__
#define __AD7124_DEFS_H__

namespace Ad7124 {
  
  /*! AD7124 registers list*/
  enum RegisterId {
    Status = 0x00,
    ADC_Control,
    Data,
    IOCon_1,
    IOCon_2,
    ID,
    Error,
    Error_En,
    Mclk_Count,
    Channel_0,
    Channel_1,
    Channel_2,
    Channel_3,
    Channel_4,
    Channel_5,
    Channel_6,
    Channel_7,
    Channel_8,
    Channel_9,
    Channel_10,
    Channel_11,
    Channel_12,
    Channel_13,
    Channel_14,
    Channel_15,
    Config_0,
    Config_1,
    Config_2,
    Config_3,
    Config_4,
    Config_5,
    Config_6,
    Config_7,
    Filter_0,
    Filter_1,
    Filter_2,
    Filter_3,
    Filter_4,
    Filter_5,
    Filter_6,
    Filter_7,
    Offset_0,
    Offset_1,
    Offset_2,
    Offset_3,
    Offset_4,
    Offset_5,
    Offset_6,
    Offset_7,
    Gain_0,
    Gain_1,
    Gain_2,
    Gain_3,
    Gain_4,
    Gain_5,
    Gain_6,
    Gain_7,
    Reg_No
  };
}

#if defined(__cplusplus)
extern "C" {
#endif
/* ========================================================================== */
#include <stdint.h>
#include <string.h>

/* macros & constants ======================================================= */
/******************************************************************************/
/******************* Register map and register definitions ********************/
/******************************************************************************/
#define AD7124_RW 1   /* Read and Write */
#define AD7124_R  2   /* Read only */
#define AD7124_W  3   /* Write only */

/* Error codes */
#define AD7124_INVALID_VAL -1 /* Invalid argument */
#define AD7124_COMM_ERR    -2 /* Communication error on receive */
#define AD7124_TIMEOUT     -3 /* A timeout has occured */
#define AD7124_SPI_ERR     -4 /* A SPI has occured */

/* AD7124 Register Map */
#define AD7124_COMM_REG      0x00
#define AD7124_STATUS_REG    0x00
#define AD7124_ADC_CTRL_REG  0x01
#define AD7124_DATA_REG      0x02
#define AD7124_IO_CTRL1_REG  0x03
#define AD7124_IO_CTRL2_REG  0x04
#define AD7124_ID_REG        0x05
#define AD7124_ERR_REG       0x06
#define AD7124_ERREN_REG     0x07
#define AD7124_CH0_MAP_REG   0x09
#define AD7124_CH1_MAP_REG   0x0A
#define AD7124_CH2_MAP_REG   0x0B
#define AD7124_CH3_MAP_REG   0x0C
#define AD7124_CH4_MAP_REG   0x0D
#define AD7124_CH5_MAP_REG   0x0E
#define AD7124_CH6_MAP_REG   0x0F
#define AD7124_CH7_MAP_REG   0x10
#define AD7124_CH8_MAP_REG   0x11
#define AD7124_CH9_MAP_REG   0x12
#define AD7124_CH10_MAP_REG  0x13
#define AD7124_CH11_MAP_REG  0x14
#define AD7124_CH12_MAP_REG  0x15
#define AD7124_CH13_MAP_REG  0x16
#define AD7124_CH14_MAP_REG  0x17
#define AD7124_CH15_MAP_REG  0x18
#define AD7124_CFG0_REG      0x19
#define AD7124_CFG1_REG      0x1A
#define AD7124_CFG2_REG      0x1B
#define AD7124_CFG3_REG      0x1C
#define AD7124_CFG4_REG      0x1D
#define AD7124_CFG5_REG      0x1E
#define AD7124_CFG6_REG      0x1F
#define AD7124_CFG7_REG      0x20
#define AD7124_FILT0_REG     0x21
#define AD7124_FILT1_REG     0x22
#define AD7124_FILT2_REG     0x23
#define AD7124_FILT3_REG     0x24
#define AD7124_FILT4_REG     0x25
#define AD7124_FILT5_REG     0x26
#define AD7124_FILT6_REG     0x27
#define AD7124_FILT7_REG     0x28
#define AD7124_OFFS0_REG     0x29
#define AD7124_OFFS1_REG     0x2A
#define AD7124_OFFS2_REG     0x2B
#define AD7124_OFFS3_REG     0x2C
#define AD7124_OFFS4_REG     0x2D
#define AD7124_OFFS5_REG     0x2E
#define AD7124_OFFS6_REG     0x2F
#define AD7124_OFFS7_REG     0x30
#define AD7124_GAIN0_REG     0x31
#define AD7124_GAIN1_REG     0x32
#define AD7124_GAIN2_REG     0x33
#define AD7124_GAIN3_REG     0x34
#define AD7124_GAIN4_REG     0x35
#define AD7124_GAIN5_REG     0x36
#define AD7124_GAIN6_REG     0x37
#define AD7124_GAIN7_REG     0x38

/* Communication Register bits */
#define AD7124_COMM_REG_WEN    (0 << 7)
#define AD7124_COMM_REG_WR     (0 << 6)
#define AD7124_COMM_REG_RD     (1 << 6)
#define AD7124_COMM_REG_RA(x)  ((x) & 0x3F)

/* Status Register bits */
#define AD7124_STATUS_REG_RDY          (1 << 7)
#define AD7124_STATUS_REG_ERROR_FLAG   (1 << 6)
#define AD7124_STATUS_REG_POR_FLAG     (1 << 4)
#define AD7124_STATUS_REG_CH_ACTIVE(x) ((x) & 0xF)

/* ADC_Control Register bits */
#define AD7124_ADC_CTRL_REG_DOUT_RDY_DEL   (1 << 12)
#define AD7124_ADC_CTRL_REG_CONT_READ      (1 << 11)
#define AD7124_ADC_CTRL_REG_DATA_STATUS    (1 << 10)
#define AD7124_ADC_CTRL_REG_CS_EN          (1 << 9)
#define AD7124_ADC_CTRL_REG_REF_EN         (1 << 8)
#define AD7124_ADC_CTRL_REG_POWER_MODE(x)  (((x) & 0x3) << 6)
#define AD7124_ADC_CTRL_REG_MODE(x)        (((x) & 0xF) << 2)
#define AD7124_ADC_CTRL_REG_CLK_SEL(x)    (((x) & 0x3) << 0)

/* IO_Control_1 Register bits */
#define AD7124_IO_CTRL1_REG_GPIO_DAT2     (1UL << 23)
#define AD7124_IO_CTRL1_REG_GPIO_DAT1     (1UL << 22)
#define AD7124_IO_CTRL1_REG_GPIO_CTRL2    (1UL << 19)
#define AD7124_IO_CTRL1_REG_GPIO_CTRL1    (1UL << 18)
#define AD7124_IO_CTRL1_REG_PDSW          (1UL << 15)
#define AD7124_IO_CTRL1_REG_IOUT1(x)      (((x) & 0x7) << 11)
#define AD7124_IO_CTRL1_REG_IOUT0(x)      (((x) & 0x7) << 8)
#define AD7124_IO_CTRL1_REG_IOUT_CH1(x)   (((x) & 0xF) << 4)
#define AD7124_IO_CTRL1_REG_IOUT_CH0(x)   (((x) & 0xF) << 0)

/* IO_Control_1 AD7124-8 specific bits */
#define AD7124_8_IO_CTRL1_REG_GPIO_DAT4     (1UL << 23)
#define AD7124_8_IO_CTRL1_REG_GPIO_DAT3     (1UL << 22)
#define AD7124_8_IO_CTRL1_REG_GPIO_DAT2     (1UL << 21)
#define AD7124_8_IO_CTRL1_REG_GPIO_DAT1     (1UL << 20)
#define AD7124_8_IO_CTRL1_REG_GPIO_CTRL4    (1UL << 19)
#define AD7124_8_IO_CTRL1_REG_GPIO_CTRL3    (1UL << 18)
#define AD7124_8_IO_CTRL1_REG_GPIO_CTRL2    (1UL << 17)
#define AD7124_8_IO_CTRL1_REG_GPIO_CTRL1    (1UL << 16)

/* IO_Control_2 Register bits */
#define AD7124_IO_CTRL2_REG_GPIO_VBIAS7   (1 << 15)
#define AD7124_IO_CTRL2_REG_GPIO_VBIAS6   (1 << 14)
#define AD7124_IO_CTRL2_REG_GPIO_VBIAS5   (1 << 11)
#define AD7124_IO_CTRL2_REG_GPIO_VBIAS4   (1 << 10)
#define AD7124_IO_CTRL2_REG_GPIO_VBIAS3   (1 << 5)
#define AD7124_IO_CTRL2_REG_GPIO_VBIAS2   (1 << 4)
#define AD7124_IO_CTRL2_REG_GPIO_VBIAS1   (1 << 1)
#define AD7124_IO_CTRL2_REG_GPIO_VBIAS0   (1 << 0)

/* IO_Control_2 AD7124-8 specific bits */
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS15  (1 << 15)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS14  (1 << 14)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS13  (1 << 13)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS12  (1 << 12)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS11  (1 << 11)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS10  (1 << 10)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS9   (1 << 9)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS8   (1 << 8)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS7   (1 << 7)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS6   (1 << 6)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS5   (1 << 5)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS4   (1 << 4)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS3   (1 << 3)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS2   (1 << 2)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS1   (1 << 1)
#define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS0   (1 << 0)

/* ID Register bits */
#define AD7124_ID_REG_DEVICE_ID(x)   (((x) & 0xF) << 4)
#define AD7124_ID_REG_SILICON_REV(x) (((x) & 0xF) << 0)

/* Error Register bits */
#define AD7124_ERR_REG_LDO_CAP_ERR        (1UL << 19)
#define AD7124_ERR_REG_ADC_CAL_ERR        (1UL << 18)
#define AD7124_ERR_REG_ADC_CONV_ERR       (1UL << 17)
#define AD7124_ERR_REG_ADC_SAT_ERR        (1UL << 16)
#define AD7124_ERR_REG_AINP_OV_ERR        (1UL << 15)
#define AD7124_ERR_REG_AINP_UV_ERR        (1UL << 14)
#define AD7124_ERR_REG_AINM_OV_ERR        (1UL << 13)
#define AD7124_ERR_REG_AINM_UV_ERR        (1UL << 12)
#define AD7124_ERR_REG_REF_DET_ERR        (1UL << 11)
#define AD7124_ERR_REG_DLDO_PSM_ERR       (1UL << 9)
#define AD7124_ERR_REG_ALDO_PSM_ERR       (1UL << 7)
#define AD7124_ERR_REG_SPI_IGNORE_ERR     (1UL << 6)
#define AD7124_ERR_REG_SPI_SLCK_CNT_ERR   (1UL << 5)
#define AD7124_ERR_REG_SPI_READ_ERR       (1UL << 4)
#define AD7124_ERR_REG_SPI_WRITE_ERR      (1UL << 3)
#define AD7124_ERR_REG_SPI_CRC_ERR        (1UL << 2)
#define AD7124_ERR_REG_MM_CRC_ERR         (1UL << 1)

/* Error_En Register bits */
#define AD7124_ERREN_REG_MCLK_CNT_EN           (1UL << 22)
#define AD7124_ERREN_REG_LDO_CAP_CHK_TEST_EN   (1UL << 21)
#define AD7124_ERREN_REG_LDO_CAP_CHK(x)        (((x) & 0x3) << 19)
#define AD7124_ERREN_REG_ADC_CAL_ERR_EN        (1UL << 18)
#define AD7124_ERREN_REG_ADC_CONV_ERR_EN       (1UL << 17)
#define AD7124_ERREN_REG_ADC_SAT_ERR_EN        (1UL << 16)
#define AD7124_ERREN_REG_AINP_OV_ERR_EN        (1UL << 15)
#define AD7124_ERREN_REG_AINP_UV_ERR_EN        (1UL << 14)
#define AD7124_ERREN_REG_AINM_OV_ERR_EN        (1UL << 13)
#define AD7124_ERREN_REG_AINM_UV_ERR_EN        (1UL << 12)
#define AD7124_ERREN_REG_REF_DET_ERR_EN        (1UL << 11)
#define AD7124_ERREN_REG_DLDO_PSM_TRIP_TEST_EN (1UL << 10)
#define AD7124_ERREN_REG_DLDO_PSM_ERR_ERR      (1UL << 9)
#define AD7124_ERREN_REG_ALDO_PSM_TRIP_TEST_EN (1UL << 8)
#define AD7124_ERREN_REG_ALDO_PSM_ERR_EN       (1UL << 7)
#define AD7124_ERREN_REG_SPI_IGNORE_ERR_EN     (1UL << 6)
#define AD7124_ERREN_REG_SPI_SCLK_CNT_ERR_EN   (1UL << 5)
#define AD7124_ERREN_REG_SPI_READ_ERR_EN       (1UL << 4)
#define AD7124_ERREN_REG_SPI_WRITE_ERR_EN      (1UL << 3)
#define AD7124_ERREN_REG_SPI_CRC_ERR_EN        (1UL << 2)
#define AD7124_ERREN_REG_MM_CRC_ERR_EN         (1UL << 1)

/* Channel Registers 0-15 bits */
#define AD7124_CH_MAP_REG_CH_ENABLE    (1UL << 15)
#define AD7124_CH_MAP_REG_SETUP(x)     (((x) & 0x7) << 12)
#define AD7124_CH_MAP_REG_AINP(x)      (((x) & 0x1F) << 5)
#define AD7124_CH_MAP_REG_AINM(x)      (((x) & 0x1F) << 0)

/* Configuration Registers 0-7 bits */
#define AD7124_CFG_REG_BIPOLAR     (1UL << 11)
#define AD7124_CFG_REG_BURNOUT(x)  (((x) & 0x3) << 9)
#define AD7124_CFG_REG_REF_BUFP    (1UL << 8)
#define AD7124_CFG_REG_REF_BUFM    (1UL << 7)
#define AD7124_CFG_REG_AIN_BUFP    (1UL << 6)
#define AD7124_CFG_REG_AINN_BUFM   (1UL << 5)
#define AD7124_CFG_REG_REF_SEL(x)  ((x) & 0x3) << 3
#define AD7124_CFG_REG_PGA(x)      (((x) & 0x7) << 0)

/* Filter Register 0-7 bits */
#define AD7124_FILT_REG_FILTER(x)         (((x) & 0x7) << 21)
#define AD7124_FILT_REG_REJ60             (1UL << 20)
#define AD7124_FILT_REG_POST_FILTER(x)    (((x) & 0x7) << 17)
#define AD7124_FILT_REG_SINGLE_CYCLE      (1UL << 16)
#define AD7124_FILT_REG_FS(x)             (((x) & 0x7FF) << 0)

/******************************************************************************/
/******************* AD7124 Constants *****************************************/
/******************************************************************************/
#define AD7124_CRC8_POLYNOMIAL_REPRESENTATION 0x07 /* x8 + x2 + x + 1 */
#define AD7124_DISABLE_CRC 0
#define AD7124_USE_CRC 1

/* ========================================================================== */
#if defined(__cplusplus)
}
#endif
#endif /* __AD7124_DEFS_H__ */
