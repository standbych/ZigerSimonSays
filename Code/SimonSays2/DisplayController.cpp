#include "DisplayController.h"

// Initialisierung der statischen Mitglieder
U8GLIB_SSD1306_128X64 DisplayController::u8g(U8G_I2C_OPT_NONE);
int DisplayController::currentPosition = -1;

// Setup-Funktion
void DisplayController::setup() {
  u8g.begin();
  Serial.println("display controller setup complete");
}

// Funktion zum Schreiben von Text mit kleiner Schrift
void DisplayController::writeLineS(const char* text) {
  currentPosition += 8;
  if (text == nullptr) return;
  u8g.setFont(u8g_font_6x12);
  u8g.drawStr(0, currentPosition, text);
}

// Funktion zum Schreiben von Text mit mittlerer Schrift
void DisplayController::writeLineM(const char* text) {
  currentPosition += 10;
  if (text == nullptr) return;
  u8g.setFont(u8g_font_8x13);
  u8g.drawStr(0, currentPosition, text);
}

// Funktion zum Schreiben von Text mit großer Schrift
void DisplayController::writeLineL(const char* text) {
  currentPosition += 14;
  if (text == nullptr) return;
  u8g.setFont(u8g_font_courB14);
  u8g.drawStr(0, currentPosition, text);
}

// Funktion zum Schreiben von Text mit sehr großer Schrift
void DisplayController::writeLineXL(const char* text) {
  currentPosition += 18;
  if (text == nullptr) return;
  u8g.setFont(u8g_font_courB18);
  u8g.drawStr(0, currentPosition, text);
}

// Funktion zum Schreiben von Text mit maximal großer Schrift
void DisplayController::writeLineXXL(const char* text) {
  currentPosition += 24;
  if (text == nullptr) return;
  u8g.setFont(u8g_font_courB24);
  u8g.drawStr(4, currentPosition, text);
}

// Funktion zum Anzeigen des Headers
void DisplayController::prepareHeader() {
  writeLineS("         MiZ");
  writeLineS(".-=-.-=-.-=-.-=-.-=-.");
}

void DisplayController::clear() {
  u8g.firstPage();
  while (u8g.nextPage())
    ;
}

// Funktion zum Anzeigen von Text mit kleiner Schrift (5 Zeilen)
void DisplayController::showTextS(const char* line1, const char* line2, const char* line3, const char* line4, const char* line5) {
  u8g.firstPage();
  do {
    currentPosition = -1;
    prepareHeader();
    if (line5 == nullptr) currentPosition += 4;
    writeLineS(line1);
    writeLineS(line2);
    writeLineS(line3);
    writeLineS(line4);
    writeLineS(line5);
  } while (u8g.nextPage());
}

// Funktion zum Anzeigen von Text mit großer Schrift (3 Zeilen)
void DisplayController::showTextM(const char* line1, const char* line2, const char* line3, const char* line4) {
  u8g.firstPage();
  do {
    currentPosition = -1;
    prepareHeader();
    writeLineM(line1);
    writeLineM(line2);
    writeLineM(line3);
    writeLineM(line4);
  } while (u8g.nextPage());
}

// Funktion zum Anzeigen von Text mit großer Schrift (3 Zeilen)
void DisplayController::showTextL(const char* line1, const char* line2, const char* line3) {
  u8g.firstPage();
  do {
    currentPosition = -1;
    prepareHeader();
    if (line3 == nullptr) currentPosition += 8;
    writeLineL(line1);
    writeLineL(line2);
    writeLineL(line3);
  } while (u8g.nextPage());
}

// Funktion zum Anzeigen von Text mit sehr großer Schrift (2 Zeilen)
void DisplayController::showTextXL(const char* line1, const char* line2) {
  u8g.firstPage();
  do {
    currentPosition = -1;
    prepareHeader();
    currentPosition += 5;
    if (line2 == nullptr)
      currentPosition += 12;
    writeLineXL(line1);
    writeLineXL(line2);
  } while (u8g.nextPage());
}

// Funktion zum Anzeigen von Text mit maximal großer Schrift (2 Zeilen)
void DisplayController::showTextXXL(const char* line1, const char* line2) {
  u8g.firstPage();
  do {
    currentPosition = -1;
    prepareHeader();
    if (line2 == nullptr) currentPosition += 11;
    writeLineXXL(line1);
    writeLineXXL(line2);
  } while (u8g.nextPage());
}
