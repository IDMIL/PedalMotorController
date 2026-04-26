#pragma once

#include <Joystick.h>
#include "Menu.h"

class MultiplierSelectMenu : public Menu {
    public:
        MultiplierSelectMenu(LiquidCrystal* lcd, MotorInfo* motor, Joystick* joystick);

        void init() override;
        void update() override;
        bool isSelected() override;

    private:
        Joystick* joystick;
        
        int selectedMultiplier = 6; // default multiplier = 10000
        long multipliers[9] = {-1000000, -100000, -10000, -1000, 0, 1000, 10000, 100000, 1000000};

        void printMultiplier();
};