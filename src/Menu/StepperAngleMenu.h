#pragma once

#include "Menu.h"

class StepperAngleMenu : public Menu {
    public:
        virtual void init() {
            printMotorNum();
            lcd.print("Stepper Angle:");
        }
        virtual void update() {
            lcd.setCursor(0, 1);
            lcd.print(String((double) motor.currentStep / (double) motor.maxSteps * 270.0f) + " / " + String(270));
        }
};