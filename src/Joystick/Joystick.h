#pragma once

#define ANGLE_SENSITIVITY PI / 6.0f
#define MAG_SENSITIVITY 0.2

#define RESTING_X 755
#define RESTING_Y 730

#include <arduino-timer.h>

#include <functional>
#include <string>

/**
 * Joystick: A class for encapsulating PMC joystick behavior
 * @author Ian Doherty
 */
class Joystick {
    public:
        Joystick(int swPin, int xPin, int yPin, std::function<void()> onClick = nullptr);

        // Enum representing the different states the joystick can be in at any given time
        enum class Action {
            IDLE,
            COOLDOWN,

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

        // Reads from the joystick and determines if an action has occurred
        void update();

        // Returns the most recent action found from update
        Action getCurrentAction();

        // Converts the action enum to a human-readable string
        static std::string actionToString(Action action);

        // Callback for joystick clicks
        std::function<void()> onClick; 

    private:
        // Joystick pins
        int swPin;
        int xPin;
        int yPin;
        
        // Most recent action from calling update
        Action currentAction = Action::IDLE;

        // Cooldown logic
        bool joystickCooldownDone;
        Timer<> joystickCooldownTimer;
        static bool endJoystickCooldown(void* arg);
};