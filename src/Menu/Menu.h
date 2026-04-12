#pragma once

#include <LiquidCrystal.h>

class MotorInfo;

/**
 * Menu: A class for encapsulating PMC basic menu behavior
 * @author Ian Doherty
 */
class Menu {
    public:
        Menu(LiquidCrystal* lcd, MotorInfo* motor);

        /**
         * Writes the motor number to the bottom right of a 2x16 LCD screen.
         */
        void printMotorNum();

        /**
         * Clears the last print of changing information given by update().
         * All changing information is, by default, printed on the second row.
         */
        void clearLastPrint();

        /**
         * Writes non-changing menu information to the LCD.
         */
        virtual void init() { };

        /**
         * Writes changing menu information to the LCD.
         * Must be called as much as possible (i.e., in loop()) and may modify motor state.
         */
        virtual void update() { };

        /**
         * Returns whether or not an element in the menu is selected.
         * Not all menus are selectable, so this returns false by default. Selectable menus should
         * redefine this function.
         */
        virtual bool isSelected() { return false; };

    protected:
        LiquidCrystal* lcd;
        MotorInfo* motor;
        String lastPrint;
};