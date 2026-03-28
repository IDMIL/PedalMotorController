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
    if (digitalRead(swPin) > 0)
        return Joystick::Action::CLICK;
    
    float x = (analogRead(xPin) - 512l) / 512.0f;
    float y = (analogRead(yPin) - 512l) / 512.0f;

    float mag = sqrt(x * x + y * y);

    if (mag < MAG_SENSITIVITY)
        return Joystick::Action::IDLE;
    
    float angle = atan(y / x);

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
    else if (angle < (3.0f * PI / 2) - ANGLE_SENSITIVITY)
        return Joystick::Action::SW;
    else if (angle < (3.0f * PI / 2) + ANGLE_SENSITIVITY)
        return Joystick::Action::S;
    else
        return Joystick::Action::SE;
}