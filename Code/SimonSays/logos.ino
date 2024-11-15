void showGameOver(int points)    {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("         MiZ");
  display.println(".-=-.-=-.-=-.-=-.-=-.");
  display.setCursor(0, 16);
  display.setTextSize(2);
  display.println("Game over!");
  display.println("");
  display.print(points);
  display.print(" points");
  display.display();
}
void showCorrect()    {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("         MiZ");
  display.println(".-=-.-=-.-=-.-=-.-=-.");
  display.setCursor(0, 16);
  display.setTextSize(3);
  display.println("Correct");
  display.display();
  delay(400);
}
void showWrong()    {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("         MiZ");
  display.println(".-=-.-=-.-=-.-=-.-=-.");
  display.setCursor(0, 16);
  display.setTextSize(3);
  display.println("Wrong!");
  display.display();
  delay(400);
}
void showSimonSaysLogo()    {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("         MiZ");
  display.println(".-=-.-=-.-=-.-=-.-=-.");
  display.setCursor(0, 16);
  display.setTextSize(2);
  display.println("Simon");
  display.println("says...");
  display.display();
  delay(1000);
}
void showPlayerSaysLogo(int delaytime)    {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("         MiZ");
  display.println(".-=-.-=-.-=-.-=-.-=-.");
  display.setCursor(0, 16);
  display.setTextSize(2);
  display.println("You");
  display.println("say...");
  display.display();
  delay(delaytime);
}
void showHighscore()    {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("         MiZ");
  display.println(".-=-.-=-.-=-.-=-.-=-.");
  display.setCursor(0, 16);
  display.setTextSize(2);
  display.println("Highscore:");
  display.println("");
  display.println(highscore);
  display.display();
  delay(1000);
}
void showProgress(int current, int max) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("         MiZ");
  display.println(".-=-.-=-.-=-.-=-.-=-.");
  display.setCursor(0, 16);
  display.setTextSize(2);
  if (max > 9)
    display.print(" ");
  else
    display.print("  ");
  display.print(current);
  display.print(" / ");
  display.println(max);
  display.display();
}
void showPressStart()    {
  display.clearDisplay();
  display.setCursor(0, 16);
  display.setTextSize(2);
  display.println("   Press  ");
  display.println("   START  ");
  display.display();
}
void showPressColor(String c)    {
  display.clearDisplay();
  display.setCursor(0, 16);
  display.setTextSize(3);
  String cLoc = "";
  if (c == "r") {
    cLoc = "  red";
  } else   if (c == "g") {
    cLoc = " green";
  } else   if (c == "b") {
    cLoc = " blue";
  } else   if (c == "y") {
    cLoc = "yellow";
  }
  display.println(cLoc);
  display.display();
}
