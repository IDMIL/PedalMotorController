#include "Menu.h"

Menu::Menu(LiquidCrystal& lcd, MotorInfo& motor) :
    lcd(lcd),
    motor(motor)
{
}

void Menu::printMotorNum() {
    String motorInfoString = "MOTOR " + String(motor.motorNum + 1);
    lcd.setCursor(20 - motorInfoString.length(), 0);
    lcd.print(motorInfoString);
    lcd.setCursor(0, 0);
}

void Menu::init() {
    // nothing
}

void Menu::update() {
    // nothing
}

void Menu::clearLastPrint() {
    lcd.setCursor(0, 1);

    for (int i = 0; i < lastPrint.length(); i++)
        lcd.print(" ");

    lcd.setCursor(0, 1);
}

bool Menu::isSelected() {
    return false;
}