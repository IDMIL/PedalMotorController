#pragma once

#include "Menu.h"

class StepperPositionMenu : public Menu {
    public:
        StepperPositionMenu(LiquidCrystal& lcd, MotorInfo& motor);
        
        virtual void init();
        virtual void update();
};