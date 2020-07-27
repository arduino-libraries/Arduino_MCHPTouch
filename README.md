# MCHPTouch Library for Arduino

This library allows you to read touch sensors values from the [Arduino MKR](https://store.arduino.cc/arduino-mkr-wifi-1010) boards and the [Arduino Nano 33 IoT](https://store.arduino.cc/arduino-nano-33-iot). Touch sensing is a hardware capability of the SAMD21 processor.

```c++
#include "Arduino_MCHPTouch.h"

void setup() {
    TOUCH.begin();
}

void loop() {
    TOUCH.poll();
    if (TOUCH.available()) {
        int value = TOUCH.read(0);  // read sensor 0
    }
}
```

See the bundled [examples](examples/) for usage and visit the [Microchip Developer](https://microchipdeveloper.com/touch:start) website to learn more about touch sensing.

## License

This library is a wrapper around the MCHPTouch library by Microchip, which is bundled in binary form in this distribution.

The MCHPTouch library is distributed under the following terms:

    (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any derivatives exclusively with Microchip products. It is your responsibility to comply with third party license terms applicable to your use of third party software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.

The Arduino_MCHPTouch wrapper library is distributed under the terms of the MPL-2.0 license.
