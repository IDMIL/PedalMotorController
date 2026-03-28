#pragma once

#include "Joystick.h"
#include "Menu.h"
#include "MotorInfo.h"

class AxisSelectMenu : public Menu {
    public:
        AxisSelectMenu(LiquidCrystal& lcd, MotorInfo& motor, Joystick& joystick);

        virtual void init();
        virtual void update();
        virtual bool isSelected();
        
    private:
        Joystick& joystick;
        bool selected = false;
};