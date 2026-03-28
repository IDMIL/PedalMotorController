#pragma once

#include "Menu.h"

class StepperPositionMenu : public Menu {
    public:
        virtual void init() {
            printMotorNum();
            lcd.print("Stepper Position:");
        }
        virtual void update() {
            lcd.setCursor(0, 1);
            lcd.print(String(motor.currentStep) + " / " + String(motor.maxSteps));
        }
};