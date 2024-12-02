#include "Highscore.h"

// Statische Methode zum Abrufen des Highscores
int Highscore::get() {
  int result;
  EEPROM.get(0, result);
  if (result == -1) {
    result = 0;
  }
  return result;
}

// Statische Methode zum Setzen des Highscores
void Highscore::set(int highscore, bool force) {
  if (force || highscore > Highscore::get()) {
    EEPROM.put(0, highscore);
  }
}
