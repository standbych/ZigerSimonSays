#ifndef BUZZER_H
#define BUZZER_H

#define BUZZER_PIN 10  // Buzzer an Pin 10

class Buzzer {
public:
  static void setup(bool noSound);
  static void click();
  static void quiet();
  static void playIntro();
  static void playGameOver();
  static void playCorrectBeepSync();
  static void playNextRoundSync();

  static void timerInterrupt();

private:
  static const int buzzer_Intro_Melody[];
  static const int buzzer_Intro_Durations[];

  static const int buzzer_Gameover_Melody[];
  static const int buzzer_Gameover_Durations[];

  static int* currentMelody;
  static int* currentNoteDurations;
  static int melodyLength;
  static int noteIndex;
  static unsigned long noteStartTime;
  static volatile bool playingNote;
  static bool noSound;

  static void playTone(int frequency, int duration);
};

#endif
