/**
 * Copyright © 2017 epsilonRT. All rights reserved.
 *
 * This file is part of AvrIO.
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
#include "avrio-config.h"

#ifdef AVRIO_SPI_ENABLE
/* ========================================================================== */
#include <avrio/spi.h>
#include <avrio/delay.h>
#include "ad7124-driver.h"

extern "C" {
#include <avr/io.h>
}

using namespace Ad7124;

/* constants ================================================================ */
#define SPI_SS_BIT       2
#define SPI_DDR          DDRB
#define SPI_PORT         PORTB

/* private functions ======================================================== */

// -----------------------------------------------------------------------------
inline void
vSetSs (void) {

  SPI_PORT &= ~_BV (SPI_SS_BIT); /* SS = 0 -> validé */
}

// -----------------------------------------------------------------------------
inline void
vClearSs (void) {

  SPI_PORT |= _BV (SPI_SS_BIT); /* SS = 1 -> invalidé */
}

/* internal public functions ================================================ */
// -----------------------------------------------------------------------------
bool
Ad7124Driver::init (uint8_t slaveDeviceId, bool lsbFirst,
                    uint32_t clockFreq, uint8_t clockPol, uint8_t clockEdg) {

  eSpiFclkDiv eDiv = SPI_DIV128;
  int eMode = eSpiMode0;
  eSpiBitOrder eOrder = lsbFirst ? eSpiBitOrderLsb : eSpiBitOrderMsb;

  clockFreq = F_CPU / clockFreq;
  if (clockFreq <= 2) {
    eDiv = SPI_DIV2;
  }
  else if (clockFreq <= 4) {
    eDiv = SPI_DIV4;
  }
  else if (clockFreq <= 8) {
    eDiv = SPI_DIV8;
  }
  else if (clockFreq <= 16) {
    eDiv = SPI_DIV16;
  }
  else if (clockFreq <= 32) {
    eDiv = SPI_DIV32;
  }
  else if (clockFreq <= 64) {
    eDiv = SPI_DIV64;
  }

  if (clockPol != 0) {

    eMode |= SPI_CPOL;
  }

  if (clockEdg == 0) {

    eMode |= SPI_CPHA;
  }

  vSpiSetSsAsOutput();
  vSpiMasterInit (eDiv);
  vSpiSetMode ( (eSpiMode) eMode);
  vSpiSetBitOrder (eOrder);

  id = slaveDeviceId;
  return true;
}

// -----------------------------------------------------------------------------
int
Ad7124Driver::read (uint8_t* data, uint8_t len) {

  vSetSs();
  vSpiMasterXfer (data, len, data, len);
  vClearSs();
  return len;
}

// -----------------------------------------------------------------------------
int
Ad7124Driver::write (const uint8_t * data, uint8_t len) {

  vSetSs();
  vSpiMasterXfer (data, len, NULL, 0);
  vClearSs();
  return len;
}

// -----------------------------------------------------------------------------
int 
Ad7124Driver::delay (unsigned long ms) {
  
  delay_ms (ms);
  return 0;
}

#endif /* AVRIO_SPI_ENABLE defined */
/* ========================================================================== */
