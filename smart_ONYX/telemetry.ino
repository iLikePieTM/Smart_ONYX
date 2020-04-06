/*
   telemetry
   Gather data from all the bike's sensors and update a CSV list
   - Designed to be called often but only updates at a set interval
   - This is to enable the use of a low passfilter while staying "real time"
   - Returns true when data has been updated

   Alex Hoppe (c) 2020
   Updated: 3/16/2020
*/

bool calculateTelemetry(String &telemetryData) {
  // Internal timekeeping
  const unsigned int TELEMETRY_INTERVAL = 500;
  static unsigned long lastCheck = 0;

  // Implement a low-pass filter for the roll
  const float ALPHA = .5;
  static int bikeRoll = 0;
  int tempBikeRoll = findRoll();
  
  // Has real data been returned or an error?
  if (tempBikeRoll != 180) {
    bikeRoll = tempBikeRoll * ALPHA + bikeRoll * (1 - ALPHA);
  }

  // Has the collection interval been reached?
  if (deltaT - lastCheck >= TELEMETRY_INTERVAL) {
    // Update the telemetry string: enclosureTemp,bikeRoll
    telemetryData = "";
    telemetryData += String(findEnclosureT());    telemetryData += ",";
    telemetryData += String(bikeRoll);

    lastCheck = deltaT;

    return true;
  }

  return false;
}


// Return the temerature of the enclosure to the nearest degree C
int findEnclosureT() {
  // If there is an error, return -99(deg)C
  float t = -99;

  if (IMU.temperatureAvailable()) {
    IMU.readTemperature(t);
  }

  return round(t);
}


// Returns the bike's roll rounded to the nearest whole number
// - Note: data can be noisy, recomend utilizing a low-pass filter
int findRoll() {
  float xAccel, yAccel, zAccel;
  // If there is an error, return 180(deg)
  float roll = 180;

  if (IMU.accelerationAvailable()) {
    // The yAccel from the IMU corrisponds to the bike's zAccel due to the mounting orentation
    IMU.readAcceleration(xAccel, zAccel, yAccel);
    roll = atan2(xAccel, sqrt(zAccel * zAccel)) * (180 / 3.1459);
  }

  return round(roll);
}
