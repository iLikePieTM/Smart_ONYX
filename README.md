# SMART_ONYX

### An Arduino based modification platform for the ONYX RCR electric motorbike.

The ONYX RCR is an awesome bike that I've been having a lot of fun with but it lacks some modern creature comforts. Therefore, I decided to spend way to much time designing and building mods to bring the RCR into the 21st century.


### Features:
 - Integrated signal lights via NeoPixel LED strips that combine running, turn, and break signals into a clean package.
   - Mounting: The front signals are wrapped around the headlight and back signals are supported by a custom, 3D printed bracket.
 - Underglow LEDs with multiple effects and color options.
 - CAD / STL Files for the tail light and Arduino mounts in addition to a license plate mount / fender eliminator.
 - Other features in progress:
   - Sensors: currently bike roll and temperature data are collected with the Arduino UNO Wifi Rev 2 integrated IMU. The ultimate goal is to collect additional speed, acceleration, and positional (GPS) data.
   - IoT: Another future goal to utilize a cellular shield to sync the bike telemetry with an IoT service.


## Getting Started
This is not indented as a guide but I'm making all my work available to inspire others. The file structure overview and bill of materials are located bellow and if you have any questions please reach out.

### File structure:
 - **CAD:** includes the Solidworks files (and STL files when applicable) for the physical modifications.
 - **Reference_Pictures:** includes assembly pictures, a wiring diagram, and some glamour shots.
 - **smart_ONYX:** includes all the Arduino code to run the lights, sensors, etc. See it's readme for more info.

 ### Bill of Materials *(electronics)*:
 - [Arduino UNO WiFi Rev 2](https://www.digikey.com/product-detail/en/arduino/ABX00021/1050-1166-ND/9486717)
 - [NeoPixel RGBW Strip - 1m](https://www.adafruit.com/product/2837?length=1)
 - [DC/DC Buck Converter - 5V @ 3A](https://www.adafruit.com/product/1385)
 - [L4931CZ50-AP - 5.0V Voltage Regulator](https://www.digikey.com/product-detail/en/stmicroelectronics/L4931CZ50-AP/497-5838-1-ND/1506450)
 - [BK/ATC-5 - 5A Fuse](https://www.digikey.com/product-detail/en/eaton-bussmann-electrical-division/BK-ATC-5/283-2316-ND/264840)
 - [UFW1V472MHD - 4700uF @ 35v Electrolytic Capacitor](https://www.digikey.com/product-detail/en/nichicon/UFW1V472MHD/493-3182-ND/1965204)
 - Basic electronic supplies: wires, solder, etc.
