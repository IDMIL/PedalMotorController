#pragma once

#include "Menu.h"

class StepperAngleMenu : public Menu {
    public:
        StepperAngleMenu(LiquidCrystal& lcd, MotorInfo& motor);
        
        virtual void init();
        virtual void update();
};