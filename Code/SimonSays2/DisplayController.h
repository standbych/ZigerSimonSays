#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <U8glib.h>
#include <Arduino.h>

class DisplayController {
public:
  // Setup-Funktion
  static void setup();

  // Funktionen zum Anzeigen von Texten auf dem Display
  static void clear();
  static void showTextS(const char* line1, const char* line2, const char* line3, const char* line4, const char* line5);
  static void showTextM(const char* line1, const char* line2, const char* line3, const char* line4);
  static void showTextL(const char* line1, const char* line2, const char* line3);
  static void showTextXL(const char* line1, const char* line2);
  static void showTextXXL(const char* line1, const char* line2);

private:
  static U8GLIB_SSD1306_128X64 display_u8g;  // Display-Objekt (statisch)
  static int display_currentPosition;        // Aktuelle Position für Textanzeige (statisch)

  // Funktionen zum Schreiben von Texten mit verschiedenen Schriftgrößen
  static void writeLineS(const char* text);
  static void writeLineM(const char* text);
  static void writeLineL(const char* text);
  static void writeLineXL(const char* text);
  static void writeLineXXL(const char* text);

  // Funktion zum Anzeigen des Headers
  static void prepareHeader();
};

#endif
