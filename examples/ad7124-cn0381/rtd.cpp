#include "rtd.h"

using namespace Ad7124;

// Mathematical constants
const double Gain = 16;
const double Rf = 5.11E3;
const long Zero = 1L << 23;
const long FullScale = 1L << 24;

// -----------------------------------------------------------------------------
int Rtd::begin (int slave_select, IoutCurrent current) {
  int ret;

  _current = current;

  // Initializes the AD7124 device
  ret = _adc.begin (slave_select);
  if (ret == 0) {
    // Setting the configuration 0:
    // - use of the REFIN1(+)/REFIN1(-) reference
    // - gain of 16 for a bipolar measurement
    // - digital filter Sync4 FS=384
    _adc.setConfig (0, RefIn1, Pga16, true);
    _adc.setConfigFilter (0, Sinc4Filter, 384);

    // Setting channel 0 with config 0 using pins AIN2(+)/AIN3(-)
    _adc.setChannel (0, 0, AIN2Input, AIN3Input);
    // Setting channel 1 with config 0 using pins AIN4(+)/AIN5(-)
    _adc.setChannel (1, 0, AIN4Input, AIN5Input);

    // Configuring ADC in Full Power Mode (Fastest)
    ret = _adc.setAdcControl (StandbyMode, FullPower, true);
  }
  return ret;
}

// -----------------------------------------------------------------------------
long Rtd::code (uint8_t ch) {
  long value;

  if (ch > 1) {
    return ChannelError;
  }

  // detect an open wire circuit (no RTD connected) or a short-circuit
  _adc.setConfig (0, RefInternal, Pga1, true, Burnout4uA);
  value = _adc.read (ch);
  _adc.setConfig (0, RefInternal, Pga1, true, BurnoutOff);

  if (value >= 0) {

    if (value >= (FullScale - 10))  {

      // A near full-scale reading can mean that the front-end sensor is open circuit.
      return OpenCircuitError;
    }
    else {

      // Setting the configuration 0 for measuring
      _adc.setConfig (0, RefIn1, Pga16, true);
      // Program the excitation currents and output the currents on the AIN0/1
      _adc.setCurrentSource (ch, ch, _current);

      // Measuring on Channel 0 in Single Conversion Mode
      value = _adc.read (ch);

      // Program the excitation currents to Off
      _adc.setCurrentSource (ch, ch, CurrentOff);
    }
  }
  return value;
}

// -----------------------------------------------------------------------------
double Rtd::toResistance (long value) {

  return ( (value - Zero) * Rf) / (Zero * Gain);
}

// -----------------------------------------------------------------------------
double Rtd::toTemperature (double r) {

  return (r - 100.0) / 0.385;
}

// -----------------------------------------------------------------------------
double Rtd::resistance (uint8_t ch) {
  long value = code (ch);
  if (value >= 0) {
    return toResistance (value);
  }
  return NAN;
}

// -----------------------------------------------------------------------------
double Rtd::temperature (uint8_t ch) {
  long value = code (ch);
  if (value >= 0) {
    return toTemperature (toResistance (value));
  }
  return NAN;
}
