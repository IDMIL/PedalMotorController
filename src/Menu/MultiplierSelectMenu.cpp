#include "MutliplierSelectMenu.h"

MultiplierSelectMenu::MultiplierSelectMenu(LiquidCrystal& lcd, MotorInfo& motor, Joystick& joystick) : 
    Menu(lcd, motor),
    joystick(joystick)
{
}

void MultiplierSelectMenu::init() {
    printMotorNum();
    lcd.print("Multiplier:");
}
void MultiplierSelectMenu::update() {
    if (joystick.getCurrentAction() == Joystick::Action::CLICK) 
        selected = !selected;

    if (selected) {
        lcd.blink();

        switch (joystick.getCurrentAction()) {
            case Joystick::Action::N:
                selectedMultiplier = (selectedMultiplier + 1) % 9;
                motor.multiplier = multipliers[selectedMultiplier];
                break;
            case Joystick::Action::S:
                selectedMultiplier = (selectedMultiplier - 1) % 9;
                motor.multiplier = multipliers[selectedMultiplier];
                break;
            default:
                break;
        }
    }
    else
        lcd.noBlink();

    String toPrint = String(motor.multiplier) + "x";

    if (!toPrint.equals(lastPrint)) {
        clearLastPrint();
        lcd.print(toPrint);
        lastPrint = toPrint;
    }
}

bool MultiplierSelectMenu::isSelected() {
    return selected;
}