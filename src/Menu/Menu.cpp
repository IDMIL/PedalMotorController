#include "Menu.h"

Menu::Menu(LiquidCrystal& lcd, MotorInfo& motor) {
    this->lcd = lcd;
    this->motor = motor;
}

void Menu::printMotorNum() {
    String motorInfoString = "MOTOR " + String(motor.motorNum);
    lcd.setCursor(20 - motorInfoString.length(), 0);
    lcd.write(motorInfoString);
    lcd.setCursor(0, 0);
}