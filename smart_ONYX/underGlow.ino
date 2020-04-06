/*
   underGlow
   Controls the bike's runderglow lights during standard driving operation
   - Accepts a pointer to a glowStrip NeoPixel object and an int to chose the effect
    - 0 = default white glow; 1 = pulsing white glow; 2 = fire effect
   - Optional bool argument can be passed to turn everything off

   Alex Hoppe (c) 2020
   Updated: 4/3/2020
*/

void underGlow(Adafruit_NeoPixel *glowStrip, int effect, bool bikeOn) {
  // Is the bike on or off?
  if (bikeOn) {
    // Run through the possible underglow effects
    switch (effect) {
      case 1:   // Pulsing effect
        pulseEffect(glowStrip);
        break;

      case 2:   // Crackling fire
        fireEffect(glowStrip);
        break;

      default:  // Static glow
        glowStrip->fill(glowStrip->Color(8, 32, 0, 196), 0, NUM_GLOW_LEDS);
        break;
    }

  } else {
    glowStrip->fill(glowStrip->Color(0, 0, 0, 0), 0, NUM_GLOW_LEDS);
  }

  // Push color data to the strips
  glowStrip->show();
}

// Creates a white pulsing effect when passed a refrence to a Neopixel strip
void pulseEffect(Adafruit_NeoPixel *strip) {
  const unsigned int PULSE_INTERVAL = 4000;

  // Calculate the current magnitude of the lights bassed on the time elapsed then push to the strip
  int pulseMag = 128 + 96 * cos(deltaT * 3.1459 * 2 / PULSE_INTERVAL);
  strip->fill(strip->Color(4, 16, 0, pulseMag), 0, NUM_GLOW_LEDS);
}

// Creates a fire effect when passed a refrence to a Neopixel strip
// - Update the size of fule and deltaSpark if your strip has more than 10 pixels
void fireEffect(Adafruit_NeoPixel *strip) {
  // Define constants and timekeeping variables
  const int STRIP_LENGTH = strip->numPixels();
  static float fule[10];
  static unsigned int deltaFule[10];
  const unsigned int DELTA_UPDATE = 50;
  static unsigned long deltaBurn = 0;
  static unsigned long deltaSpark[10];
  
  // If the function has just been called, fill in the default values
  if (!deltaBurn) {
    for (int i = 0; i < STRIP_LENGTH; i++) {
      fule[i] = 1;
      deltaFule[i] = 0;
      deltaSpark[i] = deltaT;
    }
    deltaBurn = deltaT;
    randomSeed(analogRead(0));
  }

  // If the update time has passed, calculate new color values
  if (deltaT - deltaBurn >= DELTA_UPDATE) {
    int r, g, b, w;
    deltaBurn = deltaT;

    for (int i = 0; i < STRIP_LENGTH; i++) {
      // Burn the fule
      fule[i] -= DELTA_UPDATE / 1000.0;

      // Add a random spark at a random time
      if (deltaT - deltaSpark[i] >= (unsigned long)random(1000, 2000)) {
        deltaFule[i] = random(100, 2000);
        deltaSpark[i] = deltaT;
      }

      // Ensure that the sparks are applied smoothly with the deltaFule buffer
      if (deltaFule[i] > DELTA_UPDATE * 4) {
        fule[i] += DELTA_UPDATE * 4 / 1000.0;
        deltaFule[i] -= DELTA_UPDATE * 4;
      } else {
        fule[i] += deltaFule[i] / 1000.0;
        deltaFule[i] = 0;
      }

      // Ensure the fule value bounces between 0 and 3
      if (fule[i] > 3) {
        fule[i] = 3;
      } else if (fule[i] < 0) {
        fule[i] = 0;
      }

      // Calculate the new color values
      if (fule[i] < 2) {
        r = 64 + 191 * sin(fule[i] * 3.1459 / 4);
        g = 32 * sin(fule[i] * 3.1459 / 2);
        b = 0;
        w = 8 * sin(fule[i] * 3.1459 / 4);
      } else {
        r = 64 + 191 * cos((fule[i] - 2) * 3.1459 / 2);
        g = 0;
        b = 196 * sin((fule[i] - 2) * 3.1459 / 2);
        w = 8 + 118 * sin((fule[i] - 2) * 3.1459 / 2);
      }

      // Update the pixel color
      strip->setPixelColor(i, g, r, b, w);
    }
  }

}
