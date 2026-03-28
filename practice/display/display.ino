#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 3, 4, 5, 6);

int num = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Test");
}

void loop() {
  lcd.print("Testing...");
  
  lcd.setCursor(0, 1); // column 0 row 1
  lcd.print(num);
  lcd.print(" / 360");

  num = (num + 1) % 360;
  lcd.clear();
}
