/* This source file is part of the ATMEL QTouch Library 5.0.1 */
/* Software provided by Microchip under the license agreement 
   “Microchip Touch Library License Agreement - Arduino 082420 
   (part of this downloaded package) */

/**
 *
 * \file
 *
 * \brief  This file contains the SAMD QTouch library initialization,
 * sensor configuration and measurement routines.
 *
 * - Userguide:          QTouch Library Peripheral Touch Controller User Guide.
 * - Support: https://www.microchip.com/support/
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

/**
 * Includes for Touch Library.
 */
#include <Arduino.h>
#include "touch_api_SAMD.h"
//#include "datastreamer/datastreamer.h"
/*----------------------------------------------------------------------------
*                           manifest constants
*  ----------------------------------------------------------------------------*/
#define   DEF_SELFCAP_CAL_SEQ1_COUNT	8
#define   DEF_SELFCAP_CAL_SEQ2_COUNT	4
#define   DEF_SELFCAP_CC_CAL_CLK_PRESCALE PRSC_DIV_SEL_2
#define   DEF_SELFCAP_CC_CAL_SENSE_RESISTOR RSEL_VAL_0
#define   DEF_SELFCAP_QUICK_REBURST_ENABLE 0u

/*----------------------------------------------------------------------------
*                                   macros
*  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*                           type definitions
*  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*                           Structure Declarations
*  ----------------------------------------------------------------------------*/
/* Node status, signal, calibration values */
qtm_acq_node_data_t ptc_qtlib_node_stat1[DEF_SELFCAP_NUM_CHANNELS];
qtm_touch_key_data_t qtlib_key_data_set1[DEF_SELFCAP_NUM_SENSORS];
/*----------------------------------------------------------------------------
*                               global variables
*  ----------------------------------------------------------------------------*/
/* ! QTouch Library Timing info. */
touch_time_t touch_time;

/**
 * Mutual Cap sensors measured data pointer.
 * Note: This pointer is initialized by the QTouch library once the
 * touch_mutlcap_sensors_init API is called. */
touch_measure_data_t *p_mutlcap_measure_data = NULL;

/**
 * Self Cap sensors measured data pointer.
 * Note: This pointer is initialized by the QTouch library once the
 * touch_selfcap_sensors_init API is called. */
touch_measure_data_t *p_selfcap_measure_data = NULL;

/**
 * Default variables for the sensor config, then they are changed with
 * setHysteresis() , setSensitivity() and setSensitivityChannel before the init
 */
unsigned int _sensitivity = 50u;
unsigned int _sensitivity_ch[5] = {50u , 50u, 50u, 50u, 50u};

hysteresis_t _hysteresis = HYST_6_25;
int _pad[5] = {-1,-1,-1,-1,-1};
uint8_t module_error_code = 0;
/*----------------------------------------------------------------------------
*                               static variables
*  ----------------------------------------------------------------------------*/

/**
 * Self Cap sensors data block provided as input to Touch library.
 */
static uint8_t selfcap_data_blk[PRIV_SELFCAP_DATA_BLK_SIZE];

/**
 * Self Cap sensors Pins Info.
 */

uint16_t selfcap_y_nodes[DEF_SELFCAP_NUM_CHANNELS] = {DEF_SELFCAP_LINES};

gain_t selfcap_gain_per_node[DEF_SELFCAP_NUM_CHANNELS]
	= {DEF_SELFCAP_GAIN_PER_NODE};

freq_hop_sel_t selfcap_freq_hops[3u]
	= {DEF_SELFCAP_HOP_FREQS};

/**
 * Self Cap Configuration structure provided as input to Touch Library.
 *
 * Note: Use the touch.h configuration header file to fill in
 * the elements of this structure.  DO NOT modify any of the input values
 * directly in this structure.
 */
static touch_selfcap_config_t selfcap_config = {
	DEF_SELFCAP_NUM_CHANNELS,       /* Self Cap number of channels. */
	DEF_SELFCAP_NUM_SENSORS,        /* Self Cap number of sensors. */
	DEF_SELFCAP_NUM_ROTORS_SLIDERS, /* Self Cap number of rotors and
	                                 *sliders. */

	/* Self Cap GLOBAL SENSOR CONFIGURATION INFO. */
	{
		DEF_SELFCAP_DI,         /* uint8_t  di; Sensor detect
		                         *integration (DI) limit. */
		/* Interchanging Negative and Positive Drift rate, since Signal
		 *increases on Touch. */
		DEF_SELFCAP_ATCH_DRIFT_RATE, /* uint8_t  neg_drift_rate; Sensor
		                              *negative drift rate. */
		DEF_SELFCAP_TCH_DRIFT_RATE, /* uint8_t  pos_drift_rate; Sensor
		                             *positive drift rate. */
		DEF_SELFCAP_MAX_ON_DURATION, /* uint8_t  max_on_duration; Sensor
		                              *maximum on duration. */
		DEF_SELFCAP_DRIFT_HOLD_TIME, /* uint8_t  drift_hold_time; Sensor
		                              *drift hold time. */
		DEF_SELFCAP_ATCH_RECAL_DELAY,   /* uint8_t  pos_recal_delay;
		                                 *Sensor positive recalibration
		                                 *delay. */
                DEF_SELFCAP_CAL_SEQ1_COUNT,
                DEF_SELFCAP_CAL_SEQ2_COUNT,
		DEF_SELFCAP_ATCH_RECAL_THRESHOLD, /* recal_threshold_t
		                              *recal_threshold; Sensor
		                              *recalibration threshold. */
	},
	{
	selfcap_gain_per_node, /* Self Cap channel gain setting. */
	DEF_SELFCAP_FREQ_MODE, /* Self Cap noise counter measure
	                            *enable/disable. */
        DEF_SELFCAP_CLK_PRESCALE,
        DEF_SELFCAP_SENSE_RESISTOR,
        DEF_SELFCAP_CC_CAL_CLK_PRESCALE,
        DEF_SELFCAP_CC_CAL_SENSE_RESISTOR,
        selfcap_freq_hops,
	DEF_SELFCAP_FILTER_LEVEL, /* Self Cap filter level setting. */
	DEF_SELFCAP_AUTO_OS, /* Self Cap auto oversamples setting. */
	},
	selfcap_data_blk,               /* Self Cap data block index. */
	PRIV_SELFCAP_DATA_BLK_SIZE, /* Self Cap data block size. */
	selfcap_y_nodes, /* Self Cap channel nodes. */
        DEF_SELFCAP_QUICK_REBURST_ENABLE,
	DEF_SELFCAP_FILTER_CALLBACK     /* Self Cap filter callback function
	                                 *pointer. */
};

/**
 * Touch Library input configuration structure.
 */
touch_config_t touch_config = {
	NULL,
	&selfcap_config,                /* Pointer to Self Cap configuration
	                                 *structure. */
    DEF_TOUCH_PTC_ISR_LVL,  		/* PTC interrupt level. */
};

/*----------------------------------------------------------------------------
*                               prototypes
*  ----------------------------------------------------------------------------*/

/*! \brief configure keys, rotors and sliders.
 */
static touch_ret_t touch_sensors_config(void);

/*! \brief Self Cap measure complete callback function example prototype.
 */
void touch_selfcap_measure_complete_callback( void );

/*! \brief Initialize and enable PTC clock.
 */
void touch_configure_ptc_clock(void);
/*----------------------------------------------------------------------------
*  static functions
*  ----------------------------------------------------------------------------*/

void touch_configure_ptc_clock(void)
{
	uint8_t channel = PTC_GCLK_ID;
	uint8_t source_generator = 0;

	uint32_t new_clkctrl_config = (channel << GCLK_CLKCTRL_ID_Pos);
	new_clkctrl_config |= source_generator << GCLK_CLKCTRL_GEN_Pos;

	// Disable generic clock channel
	noInterrupts();

	// Select the requested generator channel
	*((uint8_t*)&GCLK->CLKCTRL.reg) = channel;

	// Switch to known-working source so that the channel can be disabled
	uint32_t prev_gen_id = GCLK->CLKCTRL.bit.GEN;
	GCLK->CLKCTRL.bit.GEN = 0;

	// Disable the generic clock
	GCLK->CLKCTRL.reg &= ~GCLK_CLKCTRL_CLKEN;

	// Wait for clock to become disabled
	while (GCLK->CLKCTRL.reg & GCLK_CLKCTRL_CLKEN);

	// Restore previous configured clock generator
	GCLK->CLKCTRL.bit.GEN = prev_gen_id;

	// restore interupt
	interrupts();

	// Write the new configuration
	GCLK->CLKCTRL.reg = new_clkctrl_config;

	*((uint8_t*)&GCLK->CLKCTRL.reg) = channel;

	// Enable the generic clock
	GCLK->CLKCTRL.reg |= GCLK_CLKCTRL_CLKEN;

	PM->APBCMASK.reg |= PM_APBCMASK_PTC;
}

/* ! [setup] */

/*! \brief Example application entry function.
 */
touch_ret_t touch_sensors_init(void)
{
	touch_ret_t touch_ret = TOUCH_SUCCESS;

	/* Setup and enable generic clock source for PTC module. */
	touch_configure_ptc_clock();

	touch_time.measurement_period_ms = DEF_TOUCH_MEASUREMENT_PERIOD_MS;

	for(int i = 0; i < 5; i++) {
		touch_config.p_selfcap_config->p_selfcap_y_nodes[i] = Y(_pad[i]);
	}
	/* Initialize touch library for Self Cap operation. */
	touch_ret = touch_selfcap_sensors_init(&touch_config);
	if (touch_ret != TOUCH_SUCCESS) {
		while (1u) {    /* Check API Error return code. */
		}
	}

	/* configure the touch library sensors. */
	touch_ret = touch_sensors_config();
	if (touch_ret != TOUCH_SUCCESS) {
		while (1u) {    /* Check API Error return code. */
		}
	}

	/* Auto Tuning setting for calibration.
	 *
	 * AUTO_TUNE_PRSC: When Auto tuning of pre-scaler is selected
	 * the PTC uses the user defined internal series resistor setting
	 * (DEF_MUTLCAP_SENSE_RESISTOR) and the pre-scaler is adjusted
	 * to slow down the PTC operation to ensure full charge transfer.
	 *
	 * AUTO_TUNE_RSEL: When Auto tuning of the series resistor is
	 * selected the PTC runs at user defined pre-scaler setting speed
	 * (DEF_MUTLCAP_CLK_PRESCALE) and the internal series resistor is
	 * tuned automatically to the optimum value to allow for full
	 * charge transfer.
	 *
	 * AUTO_TUNE_NONE: When manual tuning option is selected (AUTO_TUNE_NONE),
	 * the user defined values of PTC pre-scaler and series resistor is used
	 * for PTC operation as given in DEF_MUTLCAP_CLK_PRESCALE and
	 * DEF_MUTLCAP_SENSE_RESISTOR
	 *
	 */
	touch_ret = touch_selfcap_sensors_calibrate(AUTO_TUNE_RSEL);
	if (touch_ret != TOUCH_SUCCESS) {
		while (1) {    /* Check API Error return code. */
		}
	}
	return (touch_ret);
}

touch_ret_t touch_sensors_measure(void)
{
	touch_ret_t touch_ret = TOUCH_SUCCESS;

	if (touch_time.time_to_measure_touch == 1u) {
		touch_ret = touch_selfcap_sensors_measure(
				touch_time.current_time_ms,
				NORMAL_ACQ_MODE,
				touch_selfcap_measure_complete_callback);

		if ((touch_ret != TOUCH_ACQ_INCOMPLETE) &&
				(touch_ret == TOUCH_SUCCESS)) {
			touch_time.time_to_measure_touch = 0u;
		} else if ((touch_ret != TOUCH_SUCCESS) &&
				(touch_ret != TOUCH_ACQ_INCOMPLETE)) {
			while (1) {
			}

			/* Reaching this point can be due to -
			 *     1. The api has retured an error due to a invalid
			 * input parameter.
			 *     2. The api has been called during a invalid Touch
			 * Library state. */
		}
	}

	return (touch_ret);
}

/*! \brief Example configuration for touch keys, rotors and sliders.
 *
 * \retval TOUCH_SUCCESS   Configuration setting successful.
 * \retval TOUCH_INVALID_xx   Invalid input configuration setting.
 */
touch_ret_t touch_sensors_config(void)
{
	touch_ret_t touch_ret = TOUCH_SUCCESS;
	sensor_id_t sensor_id;

touch_ret = touch_selfcap_sensor_config(SENSOR_TYPE_KEY, CHANNEL_0,
			CHANNEL_0, NO_AKS_GROUP,_sensitivity_ch[0],
			HYST_6_25, RES_1_BIT,
			&sensor_id);
	if (touch_ret != TOUCH_SUCCESS) {
		while (1) {
		}
	}

	touch_ret = touch_selfcap_sensor_config(SENSOR_TYPE_KEY, CHANNEL_1,
			CHANNEL_1, NO_AKS_GROUP, _sensitivity_ch[1],
			HYST_6_25, RES_1_BIT,
			&sensor_id);
	if (touch_ret != TOUCH_SUCCESS) {
		while (1) {
		}
	}

	touch_ret = touch_selfcap_sensor_config(SENSOR_TYPE_KEY, CHANNEL_2,
			CHANNEL_2,  NO_AKS_GROUP, _sensitivity_ch[2],
			HYST_6_25, RES_1_BIT,
			&sensor_id);
	if (touch_ret != TOUCH_SUCCESS) {
		while (1) {
		}
	}

	touch_ret = touch_selfcap_sensor_config(SENSOR_TYPE_KEY, CHANNEL_3,
			CHANNEL_3,  NO_AKS_GROUP, _sensitivity_ch[3],
			HYST_6_25, RES_1_BIT,
			&sensor_id);
	if (touch_ret != TOUCH_SUCCESS) {
		while (1) {
		}
	}

		touch_ret = touch_selfcap_sensor_config(SENSOR_TYPE_KEY, CHANNEL_4,
			CHANNEL_4,  NO_AKS_GROUP, _sensitivity_ch[4],
			HYST_6_25, RES_1_BIT,
			&sensor_id);
	if (touch_ret != TOUCH_SUCCESS) {
		while (1) {
		}
	}

	return (touch_ret);
}

/*! \brief Self Cap measure complete callback function.
 *
 * This function is called by the library when the touch measurement
 * process for Self Cap sensors is completed.
 *
 * \param p_measure_data   Base address of touch_measure_data_t instance.
 * \note A touch_selfcap_measure_complete_callback() call signifies that fresh
 * values of touch status, rotor/slider position, measured signals,
 * references and Sensor data is available.
 * The Self Cap measured data can be accessed using the p_measure_data
 * pointer.
 */
void touch_selfcap_measure_complete_callback( void )
{
	if (!(p_selfcap_measure_data->acq_status & TOUCH_BURST_AGAIN)) {
		/* Set the QTouch measurement done flag. */
		p_selfcap_measure_data->measurement_done_touch = 1u;
	}
}

void setHysteresis(hysteresis_t newHyst){
	_hysteresis = newHyst;
}

void setSensitivity(unsigned int newSens){
	_sensitivity = newSens;
	for (int i = 0; i < 5; i++){
		_sensitivity_ch[i] = _sensitivity;
	}
}

void setPads(int *pad){
	for(int i = 0; i < 5; i++) {
		if(pad[i] != -1){
			_pad[i] = pad[i];
		}
	}
}

void setSensitivityChannel(unsigned int newSens, unsigned int btn_channel){
	_sensitivity_ch[btn_channel] = newSens;
}

hysteresis_t getHysteresis() {
 	return _hysteresis;
}

unsigned int getSensitivity() {
 	return _sensitivity;
}

uint16_t get_sensor_node_signal(uint16_t sensor_node)
{
	return (p_selfcap_measure_data->p_channel_signals[sensor_node]);
}

void update_sensor_node_signal(uint16_t sensor_node, uint16_t new_signal)
{
	p_selfcap_measure_data->p_channel_signals[sensor_node] = new_signal;
}

uint16_t get_sensor_node_reference(uint16_t sensor_node)
{
	return (p_selfcap_measure_data->p_channel_references[sensor_node]);
}

void update_sensor_node_reference(uint16_t sensor_node, uint16_t new_reference)
{
	p_selfcap_measure_data[sensor_node].p_channel_references[sensor_node] = new_reference;
}

uint16_t get_sensor_cc_val(uint16_t sensor_node)
{
	return (p_selfcap_measure_data->p_cc_calibration_vals[sensor_node]);
}

void update_sensor_cc_val(uint16_t sensor_node, uint16_t new_cc_value)
{
	p_selfcap_measure_data->p_cc_calibration_vals[sensor_node] = new_cc_value;
}

uint8_t get_sensor_state(uint16_t sensor_node)
{
	return GET_SELFCAP_SENSOR_STATE(sensor_node);
}

void update_sensor_state(uint16_t sensor_node, uint8_t new_state)
{
	p_selfcap_measure_data->p_sensor_states[sensor_node] = new_state;
}
