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
/* ========================================================================== */
#include "ad7124.h"

using namespace Ad7124;

// -----------------------------------------------------------------------------
//
//                            Ad7124Chip class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
Ad7124Chip::Ad7124Chip () {

  Ad7124Register::fillAllRegsWithDefault (reg);
}

// -----------------------------------------------------------------------------
Ad7124Chip::~Ad7124Chip() {

}

// -----------------------------------------------------------------------------
int
Ad7124Chip::init (int slave_select) {
  int ret;

  ret = d.init (slave_select, reg);
  if (ret < 0) {
    return ret;
  }
  
  return setAdcControl(StandbyMode, LowPower, false);
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::reset() {

  return d.reset();
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::status() {

  return (uint8_t) getRegister (AD7124_Status);
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::currentChannel() {
  int ret = status();

  if (ret) {
    return ret;
  }
  return (uint8_t) (ret & AD7124_STATUS_REG_CH_ACTIVE (15));
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::setChannel (uint8_t ch, uint8_t cfg, InputSel ainp,
                        InputSel ainm, bool enable) {

  if ( (ch < 16) && (cfg < 8)) {

    int id =  AD7124_CH0_MAP_REG +  ch;

    reg[id].value = AD7124_CH_MAP_REG_SETUP (cfg) |
                    AD7124_CH_MAP_REG_AINP (ainp) |
                    AD7124_CH_MAP_REG_AINM (ainm) |
                    (enable ? AD7124_CH_MAP_REG_CH_ENABLE : 0);

    return writeRegister ( (RegisterId) id);
  }
  return -1;
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::enableChannel (uint8_t ch, bool enable) {

  if (ch < 16) {
    int ret;

    ch += AD7124_CH0_MAP_REG;

    ret = readRegister ( (RegisterId) ch);
    if (ret < 0) {
      return ret;
    }

    if (enable) {

      reg[ch].value |= AD7124_CH_MAP_REG_CH_ENABLE;

    }
    else {

      reg[ch].value &= ~AD7124_CH_MAP_REG_CH_ENABLE;
    }

    return writeRegister ( (RegisterId) ch);
  }
  return -1;
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::setConfig (uint8_t cfg, RefSel ref, PgaSel pga,
                       bool bipolar, BurnoutCurrent burnout) {

  if (cfg < 8) {
    cfg += AD7124_CFG0_REG;

    reg[cfg].value =    AD7124_CFG_REG_REF_SEL (ref) |
                        AD7124_CFG_REG_PGA (pga) |
                        (bipolar ? AD7124_CFG_REG_BIPOLAR : 0) |
                        AD7124_CFG_REG_BURNOUT (burnout) |
                        AD7124_CFG_REG_REF_BUFP | AD7124_CFG_REG_REF_BUFM |
                        AD7124_CFG_REG_AIN_BUFP | AD7124_CFG_REG_AINN_BUFM;
    return writeRegister ( (RegisterId) cfg);
  }
  return -1;
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::setConfigFilter (uint8_t cfg, FilterType filter, PostFilterType postfilter, uint16_t fs, bool rej60, bool single) {

  if (cfg < 8) {
    cfg += AD7124_FILT0_REG;


    reg[cfg].value =    AD7124_FILT_REG_FILTER ( (uint32_t) filter) |
                        AD7124_FILT_REG_POST_FILTER ( (uint32_t) postfilter) |
                        AD7124_FILT_REG_FS (fs)    |
                        (rej60 ? AD7124_FILT_REG_REJ60 : 0) |
                        (single ? AD7124_FILT_REG_SINGLE_CYCLE : 0);
    return writeRegister ( (RegisterId) cfg);
  }
  return -1;
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::setConfigOffset (uint8_t cfg, uint32_t value) {

  if (cfg < 8) {
    cfg += AD7124_OFFS0_REG;
    return setRegister ( (RegisterId) cfg, value);
  }
  return -1;
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::setConfigGain (uint8_t cfg, uint32_t value) {

  if (cfg < 8) {
    cfg += AD7124_GAIN0_REG;
    return setRegister ( (RegisterId) cfg, value);
  }
  return -1;
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::setAdcControl (OperatingMode mode,
                           PowerMode power_mode,
                           bool ref_en, ClkSel clk_sel) {

  reg[AD7124_ADC_Control].value = AD7124_ADC_CTRL_REG_MODE (mode) |
                                  AD7124_ADC_CTRL_REG_POWER_MODE (power_mode) |
                                  AD7124_ADC_CTRL_REG_CLK_SEL (clk_sel) |
                                  (ref_en ? AD7124_ADC_CTRL_REG_REF_EN : 0) |
                                  AD7124_ADC_CTRL_REG_DOUT_RDY_DEL;

  return writeRegister (AD7124_ADC_Control);
}

// -----------------------------------------------------------------------------
long
Ad7124Chip::read (uint8_t ch) {
  int ret;
  int32_t value;
  uint8_t cur_ch = currentChannel();


  if (ch != cur_ch) {

    ret = enableChannel (cur_ch, false);
    if (ret < 0) {
      return ret;
    }
  }

  ret = enableChannel (ch, true);
  if (ret < 0) {
    return ret;
  }
  
  ret = d.waitForConvReady(timeout());
  if (ret < 0) {
    return ret;
  }
  
  ret = d.readData(&value);
  if (ret < 0) {
    return ret;
  }

  return (long) value;
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::readRegister (RegisterId id) {

  if ( (id >= AD7124_Status) && (id < AD7124_REG_NO))  {

    return d.readRegister (&reg[id]);
  }
  return -1;
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::writeRegister (RegisterId id) {

  if ( (id >= AD7124_Status) && (id < AD7124_REG_NO))  {

    return d.writeRegister (reg[id]);
  }
  return -1;
}

// -----------------------------------------------------------------------------
long
Ad7124Chip::getRegister (RegisterId id) {
  int ret;

  ret = readRegister (id);
  if (ret < 0) {

    return ret;
  }
  return reg[id].value;
}

// -----------------------------------------------------------------------------
int
Ad7124Chip::setRegister (RegisterId id, long value) {

  if ( (id >= AD7124_Status) && (id < AD7124_REG_NO))  {

    reg[id].value = value;
    return writeRegister (id);
  }
  return -1;
}
/* ========================================================================== */
