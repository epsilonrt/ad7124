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
#ifndef __AD7124_DRIVER_ARDUINO_H__
#define __AD7124_DRIVER_ARDUINO_H__
/* ========================================================================== */
#include "ad7124-defs.h"

/**
 * @class Ad7124Driver
 * @brief SPI driver
 */
class Ad7124Driver {

  public:
    /**
     * @brief Initializes the SPI communication peripheral.
     *
     * @param slaveDeviceId - The ID of the selected slave device.
     * @param lsbFirst - Transfer format (0 or 1).
     *                   Example: 0x0 - MSB first.
     *                            0x1 - LSB first.
     * @param clockFreq - SPI clock frequency (Hz).
     *                    Example: 1000 - SPI clock frequency is 1 kHz.
     * @param clockPol - SPI clock polarity (0 or 1).
     *                   Example: 0x0 - Idle state for clock is a low level; active
     *                                  state is a high level;
     *                        0x1 - Idle state for clock is a high level; active
     *                                  state is a low level.
     * @param clockEdg - SPI clock edge (0 or 1).
     *                   Example: 0x0 - Serial output data changes on transition
     *                                  from idle clock state to active clock state;
     *                            0x1 - Serial output data changes on transition
     *                                  from active clock state to idle clock state.
     *
     * @return status - Result of the initialization procedure.
     *                  Example: true - if initialization was successful;
     *                           false - if initialization was unsuccessful.
     */
    bool init (uint8_t slaveDeviceId, bool lsbFirst,
               uint32_t clockFreq, uint8_t clockPol, uint8_t clockEdg);

    /**
     * @brief Reads data from SPI.
     *
     * @param data - Data represents the write buffer as an input parameter and the
     *               read buffer as an output parameter.
     * @param len - Number of bytes to read.
     *
     * @return Number of read bytes, negative for error.
     */
    int read (uint8_t* data, uint8_t len);

    /**
     * @brief Writes data to SPI.
     *
     * @param data - Data represents the write buffer.
     * @param len - Number of bytes to write.
     *
     * @return Number of written bytes, negative for error.
     */
    int write (const uint8_t * data, uint8_t len);

    /**
     * @brief Pauses the program for the amount of time (in milliseconds) specified as parameter. 
     * @param ms in milliseconds
     * @return 0, negative for error.
     */
    int delay (unsigned long ms);

  protected:
    uint8_t id;
    
  private:
    uint32_t speedMaximum;
    uint8_t dataOrder;
    uint8_t dataMode;
};
/* ========================================================================== */
#endif /* __AD7124_DRIVER_ARDUINO_H__ */
