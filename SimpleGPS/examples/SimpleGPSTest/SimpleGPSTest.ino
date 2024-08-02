#include <SimpleGPS.h>

// Define RX and TX pins and baud rate for the GPS module
#define RX_PIN 4
#define TX_PIN 3
#define GPS_BAUD 9600

// Create a SimpleGPS object
SimpleGPS gps(RX_PIN, TX_PIN, GPS_BAUD);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the GPS module
  gps.begin();
}

void loop() {
  // Update GPS data
  gps.update();
  
  // Print the time, latitude, and longitude
  Serial.print("Time: ");
  Serial.println(gps.getTime());
  Serial.print("Latitude: ");
  Serial.println(gps.getLatitude());
  Serial.print("Longitude: ");
  Serial.println(gps.getLongitude());
  
  // Wait for a second before the next update
  delay(1000);
}
