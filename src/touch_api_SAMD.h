/* This source file is part of the ATMEL QTouch Library 5.0.1 */
/* Software provided by Microchip under the license agreement 
   “Microchip Touch Library License Agreement - Arduino 082420 
   (part of this downloaded package) */

/**
 *
 * \file
 *
 * \brief  This file contains the SAMD QTouch Library API for
 * Capacitive Touch acquisition using the PTC module.
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
 */

#ifndef TOUCH_API_SAMD_H
#define TOUCH_API_SAMD_H

/**
 * \defgroup group_thirdparty_qtouch_devspecific_sam0_samd QTouch Library for SAM0
 * 
 * This is the QTouch Library for SAM0 devices that consists in
 * one api header file(touch_api_SAMD.h) and one pre-compiled
 * library(libsamd-qt-gcc.a).
 *
 * All projects using this library must also provide the required header
 * file(touch_config_samd.h) used to configure the library.
 *
 * For more information on the Qtouch Library, check www.atmel.com/qtouchlib.
 *
 * \{
 */

#ifdef __cplusplus
extern "C"
{
#endif

/*----------------------------------------------------------------------------
*                           compiler information
*  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*                               include files
*  ----------------------------------------------------------------------------*/
#include "touch_config_samd.h"

/*----------------------------------------------------------------------------
*                                   macros
*  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*                           manifest constants
*  ----------------------------------------------------------------------------*/

/*! \name Touch Library Acquisition Status bitfields.
 */
/* ! @{ */

#define TOUCH_NO_ACTIVITY             (0x0000u) /* !< No Touch activity. */
#define TOUCH_IN_DETECT               (0x0001u) /* !< Atleast one Touch channel
	                                         * is in detect. */
#define TOUCH_STATUS_CHANGE           (0x0002u) /* !< Change in Touch status of
	                                         * atleast one Touch channel. */
#define TOUCH_ROTOR_SLIDER_POS_CHANGE (0x0004u) /* !< Change in Rotor or Slider
	                                         * position of atleast one rotor
	                                         * or slider. */
#define TOUCH_CHANNEL_REF_CHANGE      (0x0008u) /* !< Change in Reference value
	                                         * of atleast one Touch channel. */
#define TOUCH_BURST_AGAIN             (0x0100u) /* !< Indicates that reburst is
	                                         * required to resolve Filtering
	                                         * or Calibration state. */
#define TOUCH_RESOLVE_CAL             (0x0200u) /* !< Indicates that reburst is
	                                         * needed to resolve
	                                         * Calibration. */
#define TOUCH_RESOLVE_FILTERIN        (0x0400u) /* !< Indicates that reburst is
	                                         * needed to resolve Filtering. */
#define TOUCH_RESOLVE_DI              (0x0800u) /* !< Indicates that reburst is
	                                         * needed to resolve Detect
	                                         * Integration. */
#define TOUCH_RESOLVE_POS_RECAL       (0x1000u) /* !< Indicates that reburst is
	                                         * needed to resolve
	                                         * Recalibration. */

/* ! @} */

/* ! \name SENSOR STATE CONFIGURATIONS */
/* !@{ */

/**
 * \def GET_SENSOR_STATE(SENSOR_NUMBER)
 * \brief To get the sensor state that it is in detect or not
 * \param SENSOR_NUMBER for which the state to be detected
 * \return Returns either 0 or 1
 * If the bit value is 0, it is not in detect
 * If the bit value is 1, it is in detect
 */
/* Self capacitance method */
   #define GET_SELFCAP_SENSOR_STATE(SENSOR_NUMBER) p_selfcap_measure_data-> \
	p_sensor_states[(SENSOR_NUMBER / \
	8)] & (1 << (SENSOR_NUMBER % 8))
/* Mutual capacitance method */
   #define GET_MUTLCAP_SENSOR_STATE(SENSOR_NUMBER) p_mutlcap_measure_data-> \
	p_sensor_states[(SENSOR_NUMBER / \
	8)] & (1 << (SENSOR_NUMBER % 8))

/**
 * \def GET_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER)
 * \brief To get the rotor angle or slider position.
 * These values are valid only when the sensor state for
 * corresponding rotor or slider shows in detect.
 * \param ROTOR_SLIDER_NUMBER for which the position to be known
 * \return Returns rotor angle or sensor position
 */
/* !@} */
/* Self capacitance method */
  #define GET_SELFCAP_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER) \
	p_selfcap_measure_data->p_rotor_slider_values[ \
		ROTOR_SLIDER_NUMBER]
/* Mutual capacitance method */
  #define GET_MUTLCAP_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER) \
	p_mutlcap_measure_data->p_rotor_slider_values[ \
		ROTOR_SLIDER_NUMBER]

/**
 * Calculate X line bit position.
 */
#define X(n) (uint16_t)(1u << n)

/**
 * Calculate Y line bit position.
 */
#define Y(n) (uint16_t)(1u << n)

/**
 * Max position hysteresis allowed
 */
#define TOUCH_MAX_POS_HYST              (100u)

/*----------------------------------------------------------------------------
*                          Mutual cap  macros
*  ----------------------------------------------------------------------------*/
#if DEF_TOUCH_MUTLCAP == 1

#if (DEF_MUTLCAP_NUM_SENSORS == 0u)
#error 'Number of Sensors cannot be 0.'
#endif

#if (DEF_MUTLCAP_NUM_SENSORS > DEF_MUTLCAP_NUM_CHANNELS)
  #error 'Number of Sensors cannot exceed number of channels'
#endif

/**
  * QTouch number of channels.
  */
#define QT_NUM_CHANNELS  DEF_MUTLCAP_NUM_CHANNELS

/**
 * Size of Touch Sensor.
 */
#define PRIV_MUTLCAP_SIZE_SENSOR      (8u)

/**
 * Size of Touch Channel.
 */
#define PRIV_MUTLCAP_SIZE_CHANNEL     (13u)

/**
 * Size of Touch Rotor Slider.
 */
#define PRIV_MUTLCAP_SIZE_RS          (13u)

/**
 * Size of Touch Pad bytes.
 */
#define PRIV_MUTLCAP_PAD_BYTE_SIZE    (36u)

#define PRIV_CHANNELS_64_NO					  (64u)
#define PRIV_BYTES_IN_UINT64				  (8u)
/**
 * Touch Data block size.
 */
#define PRIV_MUTLCAP_DATA_BLK_SIZE    ((PRIV_MUTLCAP_SIZE_SENSOR          * \
	DEF_MUTLCAP_NUM_SENSORS)        + \
	(PRIV_MUTLCAP_SIZE_CHANNEL         * DEF_MUTLCAP_NUM_CHANNELS)       + \
	(PRIV_MUTLCAP_SIZE_RS              * DEF_MUTLCAP_NUM_ROTORS_SLIDERS) + \
	((DEF_MUTLCAP_NUM_CHANNELS + 7u) / 8u)  + (PRIV_MUTLCAP_PAD_BYTE_SIZE) + \
        (((((DEF_MUTLCAP_NUM_CHANNELS - 1u) / PRIV_CHANNELS_64_NO) + 1u) * PRIV_BYTES_IN_UINT64)*2u))

/**
 * Initialize rotor slider table.
 */
#if   (DEF_MUTLCAP_NUM_ROTORS_SLIDERS != 0u)
#define PRIV_MUTLCAP_RS_TABLE_INIT  touch_mutlcap_rs_table_init
#else
#define PRIV_MUTLCAP_RS_TABLE_INIT  NULL
#endif /* SELF_NUM_ROTORS_SLIDERS*/


#endif /* DEF_TOUCH_MUTLCAP. */

/*----------------------------------------------------------------------------
*                          Self cap  macros
*  ----------------------------------------------------------------------------*/
#if DEF_TOUCH_SELFCAP == 1

#if (DEF_SELFCAP_NUM_SENSORS == 0u)
#error 'Number of Sensors cannot be 0.'
#endif

#if (DEF_SELFCAP_NUM_SENSORS > DEF_SELFCAP_NUM_CHANNELS)
  #error 'Number of Sensors cannot exceed number of channels'
#endif

/**
  * QTouch number of channels.
  */
#define QT_NUM_CHANNELS  DEF_SELFCAP_NUM_CHANNELS

/**
 * Size of Touch Sensor.
 */
#define PRIV_SELFCAP_SIZE_SENSOR      (8u)

/**
 * Size of Touch Channel.
 */
#define PRIV_SELFCAP_SIZE_CHANNEL     (13u)

/**
 * Size of Touch Rotor Slider.
 */
#define PRIV_SELFCAP_SIZE_RS          (13u)

/**
 * Size of Touch Pad bytes.
 */
#define PRIV_SELFCAP_PAD_BYTE_SIZE    (36u)

#define PRIV_BYTES_IN_UINT64				  (8u)
/**
 * Touch Data block size.
 */
#define PRIV_SELFCAP_DATA_BLK_SIZE    ((PRIV_SELFCAP_SIZE_SENSOR          * \
	DEF_SELFCAP_NUM_CHANNELS)        + \
	(PRIV_SELFCAP_SIZE_CHANNEL         * DEF_SELFCAP_NUM_CHANNELS)       + \
	(PRIV_SELFCAP_SIZE_RS              * DEF_SELFCAP_NUM_ROTORS_SLIDERS) + \
	((DEF_SELFCAP_NUM_CHANNELS + 7u) / 8u)  + (PRIV_SELFCAP_PAD_BYTE_SIZE) + \
        (PRIV_BYTES_IN_UINT64 * 2u))

/**
 * Initialize rotor slider table.
 */
#if   (DEF_SELFCAP_NUM_ROTORS_SLIDERS != 0u)
#define PRIV_SELFCAP_RS_TABLE_INIT  touch_selfcap_rs_table_init
#else
#define PRIV_SELFCAP_RS_TABLE_INIT  NULL
#endif /* SELF_NUM_ROTORS_SLIDERS*/


#endif /* DEF_TOUCH_SELFCAP. */

/*----------------------------------------------------------------------------
*                           type definitions
*  ----------------------------------------------------------------------------*/

/* ! An unsigned 8-bit number setting a sensor detection threshold. */
typedef uint8_t threshold_t;

/* ! Sensor number type. */
typedef uint8_t sensor_id_t;

/* ! Current time type. */
typedef uint16_t touch_current_time_t;

/* ! Touch sensor delta value type. */
typedef int16_t touch_delta_t;

/* ! Status of Touch measurement. */
typedef uint16_t touch_acq_status_t;

/* ! Touch library GAIN setting */
typedef enum tag_gain_t {
	GAIN_1,
	GAIN_2,
	GAIN_4,
	GAIN_8,
	GAIN_16,
	GAIN_32
}
gain_t;
/* ! Touch library FILTER LEVEL setting */
typedef enum tag_filter_level_t {
	FILTER_LEVEL_1,
	FILTER_LEVEL_2,
	FILTER_LEVEL_4,
	FILTER_LEVEL_8,
	FILTER_LEVEL_16,
	FILTER_LEVEL_32,
	FILTER_LEVEL_64
}
filter_level_t;
/* ! Touch library AUTO OS setting */
typedef enum tag_auto_os_t {
	AUTO_OS_DISABLE,
	AUTO_OS_2,
	AUTO_OS_4,
	AUTO_OS_8,
	AUTO_OS_16,
	AUTO_OS_32,
	AUTO_OS_64,
	AUTO_OS_128
}
auto_os_t;
/* ! Touch Library error codes. */
typedef enum tag_touch_ret_t {
	/* ! Successful completion of operation. */
	TOUCH_SUCCESS,
	/* ! Touch Library is busy with pending previous Touch measurement. */
	TOUCH_ACQ_INCOMPLETE,
	/* ! Invalid input parameter. */
	TOUCH_INVALID_INPUT_PARAM,
	/* ! Operation not allowed in the current Touch Library state. */
	TOUCH_INVALID_LIB_STATE,
	/* ! Invalid self cap config input parameter. */
	TOUCH_INVALID_SELFCAP_CONFIG_PARAM,
	/* ! Invalid mutual cap config input parameter. */
	TOUCH_INVALID_MUTLCAP_CONFIG_PARAM,
	/* ! Invalid Recalibration threshold input value. */
	TOUCH_INVALID_RECAL_THRESHOLD,
	/* ! Channel number parameter exceeded total number of channels
	 * configured. */
	TOUCH_INVALID_CHANNEL_NUM,
	/* ! Invalid sensor type. Sensor type can NOT be SENSOR_TYPE_UNASSIGNED. */
	TOUCH_INVALID_SENSOR_TYPE,
	/* ! Invalid Sensor number parameter. */
	TOUCH_INVALID_SENSOR_ID,
	/* ! Number of Rotor/Sliders set as 0, */
	/* ! when trying to configure a rotor/slider. */
	TOUCH_INVALID_RS_NUM
}
touch_ret_t;

/* ! Sensor start and end channel type of a Sensor. Channel number starts with
 * value 0. */
typedef enum tag_channel_t {
	CHANNEL_0, CHANNEL_1, CHANNEL_2, CHANNEL_3, CHANNEL_4, CHANNEL_5,
	CHANNEL_6, CHANNEL_7,
	CHANNEL_8, CHANNEL_9, CHANNEL_10, CHANNEL_11, CHANNEL_12, CHANNEL_13,
	CHANNEL_14, CHANNEL_15,
	CHANNEL_16, CHANNEL_17, CHANNEL_18, CHANNEL_19, CHANNEL_20, CHANNEL_21,
	CHANNEL_22, CHANNEL_23,
	CHANNEL_24, CHANNEL_25, CHANNEL_26, CHANNEL_27, CHANNEL_28, CHANNEL_29,
	CHANNEL_30, CHANNEL_31,
	CHANNEL_32, CHANNEL_33, CHANNEL_34, CHANNEL_35, CHANNEL_36, CHANNEL_37,
	CHANNEL_38, CHANNEL_39,
	CHANNEL_40, CHANNEL_41, CHANNEL_42, CHANNEL_43, CHANNEL_44, CHANNEL_45,
	CHANNEL_46, CHANNEL_47,
	CHANNEL_48, CHANNEL_49, CHANNEL_50, CHANNEL_51, CHANNEL_52, CHANNEL_53,
	CHANNEL_54, CHANNEL_55,
	CHANNEL_56, CHANNEL_57, CHANNEL_58, CHANNEL_59, CHANNEL_60, CHANNEL_61,
	CHANNEL_62, CHANNEL_63,
	CHANNEL_64, CHANNEL_65, CHANNEL_66, CHANNEL_67, CHANNEL_68, CHANNEL_69,
	CHANNEL_70, CHANNEL_71,
	CHANNEL_72, CHANNEL_73, CHANNEL_74, CHANNEL_75, CHANNEL_76, CHANNEL_77,
	CHANNEL_78, CHANNEL_79,
	CHANNEL_80, CHANNEL_81, CHANNEL_82, CHANNEL_83, CHANNEL_84, CHANNEL_85,
	CHANNEL_86, CHANNEL_87,
	CHANNEL_88, CHANNEL_89, CHANNEL_90, CHANNEL_91, CHANNEL_92, CHANNEL_93,
	CHANNEL_94, CHANNEL_95,
	CHANNEL_96, CHANNEL_97, CHANNEL_98, CHANNEL_99, CHANNEL_100,
	CHANNEL_101, CHANNEL_102, CHANNEL_103,
	CHANNEL_104, CHANNEL_105, CHANNEL_106, CHANNEL_107, CHANNEL_108,
	CHANNEL_109, CHANNEL_110, CHANNEL_111,
	CHANNEL_112, CHANNEL_113, CHANNEL_114, CHANNEL_115, CHANNEL_116,
	CHANNEL_117, CHANNEL_118, CHANNEL_119,
	CHANNEL_120, CHANNEL_121, CHANNEL_122, CHANNEL_123, CHANNEL_124,
	CHANNEL_125, CHANNEL_126, CHANNEL_127,
	CHANNEL_128, CHANNEL_129, CHANNEL_130, CHANNEL_131, CHANNEL_132,
	CHANNEL_133, CHANNEL_134, CHANNEL_135,
	CHANNEL_136, CHANNEL_137, CHANNEL_138, CHANNEL_139, CHANNEL_140,
	CHANNEL_141, CHANNEL_142, CHANNEL_143,
	CHANNEL_144, CHANNEL_145, CHANNEL_146, CHANNEL_147, CHANNEL_148,
	CHANNEL_149, CHANNEL_150, CHANNEL_151,
	CHANNEL_152, CHANNEL_153, CHANNEL_154, CHANNEL_155, CHANNEL_156,
	CHANNEL_157, CHANNEL_158, CHANNEL_159,
	CHANNEL_160, CHANNEL_161, CHANNEL_162, CHANNEL_163, CHANNEL_164,
	CHANNEL_165, CHANNEL_166, CHANNEL_167,
	CHANNEL_168, CHANNEL_169, CHANNEL_170, CHANNEL_171, CHANNEL_172,
	CHANNEL_173, CHANNEL_174, CHANNEL_175,
	CHANNEL_176, CHANNEL_177, CHANNEL_178, CHANNEL_179, CHANNEL_180,
	CHANNEL_181, CHANNEL_182, CHANNEL_183,
	CHANNEL_184, CHANNEL_185, CHANNEL_186, CHANNEL_187, CHANNEL_188,
	CHANNEL_189, CHANNEL_190, CHANNEL_191,
	CHANNEL_192, CHANNEL_193, CHANNEL_194, CHANNEL_195, CHANNEL_196,
	CHANNEL_197, CHANNEL_198, CHANNEL_199,
	CHANNEL_200, CHANNEL_201, CHANNEL_202, CHANNEL_203, CHANNEL_204,
	CHANNEL_205, CHANNEL_206, CHANNEL_207,
	CHANNEL_208, CHANNEL_209, CHANNEL_210, CHANNEL_211, CHANNEL_212,
	CHANNEL_213, CHANNEL_214, CHANNEL_215,
	CHANNEL_216, CHANNEL_217, CHANNEL_218, CHANNEL_219, CHANNEL_220,
	CHANNEL_221, CHANNEL_222, CHANNEL_223,
	CHANNEL_224, CHANNEL_225, CHANNEL_226, CHANNEL_227, CHANNEL_228,
	CHANNEL_229, CHANNEL_230, CHANNEL_231,
	CHANNEL_232, CHANNEL_233, CHANNEL_234, CHANNEL_235, CHANNEL_236,
	CHANNEL_237, CHANNEL_238, CHANNEL_239,
	CHANNEL_240, CHANNEL_241, CHANNEL_242, CHANNEL_243, CHANNEL_244,
	CHANNEL_245, CHANNEL_246, CHANNEL_247,
	CHANNEL_248, CHANNEL_249, CHANNEL_250, CHANNEL_251, CHANNEL_252,
	CHANNEL_253, CHANNEL_254, CHANNEL_255
}
channel_t;

/* ! Touch library state. */
typedef enum tag_touch_lib_state_t {
	TOUCH_STATE_NULL,
	TOUCH_STATE_INIT,
	TOUCH_STATE_READY,
	TOUCH_STATE_CALIBRATE,
	TOUCH_STATE_BUSY
}
touch_lib_state_t;

/* ! Sensor types available. */
typedef enum tag_sensor_type_t {
	SENSOR_TYPE_UNASSIGNED,
	SENSOR_TYPE_KEY,
	SENSOR_TYPE_ROTOR,
	SENSOR_TYPE_SLIDER,
	MAX_SENSOR_TYPE
}
sensor_type_t;
/* ! Touch library acquisition mode. */
typedef enum tag_touch_acq_mode_t {
	/* ! When Raw acquisition mode is used, the measure_complete_callback */
	/* ! function is called immediately once a fresh value of Signals are */
	/* ! available.  In this mode, the Touch Library does not do any */
	/* ! processing on the Signals.  So, the References, Sensor states or */
	/* ! Rotor/Slider position values are not updated in this mode. */
	RAW_ACQ_MODE,
	/* ! When Nomal acquisition mode is used, the measure_complete_callback */
	/* ! function is called only after the Touch Library completes
	 * processing */
	/* ! of the Signal values obtained. The References, Sensor states and */
	/* ! Rotor/Slider position values are updated in this mode. */
	NORMAL_ACQ_MODE
}
touch_acq_mode_t;

/* ! Touch library PTC prescaler clock and sense resistor auto tuning setting. */
typedef enum tag_auto_tune_type_t {
	/*! Auto tuning disabled. */
	AUTO_TUNE_NONE,
	/* Auto tune PTC prescaler and sense resistor for best noise performance. */
	AUTO_TUNE_PRSC,
	/* Auto tune PTC prescaler and sense resistor for least power consumption. */
	AUTO_TUNE_RSEL
}
auto_tune_type_t;


/**
 * PTC frequency mode setting.
 * Example: if Generic clock input to PTC = 4MHz, then:
 *   FREQ_MODE_NONE   			No Frequency hopping
 *   FREQ_MODE_HOP   			Frequency hopping is enabled.
 *   FREQ_MODE_SPREAD   		pread spectrum mode with median filter disabled.
 *   FREQ_MODE_SPREAD_MEDIAN   	Spread spectrum mode with median filter enabled.
 *
 */
typedef enum tag_freq_mode_sel_t {
FREQ_MODE_NONE,
FREQ_MODE_HOP,
FREQ_MODE_SPREAD,
FREQ_MODE_SPREAD_MEDIAN
}
freq_mode_sel_t;


/**
 * PTC clock prescale setting.   Refer touch_configure_ptc_clock() API in touch.c
 * Example: if Generic clock input to PTC = 4MHz, then:
 *   PRSC_DIV_SEL_1   sets PTC Clock to  4MHz
 *   PRSC_DIV_SEL_2   sets PTC Clock to  2MHz
 *   PRSC_DIV_SEL_4   sets PTC Clock to 1MHz
 *   PRSC_DIV_SEL_8   sets PTC Clock to 500KHz
 *
 */
typedef enum tag_prsc_div_sel_t {
	PRSC_DIV_SEL_1,
	PRSC_DIV_SEL_2,
	PRSC_DIV_SEL_4,
	PRSC_DIV_SEL_8
}
prsc_div_sel_t;

/**
 * PTC series resistor setting.  For Mutual cap mode, this series
 * resistor is switched internally on the Y-pin.  For Self cap mode,
 * thes series resistor is switched internally on the Sensor pin.
 *
 * Example:
 *  RSEL_VAL_0   sets internal series resistor to 0ohms.
 *  RSEL_VAL_20  sets internal series resistor to 20Kohms.
 *  RSEL_VAL_50  sets internal series resistor to 50Kohms.
 *  RSEL_VAL_100 sets internal series resistor to 100Kohms.
 */
typedef enum tag_rsel_val_t {
	RSEL_VAL_0,
	RSEL_VAL_20,
	RSEL_VAL_50,
	RSEL_VAL_100
}
rsel_val_t;

/**
 * PTC acquisition frequency delay setting.
 *
 * The PTC acquisition frequency is dependent on the Generic clock
 * input to PTC and PTC clock prescaler setting.  This delay setting
 * inserts "n" PTC clock cycles between consecutive measurements on
 * a given sensor, thereby changing the PTC acquisition frequency.
 * FREQ_HOP_SEL_1 setting inserts 1 PTC clock cycle between consecutive
 * measurements.  FREQ_HOP_SEL_14 setting inserts 14 PTC clock cycles.
 * Hence, higher delay setting will increase the total time taken for
 * capacitance measurement on a given sensor as compared to a lower
 * delay setting.
 *
 * A desired setting can be used to avoid noise around the same frequency
 * as the acquisition frequency.
 *
 */
typedef enum tag_freq_hop_sel_t {
	FREQ_HOP_SEL_1,
	FREQ_HOP_SEL_2,
	FREQ_HOP_SEL_3,
	FREQ_HOP_SEL_4,
	FREQ_HOP_SEL_5,
	FREQ_HOP_SEL_6,
	FREQ_HOP_SEL_7,
	FREQ_HOP_SEL_8,
	FREQ_HOP_SEL_9,
	FREQ_HOP_SEL_10,
	FREQ_HOP_SEL_11,
	FREQ_HOP_SEL_12,
	FREQ_HOP_SEL_13,
	FREQ_HOP_SEL_14,
	FREQ_HOP_SEL_15,
	FREQ_HOP_SEL_16
}
freq_hop_sel_t;

/**
 * Which AKS group, if any, a sensor is in.
 * NO_AKS_GROUP = sensor is not in an AKS group, and cannot be suppressed.
 * AKS_GROUP_x  = sensor is in AKS group x.
 */
typedef enum tag_aks_group_t {
	NO_AKS_GROUP,
	AKS_GROUP_1,
	AKS_GROUP_2,
	AKS_GROUP_3,
	AKS_GROUP_4,
	AKS_GROUP_5,
	AKS_GROUP_6,
	AKS_GROUP_7,
	MAX_AKS_GROUP
}
aks_group_t;

/**
 * A sensor detection hysteresis value.  This is expressed as a percentage of
 * the sensor detection threshold.
 * HYST_x = hysteresis value is x% of detection threshold value (rounded down).
 * NB: a minimum value of 2 is used.
 *
 * Example: if detection threshold = 20, then:
 *    HYST_50   = 10 (50% of 20)
 *    HYST_25   = 5  (25% of 20)
 *    HYST_12_5 = 2  (12.5% of 20)
 *    HYST_6_25 = 2  (6.25% of 20 = 1, but value is hardlimited to 2)
 */
typedef enum tag_hysteresis_t {
	HYST_50,
	HYST_25,
	HYST_12_5,
	HYST_6_25,
	MAX_HYST
}
hysteresis_t;

/**
 * A sensor recalibration threshold.  This is expressed as a percentage of the
 * sensor detection threshold.
 * RECAL_x = recalibration threshold is x% of detection threshold value
 *           (rounded down).
 * NB: a minimum value of 4 is used.
 *
 * Example: if detection threshold = 40, then:
 *     RECAL_100  = 40 (100% of 40)
 *     RECAL_50   = 20 (50% of 40)
 *     RECAL_25   = 10 (25% of 40)
 *     RECAL_12_5 = 5  (12.5% of 40)
 *     RECAL_6_25 = 4  (6.25% of 40 = 2, but value is hardlimited to 4)
 */
typedef enum tag_recal_threshold_t {
	RECAL_100,
	RECAL_50,
	RECAL_25,
	RECAL_12_5,
	RECAL_6_25,
	MAX_RECAL
}
recal_threshold_t;

/**
 * For rotors and sliders, the resolution of the reported angle or position.
 * RES_x_BIT = rotor/slider reports x-bit values.
 *
 * Example: if slider resolution is RES_7_BIT, then reported positions are in
 * the range 0..127.
 */
typedef enum tag_resolution_t {
	RES_1_BIT,
	RES_2_BIT,
	RES_3_BIT,
	RES_4_BIT,
	RES_5_BIT,
	RES_6_BIT,
	RES_7_BIT,
	RES_8_BIT,
	MAX_RES
}
resolution_t;

/* ! Touch Library Timing info. */
typedef struct tag_touch_time_t {
	/* ! Touch Measurement period in milliseconds.  This variable determines
	 * how */
	/* ! often a new touch measurement must be done. */
	/* ! Default value: Every 25 milliseconds. */
	uint16_t measurement_period_ms;
	/* ! Current time, set by timer ISR. */
	volatile uint16_t current_time_ms;
	/* ! Flag set by timer ISR when it's time to measure touch. */
	volatile uint8_t time_to_measure_touch;
}
touch_time_t;

/* ! Sensor structure for storing sensor related information. */
typedef struct tag_sensor_t {
	/* ! sensor state (calibrating, on, ...). */
	uint8_t state;
	/* ! general purpose ctr: used for calibration, drifting, etc. */
	uint8_t general_counter;
	/* ! Detect Integration ctr. */
	uint8_t ndil_counter;
	/* ! sensor detection threshold. */
	uint8_t threshold;
	/* ! bits 7..6: sensor type: */
	/* ! {00: key,01: rotor,10: slider,11: reserved} */
	/* ! bits 5..3: AKS group (0..7): 0 = no AKS group */
	/* ! bit 2    : positive recal flag */
	/* ! bits 1..0: hysteresis */
	uint8_t type_aks_pos_hyst;
	/* ! sensor from channel */
	/* ! for keys: from channel = to channel */
	/* ! rotors  : Top channel */
	/* ! sliders : Left most channel */
	/* ! NB:only need to_channel for keys in rotors/sliders build */
	uint8_t from_channel;
	/* ! FOR KEY's: this is unused, */
	/* ! rotors:  Bottom left channel */
	/* ! sliders: Middle  channel */
	uint8_t to_channel;
	/* ! index into array of rotor/slider values. */
	uint8_t index;
}
sensor_t;

/* ! Global sensor configuration info. */
typedef struct tag_touch_global_param_t {
	/* ! Sensor detect integration (DI) limit. */
	uint8_t di;
	/* ! Sensor away from touch drifet rate */
	uint8_t atch_drift_rate;
	/* ! Sensor towards touch drift rate */
	uint8_t tch_drift_rate;
	/* ! Sensor maximum on duration. */
	uint8_t max_on_duration;
	/* ! Sensor drift hold time. */
	uint8_t drift_hold_time;
	/* ! Sensor Positive recalibration delay. */
	uint8_t atch_recal_delay;
	/* ! Sensor calibration dummy burst count. */
	uint8_t cal_seq_1_count;
	/* ! Sensor calibration settling burst count. */
	uint8_t cal_seq_2_count;
	/* ! Sensor recalibration threshold. */
	recal_threshold_t recal_threshold;
}
touch_global_param_t;

/* ! Touch Filter Callback data type. */
typedef struct tag_touch_filter_data_t {
	/* ! Length of the measured signal values list. */
	uint16_t num_channel_signals;
	/* ! Pointer to measured signal values for each channel. */
	uint16_t *p_channel_signals;
}
touch_filter_data_t;

/* ! Touch Measured data type. */
typedef struct tag_touch_measure_data_t {
	/* ! Flag set by touch_xxcap_measure_complete_callback() function when
	 * a fresh Touch */
	/* ! status is available. */
	volatile uint8_t measurement_done_touch;
	/* ! Status of Touch measurement. */
	touch_acq_status_t acq_status;
	/* ! Length of the measured signal values list. */
	uint16_t num_channel_signals;
	/* ! Pointer to measured signal values for each channel. */
	uint16_t *p_channel_signals;
	/* ! Length of the measured reference values list. */
	uint16_t num_channel_references;
	/* ! Pointer to reference values for each channel. */
	uint16_t *p_channel_references;
	/* ! Number of sensor state bytes. */
	uint8_t num_sensor_states;
	/* ! Pointer to Touch Status of each sensor. */
	uint8_t *p_sensor_states;
	/* ! Length of the Rotor and Slider position values list. */
	uint8_t num_rotor_slider_values;
	/* ! Pointer to Rotor and Slider position values. */
	uint8_t *p_rotor_slider_values;
	/* ! Length of the sensors data list. */
	uint16_t num_sensors;
	uint16_t *p_cc_calibration_vals;
	/* ! Pointer to Sensor data. */
	sensor_t *p_sensors;
}
touch_measure_data_t;

/* ! Touch sensor configuration type. */
typedef struct tag_touch_selfcap_param_t {
	/* ! Sensor detection threshold. */
	aks_group_t aks_group;
	/* ! Sensor detection threshold. */
	threshold_t detect_threshold;
	/* ! Sensor detection hysteresis. */
	hysteresis_t detect_hysteresis;
	/* ! Sensor position resolution. This is valid only for a Rotor or
	 * Slider. */
	resolution_t position_resolution;
}
touch_selfcap_param_t;

/* ! Touch sensor configuration type. */
typedef struct tag_touch_mutlcap_param_t {
	/* ! Sensor detection threshold. */
	aks_group_t aks_group;
	/* ! Sensor detection threshold. */
	threshold_t detect_threshold;
	/* ! Sensor detection hysteresis. */
	hysteresis_t detect_hysteresis;
	/* ! Sensor position resolution. This is valid only for a Rotor or
	 * Slider. */
	resolution_t position_resolution;
	/* ! Sensor position hysteresis. This is valid only for a Rotor or
	 * Slider. */
	/* ! Range of position_hysteresis value is from 0 to 7. */
	uint8_t position_hysteresis;
}
touch_mutlcap_param_t;
 //! Mutual capacitance sensor acquisition parameter type.
  typedef struct tag_touch_mutlcap_acq_param_t
  {
    //!pointer to gain per node
    gain_t *p_mutlcap_gain_per_node;
    //! setup acquisition frequency mode
    freq_mode_sel_t touch_mutlcap_freq_mode;
    //! PTC clock prescale value
    prsc_div_sel_t mutlcap_ptc_prsc;
    //! PTC series resistor value
    rsel_val_t mutlcap_resistor_value;
    //! PTC clock prescale value during CC cal
    prsc_div_sel_t mutlcap_ptc_prsc_cc_cal;
    //! PTC series resistor value during CC cal
    rsel_val_t mutlcap_resistor_value_cc_cal;
    //!pointer to acquisition frequency settings
    freq_hop_sel_t *p_mutlcap_hop_freqs;
    //! filter level
    filter_level_t mutlcap_filter_level;
    //! auto oversampling
    auto_os_t mutlcap_auto_os;
  }
  touch_mutlcap_acq_param_t;

  //! Self capacitance sensor acquisition parameter type.
  typedef struct tag_touch_selfcap_acq_param_t
  {
	//!pointer to gain per node
	gain_t *p_selfcap_gain_per_node;
	//! enable/disable noise counter-measures
	freq_mode_sel_t touch_selfcap_freq_mode;
	//! PTC clock prescale value
	prsc_div_sel_t selfcap_ptc_prsc;
	//! PTC sense resistor value
	rsel_val_t selfcap_resistor_value;
        //! PTC clock prescale value during CC cal
	prsc_div_sel_t selfcap_ptc_prsc_cc_cal;
	//! PTC sense resistor value during CC cal
	rsel_val_t selfcap_resistor_value_cc_cal;
	//!pointer to hop frequency options
	freq_hop_sel_t *p_selfcap_hop_freqs;
	//! filter level
	filter_level_t selfcap_filter_level;
	//! auto oversampling
	auto_os_t selfcap_auto_os;
  }
  touch_selfcap_acq_param_t;

/* ! Self Capacitance configuration input. */
typedef struct tag_touch_selfcap_config_t {
	/* ! Number of channels using self cap method. */
	uint16_t num_channels;
	/* ! Number of sensors using self cap method. */
	uint16_t num_sensors;
	/* ! Number of rotors/sliders using self cap method. */
	uint8_t num_rotors_and_sliders;
	/* !global sensor configuration info. */
	touch_global_param_t global_param;
    //!sensor acquisition param info.
    touch_selfcap_acq_param_t touch_selfcap_acq_param;
	/* ! Pointer to data block buffer. */
	uint8_t *p_data_blk;
	/* ! size of data block buffer */
	uint16_t buffer_size;
	/* !pointer to xy nodes */
	uint16_t *p_selfcap_y_nodes;
	/* !pointer to gain per node */
        uint8_t self_quick_reburst_enable;

	void (*filter_callback)(touch_filter_data_t *p_filter_data);
}
touch_selfcap_config_t;
/* ! Mutual Capacitance configuration input. */
typedef struct tag_touch_mutlcap_config_t {
	/* ! Number of channels using mutual cap method. */
	uint16_t num_channels;
	/* ! Number of sensors using mutual cap method. */
	uint16_t num_sensors;
	/* ! Number of rotors/sliders using mutual cap method. */
	uint8_t num_rotors_and_sliders;
	/* !global sensor configuration info. */
	touch_global_param_t global_param;
    //!sensor acquisition param info.
    touch_mutlcap_acq_param_t touch_mutlcap_acq_param;
	/* ! Pointer to data block buffer. */
	uint8_t *p_data_blk;
	/* ! size of data block buffer */
	uint16_t buffer_size;
	/* !pointer to xy nodes */
	uint16_t *p_mutlcap_xy_nodes;
        uint8_t mutl_quick_reburst_enable;

	void (*filter_callback)(touch_filter_data_t *p_filter_data);
}
touch_mutlcap_config_t;

/* ! Touch Input Configuration type. */
typedef struct tag_touch_config_t {
	/* ! Mutual cap configuration pointer. */
	touch_mutlcap_config_t *p_mutlcap_config;
	/* ! Self cap configuration pointer. */
	touch_selfcap_config_t *p_selfcap_config;
    //! PTC ISR priority level
    uint8_t ptc_isr_lvl;
}
touch_config_t;

/* ! Touch library information type. */
typedef struct tag_touch_info_t {
	/* ! Touch Library state specific to method. */
	touch_lib_state_t tlib_state;
	/* ! Number of channels in use, irrespective of the corresponding Sensor
	 * being disabled or enabled. */
	uint16_t num_channels_in_use;
	/* ! Number of sensors in use, irrespective of the Sensor being disabled
	 * or enabled. */
	uint16_t num_sensors_in_use;
	/* ! Number of rotor sliders in use, irrespective of the Rotor/Slider
	 * being disabled or enabled. */
	uint8_t num_rotors_sliders_in_use;
	/* ! Max possible number of channels per rotor or slider. */
	uint8_t max_channels_per_rotor_slider;
	/* ! Touch Library version. */
	uint16_t fw_version;
}
touch_info_t;

/*----------------------------------------------------------------------------
*                           Structure Declarations
*  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*                               global variables
*  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*                               extern variables
*  ----------------------------------------------------------------------------*/
/* ! Touch Library Timing info. */
extern touch_time_t touch_time;

/* ! Self capacitance method measured data pointer. */
extern touch_measure_data_t *p_selfcap_measure_data;

/* ! Mutual capacitance method measured data pointer. */
extern touch_measure_data_t *p_mutlcap_measure_data;

/*----------------------------------------------------------------------------
*                               static variables
*  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*                               prototypes
*  ----------------------------------------------------------------------------*/
uint16_t get_sensor_node_signal(uint16_t sensor_node);
void     update_sensor_node_signal(uint16_t sensor_node, uint16_t new_signal);
uint16_t get_sensor_node_reference(uint16_t sensor_node);
void     update_sensor_node_reference(uint16_t sensor_node, uint16_t new_reference);
uint16_t get_sensor_cc_val(uint16_t sensor_node);
void     update_sensor_cc_val(uint16_t sensor_node, uint16_t new_cc_value);
uint8_t  get_sensor_state(uint16_t sensor_node);
void     update_sensor_state(uint16_t sensor_node, uint8_t new_state);
/*! \name Touch Helper API.
 */
/* ! @{ */

/*! \brief This API is used to initialize and configure the Touch Library.
 * \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_sensors_init(void);

/*! \brief This API is used to perform a Single Capacitance measurement
 * using the Touch Library.
 * \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_sensors_measure(void);

/*! \brief This API is used to update Timing info for Touch Library.
 * Typical usage of this API is inside a periodic timer ISR.
 * \return touch_ret_t: Touch Library Error status.
 */
void touch_sensors_update_time(void);

/*! \brief This API is used to change the config of the Detect Treshold
 * and the Hysteresis
 * */
void setHysteresis(hysteresis_t newHyst);
void setSensitivity(unsigned int newSens);
void setSensitivityChannel(unsigned int newSens, unsigned int btn_channel);
hysteresis_t getHysteresis();
unsigned int getSensitivity();
void setPads(int *pad);

/* Acquisition module SAMD21 Sequential */

typedef struct {
	uint8_t  node_acq_status;
	uint16_t node_acq_signals;
	uint16_t node_comp_caps;
} qtm_acq_node_data_t;


typedef struct {
	uint16_t node_xmask;        /* Selects the X Pins for this node */
	uint16_t node_ymask;        /* Selects the Y Pins for this node */
	uint8_t  node_rsel_prsc;    /* Bits 7:4 = Resistor, Bits 3:0  Prescaler */
	uint8_t  node_gain;         /* Bits 7:4 = Analog gain, Bits 3:0 = Digital gain */
	uint8_t  node_oversampling; /* Accumulator setting  */
} qtm_acq_samd21_node_config_t;

/* Node run-time data - Defined in common api as it will be used with all acquisition modules */

/* Node group configuration */
typedef struct {
	uint16_t num_sensor_nodes;       /* Number of sensor nodes */
	uint8_t  acq_sensor_type;        /* Self or mutual sensors */
	uint8_t  calib_option_select;    /* Hardware tuning: XX | TT 3/4/5 Tau | X | XX None/RSEL/PRSC/CSD */
	uint8_t  freq_option_select;     /* SDS or ASDV setting */
	uint8_t  ptc_interrupt_priority; /* Runtime priority of PTC interrupt */
} qtm_acq_node_group_config_t;

/* Container structure for sensor group */
typedef struct {
	qtm_acq_node_group_config_t(*qtm_acq_node_group_config);
	qtm_acq_samd21_node_config_t(*qtm_acq_node_config);
	qtm_acq_node_data_t(*qtm_acq_node_data);
} qtm_acquisition_control_t;

/* Key process module */
/* Sensor group config */
typedef struct {
	uint16_t num_key_sensors;              /* Number of sensors */
	uint8_t  sensor_touch_di;              /* Count in to Detect */
	uint8_t  sensor_max_on_time;           /* Max on duration x 200ms */
	uint8_t  sensor_anti_touch_di;         /* Count in to Anti-touch recal */
	uint8_t  sensor_anti_touch_recal_thr;  /* Anti-touch recal threshold % */
	uint8_t  sensor_touch_drift_rate;      /* One count per <200> ms */
	uint8_t  sensor_anti_touch_drift_rate; /* One count per <200> ms */
	uint8_t  sensor_drift_hold_time;       /* Drift hold time */
	uint8_t  sensor_reburst_mode;          /* None / Unresolved / All */
} qtm_touch_key_group_config_t;

/* Sensor group data */
typedef struct {
	uint8_t  qtm_keys_status;     /* Status byte - bitfield: Bit 7 = REBURST_REQ, Bits 6:1 = Reserved, Bit 0 = Detect */
	uint16_t acq_group_timestamp; /* For tracking this group drift etc */
	uint8_t  dht_count_in;        /* Count of drift hold time */
	uint8_t  tch_drift_count_in;  /* Count of towards touch drift */
	uint8_t  antitch_drift_count_in; /* Count of away from touch drift */
} qtm_touch_key_group_data_t;

/* Sensor keys config */
typedef struct {
	uint8_t channel_threshold;  /* Touch detection threshold */
	uint8_t channel_hysteresis; /* Percentage of threshold reduction to exit detect state */
	uint8_t channel_aks_group;  /* 0 = None, 1-255 = group number */
} qtm_touch_key_config_t;

/* ---------------------------------------------------------------------------------------- */
/* Key sensor run-time data - api common */
/* ---------------------------------------------------------------------------------------- */

typedef struct {
	uint8_t              sensor_state;         /* Disabled, Off, On, Filter, Cal... */
	uint8_t              sensor_state_counter; /* State counter */
	qtm_acq_node_data_t *node_data_struct_ptr; /* Pointer to node data structure */
	uint16_t             channel_reference;    /* Reference signal */
} qtm_touch_key_data_t;


/* Container */
typedef struct {
	qtm_touch_key_group_data_t(*qtm_touch_key_group_data);
	qtm_touch_key_group_config_t(*qtm_touch_key_group_config);
	qtm_touch_key_data_t(*qtm_touch_key_data);
	qtm_touch_key_config_t(*qtm_touch_key_config);
} qtm_touch_key_control_t;
/* ! @} */

/*----------------------------------------------------------------------------
*                               Touch API
*  ----------------------------------------------------------------------------*/

/*! \name Touch API.
 */
/* ! @{ */

/**
 * touch_ret_t touch_mutlcap_sensors_init( touch_config_t *p_touch_config);
 */
#define touch_mutlcap_sensors_init( y )	\
	touch_mutlcap_sensors_init_with_rs_table((y), \
		PRIV_MUTLCAP_RS_TABLE_INIT );

/**
 * touch_ret_t touch_selfcap_sensors_init( touch_config_t *p_touch_config);
 */
#define touch_selfcap_sensors_init( y )	\
	touch_selfcap_sensors_init_with_rs_table((y), \
		PRIV_SELFCAP_RS_TABLE_INIT );

/*! \brief This API is used to initialize the Touch Library with Mutual cap
 * method
 * pin, register and sensor configuration provided by the user.
 *
 * \param  p_touch_config: Pointer to Touch configuration structure.
 * \return touch_ret_t: Touch Library Error status.
 */
  touch_ret_t touch_mutlcap_sensors_init_with_rs_table (touch_config_t *p_touch_config,
						   void (*rs_table_init) (void));

/*! \brief This API is used to initialize the Touch Library with Self cap method
 * pin, register and sensor configuration provided by the user.
 *
 * \param  p_touch_config: Pointer to Touch configuration structure.
 * \return touch_ret_t: Touch Library Error status.
 */
  touch_ret_t touch_selfcap_sensors_init_with_rs_table (touch_config_t *p_touch_config,
						   void (*rs_table_init) (void));
/*! \brief This API can be used to configure a sensor of type key, rotor or slider.
 *
 * \param  sensor_type: can be of type key, rotor or slider.
 * \param  from_channel: the first channel in the slider sensor.
 * \param  to_channel: the last channel in the slider sensor.
 * \param  aks_group: which AKS group (if any) the sensor is in.
 * \param  detect_threshold: the sensor detection threshold.
 * \param  detect_hysteresis: the sensor detection hysteresis value.
 * \param  position_resolution: the resolution of the reported position value.
 * \param  p_sensor_id: The sensor id value of the configured sensor is updated
 * by the Touch Library.
 * \note   Range of position_hysteresis value is from 0 to 7.
 * \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_mutlcap_sensor_config(
		sensor_type_t sensor_type,
		channel_t from_channel,
		channel_t to_channel,
		aks_group_t aks_group,
		threshold_t detect_threshold,
		hysteresis_t detect_hysteresis,
		resolution_t position_resolution,
        uint8_t position_hysteresis,
		sensor_id_t *p_sensor_id);

touch_ret_t touch_selfcap_sensor_config(
		sensor_type_t sensor_type,
		channel_t from_channel,
		channel_t to_channel,
		aks_group_t aks_group,
		threshold_t detect_threshold,
		hysteresis_t detect_hysteresis,
		resolution_t position_resolution,
		sensor_id_t *p_sensor_id);

/*! \brief This API is used to calibrate the sensors for the first time before
 * starting a Touch measurement.  This API can also be used to force
 * calibration of sensors when any of the Touch sensor parameters are
 * changed during runtime.
 *
 * \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_mutlcap_sensors_calibrate(auto_tune_type_t );

touch_ret_t touch_selfcap_sensors_calibrate(auto_tune_type_t );

/*! \brief This API can be used to start a Touch measurement.
 *
 * \param  current_time_ms: Current time in millisecond.
 * \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_selfcap_sensors_measure(
		touch_current_time_t
		current_time_ms,
		touch_acq_mode_t
		selfcap_acq_mode,
		void
		(*measure_complete_callback)
		(void));

touch_ret_t touch_mutlcap_sensors_measure(
		touch_current_time_t
		current_time_ms,
		touch_acq_mode_t
		mutlcap_acq_mode,
		void
		(*measure_complete_callback)
		(void));

/*! \brief This API can be used retrieve the delta value corresponding to
 * a given sensor.
 *
 * \param  sensor_id: The sensor id for which delta value is being seeked.
 * \param  p_delta: Pointer to the delta variable to be updated by the Touch
 * Library.
 * \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_mutlcap_sensor_get_delta(
		sensor_id_t sensor_id,
		touch_delta_t *p_delta);

touch_ret_t touch_selfcap_sensor_get_delta(
		sensor_id_t sensor_id,
		touch_delta_t *p_delta);

/*! \brief This API can be used to set the sensor configuration parameters.
 *  \param p_sensor_id: The sensor id for which configuration parameter
 *         information is being set.
 *  \param p_touch_sensor_param: The touch sensor parameter structure that will
 *         be used by the Touch Library to update.
 *  \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_mutlcap_sensor_update_config( sensor_id_t sensor_id,
		touch_mutlcap_param_t *p_touch_sensor_param );

touch_ret_t touch_selfcap_sensor_update_config(sensor_id_t sensor_id,
		touch_selfcap_param_t *p_touch_sensor_param );

/*! \brief This API can be used to read back the sensor configuration
 * parameters.
 *  \param p_sensor_id: The sensor id for which configuration parameter
 *         information is being set.
 *  \param p_touch_sensor_param: The touch sensor parameter structure that will
 *         be updated by the Touch Library.
 *  \return touch_ret_t: Touch Library Error status.
 */

touch_ret_t touch_mutlcap_sensor_get_config(sensor_id_t sensor_id,
		touch_mutlcap_param_t *p_touch_sensor_param );

touch_ret_t touch_selfcap_sensor_get_config(sensor_id_t sensor_id,
		touch_selfcap_param_t *p_touch_sensor_param );
  /*! \brief This API can be used to set the sensor configuration parameters.
 *  \param p_sensor_id: The sensor id for which configuration parameter
 *         information is being set.
 *  \param p_touch_sensor_param: The touch sensor parameter structure that will
 *         be used by the Touch Library to update.
 *  \return touch_ret_t: Touch Library Error status.
 */
  touch_ret_t touch_mutlcap_sensor_update_acq_config(
                            touch_mutlcap_acq_param_t *p_touch_mutlcap_acq_param );

  touch_ret_t touch_selfcap_sensor_update_acq_config(
                             touch_selfcap_acq_param_t *p_touch_selfcap_acq_param );

/*! \brief This API can be used to read back the sensor configuration parameters.
 *  \param p_sensor_id: The sensor id for which configuration parameter
 *         information is being set.
 *  \param p_touch_sensor_param: The touch sensor parameter structure that will
 *         be updated by the Touch Library.
 *  \return touch_ret_t: Touch Library Error status.
 */

  touch_ret_t touch_mutlcap_sensor_get_acq_config(
                             touch_mutlcap_acq_param_t *p_touch_mutlcap_acq_param );

  touch_ret_t touch_selfcap_sensor_get_acq_config(
                             touch_selfcap_acq_param_t *p_touch_selfcap_acq_param );

/*! \brief This API can be used to update the global parameter
 *
 *  \param p_global_param: The pointer to global sensor configuration.
 *
 *  \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_mutlcap_update_global_param(
		touch_global_param_t *p_global_param );

touch_ret_t touch_selfcap_update_global_param(
		touch_global_param_t *p_global_param );

/*! \brief This API can be used to read back the global parameter
 *
 *  \param p_global_param: The pointer to global sensor configuration.
 *
 *  \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_mutlcap_get_global_param( touch_global_param_t *p_global_param );

touch_ret_t touch_selfcap_get_global_param(touch_global_param_t *p_global_param );
/*! \brief This API can be used to disable any sensor
 *
 *  \param p_global_param: Sensor number which needs to be disabled
 *
 *  \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_mutlcap_sensor_disable(sensor_id_t sensor_id);

touch_ret_t touch_selfcap_sensor_disable(sensor_id_t sensor_id);
/*! \brief This API can be used to reenable a disabled sensor
 *
 *  \param p_global_param: Sensor number which needs to be reenabled
 *
 *  \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_mutlcap_sensor_reenable(sensor_id_t sensor_id);

touch_ret_t touch_selfcap_sensor_reenable(sensor_id_t sensor_id);
/*! \brief This API can be used to get the Touch Library configuration
 *
 *  \param p_touch_info: Pointer to the Touch info data structure that will be
 *                       updated by the Touch Library.
 *
 *  \return touch_ret_t: Touch Library Error status.
 */
touch_ret_t touch_mutlcap_get_libinfo( touch_info_t *p_touch_info );

touch_ret_t touch_selfcap_get_libinfo(touch_info_t *p_touch_info );

/* ! @} */

/*----------------------------------------------------------------------------
*                          Extern Functions
*  ----------------------------------------------------------------------------*/

/*! \name Touch Library internal use functions.
 */
/* ! @{ */

/*! \brief This is an extern function of the Touch Library.
 * This function is NOT to be used by the user.
 */
void touch_mutlcap_rs_table_init(void);

void touch_selfcap_rs_table_init(void);

/* ! @} */

#ifdef __cplusplus
}
#endif
#endif                          /* TOUCH_API_SAMD_H */
