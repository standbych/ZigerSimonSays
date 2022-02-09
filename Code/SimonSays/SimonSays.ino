#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int redLedPin = 5;
const int redButtonPin = 3;
const int greenLedPin = 6;
const int greenButtonPin = 7;
const int blueLedPin = A0;
const int blueButtonPin = 2;
const int yellowLedPin = 9;
const int yellowButtonPin = 8;
const int startButtonPin = 4;
const int beeperPin = 10;

long highscore = 0;
bool nosound = false;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(beeperPin, OUTPUT);

  pinMode(redButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(blueButtonPin, INPUT_PULLUP);
  pinMode(yellowButtonPin, INPUT_PULLUP);
  pinMode(startButtonPin, INPUT_PULLUP);

  digitalWrite(redLedPin, HIGH);
  delay(500);
  digitalWrite(redLedPin, LOW);

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.display();
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);

  // Check for GreenButton on Startup
  if (digitalRead(greenButtonPin) == LOW) {
    nosound = true;
  }
  // Check for RedButton on Startup
  if (digitalRead(redButtonPin) == LOW) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("  Delete Highscore?");
    display.println(".-=-.-=-.-=-.-=-.-=-.");
    display.setCursor(0, 30);
    display.println("YES: Press Green");
    display.println("NO:  Press Red");
    display.display();
    delay(1000);

    long nowTime = millis();
    bool exitFlag = false;
    while (!exitFlag) {
      display.setCursor(0, 50);
      display.print(millis() - nowTime);
      display.display();
      if (digitalRead(greenButtonPin) == LOW) {
        highscore = 0;
        EEPROM.put(0, highscore);
        display.clearDisplay();
        display.setCursor(0, 30);
        display.setTextSize(3);
        display.println("Deleted");
        display.display();
        exitFlag = true;
        delay(1000);
      } else if (digitalRead(redButtonPin) == LOW) {
        display.clearDisplay();
        display.setCursor(0, 30);
        display.setTextSize(3);
        display.println("Exit");
        display.display();
        exitFlag = true;
        delay(1000);
      }
      if (millis() >= nowTime + 5000) {
        exitFlag = true;
      }
    }
  }
  EEPROM.get(0, highscore);
  display.clearDisplay();
  showSimonSaysLogo();
  showHighscore();
  if (!nosound) {
    introSound();
  }
  showPressStart();

}

// the loop function runs over and over again forever
void loop() {

  while (digitalRead(startButtonPin) == LOW) {
    playGame();
  }
}
