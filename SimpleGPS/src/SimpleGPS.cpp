/***************************************************************************
 SimpleGPS_Library
 Author      : ANAS ALSAYAR
 Date        : Jul 31 - 2024
****************************************************************************/


#include "SimpleGPS.h"

SimpleGPS::SimpleGPS(int rxPin, int txPin, uint32_t baudRate)
  : _rxPin(rxPin), _txPin(txPin), _baudRate(baudRate), _ss(rxPin, txPin) {}

void SimpleGPS::begin() {
  Serial.begin(9600); // serial1
  _ss.begin(_baudRate);
  if (_ss.available())
    _onceki = _ss.read();
}

void SimpleGPS::update() {
  if (_ss.available()) { // serial1
    _simdiki = _ss.read();
    if (_depola == 0) {
      if (_onceki == 71 && _simdiki == 65) {
        _counter = 37;
        _depola = 1;
      } else {
        _onceki = _simdiki;
      }
    } else {
      _depo[37 - _counter] = _simdiki;
      _counter--;
      if (_counter == 0) {
        _depola = 0;
        parseGPSData();
      }
    }
  }
}

void SimpleGPS::parseGPSData() {
  _saat = 10 * (_depo[1] - 48) + _depo[2] - 48 + 3;
  _dakika = 10 * (_depo[3] - 48) + _depo[4] - 48;
  _saniye = 10 * (_depo[5] - 48) + _depo[6] - 48;

  _enlem = float((10 * (_depo[11] - 48) + _depo[12] - 48) * 6000000 +
                (_depo[13] - 48) * 1000000 + (_depo[14] - 48) * 100000 +
                (_depo[16] - 48) * 10000 + (_depo[17] - 48) * 1000 +
                (_depo[18] - 48) * 100 + (_depo[19] - 48) * 10 +
                _depo[20] - 48);
  _enlemrad = _enlem * 3.1415 / 1080000000.0;
  _enlemcm = _enlem * 1.852;
  _boylamcm = float((100 * (_depo[24] - 48) + 10 * (_depo[25] - 48) +
                    _depo[26] - 48) * 600000
