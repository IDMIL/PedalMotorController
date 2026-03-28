#pragma once

#define ANGLE_SENSITIVITY 0.25
#define MAG_SENSITIVITY 0.1

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
    private:
        int swPin;
        int xPin;
        int yPin;
}