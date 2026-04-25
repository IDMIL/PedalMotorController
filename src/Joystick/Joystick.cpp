#include "Joystick.h"

#include <Arduino.h>

Joystick::Joystick(int swPin, int xPin, int yPin, std::function<void()> onClick) {
    this->swPin = swPin;
    this->xPin = xPin;
    this->yPin = yPin;
    this->joystickCooldownDone = true;
    this->joystickCooldownTimer = timer_create_default();
    this->onClick = onClick;

    pinMode(swPin, INPUT);
    digitalWrite(swPin, HIGH);

    joystickCooldownTimer.every(500, this->endJoystickCooldown, (void*) this); // half second cooldown
}

void Joystick::update() {
    // still on cooldown
    if (!joystickCooldownDone) {
        joystickCooldownTimer.tick();
        currentAction = Joystick::Action::COOLDOWN;
        return;
    }

    // clicks
    if (digitalRead(swPin) == 0) {
        joystickCooldownDone = false; // start cooldown
        currentAction = Joystick::Action::CLICK; // set action to click
        if (onClick != nullptr) onClick(); // call the click callback
        return;
    }
    
    float x = (analogRead(xPin) - RESTING_X) / 512.0f;
    float y = (analogRead(yPin) - RESTING_Y) / 512.0f;

    // checking magnitude
    float mag = sqrt(x * x + y * y);

    if (mag < MAG_SENSITIVITY) {
        currentAction = Joystick::Action::IDLE; // no action has occurred, so don't cooldown the joystick
        return;
    }

    joystickCooldownDone = false; // an action has occurred at this point!

    // checking angle
    float angle = atan2(y, x); // angle in -pi to pi
    angle = (angle < 0 ? TWO_PI + angle : angle); // angle in 0 to 2pi

    if (angle < ANGLE_SENSITIVITY)
        currentAction = Joystick::Action::E;
    else if (angle < HALF_PI - ANGLE_SENSITIVITY)
        currentAction = Joystick::Action::NE;
    else if (angle < HALF_PI + ANGLE_SENSITIVITY)
        currentAction = Joystick::Action::N;
    else if (angle < PI - ANGLE_SENSITIVITY)
        currentAction = Joystick::Action::NW;
    else if (angle < PI + ANGLE_SENSITIVITY)
        currentAction = Joystick::Action::W;
    else if (angle < (3.0f * HALF_PI) - ANGLE_SENSITIVITY)
        currentAction = Joystick::Action::SW;
    else if (angle < (3.0f * HALF_PI) + ANGLE_SENSITIVITY)
        currentAction = Joystick::Action::S;
    else
        currentAction = Joystick::Action::SE;
}

Joystick::Action Joystick::getCurrentAction() {
    return currentAction;
}

bool Joystick::endJoystickCooldown(void* arg) {
    Joystick* obj = (Joystick*) arg;
    obj->joystickCooldownDone = true;
    return true;
}

std::string Joystick::actionToString(Joystick::Action action) {
    switch (action) {
        case Joystick::Action::IDLE:
            return "Idle";
        case Joystick::Action::COOLDOWN:
            return "Cooldown";
        case Joystick::Action::CLICK:
            return "Click";
        case Joystick::Action::E:
            return "East";
        case Joystick::Action::NE:
            return "Northeast";
        case Joystick::Action::N:
            return "North";
        case Joystick::Action::NW:
            return "Northwest";
        case Joystick::Action::W:
            return "West";
        case Joystick::Action::SW:
            return "Southwest";
        case Joystick::Action::S:
            return "South";
        case Joystick::Action::SE:
            return "Southeast";
    };

    return "";
}