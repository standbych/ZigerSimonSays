#include "ButtonHandler.h"

// Pin states and button variables
volatile bool ButtonHandler::buttons_is_last_button_pressed = false;
volatile Button ButtonHandler::buttons_last_button = BUTTON_COUNT;
volatile bool ButtonHandler::buttons_state[BUTTON_COUNT] = { false, false, false, false, false, false };
volatile Button ButtonHandler::buttons_play_button = BUTTON_COUNT;  // Invalid initially

// Pin definitions using enum indices
const int ButtonHandler::BUTTON_PINS[BUTTON_COUNT] = {
  2,  // BUTTON_BLUE
  8,  // BUTTON_YELLOW
  3,  // BUTTON_RED
  7,  // BUTTON_GREEN
  0,  // BUTTON_SELECT
  4   // BUTTON_START
};

// Constants for debounce delay
#define DEBOUNCE_DELAY 20

void ButtonHandler::setup() {

  bool enablePortB = false;
  bool enablePortD = false;
  
  for (int i = 0; i < BUTTON_COUNT; i++) {
    if (BUTTON_PINS[i] <= 0)
      continue;
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);  // Set up each button pin
    buttons_state[i] = digitalRead(BUTTON_PINS[i]) == LOW;
    if (BUTTON_PINS[i] == 8) {
      PCMSK0 |= (1 << PCINT0); // Maskiere Pin 8 (PCINT0 für Pin 8)
      enablePortB = true;
    }
    else {
      enablePortD = true;
      PCMSK2 |= (1 << BUTTON_PINS[i]);
    }
  }

  if (enablePortB) PCICR |= (1 << PCIE0);
  if (enablePortD) PCICR |= (1 << PCIE2);

  Serial.println("buttonhandler setup complete");
}

void ButtonHandler::debounce() {
  delay(DEBOUNCE_DELAY);
}

int ButtonHandler::readButton(int button_pin) {
  return digitalRead(button_pin);
}

void ButtonHandler::handleButtonPress(Button button) {
  buttons_state[button] = true;  // Set state to pressed
  buttons_is_last_button_pressed = true;
  buttons_last_button = button;
}

void ButtonHandler::handleButtonRelease(Button button) {
  buttons_state[button] = false;  // Set state to released
  if (buttons_last_button == button) {
    buttons_is_last_button_pressed = false;  // If the last button pressed is released
  }
  if (buttons_play_button == button) {
    buttons_play_button = BUTTON_COUNT;  // Reset play button
  }
}

bool* ButtonHandler::getButtonState() {
  return buttons_state;
}

bool ButtonHandler::isButtonPressed(Button button) {
  bool isPressed = buttons_state[button];
  return isPressed;
}

void ButtonHandler::waitForButton(Button button, bool waitForRelease) {
  while (buttons_state[button]) { delay(10); }                    // Wait until released
  while (!buttons_state[button]) { delay(10); }                   // Wait until pressed
  while (waitForRelease && buttons_state[button]) { delay(10); }  // Wait until released
}

void ButtonHandler::waitForAllRelease() {
  bool isPressed = true;
  while (isPressed) {
    isPressed = false;
    for (int i = 0; i < 6; i++) {
      if (buttons_state[i]) {
        isPressed = true;
        break;
      }
    }
  }
}

Button ButtonHandler::getPressedButton() {
  while (true) {
    for (int i = 0; i < 6; i++) {
      if (buttons_state[i])
        return i;
    }
    delay(10);
  }
}

void ButtonHandler::setPlayButton(Button button) {
  if (buttons_state[button]) {
    Serial.println("Set play button");
    buttons_play_button = button;
  } else {
    Serial.println("Set play button none");
    buttons_play_button = BUTTON_COUNT;
  }
}

bool ButtonHandler::isPlayButtonReleased() {
  return buttons_play_button == BUTTON_COUNT;
}

// Pin Change Interrupt for Buttons 4 to 7 (Red, Green, Start, Select)
void ButtonHandler::pinChangeInterrupt() {
  debounce();

  if (digitalRead(BUTTON_PINS[BUTTON_BLUE]) == LOW) {
    handleButtonPress(BUTTON_BLUE);
  } else {
    handleButtonRelease(BUTTON_BLUE);
  }

  if (digitalRead(BUTTON_PINS[BUTTON_YELLOW]) == LOW) {
    handleButtonPress(BUTTON_YELLOW);
  } else {
    handleButtonRelease(BUTTON_YELLOW);
  }

  if (digitalRead(BUTTON_PINS[BUTTON_RED]) == LOW) {
    handleButtonPress(BUTTON_RED);
  } else {
    handleButtonRelease(BUTTON_RED);
  }

  if (digitalRead(BUTTON_PINS[BUTTON_GREEN]) == LOW) {
    handleButtonPress(BUTTON_GREEN);
  } else {
    handleButtonRelease(BUTTON_GREEN);
  }

  if (digitalRead(BUTTON_PINS[BUTTON_START]) == LOW) {
    handleButtonPress(BUTTON_START);
  } else {
    handleButtonRelease(BUTTON_START);
  }

  if (digitalRead(BUTTON_PINS[BUTTON_SELECT]) == LOW) {
    handleButtonPress(BUTTON_SELECT);
  } else {
    handleButtonRelease(BUTTON_SELECT);
  }
}
