/**
 * Copyright © 2017 epsilonRT. All rights reserved.
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
#ifndef __AD7124_H__
#define __AD7124_H__
/* ========================================================================== */
#include "ad7124-private.h"

namespace Ad7124 {
  enum OperatingMode {
    ContinuousMode = 0,
    SingleConvMode,
    StandbyMode,
    PowerDownMode,
    IdleMode,
    InternalOffsetCalibrationMode,
    InternalGainCalibrationMode,
    SystemOffsetCalibrationMode,
    SystemGainCalibrationMode

  };
  enum PowerMode {
    LowPower = 0,
    MidPower,
    FullPower
  };
  enum ClkSel {
    InternalClk = 0,
    InternalWithOutputClk,
    ExternalClk,
    ExternalDiv4Clk,
  };
  enum IoutCurrent {
    CurrentOff = 0,
    Current50uA,
    Current100uA,
    Current250uA,
    Current500uA,
    Current750uA,
    Current1000uA,
  };
  enum IoutCh {
    IoutCh0 = 0,
    IoutCh1 = 1,
    IoutCh2 = 4,
    IoutCh3 = 5,
    IoutCh4 = 10,
    IoutCh5 = 11,
    IoutCh6 = 14,
    IoutCh7 = 15,
  };
  enum InputSel {
    AIN0Input = 0,
    AIN1Input,
    AIN2Input,
    AIN3Input,
    AIN4Input,
    AIN5Input,
    AIN6Input,
    AIN7Input,
    TEMPInput = 16,
    AVSSInput,
    REFInput,
    DGNDInput,
    AVDD6PInput,
    AVDD6MInput,
    IOVDD6PInput,
    IOVDD6MInput,
    ALDO6PInput,
    ALDO6MInput,
    DLDO6PInput,
    DLDO6MInput,
    V20mVPInput,
    V20mVMInput
  };
  enum PgaSel {
    Pga1 = 0,
    Pga2,
    Pga4,
    Pga8,
    Pga16,
    Pga32,
    Pga64,
    Pga128
  };
  enum RefSel {
    RefIn1 = 0,
    RefIn2,
    RefInternal,
    RefAVdd
  };
  enum BurnoutCurrent {
    BurnoutOff = 0,
    Burnout500nA,
    Burnout2uA,
    Burnout4uA
  };
  enum FilterType {
    Sinc4Filter = 0,
    Sinc3Filter = 2,
    Sinc4FastFilter = 4,
    Sinc3FastFilter = 5,
    PostFilter = 7
  };
  enum PostFilterType {
    dB47PostFilter = 2,
    dB62PostFilter = 3,
    dB86PostFilter = 5,
    dB92PostFilter = 6,
  };
}

/**
 * @class Ad7124Chip
 * @brief AD7124 ADC
 */
class Ad7124Chip {
  public:
    Ad7124Chip ();
    ~Ad7124Chip();
    int init (int slave_select);
    int reset();

    int status();
    int setAdcControl (Ad7124::OperatingMode mode, Ad7124::PowerMode power_mode, bool ref_en = true, Ad7124::ClkSel clk_sel = Ad7124::InternalClk);
    int setMode (Ad7124::OperatingMode mode);
    
    int setChannel (uint8_t ch, uint8_t cfg, Ad7124::InputSel ainp, Ad7124::InputSel ainm, bool enable = false);
    int enableChannel (uint8_t ch, bool enable = true);
    int channelConfig (uint8_t ch);

    int setConfig (uint8_t cfg, Ad7124::RefSel ref, Ad7124::PgaSel pga, bool bipolar, Ad7124::BurnoutCurrent burnout = Ad7124::BurnoutOff);
    int setConfigFilter (uint8_t cfg, Ad7124::FilterType filter, Ad7124::PostFilterType postfilter, uint16_t fs, bool rej60, bool single);
    int setConfigOffset (uint8_t cfg, uint32_t value);
    int setConfigGain (uint8_t cfg, uint32_t value);

    long read (uint8_t ch);
    int startSingleConversion (uint8_t ch);
    int waitEndOfConversion (uint32_t timeout_ms);
    long getData();
    int currentChannel();
    int internalCalibration (uint8_t ch);

    static double toVoltage (long value, int gain, double vref, bool bipolar = true);

    /**
     * @brief return IO timeout in milliseconds (default is 1000ms)
     */
    inline uint32_t timeout() const {
      return d.timeout();
    }

    /**
     * @brief set IO timeout in milliseconds
     */
    inline void setTimeout (uint32_t ms) {
      d.setTimeout (ms);
    }

    /**
     * @brief Reads the value of the specified register
     * @param id register identifier
     * @return 8 to 24 bits register value, negative for error.
     */
    long getRegister (Ad7124::RegisterId id);

    /**
     * @brief Writes the value of the specified register
     * @param id register identifier
     * @param value 8 to 24 bits register value
     * @return 0, negative for error.
     */
    int setRegister (Ad7124::RegisterId id, long value);

  protected:
    int readRegister (Ad7124::RegisterId id);
    int writeRegister (Ad7124::RegisterId id);

  private:
    Ad7124Private d;
    Ad7124Register reg[Ad7124::AD7124_REG_NO];
};

/* ========================================================================== */
#endif /* __AD7124_H__ */
