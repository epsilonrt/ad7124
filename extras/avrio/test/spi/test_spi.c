#include <avrio/led.h>
#include <avrio/delay.h>
#include <avrio/spi.h>
#include <analog-device/AD7124.h>

/* constants ================================================================ */
#define SPI_SS_BIT       2
#define SPI_DDR          DDRB
#define SPI_PORT         PORTB

/* macros =================================================================== */
/* structures =============================================================== */
/* types ==================================================================== */
/* private variables ======================================================== */
/* public variables ========================================================= */
/* private functions ======================================================== */
// -----------------------------------------------------------------------------
INLINE void
vSetSs (void) {

  SPI_PORT &= ~_BV (SPI_SS_BIT); /* SS = 0 -> validé */
}

// -----------------------------------------------------------------------------
INLINE void
vClearSs (void) {

  SPI_PORT |= _BV (SPI_SS_BIT); /* SS = 1 -> invalidé */
}

/* internal public functions ================================================ */
// -----------------------------------------------------------------------------
void
vAssert (bool bTestIsTrue) {

  if (bTestIsTrue != true) {

    for (;;) {

      vLedSet (LED_LED1);
      delay_ms (10);
      vLedClear (LED_LED1);
      delay_ms (50);
    }
  }
}


// -----------------------------------------------------------------------------
void
vReadBlock (uint8_t * buffer, uint8_t len) {

  vSetSs();
  vSpiMasterXfer (buffer, len, buffer, len);
  vClearSs();
}

// -----------------------------------------------------------------------------
void
vWriteBlock (const uint8_t * buffer, uint8_t len) {

  vSetSs();
  vSpiMasterXfer (buffer, len, NULL, 0);
  vClearSs();
}

// -----------------------------------------------------------------------------
void
vReset (void) {
  uint8_t buffer[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  vWriteBlock (buffer, 8);
}

/* main ===================================================================== */
int
main (void) {
  uint8_t buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  vLedInit ();
  // Votre code d'initialisation devrait être ici
  // Your initialization code should be here
  vSpiSetSsAsOutput();
  vSpiMasterInit (SPI_DIV16);
  vSpiSetMode (eSpiMode3);
  vSpiSetBitOrder (eSpiBitOrderMsb);

  vReset();
  delay_ms (10);

  for (;;) {

    buffer[0] = AD7124_COMM_REG_RD | AD7124_COMM_REG_RA (AD7124_ID_REG);
    vReadBlock (buffer, 2);
    vAssert (buffer[1] == 4);

    buffer[0] = AD7124_COMM_REG_RD | AD7124_COMM_REG_RA (AD7124_Config_0);
    vReadBlock (buffer, 3);
    vAssert ( (buffer[1] == 0x08) && (buffer[2] == 0x60));

    buffer[0] = AD7124_COMM_REG_RD | AD7124_COMM_REG_RA (AD7124_Channel_0);
    vReadBlock (buffer, 3);
    vAssert ( (buffer[1] == 0x80) && (buffer[2] == 0x01));

    buffer[0] = AD7124_COMM_REG_WR | AD7124_COMM_REG_RA (AD7124_Channel_0);
    buffer[1] = 0;
    vWriteBlock (buffer, 3);

    buffer[0] = AD7124_COMM_REG_RD | AD7124_COMM_REG_RA (AD7124_Channel_0);
    vReadBlock (buffer, 3);
    vAssert ( (buffer[1] == 0x0) && (buffer[2] == 0x01));

    buffer[0] = AD7124_COMM_REG_WR | AD7124_COMM_REG_RA (AD7124_Channel_0);
    buffer[1] = 0x80;
    vWriteBlock (buffer, 23);

    buffer[0] = AD7124_COMM_REG_RD | AD7124_COMM_REG_RA (AD7124_Channel_0);
    vReadBlock (buffer, 3);
    vAssert ( (buffer[1] == 0x80) && (buffer[2] == 0x01));

    vLedToggle (LED_LED2);
    delay_ms (100);
  }
  return 0;
}

/* ========================================================================== */
