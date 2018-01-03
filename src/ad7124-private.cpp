/***************************************************************************//**
*   @file    ad7124-private.cpp
*   @brief   AD7124 implementation file.
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
#include "include/ad7124-private.h"
#include <stdio.h>

extern "C" {
#ifdef __AVR__
#include <avr/pgmspace.h>
#else
#define PROGMEM
#define memcpy_P memcpy
#define pgm_read_word
#define sprintf_P sprintf
#endif
}

using namespace Ad7124;

// -----------------------------------------------------------------------------
//
//                            Ad7124Private class
//
// -----------------------------------------------------------------------------

/***************************************************************************//**
* @brief Reads the value of the specified register without checking if the
*        device is ready to accept user requests.
*
* @param pReg - Pointer to the register structure holding info about the
*               register to be read. The read value is stored inside the
*               register structure.
*
* @return Returns 0 for success or negative error code.
*******************************************************************************/
int
Ad7124Private::noCheckReadRegister (Ad7124Register * pReg) {
  int ret       = 0;
  uint8_t buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  uint8_t i         = 0;
  uint8_t check8    = 0;
  uint8_t msgBuf[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  if (!pReg) {

    return AD7124_INVALID_VAL;
  }

  /* Build the Command word */
  buffer[0] = AD7124_COMM_REG_WEN | AD7124_COMM_REG_RD |
              AD7124_COMM_REG_RA (pReg->addr);

  /* Read data from the device */
  ret = drv.read (buffer,
                  ( (useCRC != AD7124_DISABLE_CRC) ? pReg->size + 1
                    : pReg->size) + 1);
  if (ret < 0) {
    return ret;
  }

  /* Check the CRC */
  if (useCRC == AD7124_USE_CRC) {

    msgBuf[0] = AD7124_COMM_REG_WEN | AD7124_COMM_REG_RD |
                AD7124_COMM_REG_RA (pReg->addr);
    for (i = 1; i < pReg->size + 2; ++i) {

      msgBuf[i] = buffer[i];
    }
    check8 = computeCRC8 (msgBuf, pReg->size + 2);
  }

  if (check8 != 0) {
    /* readRegister checksum failed. */
    return AD7124_COMM_ERR;
  }

  /* Build the result */
  pReg->value = 0;
  for (i = 1; i < pReg->size + 1; i++) {

    pReg->value <<= 8;
    pReg->value += buffer[i];
  }

  return ret < 0 ? ret : 0;
}

/***************************************************************************//**
* @brief Writes the value of the specified register without checking if the
*        device is ready to accept user requests.
*
* @param reg - Register structure holding info about the register to be written
*
* @return Returns 0 for success or negative error code.
*******************************************************************************/
int
Ad7124Private::noCheckWriteRegister (Ad7124Register reg) {
  int ret      = 0;
  int32_t regValue = 0;
  uint8_t wrBuf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  uint8_t i        = 0;
  uint8_t crc8     = 0;

  /* Build the Command word */
  wrBuf[0] = AD7124_COMM_REG_WEN | AD7124_COMM_REG_WR |
             AD7124_COMM_REG_RA (reg.addr);

  /* Fill the write buffer */
  regValue = reg.value;
  for (i = 0; i < reg.size; i++) {

    wrBuf[reg.size - i] = regValue & 0xFF;
    regValue >>= 8;
  }

  /* Compute the CRC */
  if (useCRC != AD7124_DISABLE_CRC) {

    crc8 = computeCRC8 (wrBuf, reg.size + 1);
    wrBuf[reg.size + 1] = crc8;
  }

  /* Write data to the device */
  ret = drv.write (wrBuf,
                   (useCRC != AD7124_DISABLE_CRC) ? reg.size + 2
                   : reg.size + 1);

  return ret < 0 ? ret : 0;
}

/***************************************************************************//**
* @brief Reads the value of the specified register only when the device is ready
*        to accept user requests. If the device ready flag is deactivated the
*        read operation will be executed without checking the device state.
*
* @param pReg - Pointer to the register structure holding info about the
*               register to be read. The read value is stored inside the
*               register structure.
*
* @return Returns 0 for success or negative error code.
*******************************************************************************/
int
Ad7124Private::readRegister (Ad7124Register* pReg) {
  int ret;

  if (pReg->addr != AD7124_ERR_REG && isReady) {

    ret = waitForSpiReady (responseTimeout);
    if (ret < 0) {

      return ret;
    }
  }
  ret = noCheckReadRegister (pReg);

  return ret;
}

/***************************************************************************//**
* @brief Writes the value of the specified register only when the device is
*        ready to accept user requests. If the device ready flag is deactivated
*        the write operation will be executed without checking the device state.
*
* @param reg - Register structure holding info about the register to be written
*
* @return Returns 0 for success or negative error code.
*******************************************************************************/
int
Ad7124Private::writeRegister (Ad7124Register pReg) {
  int ret;

  if (isReady) {

    ret = waitForSpiReady (responseTimeout);
    if (ret < 0) {

      return ret;
    }
  }
  ret = noCheckWriteRegister (pReg);

  return ret;
}

/***************************************************************************//**
* @brief Resets the device.
*
* @return Returns true for success, AD7124_TIMEOUT for timeout
*******************************************************************************/
int
Ad7124Private::reset (void) {
  int ret = 0;
  uint8_t wrBuf[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


  ret = drv.write (wrBuf, 8);
  if (ret < 0) {
    return ret;
  }

  /* Wait for the reset to complete */
  return waitToPowerOn (responseTimeout);
}

/***************************************************************************//**
* @brief Waits until the device can accept read and write user actions.
*
* @param timeout - Count representing the number of polls to be done until the
*                  function returns.
*
* @return Returns true for success, false, AD7124_TIMEOUT for timeout
*******************************************************************************/
int
Ad7124Private::waitForSpiReady (uint32_t timeout) {
  int ret;
  bool ready = false;
  bool timeout_en;

  timeout_en = (timeout > 0);

  do {

    /* Read the value of the Error Register */
    ret = readRegister (&reg[Error]);
    if (ret < 0) {

      return ret;
    }

    /* Check the SPI IGNORE Error bit in the Error Register */
    ready = (reg[Error].value &
             AD7124_ERR_REG_SPI_IGNORE_ERR) == 0;

    if (timeout) {

      drv.delay (1);
      timeout--;
    }
  }
  while (!ready && timeout);

  return timeout_en && (timeout == 0) ? AD7124_TIMEOUT : ready;
}

/***************************************************************************//**
* @brief Waits until the device finishes the power-on reset operation.
*
* @param timeout - Count representing the number of polls to be done until the
*                  function returns.
*
* @return Returns true for success, false, AD7124_TIMEOUT for timeout
*******************************************************************************/
int
Ad7124Private::waitToPowerOn (uint32_t timeout) {
  int ret;
  bool powered_on = false;
  bool timeout_en;

  timeout /= 10;
  timeout_en = (timeout > 0);

  do {

    ret = readRegister (&reg[Status]);
    if (ret < 0) {

      return ret;
    }

    /* Check the POR_FLAG bit in the Status Register */
    powered_on = (reg[Status].value &
                  AD7124_STATUS_REG_POR_FLAG) == 0;
    if (timeout) {

      drv.delay (10);
      timeout--;
    }
  }
  while (!powered_on && timeout);

  return timeout_en && (timeout == 0) ? AD7124_TIMEOUT : powered_on;
}

/***************************************************************************//**
* @brief Waits until a new conversion result is available.
*
* @param timeout - Count representing the number of polls to be done until the
*                  function returns if no new data is available.
*
* @return Returns true for success, false if not ready, AD7124_TIMEOUT for timeout
*******************************************************************************/
int
Ad7124Private::waitForConvReady (uint32_t timeout) {
  int ret;
  bool ready = false;
  bool timeout_en;

  timeout_en = (timeout > 0);

  do {

    /* Read the value of the Status Register */
    ret = readRegister (&reg[Status]);
    if (ret < 0) {

      return ret;
    }

    /* Check the RDY bit in the Status Register */
    ready = (reg[Status].value &
             AD7124_STATUS_REG_RDY) == 0;

    if (timeout) {

      drv.delay (1);
      timeout--;
    }
  }
  while (!ready && timeout);

  return timeout_en && (timeout == 0) ? AD7124_TIMEOUT : ready;
}

/***************************************************************************//**
* @brief Reads the conversion result from the device.
*
* @param pData - Pointer to store the read data.
*
* @return Returns 0 for success or negative error code.
*******************************************************************************/
int
Ad7124Private::readData (int32_t* pData) {
  int ret;

  /* Read the value of the Data Register */
  ret = readRegister (&reg[Data]);

  /* Get the read result */
  *pData = reg[Data].value;

  return ret;
}

/***************************************************************************//**
* @brief Updates the CRC settings.
*******************************************************************************/
void
Ad7124Private::updateCRCSetting (void) {

  /* Get CRC State. */
  if (reg[Error_En].value & AD7124_ERREN_REG_SPI_CRC_ERR_EN) {

    useCRC = AD7124_USE_CRC;
  }
  else {

    useCRC = AD7124_DISABLE_CRC;
  }
}

/***************************************************************************//**
* @brief Updates the device SPI interface settings.
*******************************************************************************/
void
Ad7124Private::updateDevSpiSettings (void) {

  if (reg[Error_En].value & AD7124_ERREN_REG_SPI_IGNORE_ERR_EN) {

    isReady = true;
  }
  else {

    isReady = false;
  }
}

/***************************************************************************//**
* @brief Initializes the AD7124.
*
* @param slave_select - The Slave Chip Select Id to be passed to the SPI calls.
* @param regs - The list of registers of the device (initialized or not) to be
*               added to the instance of the driver.
*
* @return Returns > 0 for success or negative error code.
*******************************************************************************/
int
Ad7124Private::init (int slave_select, Ad7124Register * regs) {
  int ret;

  reg = regs;

  /* Initialize the SPI communication. */
  ret = drv.init (slave_select, false, 1000000, 1, 0);
  if (ret == false) {
    return AD7124_SPI_ERR;
  }

  /*  reset the device interface.*/
  ret = reset ();
  if (ret < 0) {
    return ret;
  }

  /* Update the device structure with power-on/reset settings */
  isReady = true;

  /* Initialize registers AD7124_ADC_Control through AD7124_Filter_7. */
  for (int i = Status; (i < Offset_0) && ! (ret < 0); i++) {

    if (reg[i].rw == AD7124_RW) {

      ret = writeRegister (reg[i]);
      if (ret < 0) {

        break;
      }
    }

    /* Get CRC State and device SPI interface settings */
    if (i == Error_En) {

      updateCRCSetting ();
      updateDevSpiSettings ();
    }
  }

  return ret < 0 ? ret : 0;
}

// -----------------------------------------------------------------------------
Ad7124Private::Ad7124Private() :
  reg (0), useCRC (false), isReady (false), responseTimeout (1000) {

}

// -----------------------------------------------------------------------------
Ad7124Private::~Ad7124Private() {

}

/***************************************************************************//**
* @brief Computes the CRC checksum for a data buffer.
*
* @param pBuf - Data buffer
* @param bufSize - Data buffer size in bytes
*
* @return Returns the computed CRC checksum.
*******************************************************************************/
uint8_t
Ad7124Private::computeCRC8 (uint8_t * pBuf, uint8_t bufSize) {
  uint8_t i   = 0;
  uint8_t crc = 0;

  while (bufSize) {

    for (i = 0x80; i != 0; i >>= 1) {

      if ( ( (crc & 0x80) != 0) != ( (*pBuf & i) != 0)) { /* MSB of CRC register XOR input Bit from Data */

        crc <<= 1;
        crc ^= AD7124_CRC8_POLYNOMIAL_REPRESENTATION;
      }
      else {

        crc <<= 1;
      }
    }
    pBuf++;
    bufSize--;
  }
  return crc;
}

// -----------------------------------------------------------------------------
//
//                            Ad7124Register class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
const Ad7124Register Ad7124Register::DefaultRegs[] PROGMEM = {
  {0x00, 0x00,   1, 2}, /* Status */
  {0x01, 0x0000, 2, 1}, /* ADC_Control */
  {0x02, 0x0000, 3, 2}, /* Data */
  {0x03, 0x0000, 3, 1}, /* IOCon1 */
  {0x04, 0x0000, 2, 1}, /* IOCon2 */
  {0x05, 0x02,   1, 2}, /* ID */
  {0x06, 0x0000, 3, 2}, /* Error */
  {0x07, 0x0044, 3, 1}, /* Error_En */
  {0x08, 0x00,   1, 2}, /* Mclk_Count */
  {0x09, 0x8001, 2, 1}, /* Channel_0 */
  {0x0A, 0x0001, 2, 1}, /* Channel_1 */
  {0x0B, 0x0001, 2, 1}, /* Channel_2 */
  {0x0C, 0x0001, 2, 1}, /* Channel_3 */
  {0x0D, 0x0001, 2, 1}, /* Channel_4 */
  {0x0E, 0x0001, 2, 1}, /* Channel_5 */
  {0x0F, 0x0001, 2, 1}, /* Channel_6 */
  {0x10, 0x0001, 2, 1}, /* Channel_7 */
  {0x11, 0x0001, 2, 1}, /* Channel_8 */
  {0x12, 0x0001, 2, 1}, /* Channel_9 */
  {0x13, 0x0001, 2, 1}, /* Channel_10 */
  {0x14, 0x0001, 2, 1}, /* Channel_11 */
  {0x15, 0x0001, 2, 1}, /* Channel_12 */
  {0x16, 0x0001, 2, 1}, /* Channel_13 */
  {0x17, 0x0001, 2, 1}, /* Channel_14 */
  {0x18, 0x0001, 2, 1}, /* Channel_15 */
  {0x19, 0x0860, 2, 1}, /* Config_0 */
  {0x1A, 0x0860, 2, 1}, /* Config_1 */
  {0x1B, 0x0860, 2, 1}, /* Config_2 */
  {0x1C, 0x0860, 2, 1}, /* Config_3 */
  {0x1D, 0x0860, 2, 1}, /* Config_4 */
  {0x1E, 0x0860, 2, 1}, /* Config_5 */
  {0x1F, 0x0860, 2, 1}, /* Config_6 */
  {0x20, 0x0860, 2, 1}, /* Config_7 */
  {0x21, 0x060180, 3, 1}, /* Filter_0 */
  {0x22, 0x060180, 3, 1}, /* Filter_1 */
  {0x23, 0x060180, 3, 1}, /* Filter_2 */
  {0x24, 0x060180, 3, 1}, /* Filter_3 */
  {0x25, 0x060180, 3, 1}, /* Filter_4 */
  {0x26, 0x060180, 3, 1}, /* Filter_5 */
  {0x27, 0x060180, 3, 1}, /* Filter_6 */
  {0x28, 0x060180, 3, 1}, /* Filter_7 */
  {0x29, 0x800000, 3, 1}, /* Offset_0 */
  {0x2A, 0x800000, 3, 1}, /* Offset_1 */
  {0x2B, 0x800000, 3, 1}, /* Offset_2 */
  {0x2C, 0x800000, 3, 1}, /* Offset_3 */
  {0x2D, 0x800000, 3, 1}, /* Offset_4 */
  {0x2E, 0x800000, 3, 1}, /* Offset_5 */
  {0x2F, 0x800000, 3, 1}, /* Offset_6 */
  {0x30, 0x800000, 3, 1}, /* Offset_7 */
  {0x31, 0x500000, 3, 1}, /* Gain_0 */
  {0x32, 0x500000, 3, 1}, /* Gain_1 */
  {0x33, 0x500000, 3, 1}, /* Gain_2 */
  {0x34, 0x500000, 3, 1}, /* Gain_3 */
  {0x35, 0x500000, 3, 1}, /* Gain_4 */
  {0x36, 0x500000, 3, 1}, /* Gain_5 */
  {0x37, 0x500000, 3, 1}, /* Gain_6 */
  {0x38, 0x500000, 3, 1}, /* Gain_7 */
};

namespace Ad7124 {

  const char RegNameStatus[] PROGMEM = "Status";
  const char RegNameAdcControl[] PROGMEM = "AdcControl";
  const char RegNameData[] PROGMEM = "Data";
  const char RegNameIOCon1[] PROGMEM = "IOCon1";
  const char RegNameIOCon2[] PROGMEM = "IOCon2";
  const char RegNameId[] PROGMEM = "Id";
  const char RegNameError[] PROGMEM = "Error";
  const char RegNameErrorEn[] PROGMEM = "ErrorEn";
  const char RegNameMclkCount[] PROGMEM = "MclkCount";
  const char RegNameChannel[] PROGMEM = "Channel%d";
  const char RegNameConfig[] PROGMEM = "Config%d";
  const char RegNameFilter[] PROGMEM = "Filter%d";
  const char RegNameOffset[] PROGMEM = "Offset%d";
  const char RegNameGain[] PROGMEM = "Gain%d";
  const char * const RegisterNames[] PROGMEM = {
    RegNameStatus,
    RegNameAdcControl,
    RegNameData,
    RegNameIOCon1,
    RegNameIOCon2,
    RegNameId,
    RegNameError,
    RegNameErrorEn,
    RegNameMclkCount
  };
}

// -----------------------------------------------------------------------------
int
Ad7124Register::copyRegisterName (RegisterId id, char * name) {

  if ( (id >= Channel_0) && (id <= Channel_15)) {

    return sprintf_P (name, RegNameChannel, id - Channel_0);
  }
  else if ( (id >= Config_0) && (id <= Config_7)) {

    return sprintf_P (name, RegNameConfig, id - Config_0);
  }
  else if ( (id >= Filter_0) && (id <= Filter_7)) {

    return sprintf_P (name, RegNameFilter, id - Filter_0);
  }
  else if ( (id >= Offset_0) && (id <= Offset_7)) {

    return sprintf_P (name, RegNameOffset, id - Offset_0);
  }
  else if ( (id >= Gain_0) && (id <= Gain_7)) {

    return sprintf_P (name, RegNameGain, id - Gain_0);
  }
  else {
    const char * string = (const char *) pgm_read_word (&RegisterNames[id]);
    return sprintf_P (name, string);
  }
  return -1;
}

// -----------------------------------------------------------------------------
void
Ad7124Register::fillAllRegsWithDefault (Ad7124Register * allregs) {

  memcpy_P (allregs, DefaultRegs, sizeof (DefaultRegs));
}

// -----------------------------------------------------------------------------
bool
Ad7124Register::isWritable() const {

  return rw == AD7124_RW;
}

// -----------------------------------------------------------------------------
uint8_t
Ad7124Register::sizeOf() const {

  return size;
}

/* ========================================================================== */
