/*
  Arduino_MCHPTouch - Sensor data read Example
  This example shows how to configure and read data
  from touch sensors bottons on MKR IoT Carrier and
  prints updates to the Serial Monitor.

  The circuit:
  - Arduino MKR baord;
  - MKR IoT carrier.

  This example code is in the public domain.
*/
#include "Arduino_MCHPTouch.h"

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  // Qtouch initialization
  if (!TOUCH.begin())
  {
    Serial.println("Error in sensors initialization!");
    while (1)
      ;
  }
  Serial.println("Touch initialization Done!");
}

void loop()
{
  // polling the sensor for new measure
  TOUCH.poll();

  // Checks if new data are available
  if (TOUCH.available())
  {
    //reads senseors
    Serial.print("Sensor 1 status: ");
    Serial.println(TOUCH.read(0));
    Serial.print("Sensor 2 status: ");
    Serial.println(TOUCH.read(1));
    Serial.print("Sensor 3 status: ");
    Serial.println(TOUCH.read(2));
    Serial.print("Sensor 4 status: ");
    Serial.println(TOUCH.read(3));
    Serial.print("Sensor 5 status: ");
    Serial.println(TOUCH.read(4));
    Serial.println();
  }
  delay(100);
}