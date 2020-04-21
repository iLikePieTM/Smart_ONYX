# smart_ONYX: Arduino Code Overview

As mentioned in the top-level README.md, the Smart_ONYX project brings signals, sensors, and eventually IoT capabilities to the ONYX RCR. For more information, see that README.


## Getting Started

I'm going to keep this short and sweet as the code *should* be self-documenting with comments throughout. However, I would like to note that this was written for my personal use and may not be ... polished. If you would like more help getting it set up please reach out to me.

*Use it at your own risk.*


### Prerequisites

This code is written to run on an Arduino UNO WiFi Rev 2. It is mostly compatible with the Arduino UNO and other similar devices but this is not guaranteed and modifications will be necessary. If you attempt to use this code please see the **wiring diagram** included in this repository and note that modifications to the code will be necessary if you deviate from it.

### Required Libraries:
 - ```Arduino_LSM6DS3.h``` to gather data from the IMU on the WiFi Rev 2
   - **NOTE:** the current master branch of the Arduino_LSM6DS3 library *does not* support the integrated temperature sensor. I have added support to the library but (as of writing) it has not been merged. See [here](https://github.com/arduino-libraries/Arduino_LSM6DS3/pull/12).
 - ```Adafruit_NeoPixel.h``` to control of all the LEDs
 
