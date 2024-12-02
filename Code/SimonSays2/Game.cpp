#include "Game.h"

Game::Game() {
}

void Game::setup() {

  if (ButtonHandler::isButtonPressed(BUTTON_BLUE)) {
    DisplayController::showTextS("Delete Highscore?", nullptr, "release button", nullptr, nullptr);
    ButtonHandler::waitForAllRelease();
    DisplayController::showTextS("Delete Highscore?", nullptr, "Yes  Press Red", "No   any other button", nullptr);
    Button pressed = ButtonHandler::getPressedButton();
    if (pressed == BUTTON_RED) {
      Highscore::set(0);
    }
  }

  Buzzer::playIntro();

  int highscore = Highscore::get();
  DisplayController::showTextM(("Highscore: " + String(highscore)).c_str(), nullptr, nullptr, nullptr);
  delay(1000);

  Serial.println("Game setup complete");
}

void Game::play() {
  Serial.println("Starting the game...");
  DisplayController::showTextL("   Press", "   START", nullptr);
  ButtonHandler::waitForButton(BUTTON_START, false);
  Buzzer::quiet();

  String possibilities[] = { "r", "g", "b", "y" };
  String solution = "";
  randomSeed(millis());

  int currentHighscore = Highscore::get();

  while (true) {
    Buzzer::playNextRoundSync();
    solution += possibilities[random(4)];

    DisplayController::showTextXL(" Simon", "  says...");
    delay(1000);
    displaySequence(solution);
    if (!checkSolution(solution))
      break;

    if (solution.length() > currentHighscore) {
      DisplayController::showTextL("  correct", nullptr, "HIGHSCORE !!");
      Highscore::set(solution.length() - 1);
    }
    else
      DisplayController::showTextXL(" correct", nullptr);
    delay(2000);
  }

  Buzzer::playGameOver();

  int score = solution.length() - 1;
  DisplayController::showTextL(" Game Over", (" Score: " + String(score)).c_str(), nullptr);

  delay(1000);
}

void Game::displaySequence(String sequence) {
  for (int i = 0; i < sequence.length(); i++) {
    GameColor color = parseColor(sequence[i]);
    displayColor(color, true);
    delay(500);
    displayColor(COLOR_NONE, true);
    delay(50);
  }
}
GameColor Game::parseColor(char c) {
  if (c == 'r') return COLOR_RED;
  if (c == 'g') return COLOR_GREEN;
  if (c == 'b') return COLOR_BLUE;
  if (c == 'y') return COLOR_YELLOW;
  return COLOR_NONE;
}
void Game::displayColor(GameColor color, bool showOnDisplay) {
  if (color == COLOR_RED) {
    LedMatrix::showX();
    if (showOnDisplay) DisplayController::showTextXL("  red", nullptr);
  } else if (color == COLOR_GREEN) {
    LedMatrix::showSquare();
    if (showOnDisplay) DisplayController::showTextXL(" green", nullptr);
  } else if (color == COLOR_BLUE) {
    LedMatrix::showCircle();
    if (showOnDisplay) DisplayController::showTextXL("  blue", nullptr);
  } else if (color == COLOR_YELLOW) {
    LedMatrix::showArrow();
    if (showOnDisplay) DisplayController::showTextXL(" yellow", nullptr);
  } else {
    LedMatrix::clear();
    if (showOnDisplay) DisplayController::showTextXL(nullptr, nullptr);
  }
}

bool Game::checkSolution(String solution) {
  for (int i = 0; i < solution.length(); i++) {
    DisplayController::showTextXL(" You", "  say...");
    GameColor color = COLOR_NONE;
    char colorChar = ' ';
    while (color == COLOR_NONE) {
      Button pressedButton = ButtonHandler::getPressedButton();
      if (pressedButton == BUTTON_RED) {
        color = COLOR_RED;
        colorChar = 'r';
      } else if (pressedButton == BUTTON_GREEN) {
        color = COLOR_GREEN;
        colorChar = 'g';
      } else if (pressedButton == BUTTON_BLUE) {
        color = COLOR_BLUE;
        colorChar = 'b';
      } else if (pressedButton == BUTTON_YELLOW) {
        color = COLOR_YELLOW;
        colorChar = 'y';
      }
    }
    if (solution[i] != colorChar) {
      return false;
    }

    displayColor(color, false);

    String output = " ";
    if (solution.length() > 9) output += " ";
    output += String(i + 1);
    output += " / ";
    output += String(solution.length());
    DisplayController::showTextXL(output.c_str(), nullptr);

    Buzzer::playCorrectBeepSync();
    ButtonHandler::waitForAllRelease();
    displayColor(COLOR_NONE, false);
  }
  return true;
}
