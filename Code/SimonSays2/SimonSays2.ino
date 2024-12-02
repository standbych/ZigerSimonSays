#include "ButtonHandler.h"
#include "Highscore.h"
#include "LedMatrix.h"
#include "DisplayController.h"
#include "Buzzer.h"
#include "Game.h"

Game game;

void setup() {
  Serial.begin(9600);

  DisplayController::setup();
  LedMatrix::setup();
  ButtonHandler::setup();
  Buzzer::setup(ButtonHandler::isButtonPressed(BUTTON_GREEN));

  game.setup();
}

void loop() {
  game.play();
}