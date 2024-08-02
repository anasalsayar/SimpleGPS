/***************************************************************************
 SimpleGPS_Library
 Author      : ANAS ALSAYAR
 Date        : Jul 31 - 2024
****************************************************************************/

#ifndef SimpleGPS_h
#define SimpleGPS_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class GPSLibrary {
  public:
    GPSLibrary(int rxPin, int txPin, uint32_t baudRate);
    void begin();
    void update();
    String getTime();
    String getLatitude();
    String getLongitude();

  private:
    int _rxPin;
    int _txPin;
    uint32_t _baudRate;
    SoftwareSerial _ss;
    byte _onceki, _simdiki, _depola, _counter;
    byte _saat, _dakika, _saniye, _depo[37];
    float _enlem, _enlemcm, _enlemrad, _enlemkm, _boylamcm, _boylamkm;
    void parseGPSData();
};

#endif