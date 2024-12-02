#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <Arduino.h>

// Button enumeration
enum Button {
  BUTTON_BLUE = 0,
  BUTTON_YELLOW,
  BUTTON_RED,
  BUTTON_GREEN,
  BUTTON_SELECT,
  BUTTON_START,
  BUTTON_COUNT  // This will automatically hold the number of buttons
};

class ButtonHandler {
public:
  // Method declarations
  static void setup();
  static bool* getButtonState();
  static bool isButtonPressed(Button button);
  static void waitForButton(Button button, bool waitForRelease);
  static void waitForAllRelease();
  static Button getPressedButton();
  static void setPlayButton(Button button);
  static bool isPlayButtonReleased();
  static void pinChangeInterrupt();

private:
  // Pin definitions (array of button pins)
  static const int BUTTON_PINS[BUTTON_COUNT];

  // State variables
  static volatile bool buttons_is_last_button_pressed;
  static volatile Button buttons_last_button;
  static volatile bool buttons_state[BUTTON_COUNT];  // Blue, Yellow, Red, Green, Start, Select
  static volatile Button buttons_play_button;        // Play Button

  // Interrupt service routines
  static void interruptPin2();
  static void interruptPin3();
  static void debounce();
  static int readButton(int button_pin);
  static void handleButtonPress(Button button);
  static void handleButtonRelease(Button button);
};

#endif  // BUTTONHANDLER_H
