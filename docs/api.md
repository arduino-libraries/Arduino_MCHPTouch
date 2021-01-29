# Servo library

## Methods

### `QtouchClass()`

Constructor, make the instance of the object.

Already accessible by using `TOUCH` object

#### Syntax

```
QtouchClass TOUCH;
```

#### See also

* [begim()](#begin)
* [poll()](#poll)


### `begin()`

Initializes Qtouch sensors

#### Returns
`true` in success, `false` if it fails.

#### Syntax

```
if(TOUCH.begin()){
    // Everything OK
}else{
    // Failure
}
```

#### Example

```
#include <Arduino_MCHPTouch.h> 

void setup() 
{
    if(TOUCH.begin()){
        // Everything OK
    }else{
        // Failure
    }
} 

void loop() {} 
```

#### See also

* [poll()](#attached)
* [read()](#read)

### `available()`

Checks for new values availability

#### Syntax

```
TOUCH.available();
```

#### Returns
  0 on no data, 1 on measure availability

### `poll()`

Updates the status of each capacitive sensor, it saves the values to be used later.

#### Syntax

```
TOUCH.poll();
```

#### See also

* [available()](#available)
* [read()](#read)

### `read()`

Gets the `sensor_id` state.

##### Syntax

´´´
TOUCH.read(sensor_id)
´´´

##### Returns
0  - not activated
1  - activated
-1 - not found

#### Parameters

* sensor_id : number of the attached sensor

#### Example

```
#include "Arduino_MCHPTouch.h"

void setup()
{
  Serial.begin(9600);

  // Qtouch initialization
  if (!TOUCH.begin())
  {
    Serial.println("Error in sensors initialization!");
    while (1);
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
```

#### See also

* [read()](#read)
* [poll()](#poll)


### `setSensorsSensitivity()`

#### Syntax

´´´
TOUCH.setSensorSensitivty()
//TOUCH.setSensorSensitivty(btn_Channel, newSens)
´´´

#### Parameters

* (optional) btn_channel : sensor's number, to change only that sensitivity
* newSens : new sensitivity  from 3 to 100

#### See also

* [getSensorsSensitivity()](#getSensorsSensitivity)

### `getSensorsSensitivity()`

#### Syntax

´´´
TOUCH.getSensorsSensitivity()
´´´

#### Parameters

* (optional) btn_channel : sensor's number, to get only that sensitivity

#### See also

* [setSensorsSensitivity()](#setSensorsSensitivity)