#include "LedMatrix.h"

CRGB LedMatrix::leds[NUM_LEDS];

void LedMatrix::setup() {
  FastLED.setBrightness(5);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  LedMatrix::clear();
  Serial.println("led matrix setup complete");
}

void LedMatrix::clear() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void LedMatrix::showArrow() {
  Serial.println("LedMatrix::showArrow");
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // Definiere die Pixel für den Pfeil (z.B. Pfeil nach oben)
  leds[LedMatrix::xyToIndex(3, 0)] = CRGB::Yellow;  // Spitze des Pfeils
  leds[LedMatrix::xyToIndex(2, 1)] = CRGB::Yellow;  // Linker Teil
  leds[LedMatrix::xyToIndex(4, 1)] = CRGB::Yellow;  // Rechter Teil
  leds[LedMatrix::xyToIndex(1, 2)] = CRGB::Yellow;  // Linker Teil
  leds[LedMatrix::xyToIndex(5, 2)] = CRGB::Yellow;  // Rechter Teil

  FastLED.show();
}

void LedMatrix::showSquare() {
  Serial.println("LedMatrix::showSquare");
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // Definiere die Pixel für das Quadrat
  for (int i = 2; i <= 5; i++) {
    leds[LedMatrix::xyToIndex(i, 2)] = CRGB::Green;
    leds[LedMatrix::xyToIndex(i, 5)] = CRGB::Green;
  }
  for (int i = 2; i <= 5; i++) {
    leds[LedMatrix::xyToIndex(2, i)] = CRGB::Green;
    leds[LedMatrix::xyToIndex(5, i)] = CRGB::Green;
  }

  FastLED.show();
}

void LedMatrix::showCircle() {
  Serial.println("LedMatrix::showCircle");
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // Definiere die Pixel für den Kreis
  leds[LedMatrix::xyToIndex(3, 1)] = CRGB::Blue;
  leds[LedMatrix::xyToIndex(4, 1)] = CRGB::Blue;
  leds[LedMatrix::xyToIndex(2, 2)] = CRGB::Blue;
  leds[LedMatrix::xyToIndex(5, 2)] = CRGB::Blue;
  leds[LedMatrix::xyToIndex(1, 3)] = CRGB::Blue;
  leds[LedMatrix::xyToIndex(6, 3)] = CRGB::Blue;
  leds[LedMatrix::xyToIndex(1, 4)] = CRGB::Blue;
  leds[LedMatrix::xyToIndex(6, 4)] = CRGB::Blue;
  leds[LedMatrix::xyToIndex(2, 5)] = CRGB::Blue;
  leds[LedMatrix::xyToIndex(5, 5)] = CRGB::Blue;
  leds[LedMatrix::xyToIndex(3, 6)] = CRGB::Blue;
  leds[LedMatrix::xyToIndex(4, 6)] = CRGB::Blue;

  FastLED.show();
}

void LedMatrix::showX() {
  Serial.println("LedMatrix::showX");

  // Setze alle LEDs auf Schwarz
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  // Definiere die Pixel für das X
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    leds[LedMatrix::xyToIndex(i, i)] = CRGB::Red;                     // Diagonale von oben links nach unten rechts
    leds[LedMatrix::xyToIndex(i, MATRIX_WIDTH - i - 1)] = CRGB::Red;  // Diagonale von oben rechts nach unten links
  }

  FastLED.show();
}

int LedMatrix::xyToIndex(int x, int y) {
  return y * MATRIX_WIDTH + x;
}
