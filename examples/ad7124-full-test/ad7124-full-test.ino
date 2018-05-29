/*
  AD7124 Full Test

  Prints out the voltages measured at pins AIN1/AIN, AIN3/AIN2, AIN5/AIN4 and
  AIN7/AIN6. Input voltages must be in the range between 0 and 2.5V.
  This is a complete test program that checks for errors and displays the
  contents of the AD7124 circuit registers.
  For a more accessible example see voltmeter.ino.

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
#include <stdlib.h>
#include <ad7124.h>

using namespace Ad7124;

// In order not to prefix the constants with Ad7124 :: !
//using namespace Ad7124;

/* constants ================================================================ */
const int ledPin = 9;
const int ssPin = 10;

/* macros =================================================================== */
// Evaluate assertion macro
// If the argument expression of this macro with functional form compares equal
// to zero (i.e., the expression is false), a message is written to the serial
// device and abort is called, terminating the program execution.
#define assert(e) ((e) ? (void)0 : __assert(__func__, __LINE__, #e))

/* public variables ========================================================= */
Ad7124Chip adc;

/* internal public functions ================================================ */

// -----------------------------------------------------------------------------
// Prints AD7124 register value
void printreg (int reg) {
  char name[16];

  if (Ad7124Register::copyRegisterName (reg, name) > 0) {
    long value = adc.getRegister (reg);

    if (value >= 0) {

      Serial.print (name);
      Serial.print ("(0x");
      Serial.print (reg, HEX);
      Serial.print (") = 0x");
      Serial.println (value, HEX);
    }
  }
}

// -----------------------------------------------------------------------------
// Print assertion function
// a message is written to the serial device and abort is called, terminating
// the program execution.
void __assert (const char *__func, int __lineno, const char *__sexp) {

  Serial.print ("Error in ");
  Serial.print (__func);
  Serial.print ("(): line ");
  Serial.print (__lineno);
  Serial.print (", assertion failed: ");
  Serial.print (__sexp);
  Serial.println (", abort !");
  delay (1000); // leave time for the message to appear before aborting
  abort();
}

// -----------------------------------------------------------------------------
void setup() {
  int ret;

  pinMode (ledPin, OUTPUT);
  digitalWrite (ledPin, 1); // clear the LED

  //Initialize serial and wait for port to open:
  Serial.begin (38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // prints title with ending line break
  Serial.println (F ("\nAD7124 Full Test"));

  // Initializes the AD7124 device, the pin /CS is pin 10 (/SS)
  ret = adc.begin (ssPin);
  assert (ret == 0);

  Serial.println (F ("\nSetting up 4 channels with  4setup"));
  for (uint8_t i = 0; i < 4; i++) {

    ret = adc.setConfig (i, RefInternal, Pga1, true);
    assert (ret == 0);
    printreg (Config_0 + i);

    ret = adc.setChannel (i, i, (i * 2 + 1), AVSSInput);
    assert (ret == 0);
    printreg (Channel_0 + i);
  }

  Serial.println (F ("\nSetting up ADC"));
  ret = adc.setAdcControl (StandbyMode, FullPower, true);
  assert (ret == 0);
  printreg (ADC_Control);

  Serial.println (F ("\nCalibration"));
  for (uint8_t i = 0; i < 4; i++) {

    printreg (Offset_0 + i);
    printreg (Gain_0 + i);
  }

  Serial.println (F ("\nV0\tV1\tV2\tV3"));
}

// -----------------------------------------------------------------------------
void loop() {
  int ret;
  long value;
  double voltage;

  for (uint8_t i = 0; i < 4; i++) {

    digitalWrite (ledPin, 0);
    value = adc.read (i);
    digitalWrite (ledPin, 1);

    if (value >= 0) {

      voltage = Ad7124Chip::toVoltage (value, 1, 2.5, true);
      Serial.print (voltage, 3);
      Serial.write ('\t');
    }
    else {

      Serial.print ("FAIL\t");
    }
  }
  Serial.write ('\n');
}
/* ========================================================================== */
