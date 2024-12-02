#include "Buzzer.h"
#include <Arduino.h>

const int Buzzer::buzzer_Intro_Melody[] = { 262, 330, 392, 524 };
const int Buzzer::buzzer_Intro_Durations[] = { 100, 100, 100, 100 };

const int Buzzer::buzzer_Gameover_Melody[] = { 131, 124, 117, 110, 104, 98, 93, 87, 110, 87 };
const int Buzzer::buzzer_Gameover_Durations[] = { 100, 120, 140, 160, 180, 200, 220, 300, 300, 300 };

int* Buzzer::currentMelody = nullptr;
int* Buzzer::currentNoteDurations = nullptr;
int Buzzer::melodyLength = 0;
int Buzzer::noteIndex = 0;
unsigned long Buzzer::noteStartTime = 0;
volatile bool Buzzer::playingNote = false;
bool Buzzer::noSound = true;

void Buzzer::setup(bool mute) {
  pinMode(BUZZER_PIN, OUTPUT);
  noSound = mute;
  if (!noSound) {
    // Timer1 für Interrupts konfigurieren
    TCCR1A = 0;                           // Normal Mode
    TCCR1B = (1 << WGM12) | (1 << CS10);  // CTC Mode, Prescaler = 1
    OCR1A = 1599;                         // Intervall für Timer1 auf 1 ms (16 MHz / 1 Prescaler / 1600 = 1 ms)
    TIMSK1 = (1 << OCIE1A);               // Timer1 Compare Match A Interrupt aktivieren
    sei();                                // Interrupts global aktivieren
  }

  Serial.println("buzzor  setup complete");
}

void Buzzer::click() {
  if (noSound) return;
  tone(BUZZER_PIN, 2500);
  delay(5);
  noTone(BUZZER_PIN);
}

void Buzzer::quiet() {
  if (noSound) return;
  currentMelody = nullptr;
  noTone(BUZZER_PIN);
  playingNote = false;
  currentNoteDurations = nullptr;
  melodyLength = 0;
  noteIndex = 0;
}

void Buzzer::playIntro() {
  if (noSound) return;
  quiet();
  currentMelody = buzzer_Intro_Melody;
  currentNoteDurations = buzzer_Intro_Durations;
  melodyLength = sizeof(buzzer_Intro_Melody) / sizeof(buzzer_Intro_Melody[0]);
  noteIndex = 0;
}

void Buzzer::playGameOver() {
  if (noSound) return;
  quiet();
  currentMelody = buzzer_Gameover_Melody;
  currentNoteDurations = buzzer_Gameover_Durations;
  melodyLength = sizeof(buzzer_Gameover_Melody) / sizeof(buzzer_Gameover_Melody[0]);
  noteIndex = 0;
}

void Buzzer::playCorrectBeepSync() {
  if (noSound) return;
  quiet();
  playTone(1760, 100);
}

void Buzzer::playNextRoundSync() {
  if (noSound) return;
  quiet();
  for (int i = 0; i < 3; i++) {
    playTone(1760, 100);  // A5
  }
}

void Buzzer::playTone(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
  delay(duration);  // Warte die Dauer, während der Ton spielt
  noTone(BUZZER_PIN);
}

void Buzzer::timerInterrupt() {
  // Alle 1 ms wird dieser Interrupt ausgelöst
  if (currentMelody != nullptr) {
    if (playingNote) {
      // Wenn eine Note läuft, prüfe, ob die Dauer abgelaufen ist
      if (millis() - noteStartTime >= currentNoteDurations[noteIndex]) {
        // Note ist zu Ende, Lautsprecher ausschalten und zur nächsten Note übergehen
        noTone(BUZZER_PIN);
        noteIndex++;
        if (noteIndex >= melodyLength) {
          // Wenn alle Noten gespielt wurden, setze die Melodie zurück (keine Melodie läuft mehr)
          currentMelody = nullptr;  // Melodie ist zu Ende
          currentNoteDurations = nullptr;
          noteIndex = 0;  // Zurücksetzen
        }
        playingNote = false;  // Nächste Note ist bereit
      }
    } else {
      // Starte die nächste Note, wenn eine Note bereit ist
      tone(BUZZER_PIN, currentMelody[noteIndex]);
      noteStartTime = millis();  // Startzeit der Note
      playingNote = true;        // Eine Note wird gerade gespielt
    }
  }
}
