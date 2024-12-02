#include "Buzzer.h"

ISR(TIMER1_COMPA_vect) {
  Buzzer::timerInterrupt();
}