#pragma once

#include <Joystick.h>
#include "Menu.h"

class AxisSelectMenu : public Menu {
    public:
        AxisSelectMenu(LiquidCrystal* lcd, MotorInfo* motor, Joystick* joystick);

        void init() override;
        void update() override;
        bool isSelected() override;
        
    private:
        Joystick* joystick;
        void printAxis();
};