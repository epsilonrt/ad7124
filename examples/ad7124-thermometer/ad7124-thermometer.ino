/*
  CN-0381 Thermometer (AD7124)
  Completely Integrated 4-Wire RTD Measurement System Using a AD7124
  See http://www.analog.com/media/en/reference-design-documentation/reference-designs/CN0381.pdf

  Prints out the RTD temperature and resistor measured at pins AIN2(+)/AIN3(-)
  for schematic see Figure 1., p.2 of CN-0381, e.g. :
  CN-0381 RTD Thermometer
  23.143,108.910
  23.143,108.910


  For more on AD7124, see
  http://www.analog.com/media/en/technical-documentation/data-sheets/AD7124-4.pdf

  The circuit:
  - AD7124 connected on the MOSI, MISO, SCK and /SS pins (pin 10)
  - LED active in low state connected to pin 9.

  created 2018
  by epsilonrt https://github.com/epsilonrt

  This example code is in the public domain.

  https://github.com/epsilonrt/ad7124/tree/master/examples
*/
#include <ad7124.h>

using namespace Ad7124;

/* constants ================================================================ */
const int ledPin = 9;
const int ssPin = 10;

// Mathematical constants
const double Gain = 16;
const double Rf = 5.11E3;
const unsigned long CodeMax = 1UL << 23;

/* public variables ========================================================= */
Ad7124Chip adc;

/* internal public functions ================================================ */

// -----------------------------------------------------------------------------
void setup() {
  int ret;
  long value;

  pinMode (ledPin, OUTPUT);
  digitalWrite (ledPin, 1); // clear the LED

  //Initialize serial and wait for port to open:
  Serial.begin (38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // prints title with ending line break
  Serial.println ("CN-0381 RTD Thermometer");

  // Initializes the AD7124 device, the pin /CS is pin 10 (/SS)
  adc.begin (ssPin);

  // Setting the configuration 0:
  // - use of the REFIN1(+)/REFIN1(-) reference
  // - gain of 16 for a bipolar measurement
  adc.setConfig (0, RefIn1, Pga16, true);

  // Setting channel 0 with config 0 using pins AIN2(+)/AIN3(-)
  adc.setChannel (0, 0, AIN2Input, AIN3Input);

  ret = adc.setCurrentSource (0, IoutCh0, Current500uA);
  if (ret < 0) {

    Serial.println ("Unable to setting up Iout0");
  }

  ret = adc.setConfigFilter (0, Sinc4Filter, 384);
  if (ret < 0) {

    Serial.println ("Unable to setting up digital filter");
  }

  // Configuring ADC in Full Power Mode (Fastest)
  ret = adc.setAdcControl (StandbyMode, FullPower, true);
  if (ret < 0) {

    Serial.println ("Unable to setting up ADC");
  }

  ret = adc.internalCalibration (0);
  if (ret < 0) {

    Serial.println ("Unable to calibrate");
  }
}

// -----------------------------------------------------------------------------
void loop() {
  long value;

  // Measuring on Channel 0 in Single Conversion Mode
  digitalWrite (ledPin, 0);
  value = adc.read (0);
  digitalWrite (ledPin, 1);

  if (value >= 0) {
    double r, t = 0;

    // See Equation (1), p.4 of CN-0381
    r = (static_cast<double> (value - CodeMax) * Rf) / (static_cast<double> (CodeMax) * Gain);

    // See Equation (2), p.4 of CN-0381
    t = (r - 100.0) / 0.385;

    // Print results
    Serial.print (t, 3);
    Serial.print (",");
    Serial.println (r, 3);
  }
  else {

    Serial.println ("FAIL");
  }
}
/* ========================================================================== */
