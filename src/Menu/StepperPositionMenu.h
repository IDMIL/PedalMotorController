#pragma once

#include "Menu.h"

class StepperPositionMenu : public Menu {
    public:
        StepperPositionMenu(LiquidCrystal* lcd, MotorInfo* motor);
        
        void init() override;
        void update() override;
        bool isSelected() override { return false; }
};