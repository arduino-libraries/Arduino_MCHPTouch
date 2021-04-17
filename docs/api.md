# MCHPTouch library

## Methods

### `QtouchClass()`

Constructor, make the instance of the object.

Already accessible by using `TOUCH` object

#### Syntax

```
QtouchClass TOUCH;
```

#### See also

* [begin()](#begin)
* [poll()](#poll)


### `begin()`

Initializes Qtouch sensors

#### Returns
`true` in success, `false` if it fails.

#### Syntax

```
TOUCH.begin()
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

Polls the qotuch sensors for new measure.

#### Syntax

```
TOUCH.poll();
```

#### See also

* [available()](#available)
* [read()](#read)

### `read()`

Querys the Qtouch and returns new touch measure.

##### Syntax

```
TOUCH.read(sensor_id)
```
#### Parameters

* sensor_id : Sensor identificator

##### Returns
0  - not activated
1  - activated
-1 - not found

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

Sets all the sensors sensitivity value, or to a specific sensor's.

#### Syntax

```
TOUCH.setSensorSensitivty()
//TOUCH.setSensorSensitivty(btn_Channel, newSens)
```

#### Parameters

* (optional) btn_channel : sensor's number, to change only that sensitivity
* newSens : new sensitivity  from 3 to 100

#### See also

* [getSensorsSensitivity()](#getSensorsSensitivity)
* [setSensorsHysteresis()](#setSensorsHysteresis)

### `getSensorsSensitivity()`

Querys the Qtouch and returns the configured Sensitivity, or from a specific sensor's
#### Syntax

```
TOUCH.getSensorsSensitivity()
```

#### Parameters

* (optional) btn_channel : sensor's number, to get only that sensitivity

#### See also

* [setSensorsSensitivity()](#setSensorsSensitivity)

### `setSensorsSensitivity()`

Sets all the sensors sensitivity value, or to a specific sensor's.

#### Syntax

```
TOUCH.setSensorSensitivty()
//TOUCH.setSensorSensitivty(btn_Channel, newSens)
```

#### Parameters

* (optional) btn_channel : sensor's number, to change only that sensitivity
* newSens : new sensitivity  from 3 to 100

#### See also

* [getSensorsSensitivity()](#getSensorsSensitivity)
* [setSensorsHysteresis()](#setSensorsHysteresis)


### `getSensorsHysteresis()`

Querys the Qtouch and returns the configured hysteresis

#### Syntax

```
TOUCH.getSensorsHysteresis()
```

#### Returns

Hysteresis

#### See also

* [setSensorsSensitivity()](#setSensorsSensitivity)


### `setSensorsHysteresis()`

Querys the Qtouch and returns the configured hysteresis

#### Syntax

```
TOUCH.setSensorsHysteresis(newHyst)
```

#### Parameteres

newHyst:
    - HYST_50
    - HYST_25
    - HYST_12_5
    - HYST_6_25
    - MAX_HYST

#### See also

* [getSensorsHysteresis()](#getSensorsHysteresis)
* [setSensorsSensitivity()](#setSensorsSensitivity)
