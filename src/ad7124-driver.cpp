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
/* ========================================================================== */
#include "include/ad7124-driver.h"
#include <Arduino.h>
#include <SPI.h>

/* private functions ======================================================== */
// -----------------------------------------------------------------------------
static inline void
setSS (int ss_pin) {

  digitalWrite (ss_pin, LOW); /* SS = 0 -> validé */
}

// -----------------------------------------------------------------------------
static inline void
clearSS (int ss_pin) {

  digitalWrite (ss_pin, HIGH); /* SS = 1 -> invalidé */
}

// ---------------------------------------------------------------------------
static inline void
initSS (int ss_pin) {

  pinMode (ss_pin, OUTPUT);
  clearSS (ss_pin);
}

/* internal public functions ================================================ */
// -----------------------------------------------------------------------------
bool
Ad7124Driver::init (uint8_t slaveDeviceId, bool lsbFirst,
                    uint32_t clockFreq, uint8_t clockPol, uint8_t clockEdg) {

  id = slaveDeviceId;
  initSS (id);

  speedMaximum = clockFreq;
  dataOrder = lsbFirst ? LSBFIRST : MSBFIRST;

  if ( (clockPol == 0) && (clockEdg == 1)) {

    dataMode = SPI_MODE0;
  }
  else if ( (clockPol == 0) && (clockEdg == 0)) {

    dataMode = SPI_MODE1;
  }
  else if ( (clockPol == 1) && (clockEdg == 1)) {

    dataMode = SPI_MODE2;
  }
  else if ( (clockPol == 1) && (clockEdg == 0)) {

    dataMode = SPI_MODE3;
  }
  
  SPI.begin();
  return true;
}

// -----------------------------------------------------------------------------
int
Ad7124Driver::read (uint8_t* data, uint8_t len) {

  SPI.beginTransaction (SPISettings (speedMaximum, dataOrder, dataMode));
  setSS(id);
  for (uint8_t i = 0; i < len; i++) {
    data[i] = SPI.transfer (data[i]);
  }
  clearSS(id);
  SPI.endTransaction();
  return len;
}

// -----------------------------------------------------------------------------
int
Ad7124Driver::write (const uint8_t * data, uint8_t len) {

  SPI.beginTransaction (SPISettings (speedMaximum, dataOrder, dataMode));
  setSS(id);
  for (uint8_t i = 0; i < len; i++) {
    SPI.transfer (data[i]);
  }
  clearSS(id);
  SPI.endTransaction();
  return len;
}

// -----------------------------------------------------------------------------
int
Ad7124Driver::delay (unsigned long ms) {

  ::delay (ms);
  return 0;
}

/* ========================================================================== */
