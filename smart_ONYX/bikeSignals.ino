/*
   bikeSignals
   Controls the bike's running, tail, and signal lights during standard driving operation
   - Accepts a pointer to a tailStrip and headStrip NeoPixel object
   - Optional bool argument can be passed to turn everything off

   Alex Hoppe (c) 2020
   Updated: 3/16/2020
*/

void bikeSignals(Adafruit_NeoPixel *tailStrip, Adafruit_NeoPixel *headStrip, bool bikeOn) {
  // Define Internal timekeeping
  static unsigned long brakeStartT = 0;
  static unsigned long signalStartT = 0;

  if (bikeOn) {

    // The running light should always be on and can be overwritten latter
    tailStrip->fill(tailStrip->Color(0, 0, 64, 96), 0, NUM_TAIL_LEDS);
    headStrip->fill(headStrip->Color(0, 0, 64, 96), 0, NUM_HEAD_LEDS);

    // Are the brakes being activated?
    if (digitalRead(BRAKE_SIGNAL) == HIGH) {
      flashyBrake(tailStrip, brakeStartT);
    } else {
      // If the brakes aren't on, update the time
      brakeStartT = deltaT;
    }

    // Are the turn signals on?
    if (digitalRead(LEFT_SIGNAL) == HIGH || digitalRead(RIGHT_SIGNAL) == HIGH) {
      signalSnake(tailStrip, digitalRead(LEFT_SIGNAL), signalStartT);
      signalSnake(headStrip, digitalRead(LEFT_SIGNAL), signalStartT);
    } else {
      // If the signals aren't on, update the time
      signalStartT = deltaT;
    }

  } else {
    tailStrip->fill(tailStrip->Color(0, 0, 0, 0), 0, NUM_TAIL_LEDS);
    headStrip->fill(headStrip->Color(0, 0, 0, 0), 0, NUM_HEAD_LEDS);
  }

  // Push color data to the strips
  tailStrip->show();
  headStrip->show();
}


// Flashes the brake lights when first activated then produces a stead output
void flashyBrake(Adafruit_NeoPixel *strip, unsigned long brakeStartT) {
  static const int FLASH_LENGTH = 1000;
  int redIntensity;

  // Is it in the inital flashy time?
  if (deltaT - brakeStartT <= FLASH_LENGTH) {
    redIntensity = 128 + 127 * cos((deltaT - brakeStartT) * 3.1459 * 4 / FLASH_LENGTH);
  } else {
    redIntensity = 255;
  }

  // Assigns the brake intensity to the strip
  strip->fill(strip->Color(4, redIntensity, 0, 4), 0, strip->numPixels());
}


// Creates a bi-directional snake effect when the passed a NeoPixel strip
// - When snakeMag is HIGH/1 it will flow left, else right
// - Note: it assumes the Neopixel data line is attached to the left side
void signalSnake(Adafruit_NeoPixel *strip, int snakeMag, unsigned long signalStartT) {
  static unsigned const int SIGNAL_INTERVAL = 1250;
  static unsigned long deltaSignal = 0;
  static int signalCounter = 0;

  uint32_t signalColor = strip->Color(64, 255, 0, 16);
  int signalLength = strip->numPixels();
  int startPixel;

  // Determines the start point and length of the signal for even or odd strips with left or right signals
  if (signalLength % 2) {
    signalLength = signalLength / 2;
    startPixel = signalLength;
  } else {
    signalLength = signalLength / 2 - 1;
    if (snakeMag) {
      startPixel = signalLength;
    } else {
      startPixel = signalLength + 1;
    }
  }

  // Is this a new signal event or a continuation of one?
  if (deltaSignal < signalStartT) {
    deltaSignal = signalStartT;
    signalCounter = 0;
  }

  // Ensure the animation speed is perportional to the strip length
  if (deltaT - deltaSignal >= SIGNAL_INTERVAL / signalLength) {
    if (signalCounter < signalLength) {
      signalCounter++;
    } else {
      signalCounter = 0;
    }
    // Update the time since a signal change
    deltaSignal = deltaT;
  }

  // Assigns values to the LEDs in the desired direction
  if (snakeMag == HIGH) {
    for (int i = startPixel; i >= (startPixel - signalCounter); i--) {
      strip->setPixelColor(i, signalColor);
    }
  } else {
    for (int i = startPixel; i <= (startPixel + signalCounter); i++) {
      strip->setPixelColor(i, signalColor);
    }
  }

}
