#include "AxisSelectMenu.h"
#include <MotorInfo.h>

AxisSelectMenu::AxisSelectMenu(LiquidCrystal* lcd, MotorInfo* motor, Joystick* joystick) : 
    Menu(lcd, motor),
    joystick(joystick)
{
}

void AxisSelectMenu::printAxis() {
    String toPrint;

    switch (motor->axis) {
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
        lcd->print(toPrint);
        lastPrint = toPrint;
    }
}

void AxisSelectMenu::init() {
    printMotorNum();
    lcd->print("Axis Selection:");
    lastPrint = String("");
}

void AxisSelectMenu::update() {
    if (selected) {
        lcd->blink();

        switch (joystick->getCurrentAction()) {
            case Joystick::Action::S:
                motor->axis = (MotorInfo::Axis) (((int) motor->axis + 1) % 3);
                break;
            case Joystick::Action::N:
                if ((int) motor->axis == 0)
                    motor->axis = (MotorInfo::Axis) 2;
                else
                    motor->axis = (MotorInfo::Axis) (((int) motor->axis - 1) % 3);
                break;
            default:
                break;
        }
    }
    else
        lcd->noBlink();

    printAxis();
}

bool AxisSelectMenu::isSelected() {
    return selected;
}