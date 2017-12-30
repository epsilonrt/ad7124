/**
 * Copyright © 2017 epsilonRT. All rights reserved.
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
/* ========================================================================== */
#include "ad7124-driver.h"
#include <Arduino.h>
#include <Spi.h>

using namespace Ad7124;

/* private functions ======================================================== */

// -----------------------------------------------------------------------------
inline void
vSetSs (int ss_pin) {

  digitalWrite (ss_pin, LOW); /* SS = 0 -> validé */
}

// -----------------------------------------------------------------------------
inline void
vClearSs (int ss_pin) {

  digitalWrite (ss_pin, HIGH); /* SS = 1 -> invalidé */
}

/* internal public functions ================================================ */
// -----------------------------------------------------------------------------
bool
Ad7124Driver::init (uint8_t slaveDeviceId, bool lsbFirst,
                       uint32_t clockFreq, uint8_t clockPol, uint8_t clockEdg) {

  speedMaximum = clockFreq;
  dataOrder = lsbFirst ? LSBFIRST : MSBFIRST;
  
  if (clockPol != 0) {

    dataMode |= SPI_CPOL;
  }

  if (clockEdg == 0) {

    dataMode |= SPI_CPHA;
  }

  id = slaveDeviceId;
  return true;
}

// -----------------------------------------------------------------------------
int
Ad7124Driver::read (uint8_t* data, uint8_t len) {

  SPI.beginTransaction (SPISettings (speedMaximum, dataOrder, dataMode));
  vSetSs (id);
  for (uint8_t i = 0; i < len; i++) {
    data[i] = SPI.transfer (data[i]);
  }
  vClearSs (id);
  SPI.endTransaction();
  return len;
}

// -----------------------------------------------------------------------------
int
Ad7124Driver::write (const uint8_t * data, uint8_t len) {

  SPI.beginTransaction (SPISettings (speedMaximum, dataOrder, dataMode));
  vSetSs (id);
  for (uint8_t i = 0; i < len; i++) {
    SPI.transfer (data[i]);
  }
  vClearSs (id);
  SPI.endTransaction();
  return len;
}

// -----------------------------------------------------------------------------
int 
Ad7124Driver::delay (unsigned long ms) {
  
  delay (ms);
  return 0;
}

/* ========================================================================== */
