void playGame() {
  String possibilities[] = {"r", "g", "b", "y"};
  String solution = "";
  int initialSpeedHigh = "200";
  int initialSpeedLow = "50";
  bool gameOver = false;
  randomSeed(millis());
  while (!gameOver) {
    if (!nosound) {
      nextRound();
    }
    solution += possibilities[random(4)];
    playSequence(solution, initialSpeedHigh, initialSpeedLow);
    if (!checkSolution(solution, initialSpeedHigh, initialSpeedLow)) {
      gameOver = true;
      int score = solution.length() - 1;
      showGameOver(score);
      if (score > highscore) {
        highscore = score;
        EEPROM.put(0, score);
      }

      if (!nosound) {
        gameOverSound();
      }
      showSimonSaysLogo();
      if (!nosound) {
        introSound();
      }
      showPressStart();
    }
  }
}

void playSequence(String solution, int initialSpeedHigh, int initialSpeedLow) {
  showSimonSaysLogo();
  delay(200);
  for (int i = 0; i < solution.length() ; i++) {
    String currentColor = String(solution[i]);
    showColor(currentColor);
    showPressColor(currentColor);
    delay(initialSpeedHigh);
    showColor("");
    display.clearDisplay();
    display.display();
    delay(initialSpeedLow);
  }
}
void showColor(String color)
{
  if (color == "r") digitalWrite(redLedPin, HIGH); else digitalWrite(redLedPin, LOW);
  if (color == "g") digitalWrite(greenLedPin, HIGH); else digitalWrite(greenLedPin, LOW);
  if (color == "b") digitalWrite(blueLedPin, HIGH); else digitalWrite(blueLedPin, LOW);
  if (color == "y") digitalWrite(yellowLedPin, HIGH); else digitalWrite(yellowLedPin, LOW);
}

bool checkSolution(String solution, int initialSpeedHigh, int initialSpeedLow)
{
  showPlayerSaysLogo(0);
  bool success = true;
  for (int i = 0; i < solution.length() ; i++) {
    String currentColor = String(solution[i]);
    String checkColor = "";
    bool pressed = false;
    while (!pressed) {
      checkColor = checkPress();
      if (checkColor != "x") {
        pressed = true;
      }
    }
    showColor(checkColor);
    if (checkColor == currentColor) {
      if (!nosound) {
        correctBeep();
      }

    showProgress(i + 1, solution.length());

    while (pressed) {
      checkColor = checkPress();
      if (checkColor == "x") {
        pressed = false;
      }
    }
    showColor("");

      if (solution.length() != i + 1) {
        showPlayerSaysLogo(0);
      }
      else
        showCorrect();
    } else {
      showColor("");
      showWrong();
      success = false;
      break;
    }
  }
  return success;
}
String checkPress()
{
  if (digitalRead(redButtonPin) == LOW) return "r";
  if (digitalRead(greenButtonPin) == LOW) return "g";
  if (digitalRead(blueButtonPin) == LOW) return "b";
  if (digitalRead(yellowButtonPin) == LOW) return "y";
  return "x";
}
