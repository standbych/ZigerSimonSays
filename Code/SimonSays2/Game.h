#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "ButtonHandler.h"
#include "Highscore.h"
#include "DisplayController.h"
#include "Buzzer.h"

#define LED_BLUE_PIN A0
#define LED_YELLOW_PIN 9
#define LED_RED_PIN 5
#define LED_GREEN_PIN 6

enum GameColor {
  COLOR_NONE,
  COLOR_BLUE,
  COLOR_YELLOW,
  COLOR_RED,
  COLOR_GREEN,
};

class Game {
public:
  // Konstruktor
  Game();

  // Setup-Methode, wird in Arduino setup() aufgerufen
  void setup();

  // Play-Methode, wird in Arduino loop() aufgerufen
  void play();

private:
  void displaySequence(String sequence);
  GameColor parseColor(char c);
  void displayColor(GameColor color, bool showOnDisplay);
  bool checkSolution(String solution);
};

#endif  // GAME_H
