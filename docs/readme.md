# Arduino_MCHPTouch

This library allows you to read touch sensors values from the [Arduino MKR](https://store.arduino.cc/arduino-mkr-wifi-1010) boards and the [Arduino Nano 33 IoT](https://store.arduino.cc/arduino-nano-33-iot). Touch sensing is a hardware capability of the SAMD21 processor.

This library allows to configure and read capacitive touch sensors, using MicroChip Technology ([Qtouch](https://www.microchip.com/en-us/development-tools-tools-and-software/libraries-code-examples-and-more/qtouch-tools))

With this you will be able to configure the sensing of the capacitive pad by changing the distance of reading.
Also it allows to get the values with an easy and handy way.

See the bundled [examples](examples/) for usage and visit the [Microchip Developer](https://microchipdeveloper.com/touch:start) website to learn more about touch sensing.


To use this library:

```
#include <Arduino_MCHPTouch.h>
```

## Circuit

[Arduino MKR](https://store.arduino.cc/arduino-mkr-wifi-1010)
[Arduino Nano 33 IoT](https://store.arduino.cc/arduino-nano-33-iot)


## License

This library is a wrapper around the MCHPTouch library by Microchip, which is bundled in binary form in this distribution in agreement with Microchip.

> Microchip Technology Inc., provides the Microchip Touch Library software subject to the license terms contained at the link below.  By using the Microchip Touch Library, you acknowledge and agree to the terms of the license contained at the link below. [Microchip Touch Library License Agreement](Microchip%20Touch%20Library%20License%20Agreement%20-%20Arduino%20082420.pdf)

The Arduino_MCHPTouch wrapper library is distributed under the terms of the MPL-2.0 license.