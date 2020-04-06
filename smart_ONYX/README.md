# Arduino Overview

I'm going to keep this short and sweet as the code *should* be self-documenting with comments throughout. However, I would like to note that this was written for my personal use and may not be... polished.

*Use it at your own risk.*

## Missilanous Things of Note:
 - This code is written to run an Arduino UNO WiFi Rev 2. It will *likely* work with the Arduino UNO and other similar devices but this is not guaranteed.
 - Required Libraries:
     - Arduino_LSM6DS3.h
         - Provides support for the IMU and temperature sensor on the WiFi Rev 2.
         - **NOTE:** the current master branch of the Arduino_LSM6DS3 library *does not* support the integrated temperature sensor. I have added support to the library but (ass of writing) it has not been merged. See [here](https://github.com/arduino-libraries/Arduino_LSM6DS3/pull/12).
 - Adafruit_NeoPixel.h
     - Allows the control of all the LEDs on the bike
 - If you attempt to use this code please see the wiring diagram included in this repository and note that modifications to the code will be necessary if you deviate from it.
