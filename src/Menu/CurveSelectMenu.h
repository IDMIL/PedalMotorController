#pragma once

#include "Joystick.h"
#include "Menu.h"
#include "MotorInfo.h"

class CurveSelectMenu : public Menu {
    public:
        CurveSelectMenu(LiquidCrystal& lcd, MotorInfo& motor, Joystick& joystick);

        virtual void init();
        virtual void update();
        virtual bool isSelected();
        
    private:
        Joystick& joystick;
        bool selected = false;
};