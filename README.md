# SMART_ONYX

## An Arduino based modification for the ONYX RCR electric bike that adds signals, lights, sensors, and IOT* capabilities to the ONYX RCR.
**Still a work in progress...*


The ONYX RCR is an awesome bike that I've been having a lot of fun with but it lacks some modern creature comforts. Therefore, I decided to spend way to much time designing and building some mods to bring the RCR into the 21st century.

First and most important, turn signals. Buying 12v LED signals off of Amazon would be too easy so I chose an RBG, addressable LED strip to combine running, turn, and break signals into a clean package. For the front, mounting was easy, I just attached them around the headlight, but for the back, I designed a custom, 3D printed bracket to hold the LED strip (there is an alternative welded steel version included but it was never tested). For a little fun, I also added an extra strip to the underside with a couple under glow effects.

Second, sensors and IoT. This one isn't fully implemented yet but the future goal is to acquire [this](https://www.botletics.com/products/sim7000-shield) LTE + GPS Shield from Botletics and sync temperature, roll, speed, acceleration, and position data with an IoT service like Adafruit.io. The temperature and roll data are collected but, since there are no connection capabilities at the moment, nothing is done with it.

*NOTE: this is not indented as a guide but I'm making all my work available to inspire others and would encourage you to copy me shamelessly.*


## File structure:
 - **CAD:** includes the Solidworks files (and STL files when applicable) for the physical modifications.
 - **Reference_Pictures:** includes assembly pictures, a wiring diagram, and some glamour shots.
 - **smart_ONYX:** includes all the Arduino code to run the lights, sensors, etc. See it's readme for more info.

 ## Bill of Materials:
 - [Arduino UNO WiFi Rev 2](https://www.digikey.com/product-detail/en/arduino/ABX00021/1050-1166-ND/9486717)
 - [Proto-Screwshield](https://www.adafruit.com/product/196)
 - [NeoPixel RGBW Strip - 1m](https://www.adafruit.com/product/2837?length=1)
 - [DC/DC Buck Converter - 5V @ 3A](https://www.adafruit.com/product/1385)
 - [L4931CZ50-AP - 5.0V Voltage Regulator](https://www.digikey.com/product-detail/en/stmicroelectronics/L4931CZ50-AP/497-5838-1-ND/1506450)
 - [Cold Splice Wire Tap (UB) - 10 pack](https://www.adafruit.com/product/1494)
 - [3pin Waterproof Conector - 5 Pack](https://www.amazon.com/dp/B01LCV8LGA)
 - [BK/ATC-5 - 5A Fuse](https://www.digikey.com/product-detail/en/eaton-bussmann-electrical-division/BK-ATC-5/283-2316-ND/264840)
 - [UFW1V472MHD - 4700uF @ 35v Electrolytic Capacitor](https://www.digikey.com/product-detail/en/nichicon/UFW1V472MHD/493-3182-ND/1965204)
 - [RSF200JB-73-470R - 470 OHM Resistor](https://www.digikey.com/products/en?keywords=RSF200JB-73-470R)
 - [Automotive Electrical Wire Conector - Big Pack](https://www.amazon.com/dp/B07WY52N7L)
 - [Double Sided Tape - 32ft](https://www.amazon.com/dp/B00PKI7IBG) - [AL-08-18-0-C - 8" Cable Ties](https://www.digikey.com/product-detail/en/advanced-cable-ties-inc/AL-08-18-0-C/2162-AL-08-18-0-C-ND/10378818)
 - Basic electronic supplies: wires, solder, etc.
