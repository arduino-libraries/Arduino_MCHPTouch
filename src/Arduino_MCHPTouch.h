/*
  Copyright (c) 2020 Arduino SA

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef ARDUINO_MCHPTOUCH_H
#define ARDUINO_MCHPTOUCH_H

#include <Arduino.h>
#include "touch_api_SAMD.h"
#include "DataStreamer.h"
class QtouchClass
{

public:
  QtouchClass();
  ~QtouchClass();
  bool begin();
  void poll();
  int available();
  int read(int sensor_id);
  void setSensorsSensitivity(unsigned int newSens);
  void setTouchPad(int pad0, int pad1 = -1, int pad2 = -1, int pad3 = -1, int pad4 = -1);
  void setSensorsSensitivity(unsigned int newSens ,unsigned int btn_channel);
  void setSensorsHysteresis(hysteresis_t newHyst);
  unsigned int getSensorsSensitivity();
  hysteresis_t getSensorsHysteresis();
};

extern QtouchClass TOUCH;

#endif //ARDUINO_MCHPTOUCH_H
