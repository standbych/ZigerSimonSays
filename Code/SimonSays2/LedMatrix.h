#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <FastLED.h>

#define NUM_LEDS 64  // Anzahl der LEDs im Streifen
#define DATA_PIN 9   // Datenpin, der mit dem DIN des Streifens verbunden ist
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8

class LedMatrix {
public:
  static void setup();
  static void clear();
  static void showArrow();
  static void showSquare();
  static void showCircle();
  static void showX();

private:
  static CRGB leds[NUM_LEDS];
  static int xyToIndex(int x, int y);
};

#endif
