#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <EEPROM.h>

class Highscore {
public:
  // Statische Methoden zum Abrufen und Setzen des Highscores
  static int get();
  static void set(int highscore, bool force);
};

#endif  // HIGHSCORE_H
