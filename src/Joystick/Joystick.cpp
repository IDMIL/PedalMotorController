#include "Joystick.h"

#include <Arduino.h>

Joystick::Joystick(int swPin, int xPin, int yPin) {
    this->swPin = swPin;
    this->xPin = xPin;
    this->yPin = yPin;

    pinMode(swPin, INPUT);
    digitalWrite(swPin, HIGH);
}

Joystick::Action Joystick::getCurrentAction() {
    if (digitalRead(swPin) == 0)
        return Joystick::Action::CLICK;
    
    float x = (analogRead(xPin) - 512) / 512.0f;
    float y = (analogRead(yPin) - 512) / 512.0f;

    float mag = sqrt(x * x + y * y);

    if (mag < MAG_SENSITIVITY)
        return Joystick::Action::IDLE;

    float angle = atan2(y, x); // angle in -pi to pi
    angle = (angle < 0 ? TWO_PI + angle : angle); // angle in 0 to 2pi

    if (angle < ANGLE_SENSITIVITY)
        return Joystick::Action::E;
    else if (angle < HALF_PI - ANGLE_SENSITIVITY)
        return Joystick::Action::NE;
    else if (angle < HALF_PI + ANGLE_SENSITIVITY)
        return Joystick::Action::N;
    else if (angle < PI - ANGLE_SENSITIVITY)
        return Joystick::Action::NW;
    else if (angle < PI + ANGLE_SENSITIVITY)
        return Joystick::Action::W;
    else if (angle < (3.0f * HALF_PI) - ANGLE_SENSITIVITY)
        return Joystick::Action::SW;
    else if (angle < (3.0f * HALF_PI) + ANGLE_SENSITIVITY)
        return Joystick::Action::S;
    else
        return Joystick::Action::SE;
}


std::string Joystick::actionToString(Joystick::Action action) {
    switch (action) {
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