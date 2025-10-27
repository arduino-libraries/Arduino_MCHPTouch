/* This source file is part of the ATMEL QTouch Library 5.0.1 */
/* Software provided by Microchip under the license agreement 
   “Microchip Touch Library License Agreement - Arduino 082420 
   (part of this downloaded package) */

/*****************************************************************************
 *
 * \file
 *
 * \brief  This file contains the SAMD QTouch Library pin, register and
 * sensors configuration options for Capacitive Touch acquisition using
 * the PTC module.
 *
 *
 * - Userguide:          QTouch Library Peripheral Touch Controller User Guide.
 * - Support: https://www.microchip.com/support/
 *
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 ******************************************************************************/

#ifndef TOUCH_CONFIG_SAMD_H
#define TOUCH_CONFIG_SAMD_H

/*----------------------------------------------------------------------------
*                   Self Cap method enable/disable.
*  ----------------------------------------------------------------------------*/

/**
 * Enable/Disable Self/Mutual Capacitance method.
 */
#define DEF_TOUCH_SELFCAP               (1)
#define DEF_TOUCH_MUTLCAP               (0)

/*----------------------------------------------------------------------------
*                   PTC module clock and interrupt level configuration.
*  ----------------------------------------------------------------------------*/

/**
 * PTC Module clock configuration.
 * Before using the QTouch library API, the PTC module clock generator source
 * should be configured appropriately.  The PTC module clock can be generated
 * using any of the eight generic clock generators (GCLK0-GCLK7).  The associated
 * generic clock multiplexer should be configured such that the PTC module clock
 * is set to 4MHz.  Refer touch_configure_ptc_clock API in touch.c for more
 * information.
 */

/**
 * PTC Module interrupt level.
 * The Nested Vectored Interrupt Controller (NVIC) in the SAMD supports
 * four different priority levels.  The priority level of the PTC end of
 * conversion ISR, used within QTouch library can be chosen based on application
 * requirements in order to accommodate time critical operations.
 * Range: 0u (Highest priority) to 3u (Lowest prioirity)
 * For more details refer to the Cortex-M0 Technical Reference Manual.
 */
#define DEF_TOUCH_PTC_ISR_LVL   (1u)

/*----------------------------------------------------------------------------
*                   Self Cap method pin configuration.
*  ----------------------------------------------------------------------------*/

/**
 * Self Cap touch channel selected.
 * The capacitance measurement is done sequentially in the order in which
 * the touch channel (nodes) are specified below.  Touch channel numbering
 * follows the order in which Y lines are specified.
 */
#define DEF_SELFCAP_LINES  Y(0), Y(1), Y(2), Y(3), Y(4), Y(5), Y(8), Y(9), Y(14), Y(15)

/*----------------------------------------------------------------------------
*              Self Cap method channel and sensor configuration.
*  ----------------------------------------------------------------------------*/

/**
 * Self Cap number of channels.
 * Specify the number of Self Cap touch channels to be used by the Touch Library.
 * A key is formed used one touch channel.  A rotor or slider can be formed
 * using 3 touch channels.
 * Range: 1u to 16u.
 */
#define DEF_SELFCAP_NUM_CHANNELS   (10) /* Total number of channels */

/**
 * Self Cap number of Sensors.
 * Specify the number of Self Cap touch sensors to be used by the Touch Library.
 * A sensor is either a key, rotor or slider.
 * Example configuration: If the configuration has 6 keys (a key is formed
 * using one Sensor Pin), one rotor (a Self Cap rotor is formed using 3 Sensor
 * Pins) and one slider (a Self Cap slider is formed using 3 Sensor Pins), then
 * the number of sensors is 6 key + 1 rotor + 1 slider = 8 sensors.
 * Range: 1u to 16u.
 */
#define DEF_SELFCAP_NUM_SENSORS  (10)  /* Total number of sensors */

/**
 * Self Cap number of Rotors and Sliders.
 * Specify the total number of Self Cap Rotors and Sliders to be used by
 * the Touch Library.  The number of Rotors and Sliders mentioned here is part
 *of
 * the Total number of sensors specified in the QT_NUM_SENSORS macro.  When
 * no rotors or slider are required, specify a value of 0u.
 * Range: 0u to 8u.
 */
#define DEF_SELFCAP_NUM_ROTORS_SLIDERS  (0)  /* Number of rotor sliders */

/*----------------------------------------------------------------------------
*                   Self Cap method aquisition parameters.
*  ----------------------------------------------------------------------------*/

/**
 * Self Cap filter level setting.
 * The filter level setting controls the number of samples taken
 * to resolve each acquisition. A higher filter level setting provides
 * improved signal to noise ratio under noisy conditions, while
 * increasing the total time for measurement resulting in increased
 * power consumption and response time.  Refer filter_level_t in touch_api_SAMD.h
 * Range: FILTER_LEVEL_1 (one sample) to FILTER_LEVEL_64 ( 64 samples).
 */
#define  DEF_SELFCAP_FILTER_LEVEL FILTER_LEVEL_8 /* Filter level */

/**
 * Self Cap auto oversample setting.
 * Auto oversample controls the automatic oversampling of sensor channels when
 * unstable signals are detected with the default setting of 'Filter level'.
 * Enabling Auto oversample results in 'Filter level' x 'Auto Oversample' number
 * of samples taken on the corresponding sensor channel when an unstable signal
 * is observed.  In a case where 'Filter level' is set to FILTER_LEVEL_4 and
 * 'Auto Oversample' is set to AUTO_OS_4, 4 oversamples are taken with stable
 * signal values and 16 oversamples are taken when unstable signal is detected.
 * Refer auto_os_t in touch_api_SAMD.h
 * Range: AUTO_OS_DISABLE (oversample disabled) to AUTO_OS_128 (128
 * oversamples).
 */
#define  DEF_SELFCAP_AUTO_OS AUTO_OS_DISABLE                /* Automatic OverSampling */

/**
 * Self Cap gain per touch channel.
 * Gain is applied on a per-channel basis to allow a scaling-up of the touch
 * sensitivity on contact.
 * Note: delta on touch contact, not the resting signal which is measured on
 * each sensor.
 * Refer gain_t in touch_api_SAMD.h
 * Range:GAIN_1 (no scaling) to GAIN_32 (scale-up by 32)
 */
#define DEF_SELFCAP_GAIN_PER_NODE   GAIN_32,GAIN_32,GAIN_32,GAIN_32,GAIN_32

/*----------------------------------------------------------------------------
*   Tuning for Noise performance, touch response time and Power consumption.
*  ----------------------------------------------------------------------------*/

/**
 * Refer QTouch Library Peripheral Touch Controller User Guide for detailed
 * information on tuning for Noise performance, touch response time and  Power
 * consumption
 */

/**
 * For best noise performance, set -
 * - DEF_SELFCAP_FREQ_MODE to FREQ_MODE_HOP
 * - DEF_SELFCAP_SENSE_RESISTOR to RSEL_VAL_100
 * - use AUTO_TUNE_PRSC input to touch_xxcap_sensors_calibrate() API in touch.c
 * Based on the type of noise, FREQ_MODE_SPREAD or FREQ_MODE_SPREAD_MEDIAN can
 * also be used.
 *
 * For best power consumption, set -
 * - DEF_SELFCAP_FREQ_MODE to FREQ_MODE_NONE
 * - DEF_SELFCAP_CLK_PRESCALE to PRSC_DIV_SEL_1
 * - use AUTO_TUNE_RSEL input to touch_xxcap_sensors_calibrate() API in touch.c
 *
 */

/**
 * Self Cap acquisition frequency mode.
 *
 * FREQ_MODE_HOP:
 * When frequency mode hopping option is selected, the PTC runs a
 * frequency hopping cycle with subsequent measurements done using
 * the three PTC acquisition frequency delay settings as specified in
 * DEF_SELFCAP_HOP_FREQS.
 *
 * FREQ_MODE_SPREAD:
 * When frequency mode spread spectrum option is selected, the PTC
 * runs with spread spectrum enabled for jittered delay based
 * acquisition.
 *
 * FREQ_MODE_SPREAD_MEDIAN:
 * When frequency mode spread spectrum median option is selected,
 * the PTC runs with spread spectrum enabled.  In this case, an
 * additional software median filter is applied to the measured
 * signal values.
 *
 * FREQ_MODE_NONE:
 * When frequency mode none option is selected, the PTC runs at
 * constant speed.  This mode is suited for best power consumption.
 */
#define DEF_SELFCAP_FREQ_MODE FREQ_MODE_NONE

/**
 * PTC acquisition frequency delay setting.
 *
 * Specify three frequency hop delay settings.
 *
 * The PTC acquisition frequency is dependent on the Generic clock
 * input to PTC and PTC clock pre-scaler setting.  This delay setting
 * inserts "n" PTC clock cycles between consecutive measurements on
 * a given sensor, thereby changing the PTC acquisition frequency.
 * FREQ_HOP_SEL_1 setting inserts 0 PTC clock cycle between consecutive
 * measurements.  FREQ_HOP_SEL_16 setting inserts 15 PTC clock cycles.
 * Hence, higher delay setting will increase the total time taken for
 * capacitance measurement on a given sensor as compared to a lower
 * delay setting.
 *
 * A desired setting can be used to avoid noise around the same frequency
 * as the acquisition frequency.
 * Range: FREQ_HOP_SEL_1 to FREQ_HOP_SEL_16
 */
#define DEF_SELFCAP_HOP_FREQS FREQ_HOP_SEL_1,FREQ_HOP_SEL_2,FREQ_HOP_SEL_3

/**
 * Self cap PTC clock pre-scalar.
 * PTC clock prescale setting.   Refer touch_configure_ptc_clock() API in touch.c
 * Example: if Generic clock input to PTC = 4MHz, then:
 * PRSC_DIV_SEL_1   sets PTC Clock to  4MHz
 * PRSC_DIV_SEL_2   sets PTC Clock to  2MHz
 * PRSC_DIV_SEL_4   sets PTC Clock to 1MHz
 * PRSC_DIV_SEL_8   sets PTC Clock to 500KHz
 */
#define DEF_SELFCAP_CLK_PRESCALE PRSC_DIV_SEL_2

/**
 * PTC series resistor setting.  For Mutual cap mode, this series
 * resistor is switched internally on the Y-pin.  For Self cap mode,
 * the series resistor is switched internally on the Sensor pin.
 *
 * Example:
 * RSEL_VAL_0   sets internal series resistor to 0ohms.
 * RSEL_VAL_20  sets internal series resistor to 20Kohms.
 * RSEL_VAL_50  sets internal series resistor to 50Kohms.
 * RSEL_VAL_100 sets internal series resistor to 100Kohms.
 */
#define DEF_SELFCAP_SENSE_RESISTOR RSEL_VAL_0

/*----------------------------------------------------------------------------
*                   Self Cap method sensor global parameters.
*  ----------------------------------------------------------------------------*/

/*! \name Self Cap Global acquisition parameters.
 * Refer the Touch Library User guide for more information on these parameters.
 */
/* ! @{ */

/**
 * Self Cap Sensor measurement interval.
 * Speicify period in milliseconds.  Example, DEF_TOUCH_MEASUREMENT_PERIOD_MS 50u
 * will perform measurement on touch sensors every 50msec.
 */
#define DEF_TOUCH_MEASUREMENT_PERIOD_MS     30u

/**
 * Self Cap Sensor detect integration (DI) limit.
 * Range: 0u to 255u.
 */
#define   DEF_SELFCAP_DI         0u

/**
 * Self Cap Sensor towards touch drift rate.
 * Units: 200ms
 * Default value: 20 = 4 seconds.
 * Range: 1u to 127u.
 */
#define  DEF_SELFCAP_TCH_DRIFT_RATE        30u

/**
 * Self Cap Sensor away from touch drift rate.
 * Units: 200ms
 * Default value: 5u = 1 second.
 * Range: 1u to 127u.
 */
#define  DEF_SELFCAP_ATCH_DRIFT_RATE         5u

/**
 * Self Cap Sensor maximum ON time duration.
 * Units: 200ms (Example: a value 5u indicated Max ON duration of 1 second.)
 * Default value: 0 (No maximum ON time limit).
 * Range: 0u to 255u.
 */
#define   DEF_SELFCAP_MAX_ON_DURATION       0u

/**
 * Self Cap Sensor drift hold time.
 * Units: 200ms
 * Default value: 20 (hold off drifting for 4 seconds after leaving detect).
 * Range: 1u to 255u.
 */
#define   DEF_SELFCAP_DRIFT_HOLD_TIME        30u

/**
 * Self Cap Sensor away from touch recalibration delay.
 * Default value: 10.
 * Range: 1u to 255u.
 */
#define   DEF_SELFCAP_ATCH_RECAL_DELAY       1u

/** Self Cap Sensor away from touch recalibration threshold.
 * Default: RECAL_50 (recalibration threshold = 50% of detection threshold).
 * Range: refer recal_threshold_t enum in touch_api_SAMD.h.
 */
#define   DEF_SELFCAP_ATCH_RECAL_THRESHOLD      RECAL_100


/* ! @} */

/*----------------------------------------------------------------------------
*                   Self Cap Callback functions.
*  ----------------------------------------------------------------------------*/

/*! \name Self Cap Callback functions.
 */
/* ! @{ */

/**
 * Self Cap Filter callback function.
 * A filter callback (when not NULL) is called by the Touch Library each time
 * a new set of Signal values are available.
 * An Example filter callback function prototype.
 * void qm_filter_callback( void );
 */
#define DEF_SELFCAP_FILTER_CALLBACK              (NULL)

/**********************************************************/
/***************** Communication - Data Streamer ******************/
/**********************************************************/

#define DEF_TOUCH_DATA_STREAMER_ENABLE 0u
#define DATA_STREAMER_BOARD_TYPE USER_BOARD

#endif /* TOUCH_CONFIG_SAMD_H */
