/*
  AD7124 Voltmeter

  Prints out the voltage measured at pins AIN1(+)/AIN0(-)
  Input voltage must be in the range between 0 and 2.5V

  For more on AD7124, see
  http://www.analog.com/media/en/technical-documentation/data-sheets/AD7124-4.pdf

  The circuit:
  - AD7124 connected on the MOSI, MISO, SCK and /SS pins (pin 10)

  created 2018
  by epsilonrt https://github.com/epsilonrt

  This example code is in the public domain.

  https://github.com/epsilonrt/ad7124/example
*/
#include <ad7124.h>
#include <stdio.h>
#include <avrio/tc.h>

/* constants ================================================================ */
const int ssPin = 10;

/* public variables ========================================================= */
Ad7124Chip adc;

/* internal public functions ================================================ */

// -----------------------------------------------------------------------------
void setup() {

  //Initialize serial and wait for port to open:
  xSerialIos settings = {
    .baud = 500000, // vitesse en bauds
    .dbits = SERIAL_DATABIT_8, // 8 bits de données
    .parity = SERIAL_PARITY_NONE, // pas de parité
    .sbits = SERIAL_STOPBIT_ONE, // 1 bit de stop
    .flow = SERIAL_FLOW_NONE, // pas de contrôle de flux
    .eol = SERIAL_CRLF // fin de ligne en CR+LF
  };

  // Ouverture du port série en sortie non bloquant
  FILE * serial_port = xFileOpen ("tty0", O_WR | O_NONBLOCK, &settings);
  stdout = serial_port; // le port série est la sortie standard
  stderr = serial_port; // le port série est la sortie d'erreur
  sei(); // valide les interruptions

  // prints title with ending line break
  printf ("AD7124 Voltmeter\n");

  // Initializes the AD7124 device, the pin /CS is pin 10 (/SS)
  adc.begin (ssPin);

  // Setting the configuration 0:
  // - use of the internal reference voltage 2.5V
  // - gain of 1 for a bipolar measurement +/- 2.5V
  adc.setConfig (0, Ad7124::RefInternal, Ad7124::Pga1, true);
  // Setting channel 0 using pins AIN1(+)/AIN0(-)
  adc.setChannel (0, 0, Ad7124::AIN1Input, Ad7124::AIN0Input);
  // Configuring ADC in Full Power Mode (Fastest)
  adc.setAdcControl (Ad7124::StandbyMode, Ad7124::FullPower, true);
}

// -----------------------------------------------------------------------------
void loop() {
  long value;
  double voltage;

  // Measuring Voltage on Channel 0 in Single Conversion Mode
  value = adc.read (0);

  if (value >= 0) {

    // If the measurement is successful, the value is converted into voltage
    voltage = Ad7124Chip::toVoltage (value, 1, 2.5, true);
  }
  else {

    voltage = -1;
  }
  // Print result
  printf ("%.03f\n", voltage);
}

// -----------------------------------------------------------------------------
int main (void) {
  setup();
  for (;;) {
    loop();
  }
}
/* ========================================================================== */
