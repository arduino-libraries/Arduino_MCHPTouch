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

/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include <Arduino.h>
#include "DataStreamer.h"
#include "touch_api_SAMD.h"

#if (DEF_TOUCH_DATA_STREAMER_ENABLE == 1u)

/*----------------------------------------------------------------------------
 *     defines
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/
extern qtm_acquisition_control_t qtlib_acq_set1;
extern qtm_touch_key_control_t   qtlib_key_set1;
extern qtm_touch_key_config_t    qtlib_key_configs_set1[DEF_SELFCAP_NUM_SENSORS];

extern uint8_t module_error_code;

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/


/*============================================================================
void datastreamer_output(void)
------------------------------------------------------------------------------
Purpose: Forms the datastreamer frame based on the configured modules, Tranmits
         the frame as single packet through UART port.
Input  : none
Output : none
Notes  :
============================================================================*/
void DataStreamer::datastreamerOutput(void)
{
  touch_time.time_to_measure_touch = 1;
  touch_time.current_time_ms = millis();// touch_time.current_time_ms + millis();

  // trigger a new measure
  touch_sensors_measure();
  
  // check if a measure is done
  if ((p_selfcap_measure_data->measurement_done_touch == 1u))
  {
    p_selfcap_measure_data->measurement_done_touch == 0u;
  }

	int16_t           temp_int_calc;
	uint16_t          u16temp_output;
	uint8_t           u8temp_output;
	volatile uint16_t count_bytes_out;


	// Frame Start
	for (count_bytes_out = 0u; count_bytes_out < 5; count_bytes_out++) {
		/* Signals */
		u16temp_output = get_sensor_node_signal(count_bytes_out);
	

		/* Reference */
		u16temp_output = get_sensor_node_reference(count_bytes_out);


		/* Touch delta */
		temp_int_calc = get_sensor_node_signal(count_bytes_out);
		temp_int_calc -= get_sensor_node_reference(count_bytes_out);
		u16temp_output = (uint16_t)(temp_int_calc);

		Serial.print("touch_"+String(count_bytes_out) + "_delta:");
		Serial.print(temp_int_calc);
		Serial.print(" ");
		/* Comp Caps */
		u16temp_output = get_sensor_cc_val(count_bytes_out);


		
		/* State */
		u8temp_output = get_sensor_state(count_bytes_out);
		/* Threshold */


		Serial.print("threshold:");
		Serial.print(p_selfcap_measure_data->p_sensors[count_bytes_out].threshold);
		Serial.print(" ");
	}
	Serial.println();
}

#endif
