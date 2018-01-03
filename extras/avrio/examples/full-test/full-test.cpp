#include <stdlib.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avrio/led.h>
#include <avrio/delay.h>
#include <avrio/tc.h>
#include <avrio/assert.h>

#include <ad7124.h>

using namespace Ad7124;
/* constants ================================================================ */
#define BAUDRATE 500000
#define PORT "tty0" // UART0
#define VREF 2.5
#define GAIN 1
#define BIPOLAR true
#define CALIBRATION_ENABLE 0

/* macros =================================================================== */
#if GAIN == 1
#define PGA Pga1
#elif GAIN == 2
#define PGA Pga2
#elif GAIN == 4
#define PGA Pga4
#elif GAIN == 8
#define PGA Pga8
#elif GAIN == 16
#define PGA Pga16
#elif GAIN == 32
#define PGA Pga32
#elif GAIN == 64
#define PGA Pga64
#elif GAIN == 128
#define PGA Pga128
#endif

/* public variables ========================================================= */
Ad7124Chip adc;

/* private functions ======================================================== */
void vPrintReg (int id);
void vPrintAllRegs (void);

/* main ===================================================================== */
int
main (void) {
  int ret;
  long value;
  double voltage;

  vLedInit ();

  // Configuration du port série
  xSerialIos settings = {
    .baud = BAUDRATE, // vitesse en bauds
    .dbits = SERIAL_DATABIT_8, // 8 bits de données
    .parity = SERIAL_PARITY_NONE, // pas de parité
    .sbits = SERIAL_STOPBIT_ONE, // 1 bit de stop
    .flow = SERIAL_FLOW_NONE, // pas de contrôle de flux
    .eol = SERIAL_CRLF // fin de ligne en CR+LF
  };

  // Ouverture du port série en sortie non bloquant
  FILE * serial_port = xFileOpen (PORT, O_WR | O_NONBLOCK, &settings);
  stdout = serial_port; // le port série est la sortie standard
  stderr = serial_port; // le port série est la sortie d'erreur
  sei(); // valide les interruptions

  ret = adc.begin (10);
  assert (ret == 0);

  //printf_P (PSTR ("---- After reset ----\n"));
  //vPrintAllRegs();

  for (uint8_t i = 0; i < 4; i++) {

    printf_P (PSTR ("\nSetting up channel #%d with setup #%d\n"), i, i);
    
    ret = adc.setConfig (i, RefInternal, PGA, BIPOLAR);
    assert (ret == 0);
    vPrintReg (Config_0 + i);

    //ret = adc.setChannel (i, i, REFInput, AVSSInput);
    //ret = adc.setChannel (i, i, (InputSel) (i * 2 + 1), (InputSel) (i * 2));
    ret = adc.setChannel (i, i, (InputSel) (i * 2 + 1), AVSSInput);
    //ret = adc.setChannel (i, i, V20mVPInput, V20mVMInput);
    //ret = adc.setChannel (i, i, AVDD6PInput, AVDD6MInput);
    assert (ret == 0);
    vPrintReg (Channel_0 + i);
  }

  printf_P (PSTR ("\nSetting up ADC\n"));
  ret = adc.setAdcControl (StandbyMode, FullPower, true);
  assert (ret == 0);
  vPrintReg (ADC_Control);
  
  printf_P (PSTR ("\nCalibration\n"));
  for (uint8_t i = 0; i < 4; i++) {

    vPrintReg (Offset_0 + i);
    vPrintReg (Gain_0 + i);
#if CALIBRATION_ENABLE
    printf_P (PSTR ("\nInternal calibration for channel #%d\n"), i);
    ret = adc.internalCalibration (i);
    assert (ret == 0);
    vPrintReg (Offset_0 + i);
    vPrintReg (Gain_0 + i);
#endif
  }

  //printf_P (PSTR ("\nADC0\t\ADC1\t\tADC2\t\tADC3\n"));
  printf_P (PSTR ("\nV0\tV1\tV2\tV3\n"));

  for (;;) {

    for (uint8_t i = 0; i < 4; i++) {

      vLedSet (LED_LED2);
      value = adc.read (i);
      vLedClear (LED_LED2);

      if (value >= 0) {

        voltage = Ad7124Chip::toVoltage (value, GAIN, VREF, BIPOLAR);
      }
      else {
        voltage = -1;
      }
      // printf_P (PSTR ("%ld\t"), value);
      printf_P (PSTR ("%.03g\t"), voltage);
    }
    putchar ('\n');
    delay_ms (1000);
  }
  return 0;
}


/* internal public functions ================================================ */

// -----------------------------------------------------------------------------
void
vPrintReg (int id) {
  char name[16];
  if (Ad7124Register::copyRegisterName ( (RegisterId) id, name) > 0) {
    long value = adc.getRegister ( (RegisterId) id);
    if (value >= 0) {

      printf_P (PSTR ("%s(0x%02X) = 0x%lX\n"), name, id, value);
    }
  }
}

// -----------------------------------------------------------------------------
void
vPrintAllRegs (void) {

  for (int i = Status; i < Reg_No; i++) {

    vPrintReg ( (RegisterId) i);
  }
  putchar ('\n');
}

/* ========================================================================== */
