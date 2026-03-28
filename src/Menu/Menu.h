#pragma once

#include "MotorInfo.h"

#include <LiquidCrystal.h>

/**
 * Menu: A class for encapsulating PMC basic menu behavior
 * @author Ian Doherty
 */
class Menu {
    public:
        Menu(LiquidCrystal& lcd, MotorInfo& motor);

        /**
         * Writes the motor number to the top right of a 2x20 LCD screen.
         */
        void printMotorNum();

        /**
         * Writes non-changing menu information to the LCD.
         */
        virtual void init() = 0;

        /**
         * Writes changing menu information to the LCD.
         * Must be called as much as possible (i.e., in loop()).
         */
        virtual void update() = 0;

    private:
        LiquidCrystal& lcd;
        MotorInfo& motor;
};