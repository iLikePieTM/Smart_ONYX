/*
   smart_ONYX
   Adding "smart" capabilities to the ONYX RCR with an Arduino.

   Alex Hoppe (c) 2020
   Updated: 4/3/2020
*/


// Libraries:
#include <Arduino_LSM6DS3.h>      // Integrated IMU
#include <Adafruit_NeoPixel.h>    // RGBW LED controll


// Global Constants:
const int RUNNING_SIGNAL = 2;     // Input pins from ONYX
const int BRAKE_SIGNAL = 3;       // - See wiring diagram
const int LEFT_SIGNAL = 4;
const int RIGHT_SIGNAL = 5;

const int TAIL_LEDS = 6;          // Neopixel output pins
const int HEAD_LEDS = 7;
const int GLOW_LEDS = 8;

const int NUM_TAIL_LEDS = 18;      // Number of LEDS in each strip
const int NUM_HEAD_LEDS = 23;
const int NUM_GLOW_LEDS = 10;

const int SIGNAL_BRIGHTNESS = 196; // Max LED brightness
const int GLOW_BRIGHTNESS = 128;


// Glabal Variables:
unsigned long deltaT = 0;
bool bikeOn = false;
String bikeTelemetry = "";


// Declare the NeoPixel strip objects (Really GRBW order)
Adafruit_NeoPixel tailStrip(NUM_TAIL_LEDS, TAIL_LEDS, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel headStrip(NUM_HEAD_LEDS, HEAD_LEDS, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel glowStrip(NUM_GLOW_LEDS, GLOW_LEDS, NEO_RGBW + NEO_KHZ800);


// Declare functions:
void bikeSignals(Adafruit_NeoPixel *tailStrip, Adafruit_NeoPixel *headStrip, bool bikeOn = true);
bool calculateTelemetry(String &telemetryData);
void underGlow(Adafruit_NeoPixel *glowStrip, int effect, bool bikeOn = true);


void setup() {
  // Start Serial for debuging
  Serial.begin(9600);

  // Define pin mogdes
  pinMode(RUNNING_SIGNAL, INPUT);
  pinMode(BRAKE_SIGNAL, INPUT);
  pinMode(RIGHT_SIGNAL, INPUT);
  pinMode(LEFT_SIGNAL, INPUT);

  // Initalize the NeoPixel Strips
  tailStrip.begin();
  tailStrip.setBrightness(SIGNAL_BRIGHTNESS);
  tailStrip.show();
  headStrip.begin();
  headStrip.setBrightness(SIGNAL_BRIGHTNESS);
  headStrip.show();
  glowStrip.begin();
  glowStrip.setBrightness(GLOW_BRIGHTNESS);
  glowStrip.show();

  // Start the IMU
  IMU.begin();
}


void loop() {
  // Grab the current elpased time
  deltaT = millis();

  // Find all the bike telemetry data
  if (calculateTelemetry(bikeTelemetry)) {
    //Serial.println(bikeTelemetry);
  }

  // Is the bike on?
  if (digitalRead(RUNNING_SIGNAL) == HIGH) {
    bikeOn = true;
    bikeSignals(&tailStrip, &headStrip);
    underGlow(&glowStrip, 2);
  } else if (bikeOn) {
    // If the bike was just turned off, save power by turning the lights off
    bikeOn = false;
    bikeSignals(&tailStrip, &headStrip, bikeOn);
    underGlow(&glowStrip, 0, bikeOn);
  }
  
}
