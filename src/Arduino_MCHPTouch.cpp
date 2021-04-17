/*
  Copyright (c) 2020 Arduino SA

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <Arduino_MCHPTouch.h>

QtouchClass::QtouchClass()
{
}

QtouchClass::~QtouchClass()
{
}

/*******************************************************************************
 * Function Name  : begin
 * Description    : Initializes QTouch sensors
 * Input          : NONE
 * Return         : false on Error, true on Success
 *******************************************************************************/
bool QtouchClass::begin()
{
  // touch sensors init
  if (touch_sensors_init())
  {
    return false;
  }
  // set starting measure time to 0 and change the analog resolution to 10
  touch_time.current_time_ms = 0;
  analogReadResolution(10);
  return true;
}

/*******************************************************************************
 * Function Name  : available
 * Description    : Checks for new values availability
 * Input          : NONE
 * Return         : 0 on no data, 1 on measure availability
 *******************************************************************************/
int QtouchClass::available()
{
  // check if a measure is done
  if ((p_selfcap_measure_data->measurement_done_touch == 1u))
  {
    p_selfcap_measure_data->measurement_done_touch == 0u;
    return 1;
  }
  return 0;
}
/*******************************************************************************
 * Function Name  : poll
 * Description    : Polls the QTouch sensors for new measure
 * Input          : NONE
 * Return         : NONE
 *******************************************************************************/
void QtouchClass::poll()
{
  // set time flag to 1 and starting time millis()
  touch_time.time_to_measure_touch = 1;
  touch_time.current_time_ms = touch_time.current_time_ms + millis();

  // trigger a new measure
  touch_sensors_measure();
}

/*******************************************************************************
 * Function Name  : read
 * Description    : Queries the QTouch and returns new touch measure
 * Input          : sensor_id - Sensor identification
 * Return         : -1 on Error, touch measure state on Success
 *******************************************************************************/
int QtouchClass::read(int sensor_id)
{
  // checks if sensor_id exists
  if (sensor_id < DEF_SELFCAP_NUM_SENSORS)
  {
    // returns the updated sensor's state and shift it in order to be 0 or 1
    return (GET_SELFCAP_SENSOR_STATE(sensor_id)) >> sensor_id;
  }
  return -1;
}

/*******************************************************************************
 * Function Name  : setSensorsSensitivity
 * Description    : Sets all the sensors sensitivity value
 * Input          : newSens - new configure Sensitivity value
 * Return         : NONE
 *******************************************************************************/
void QtouchClass::setSensorsSensitivity(unsigned int newSens)
{
  setSensitivity(newSens);
}

/*******************************************************************************
 * Function Name  : setSensorsSensitivity
 * Description    : Sets a sensor sensitivity value
 * Input          : newSens - new configure Sensitivity value  , btn_channel - channel to apply that Sensitivity
 * Return         : NONE
 *******************************************************************************/
void QtouchClass::setSensorsSensitivity(unsigned int newSens, unsigned int btn_channel)
{
  setSensitivityChannel(newSens, btn_channel);
}

/*******************************************************************************
 * Function Name  : setSensorsHysteresis
 * Description    : Set the sensors hysteresis value
 * Input          : newHyst - new configure hysteresis value, could be:
 *                  -	HYST_50
	                  - HYST_25
	                  - HYST_12_5
	                  - HYST_6_25
	                  - MAX_HYST
 * Return         : NONE
 *******************************************************************************/
void QtouchClass::setSensorsHysteresis(hysteresis_t newHyst)
{
  setHysteresis(newHyst);
}

/*******************************************************************************
 * Function Name  : getSensorsSensitivity
 * Description    : Queries the QTouch and returns the configured Sensitivity
 *                  value
 * Input          : NONE
 * Return         : The Sensitivity value
 *******************************************************************************/
unsigned int QtouchClass::getSensorsSensitivity()
{
  return getSensitivity();
}

/*******************************************************************************
 * Function Name  : getSensorsSensitivity
 * Description    : Querys the Qtouch and returns the configured Sensitivity
 *                  value from a specific sensor
 * Input          : btn_channel - sensor's number
 * Return         : The Sensitivity value
 *******************************************************************************/

unsigned int QtouchClass::getSensorsSensitivity(unsigned int btn_channel)
{
  return getSensitivity(unsigned int btn_channel);
}

/*******************************************************************************
 * Function Name  : getSensorsHysteresis
 * Description    : Queries the QTouch and returns the configured hysteresis
 *                  value
 * Input          : NONE
 * Return         : The hysteresis value
 *******************************************************************************/
hysteresis_t QtouchClass::getSensorsHysteresis()
{
  return getHysteresis();
}

QtouchClass TOUCH;
