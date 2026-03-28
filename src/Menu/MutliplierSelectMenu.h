#pragma once

#include "Joystick.h"
#include "Menu.h"
#include "Menu.h"

class MultiplierSelectMenu : public Menu {
    public:
        MultiplierSelectMenu(LiquidCrystal& lcd, MotorInfo& motor, Joystick& joystick);

        virtual void init();
        virtual void update();
        virtual bool isSelected();

    private:
        Joystick& joystick;
        bool selected = false;
        int selectedMultiplier = 5; // default multiplier = 1
        long multipliers[9] = {-1000, -100, -10, -1, 0, 1, 10, 100, 1000};
};