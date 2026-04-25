#pragma once

#include <Joystick.h>
#include "Menu.h"

class CurveSelectMenu : public Menu {
    public:
        CurveSelectMenu(LiquidCrystal* lcd, MotorInfo* motor, Joystick* joystick);

        void init() override;
        void update() override;
        bool isSelected() override;
        
    private:
        Joystick* joystick;
        void printCurve();
};