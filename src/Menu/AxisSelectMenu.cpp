#include "AxisSelectMenu.h"

AxisSelectMenu::AxisSelectMenu(LiquidCrystal& lcd, MotorInfo& motor, Joystick& joystick) : 
    Menu(lcd, motor),
    joystick(joystick)
{
}

void AxisSelectMenu::init() {
    printMotorNum();
    lcd.print("Axis Selection:");
}

void AxisSelectMenu::update() {
    if (joystick.getCurrentAction() == Joystick::Action::CLICK) 
        selected = !selected;

    if (selected) {
        lcd.blink();

        switch (joystick.getCurrentAction()) {
            case Joystick::Action::N:
                motor.axis = (MotorInfo::Axis) (((int) motor.axis + 1) % 3);
                break;
            case Joystick::Action::S:
                motor.axis = (MotorInfo::Axis) (((int) motor.axis - 1) % 3);
                break;
            default:
                break;
        }
    }
    else
        lcd.noBlink();

    String toPrint;

    switch (motor.axis) {
        case MotorInfo::Axis::X:
            toPrint = "X-Axis";
            break;
        case MotorInfo::Axis::Y:
            toPrint = "Y-Axis";
            break;
        case MotorInfo::Axis::Z:
            toPrint = "Z-Axis";
            break;
    }

    if (!toPrint.equals(lastPrint)) {
        clearLastPrint();
        lcd.print(toPrint);
        lastPrint = toPrint;
    }
}

bool AxisSelectMenu::isSelected() {
    return selected;
}