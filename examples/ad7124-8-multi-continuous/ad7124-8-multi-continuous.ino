/*
 * AD7124-8 Six channel continuous sampling example
 * June 2019 - WizardTim
 * 
 * Prints voltages measured at differential pin pairs 2&3 to 12&13, sample rate is controlled by the limitations of the filterWord.
 * 
 * For more on AD7124-8, see
 * http://www.analog.com/media/en/technical-documentation/data-sheets/AD7124-8.pdf
 * 
 * The circuit:
 * - Arduino MCU (tested on Arduino Pro Micro aka LilyPad Arduino USB)
 * - AD7124-8 connected to MISO. MOSI. SCK amd /SS pins (pin 10) 
 */
 
#include <ad7124.h>

Ad7124Chip strainADC;

// Physical Pins
const int ssPin = 10;

long SBraw[7];
double SBvolt[7];
long dataWord;
byte statusWord;
byte ch;

// Sample Speed Setting (Full Power Sinc3 Filter Mode)
//  FW  |  SPS  |  SPS/Ch
//  600 |    6  |     1
//  100 |   60  |    10
//   40 |  156  |    26
//   20 |  300  |    50
int filterWord = 100;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);

  Serial.begin (9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }

  // Loop until ADC responds
  int state = strainADC.begin(ssPin);
  while (state < 0) {
    Serial.println(state);
    Serial.println ("Failed");
    delay(100);
    state = strainADC.begin(ssPin);
  }

  // Configuring ADC in Full Power Mode & Continuous Mode (Prevents sleep mode)
  strainADC.setAdcControl(Ad7124::ContinuousMode, Ad7124::FullPower, true);

  strainADC.setMode(Ad7124::ContinuousMode);

  // Configure Channel 0
  strainADC.setConfig(0, Ad7124::RefInternal, Ad7124::Pga1, true);
  strainADC.setConfigFilter(0, Ad7124::Sinc3Filter, filterWord);
  strainADC.setChannel(0, 0, Ad7124::AIN3Input, Ad7124::AIN2Input, true);
  
  // Configure Channel 1
  strainADC.setConfig(1, Ad7124::RefInternal, Ad7124::Pga1, true);
  strainADC.setConfigFilter(1, Ad7124::Sinc3Filter, filterWord);
  strainADC.setChannel(1, 1, Ad7124::AIN5Input, Ad7124::AIN4Input, true);
  
  // Configure Channel 2
  strainADC.setConfig(2, Ad7124::RefInternal, Ad7124::Pga1, true);
  strainADC.setConfigFilter(2, Ad7124::Sinc3Filter, filterWord);
  strainADC.setChannel(2, 2, Ad7124::AIN7Input, Ad7124::AIN6Input, true);
  
  // Configure Channel 3
  strainADC.setConfig(3, Ad7124::RefInternal, Ad7124::Pga1, true);
  strainADC.setConfigFilter(3, Ad7124::Sinc3Filter, filterWord);
  strainADC.setChannel(3, 3, Ad7124::AIN9Input, Ad7124::AIN8Input, true);
  
  // Configure Channel 4
  strainADC.setConfig(4, Ad7124::RefInternal, Ad7124::Pga1, true);
  strainADC.setConfigFilter(4, Ad7124::Sinc3Filter, filterWord);
  strainADC.setChannel(4, 4, Ad7124::AIN11Input, Ad7124::AIN10Input, true);
  
  // Configure Channel 5
  strainADC.setConfig(5, Ad7124::RefInternal, Ad7124::Pga1, true);
  strainADC.setConfigFilter(5, Ad7124::Sinc3Filter, filterWord);
  strainADC.setChannel(5, 5, Ad7124::AIN13Input, Ad7124::AIN12Input, true);

  strainADC.enableChannel(0,true);
  strainADC.enableChannel(1,true);
  strainADC.enableChannel(2,true);
  strainADC.enableChannel(3,true);
  strainADC.enableChannel(4,true);
  strainADC.enableChannel(5,true);
  strainADC.enableChannel(6,false);
  strainADC.enableChannel(7,false);

  delay(100);
}

void loop() {
  digitalWrite(LED_BUILTIN, 0);

  for (int i = 1; i <= 6; i++) {
    strainADC.waitEndOfConversion(500);
    dataWord = strainADC.getData();
    ch = strainADC.currentChannel();
  
    // check RDY bit
    if (ch >= 0) {
      SBraw[ch + 1] = dataWord;
      SBvolt[ch] = Ad7124Chip::toVoltage(SBraw[ch], 1, 2.5, true); 
    }
  }
  
  Serial.print("$");
  for (int i = 1; i <= 6; i++) {
    Serial.print(",");
    Serial.print(SBvolt[i]);
  }

  Serial.println("");
  digitalWrite(LED_BUILTIN, 1);
}
