/**
 * Copyright © 2017-2018 epsilonRT. All rights reserved.
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
#include "include/ad7124-private.h"

/**
 * @brief General namespace
 */
namespace Ad7124 {
  /**
   * @enum OperatingMode
   * @brief Control the mode of operation for ADC
   */
  enum OperatingMode {
    ContinuousMode = 0, /**< Continuous conversion mode (default). In continuous conversion mode, the ADC continuously performs conversions and places the result in the data register. */
    SingleConvMode, /**< Single conversion mode. When single conversion mode is selected, the ADC powers up and performs a single conversion on the selected channel. */
    StandbyMode, /**< Standby mode. In standby mode, all sections of the AD7124 can be powered down except the LDOs. */
    PowerDownMode, /**< Power-down mode. In power-down mode, all the AD7124 circuitry is powered down, including the current sources, power switch, burnout currents, bias voltage generator, and clock circuitry. */
    IdleMode, /**< Idle mode. In idle mode, the ADC filter and modulator are held in a reset state even though the modulator clocks continue to be provided. */
    InternalOffsetCalibrationMode, /**< Internal zero-scale (offset) calibration. An internal short is automatically connected to the input. RDY goes high when the calibration is initiated and returns low when the calibration is complete. */
    InternalGainCalibrationMode, /**< Internal full-scale (gain) calibration. A full-scale input voltage is automatically connected to the selected analog input for this calibration. */
    SystemOffsetCalibrationMode, /**< System zero-scale (offset) calibration. Connect the system zero-scale input to the channel input pins of the selected channel. RDY goes high when the calibration is initiated and returns low when the calibration is complete. */
    SystemGainCalibrationMode /**< System full-scale (gain) calibration. Connect the system full-scale input to the channel input pins of the selected channel. RDY goes high when the calibration is initiated and returns low when the calibration is complete. */
  };
  /**
   * @enum PowerMode
   * @brief Power Mode Select
   * These bits select the power mode. The current consumption and output data rate
   * ranges are dependent on the power mode.
   */
  enum PowerMode {
    LowPower = 0, /**< low power */
    MidPower, /**< mid power */
    FullPower /**< full power */
  };
  /**
   * @enum ClkSel
   * @brief These bits select the clock source for the ADC
   * Either the on-chip 614.4 kHz clock can be used or an external clock can be
   * used. The ability to use an external clock allows several AD7124 devices to be
   * synchronized. Also, 50 Hz and 60 Hz rejection is improved when an accurate external clock drives the ADC.
   */
  enum ClkSel {
    InternalClk = 0, /**< internal 614.4 kHz clock. The internal clock is not available at the CLK pin. */
    InternalWithOutputClk, /**< internal 614.4 kHz clock. This clock is available at the CLK pin. */
    ExternalClk, /**< external 614.4 kHz clock. */
    ExternalDiv4Clk /**< external clock. The external clock is divided by 4 within the AD7124. */
  };
  /**
   * @enum IoutCurrent
   * @brief These bits set the value of the excitation current for IOUT
   */
  enum IoutCurrent {
    CurrentOff = 0, /**< Off */
    Current50uA, /**< 50 μA */
    Current100uA, /**< 100 μA */
    Current250uA, /**< 250 μA */
    Current500uA, /**< 500 μA */
    Current750uA, /**< 750 μA */
    Current1000uA /**< 1 mA */
  };
  /**
   * @enum IoutCh
   * @brief Channel select bits for the excitation current for IOUT.
   */
  enum IoutCh {
    IoutCh0 = 0, /**< IOUT is available on the AIN0 pin. */
    IoutCh1 = 1, /**< IOUT is available on the AIN1 pin. */
    IoutCh2 = 4, /**< IOUT is available on the AIN2 pin. */
    IoutCh3 = 5, /**< IOUT is available on the AIN3 pin. */
    IoutCh4 = 10, /**< IOUT is available on the AIN4 pin. */
    IoutCh5 = 11, /**< IOUT is available on the AIN5 pin. */
    IoutCh6 = 14, /**< IOUT is available on the AIN6 pin. */
    IoutCh7 = 15 /**< IOUT is available on the AIN7 pin. */
  };
  /**
   * @enum InputSel
   * @brief Analog input AIN input select
   */
  enum InputSel {
    AIN0Input = 0, /**< AIN0 */
    AIN1Input, /**< AIN1 */
    AIN2Input, /**< AIN2 */
    AIN3Input, /**< AIN3 */
    AIN4Input, /**< AIN4 */
    AIN5Input, /**< AIN5 */
    AIN6Input, /**< AIN6 */
    AIN7Input, /**< AIN7 */
    TEMPInput = 16, /**< Temperature sensor (internal) */
    AVSSInput, /**< AVss */
    REFInput, /**< Internal reference */
    DGNDInput, /**< DGND. */
    AVDD6PInput, /**< (AVdd − AVss)/6+. Use in conjunction with (AVdd − AVss)/6− to monitor supply AVdd − AVss . */
    AVDD6MInput, /**< (AVdd − AVss)/6−. Use in conjunction with (AVdd − AVss)/6+ to monitor supply AVdd − AVss . */
    IOVDD6PInput, /**< (IOVdd − DGND)/6+. Use in conjunction with (IOVdd − DGND)/6− to monitor IOVdd − DGND. */
    IOVDD6MInput, /**< (IOVdd − DGND)/6−. Use in conjunction with (IOVdd − DGND)/6+ to monitor IOVdd − DGND. */
    ALDO6PInput, /**< (ALDO − AVss)/6+. Use in conjunction with (ALDO − AVss)/6− to monitor the analog LDO. */
    ALDO6MInput, /**< (ALDO − AVss)/6−. Use in conjunction with (ALDO − AVss)/6+ to monitor the analog LDO. */
    DLDO6PInput, /**< (DLDO − DGND)/6+. Use in conjunction with (DLDO − DGND)/6− to monitor the digital LDO. */
    DLDO6MInput, /**< (DLDO − DGND)/6−. Use in conjunction with (DLDO − DGND)/6+ to monitor the digital LDO. */
    V20mVPInput, /**< V_20MV_P. Use in conjunction with V_20MV_M to apply a 20 mV p-p signal to the ADC. */
    V20mVMInput /**< V_20MV_M. Use in conjunction with V_20MV_P to apply a 20 mV p-p signal to the ADC. */
  };
  /**
   * @enum PgaSel
   * @brief Gain select bits.
   * These bits select the gain to use when converting on any channels using this configuration register.
   */
  enum PgaSel {
    Pga1 = 0, /**< Gain 1, Input Range When VREF = 2.5 V: ±2.5 V */
    Pga2, /**< Gain 2, Input Range When VREF = 2.5 V: ±1.25 V */
    Pga4, /**< Gain 4, Input Range When VREF = 2.5 V: ± 625 mV */
    Pga8, /**< Gain 8, Input Range When VREF = 2.5 V: ±312.5 mV */
    Pga16, /**< Gain 16, Input Range When VREF = 2.5 V: ±156.25 mV */
    Pga32, /**< Gain 32, Input Range When VREF = 2.5 V: ±78.125 mV */
    Pga64, /**< Gain 64, Input Range When VREF = 2.5 V: ±39.06 mV */
    Pga128 /**< Gain 128, Input Range When VREF = 2.5 V: ±19.53 mV */
  };
  /**
   * @enum RefSel
   * @brief Reference source select bits.
   * These bits select the reference source to use when converting on any channels using
   * this configuration register.
   */
  enum RefSel {
    RefIn1 = 0, /**< REFIN1(+)/REFIN1(−). */
    RefIn2, /**< REFIN2(+)/REFIN2(−). */
    RefInternal, /**< internal reference. */
    RefAVdd /**< AVDD */
  };
  /**
   * @enum BurnoutCurrent
   * @brief These bits select the magnitude of the sensor burnout detect current source.
   */
  enum BurnoutCurrent {
    BurnoutOff = 0, /**< burnout current source off (default). */
    Burnout500nA, /**< burnout current source on, 0.5 μA. */
    Burnout2uA, /**< burnout current source on, 2 μA. */
    Burnout4uA /**< burnout current source on, 4 μA. */
  };
  /**
   * @enum FilterType
   * @brief Filter type select bits.
   * These bits select the filter type.
   */
  enum FilterType {
    Sinc4Filter = 0, /**< sinc4 filter (default). */
    Sinc3Filter = 2, /**< sinc 3 filter. */
    Sinc4FastFilter = 4, /**< fast settling filter using the sinc 4 filter. The sinc 4 filter is followed by an averaging block, which results in a settling time equal to the conversion time. In full power and mid power modes, averaging by 16 occurs whereas averaging by 8 occurs in low power mode. */
    Sinc3FastFilter = 5, /**< fast settling filter using the sinc 3 filter. The sinc 3 filter is followed by an averaging block, which results in a settling time equal to the conversion time. In full power and mid power modes, averaging by 16 occurs whereas averaging by 8 occurs in low power mode. */
    PostFilter = 7 /**< post filter enabled. The AD7124 includes several post filters, selectable using the POST_FILTER bits. The post filters have single cycle settling, the settling time being considerably better than a simple sinc 3 /sinc 4 filter. These filters offer excellent 50 Hz and60 Hz rejection. */
  };
  /**
   * @enum PostFilterType
   * @brief Post filter type select bits.
   * When the filter bits are set to 1, the sinc 3 filter is followed by a post filter which
   * offers good 50 Hz and 60 Hz rejection at output data rates that have zero latency approximately.
   */
  enum PostFilterType {
    NoPostFilter   = 0, /**< No Post Filter (Default value) */
    dB47PostFilter = 2, /**< Rejection at 50 Hz and 60 Hz ± 1 Hz: 47 dB, Output Data Rate (SPS): 27.27 Hz */
    dB62PostFilter = 3, /**< Rejection at 50 Hz and 60 Hz ± 1 Hz: 62 dB, Output Data Rate (SPS): 25 Hz */
    dB86PostFilter = 5, /**< Rejection at 50 Hz and 60 Hz ± 1 Hz: 86 dB, Output Data Rate (SPS): 20 Hz */
    dB92PostFilter = 6 /**< Rejection at 50 Hz and 60 Hz ± 1 Hz: 92 dB, Output Data Rate (SPS): 16.7 Hz */
  };
}

/**
 * @class Ad7124Chip
 * @brief ADC device
 */
class Ad7124Chip {

  public:
    /**
     * @brief Initializes the AD7124
     * @param slave_select The Slave Chip Select Id to be passed to the SPI calls
     * @return 0 for success or negative error code
     */
    int begin (int slave_select);

    /**
     * @brief Resets the device
     * @return Returns true for success, AD7124_TIMEOUT for timeout
     */
    int reset();

    /**
     * @brief Returns the status register
     */
    int status();

    /**
     * @brief Sets the ADC Control register
     * @param mode Control the mode of operation for ADC
     * @param power_mode Power mode
     * @param ref_en Internal reference voltage enable. When this bit is set,
     * the internal reference is enabled and available at the REFOUT pin.
     * When this bit is cleared, the internal reference is disabled.
     * @param clk_sel select the clock source for the ADC
     * @return 0 for success or negative error code
     */
    int setAdcControl (Ad7124::OperatingMode mode, Ad7124::PowerMode power_mode, bool ref_en = true, Ad7124::ClkSel clk_sel = Ad7124::InternalClk);

    /**
     * @brief Control the mode of operation for ADC
     * @param mode mode of operation
     * @return 0 for success or negative error code
     */
    int setMode (Ad7124::OperatingMode mode);

    /**
     * @brief Setup channel
     * @param ch channel number 0 to 15
     * @param cfg Setup select. These bits identify which of the eight setups are used to configure the ADC for this channel.
     * @param ainp Positive analog input AINP input select.
     * @param ainm Negative analog input AINM input select.
     * @param enable Channel enable bit. Setting this bit enables the device channel for the conversion sequence.
     * @return 0 for success or negative error code
     */
    int setChannel (uint8_t ch, uint8_t cfg, Ad7124::InputSel ainp, Ad7124::InputSel ainm, bool enable = false);

    /**
     * @brief Enable/Disable channel
     * @param ch channel number 0 to 15
     * @param enable true for enabled
     * @return 0 for success or negative error code
     */
    int enableChannel (uint8_t ch, bool enable = true);

    /**
     * @brief Returns the setup number used by the channel
     * @param ch channel number 0 to 15
     * @return setup number (0 to 7), or negative error code
     */
    int channelConfig (uint8_t ch);

    /**
     * @brief Sets a setup
     * @param cfg Setup select.
     * @param ref Reference source select bits.
     * @param pga Gain select bits.
     * @param bipolar Polarity select bit. When this bit is set, bipolar
     * operation is selected. When this bit is cleared, unipolar operation is
     * selected.
     * @param burnout These bits select the magnitude of the sensor burnout detect current source.
     * @return 0 for success or negative error code
     */
    int setConfig (uint8_t cfg, Ad7124::RefSel ref, Ad7124::PgaSel pga, bool bipolar, Ad7124::BurnoutCurrent burnout = Ad7124::BurnoutOff);

    /**
     * @brief Sets the filter type and output word rate for a setup
     * @param cfg Setup select.
     * @param filter Filter type
     * @param postfilter Post filter type
     * @param fs Filter output data rate select bits. These bits set the output
     * data rate of the sinc 3 and sinc 4 filters as well as the fast settling
     * filters. In addition, they affect the position of the first notch of the
     * filter and the cutoff frequency. In association with the gain selection,
     * they also determine the output noise and, therefore, the effective
     * resolution of the device (see noise tables).
     * FS can have a value from 1 to 2047.
     * @param rej60 When this bit is set, a first order notch is placed at 60 Hz
     * when the first notch of the sinc filter is at 50 Hz.
     * This allows simultaneous 50 Hz and 60 Hz rejection.
     * @param single Single cycle conversion enable bit. When this bit is set,
     * the AD7124 settles in one conversion cycle so that it functions as a
     * zero latency ADC. This bit has no effect when multiple analog input
     * channels are enabled or when the single conversion mode is selected.
     * When the fast filters are used, this bit has no effect.
     * @return 0 for success or negative error code
     */
    int setConfigFilter (uint8_t cfg, Ad7124::FilterType filter, uint16_t fs,
                         Ad7124::PostFilterType postfilter = Ad7124::NoPostFilter,
                         bool rej60 = false, bool single = false);

    /**
     * @brief Set offset for a setup
     * The offset registers are 24-bit registers and hold the offset calibration
     * coefficient for the ADC and its power-on reset value is 0x800000.
     * @param cfg  Setup select.
     * @param value offset
     * @return 0 for success or negative error code
     */
    int setConfigOffset (uint8_t cfg, uint32_t value);

    /**
     * @brief  Set gain for a setup
     * The gain registers are 24-bit registers and hold the
     * full-scale calibration coefficient for the ADC. The AD7124 is
     * factory calibrated to a gain of 1. The gain register contains this
     * factory generated value on power-on and after a reset.
     * @param cfg  Setup select.
     * @param value gain
     * @return 0 for success or negative error code
     */
    int setConfigGain (uint8_t cfg, uint32_t value);

    /**
     * @brief Setting up excitation current source
     *
     * The AD7124-4 contains two matched, software configurable,
     * constant current sources that can be programmed to equal 50 μA,
     * 100 μA, 250 μA, 500 μA, 750 μA, or 1 mA. These current sources
     * can be used to excite external resistive bridges or RTD sensors.
     * Both current sources source currents from AVDD and can be
     * directed to any of the analog input pins).
     *
     * @param source source index (0 or 1)
     * @param ch Channel select bits for the excitation current
     * @param current current bits choice
     * @return 0 for success or negative error code
     */
    int setCurrentSource (uint8_t source, uint8_t ch, Ad7124::IoutCurrent current);

    /**
     * @brief Sampling a channel
     * The channel is enabled in single mode, then the conversion is started
     * and the value of the sample is returned
     * @param ch channel number
     * @return sample or negative error code
     */
    long read (uint8_t ch);

    /**
     * @brief Start conversion in single mode
     * @param ch channel number
     * @return 0 for success or negative error code
     */
    int startSingleConversion (uint8_t ch);

    /**
     * @brief Waits until a new conversion result is available.
     * @param timeout_ms timeout delay
     * @return 0 for success or negative error code
     */
    int waitEndOfConversion (uint32_t timeout_ms);

    /**
     * @brief Returns the last sample
     * @return sample or negative error code
     */
    long getData();

    /**
     * @brief Returns the last sampling channel
     * @return channel or negative error code
     */
    int currentChannel();

    /**
     * @brief Proceed to Internal zero-scale and full-scale calibration
     * @param ch channel number
     * @return 0 for success or negative error code
     */
    int internalCalibration (uint8_t ch);

    /**
     * @brief Converts sample to voltage
     * @param value sample
     * @param gain gain
     * @param vref full scale voltage
     * @param bipolar
     * @return voltage
     */
    static double toVoltage (long value, int gain, double vref, bool bipolar = true);

    /**
     * @brief return IO timeout in milliseconds (default is 1000ms)
     */
#ifdef __DOXYGEN__
    inline uint32_t timeout() const;
#else
    inline uint32_t timeout() const {

      return d.timeout();
    }
#endif

    /**
     * @brief set IO timeout in milliseconds
     */
#ifdef __DOXYGEN__
    inline void setTimeout (uint32_t ms);
#else
    inline void setTimeout (uint32_t ms) {
      d.setTimeout (ms);
    }
#endif

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

#ifndef __DOXYGEN__
  protected:
    int readRegister (Ad7124::RegisterId id);
    int writeRegister (Ad7124::RegisterId id);

  private:
    Ad7124Private d;
    Ad7124Register reg[Ad7124::Reg_No];
#endif
};

/* ========================================================================== */
#endif /* __AD7124_H__ */
