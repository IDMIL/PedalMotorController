#pragma once

#include "Joystick.h"
#include "Menu.h"

class MultiplierSelectMenu {
    public:
        MultiplierSelectMenu(LiquidCrystal& lcd, MotorInfo& motor, Joystick& joystick) : Menu(lcd, motor) {
            this->joystick = joystick;
        }

        virtual void init() {
            printMotorNum();
            lcd.print("Multiplier:");
        }
        virtual void update() {
            lcd.setCursor(0, 1);

            if (joystick.getCurrentAction() == Joystick::Action::CLICK) 
                isSelected = !isSelected;

            if (isSelected) {
                lcd.blink();

                switch (joystick.getCurrentAction()) {
                    case Joystick::Action::N:
                        selected = (selected + 1) % 9;
                        motor.multiplier = multipliers[selected];
                        break;
                    case Joystick::Action::S:
                        selected = (selected - 1) % 9;
                        motor.multiplier = multipliers[selected];
                        break;
                    default:
                        break;
                }
            }
            else
                lcd.noBlink();

            lcd.print(String(motor.multiplier) + "x");
        }

    private:
        Joystick& joystick;
        bool isSelected = false;
        long multipliers[] = {-1000, -100, -10, -1, 0, 1, 10, 100, 1000};
        int selected = 5; // default multiplier = 1
};