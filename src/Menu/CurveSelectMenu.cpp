#include "CurveSelectMenu.h"
#include <MotorInfo.h>

CurveSelectMenu::CurveSelectMenu(LiquidCrystal* lcd, MotorInfo* motor, Joystick* joystick) : 
    Menu(lcd, motor),
    joystick(joystick)
{
}

void CurveSelectMenu::printCurve() {
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
        lcd->print(toPrint.c_str());
        lastPrint = toPrint;
    }
}

void CurveSelectMenu::init() {
    printMotorNum();
    lcd->print("Curve Selection:");
    lastPrint = String("");
}

void CurveSelectMenu::update() {
    if (selected) {
        lcd->blink();

        switch (joystick->getCurrentAction()) {
            case Joystick::Action::S:
                motor->curve = (MotorInfo::Curve) (((int) motor->curve + 1) % 4);
                break;
            case Joystick::Action::N:
                if ((int) motor->curve == 0)
                    motor->curve = (MotorInfo::Curve) 3;
                else
                    motor->curve = (MotorInfo::Curve) (((int) motor->curve - 1) % 4);
                break;
            default:
                break;
        }
    }
    else
        lcd->noBlink();

    printCurve();
}

bool CurveSelectMenu::isSelected() {
    return selected;
}