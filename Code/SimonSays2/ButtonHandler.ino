#include "ButtonHandler.h"  // Header-Datei einbinden

ISR(PCINT2_vect) {
  // Port D
  ButtonHandler::pinChangeInterrupt();
}

ISR(PCINT0_vect) {
  // Port B
  ButtonHandler::pinChangeInterrupt();
}