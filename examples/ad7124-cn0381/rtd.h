#ifndef AD7124_EXAMPLE_RTD_H
#define AD7124_EXAMPLE_RTD_H

#include <ad7124.h>
#include <math.h>

class Rtd {
public:
    enum {
      OpenCircuitError = -10,
      ChannelError = -11
    };
    int begin (int slave_select, Ad7124::IoutCurrent current = Ad7124::Current500uA); // return 0 for success or negative error code
    long code (uint8_t ch); // reads ADC value (negative value if error)
    double resistance (uint8_t ch); // reads the value of ADC and converts it to resistance. (NAN if error)
    double temperature (uint8_t ch); // reads the value of ADC and converts it to celcius temperature . (NAN if error)
    static double toResistance (long value);
    static double toTemperature (double resistance);
  private:
    Ad7124Chip _adc;
    Ad7124::IoutCurrent _current;
};
#endif /* AD7124_EXAMPLE_RTD_H */
