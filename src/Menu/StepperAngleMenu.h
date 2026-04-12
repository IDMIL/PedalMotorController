#pragma once

#include "Menu.h"

class StepperAngleMenu : public Menu {
    public:
        StepperAngleMenu(LiquidCrystal* lcd, MotorInfo* motor);
        
        void init() override;
        void update() override;
        bool isSelected() override { return false; }
};