/**
 * Copyright © 2017-2018 epsilonRT. All rights reserved.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * <http://www.cecill.info>.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 * @file
 * @brief
 */
#ifndef __AD7124_PRIVATE_H__
#define __AD7124_PRIVATE_H__
/* ========================================================================== */
#include "ad7124-driver.h"

/**
 * @class Ad7124Register
 * @brief Device register info
 */
class Ad7124Register {
  public:
    uint8_t addr;
    int32_t value;
    uint8_t size;
    uint8_t rw;
    bool isWritable() const;
    uint8_t sizeOf() const;
    static void fillAllRegsWithDefault (Ad7124Register * allregs);
    static int copyRegisterName (Ad7124::RegisterId id, char * name);

  private:
    static const Ad7124Register DefaultRegs[Ad7124::Reg_No];
};

/**
 * @class Ad7124Private
 * @brief Low level access to AD7124 ADC
 */
class Ad7124Private {
public:
  /**
   * @brief Constructor
   */
    Ad7124Private ();

  /**
   * @brief Destructor
   */
    ~Ad7124Private();

    /**
     * @brief Initializes the AD7124
     */
    int init (int slave_select, Ad7124Register * regs);

    /**
     * @brief Resets the device
     */
    int reset (void);

    /**
     * @brief Waits until the device can accept read and write user actions
     */
    int waitForSpiReady (uint32_t timeout);

    /**
     * @brief Waits until the device finishes the power-on reset operation
     */
    int waitToPowerOn (uint32_t timeout);

    /**
     * @brief Waits until a new conversion result is available
     */
    int waitForConvReady (uint32_t timeout);

    /**
     * @brief Reads the conversion result from the device
     */
    int readData (int32_t* pData);

    /**
     * @brief Reads the value of the specified register
     */
    int readRegister (Ad7124Register * pReg);

    /**
     * @brief Writes the value of the specified register
     */
    int writeRegister (Ad7124Register reg);

    /**
     * @brief return IO timeout in milliseconds (default 1000ms)
     */
    inline uint32_t timeout() const {
      return responseTimeout;
    }

    /**
     * @brief set IO timeout in milliseconds
     */
    inline void setTimeout (uint32_t ms) {
      responseTimeout = ms;
    }

    /**
     * @brief Computes the CRC checksum for a data buffer
     */
    static uint8_t computeCRC8 (uint8_t * pBuf, uint8_t bufSize);

  protected:
    /**
     * @brief Reads the value of the specified register without a device state check
     */
    int noCheckReadRegister (Ad7124Register * pReg);

    /**
     * @brief Writes the value of the specified register without a device state check
     */
    int noCheckWriteRegister (Ad7124Register reg);

    /**
     * @brief Updates the CRC settings
     */
    void updateCRCSetting (void);

    /**
     * @brief Updates the device SPI interface settings
     */
    void updateDevSpiSettings (void);

  protected:
    Ad7124Driver drv;
    Ad7124Register * reg;
    bool useCRC;
    bool isReady;
    uint32_t responseTimeout;
};

/* ========================================================================== */
#endif /* __AD7124_PRIVATE_H__ */
