#include "CurveSelectMenu.h"
#include <MotorInfo.h>

CurveSelectMenu::CurveSelectMenu(LiquidCrystal* lcd, MotorInfo* motor, Joystick* joystick) : 
    Menu(lcd, motor),
    joystick(joystick)
{
}

void CurveSelectMenu::init() {
    printMotorNum();
    lcd->print("Curve Selection:");
}

void CurveSelectMenu::update() {
    if (joystick->getCurrentAction() == Joystick::Action::CLICK) 
        selected = !selected;

    if (selected) {
        lcd->blink();

        switch (joystick->getCurrentAction()) {
            case Joystick::Action::N:
                motor->curve = (MotorInfo::Curve) (((int) motor->curve + 1) % 4);
                break;
            case Joystick::Action::S:
                motor->curve = (MotorInfo::Curve) (((int) motor->curve - 1) % 4);
                break;
            default:
                break;
        }
    }
    else
        lcd->noBlink();

    String toPrint;

    switch (motor->curve) {
        case MotorInfo::Curve::LINEAR:
            toPrint = "Linear";
            break;
        case MotorInfo::Curve::EXPONENTIAL:
            toPrint = "Exponential";
            break;
        case MotorInfo::Curve::LOGARITHMIC:
            toPrint = "Logarithmic";
            break;
        case MotorInfo::Curve::QUADRATIC:
            toPrint = "Quadratic";
            break;
    }

    if (!toPrint.equals(lastPrint)) {
        clearLastPrint();
        lcd->print(toPrint);
        lastPrint = toPrint;
    }
}

bool CurveSelectMenu::isSelected() {
    return selected;
}