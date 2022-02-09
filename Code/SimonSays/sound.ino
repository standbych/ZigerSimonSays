void introSound() {
  tone(beeperPin, 262, 100);
  delay(100);
  noTone(beeperPin);
  tone(beeperPin, 330, 100);
  delay(100);
  noTone(beeperPin);
  tone(beeperPin, 392, 100);
  delay(100);
  noTone(beeperPin);
  tone(beeperPin, 524, 100);
  delay(100);
  noTone(beeperPin);
}

void nextRound() {
  tone(beeperPin, 1760, 100);
  delay(100);
  noTone(beeperPin);
  tone(beeperPin, 1760, 100);
  delay(100);
  noTone(beeperPin);
  tone(beeperPin, 1760, 100);
  delay(100);
  noTone(beeperPin);
}
void correctBeep() {
  tone(beeperPin, 1760, 100);
  delay(100);
  noTone(beeperPin);
}
void gameOverSound() {
  tone(beeperPin, 131, 200);
  delay(200);
  noTone(beeperPin);
  tone(beeperPin, 124, 200);
  delay(200);
  noTone(beeperPin);
  tone(beeperPin, 117, 200);
  delay(200);
  noTone(beeperPin);
  tone(beeperPin, 110, 200);
  delay(200);
  noTone(beeperPin);
  tone(beeperPin, 104, 200);
  delay(200);
  noTone(beeperPin);
  tone(beeperPin, 98, 200);
  delay(200);
  noTone(beeperPin);
  tone(beeperPin, 93, 200);
  delay(200);
  noTone(beeperPin);
  tone(beeperPin, 87, 200);
  delay(400);
  noTone(beeperPin);
  tone(beeperPin, 87, 400);
  delay(400);
  noTone(beeperPin);
  tone(beeperPin, 117, 800);
  delay(800);
  noTone(beeperPin);
}
