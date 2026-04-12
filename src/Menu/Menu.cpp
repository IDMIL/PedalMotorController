#include "Menu.h"
#include <MotorInfo.h>

Menu::Menu(LiquidCrystal* lcd, MotorInfo* motor) :
    lcd(lcd),
    motor(motor)
{
}

void Menu::printMotorNum() {
    String motorInfoString = "MTR" + String(motor->motorNum + 1);
    lcd->setCursor(16 - motorInfoString.length(), 1);
    lcd->print(motorInfoString);
    lcd->setCursor(0, 0);
}

void Menu::clearLastPrint() {
    lcd->setCursor(0, 1);

    for (int i = 0; i < lastPrint.length(); i++)
        lcd->print(" ");

    lcd->setCursor(0, 1);
}