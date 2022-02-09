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
      long score = solution.length();
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
    if (currentColor == "r") {
      digitalWrite(redLedPin, HIGH);
    } else if (currentColor == "g") {
      digitalWrite(greenLedPin, HIGH);
    } else if (currentColor == "b") {
      digitalWrite(blueLedPin, HIGH);
    } else if (currentColor == "y") {
      digitalWrite(yellowLedPin, HIGH);
    }
    showPressColor(currentColor);
    delay(initialSpeedHigh);
    if (currentColor == "r") {
      digitalWrite(redLedPin, LOW);
    } else if (currentColor == "g") {
      digitalWrite(greenLedPin, LOW);
    } else if (currentColor == "b") {
      digitalWrite(blueLedPin, LOW);
    } else if (currentColor == "y") {
      digitalWrite(yellowLedPin, LOW);
    }
    display.clearDisplay();
    display.display();
    delay(initialSpeedLow);
  }
}
bool checkSolution(String solution, int initialSpeedHigh, int initialSpeedLow) {
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
    if (checkColor == currentColor) {
      if (!nosound) {
        correctBeep();
      }
      showCorrect();
      if (solution.length() != i + 1) {
        showPlayerSaysLogo(0);
      }
    } else {
      showWrong();
      success = false;
      break;
    }
  }
  return success;
}
String checkPress() {
  if (digitalRead(redButtonPin) == LOW) {
    return "r";
  } else if (digitalRead(greenButtonPin) == LOW) {
    return "g";
  } else if (digitalRead(blueButtonPin) == LOW) {
    return "b";
  } else if (digitalRead(yellowButtonPin) == LOW) {
    return "y";
  } else {
    return "x";
  }
}
