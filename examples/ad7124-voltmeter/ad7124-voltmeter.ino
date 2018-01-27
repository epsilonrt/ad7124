/*
  AD7124 Voltmeter

  Prints out the voltage measured at pins AIN1(+)/AIN0(-)
  Input voltage must be in the range between 0 and 2.5V

  For more on AD7124, see
  http://www.analog.com/media/en/technical-documentation/data-sheets/AD7124-4.pdf

  The circuit:
  - AD7124 connected on the MOSI, MISO, SCK and /SS pins (pin 10)
  - LED active in low state connected to pin 9.
  
  The conversion times are as follows:
  ----------------------------------------
  | Mode      | Tconv (ms) | Fconv (Sps) |
  +-----------+------------+-------------+
  | LowPower  | 652        | 1.534       |
  | MidPower  | 330        | 3.030       |
  | FullPower | 90         | 11.11       |
  ----------------------------------------

  created 2018
  by epsilonrt https://github.com/epsilonrt

  This example code is in the public domain.

  https://github.com/epsilonrt/ad7124/tree/master/examples
*/
#include <ad7124.h>

/* constants ================================================================ */
const int ledPin = 9;
const int ssPin = 10;

/* public variables ========================================================= */
Ad7124Chip adc;

/* internal public functions ================================================ */

// -----------------------------------------------------------------------------
void setup() {

  pinMode (ledPin, OUTPUT);
  digitalWrite (ledPin, 1); // clear the LED

  //Initialize serial and wait for port to open:
  Serial.begin (38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // prints title with ending line break
  Serial.println ("AD7124 Voltmeter");

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
  digitalWrite (ledPin, 0);
  value = adc.read (0);
  digitalWrite (ledPin, 1);

  if (value >= 0) {

    // If the measurement is successful, the value is converted into voltage
    voltage = Ad7124Chip::toVoltage (value, 1, 2.5, true);
    // Print result
    Serial.println (voltage, 3);
  }
  else {

    Serial.println ("FAIL");
  }
}
/* ========================================================================== */
