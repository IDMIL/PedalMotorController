#include "MultiplierSelectMenu.h"
#include <MotorInfo.h>

MultiplierSelectMenu::MultiplierSelectMenu(LiquidCrystal* lcd, MotorInfo* motor, Joystick* joystick) : 
    Menu(lcd, motor),
    joystick(joystick)
{
}

void MultiplierSelectMenu::printMultiplier() {
    String toPrint = "x" + String(motor->multiplier / 1000) + (motor->multiplier != 0 ? "k" : "");

    if (!toPrint.equals(lastPrint)) {
        clearLastPrint();
        lcd->print(toPrint);
        lastPrint = toPrint;
    }
}

void MultiplierSelectMenu::init() {
    printMotorNum();
    lcd->print("Multiplier:");
    lastPrint = String("");
}

void MultiplierSelectMenu::update() {
    if (selected) {
        lcd->blink();

        switch (joystick->getCurrentAction()) {
            case Joystick::Action::S:
                selectedMultiplier = (selectedMultiplier + 1) % 9;
                motor->multiplier = multipliers[selectedMultiplier];
                break;
            case Joystick::Action::N:
                if (selectedMultiplier == 0)
                    selectedMultiplier = 8;
                else
                    selectedMultiplier = (selectedMultiplier - 1) % 9;
                motor->multiplier = multipliers[selectedMultiplier];
                break;
            default:
                break;
        }
    }
    else
        lcd->noBlink();

    printMultiplier();
}

bool MultiplierSelectMenu::isSelected() {
    return selected;
}