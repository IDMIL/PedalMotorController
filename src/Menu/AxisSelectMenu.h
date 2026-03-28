#pragma once

#include "Joystick.h"
#include "MotorInfo.h"

class AxisSelectMenu {
    public:
        AxisSelectMenu(LiquidCrystal& lcd, MotorInfo& motor, Joystick& joystick) : Menu(lcd, motor) {
            this->joystick = joystick;
        }

        virtual void init() {
            printMotorNum();
            lcd.print("Axis Selection:");
        }

        virtual void update() {
            lcd.setCursor(0, 1);

            if (joystick.getCurrentAction() == Joystick::Action::CLICK) 
                isSelected = !isSelected;

            if (isSelected) {
                lcd.blink();

                switch (joystick.getCurrentAction()) {
                    case Joystick::Action::N:
                        motor.axis = (motor.axis + 1) % 3;
                        break;
                    case Joystick::Action::S:
                        motor.axis = (motor.axis - 1) % 3;
                        break;
                    default:
                        break;
                }
            }
            else
                lcd.noBlink();

            switch (motor.axis) {
                case MotorInfo::Axis::X:
                    lcd.print("X-Axis");
                case MotorInfo::Axis::Y:
                    lcd.print("Y-Axis");
                case MotorInfo::Axis::Z:
                    lcd.print("Z-Axis");
            }
        }
    private:
        Joystick& joystick;
        bool isSelected = false;
}