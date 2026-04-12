#pragma once

#define ANGLE_SENSITIVITY PI / 6.0f
#define MAG_SENSITIVITY 0.7

#include <string>

/**
 * Joystick: A class for encapsulating PMC joystick behavior
 * @author Ian Doherty
 */
class Joystick {
    public:
        Joystick(int swPin, int xPin, int yPin);

        enum class Action {
            IDLE,

            N,
            S,
            E,
            W,

            NW,
            NE,
            SE,
            SW,

            CLICK
        };

        Action getCurrentAction();
        static std::string actionToString(Action action);
    private:
        int swPin;
        int xPin;
        int yPin;
};