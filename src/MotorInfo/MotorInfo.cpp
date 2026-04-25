#include "MotorInfo.h"

#include <Arduino.h>

#define sgn(x) (x < 0 ? -1 : 1)

MotorInfo::MotorInfo(int motorNum, AccelStepper stepper, long maxSteps, SerialSensorGyro* ssg, LiquidCrystal* lcd, Joystick* joystick) :
    motorNum(motorNum),
    stepper(stepper),
    maxSteps(maxSteps),
    ssg(ssg),
    lcd(lcd),
    joystick(joystick),
    stepperPositionMenu(lcd, this), 
    stepperAngleMenu(lcd, this), 
    axisSelectMenu(lcd, this, joystick), 
    multiplierSelectMenu(lcd, this, joystick), 
    curveSelectMenu(lcd, this, joystick),
    menus{ &stepperPositionMenu, &stepperAngleMenu, &axisSelectMenu, &multiplierSelectMenu, &curveSelectMenu }
{
}

void MotorInfo::run() {
    float gyroData = 0.0f;

    switch (axis) {
        case MotorInfo::Axis::X:
            gyroData = ssg->getX();
            break;
        case MotorInfo::Axis::Y:
            gyroData = ssg->getY();
            break;
        case MotorInfo::Axis::Z:
            gyroData = ssg->getZ();
            break;
    }

    double velocity = gyroData * multiplier;
    currentStep = stepper.currentPosition();

    switch (curve) {
        case Curve::LINEAR:
            velocity = velocity;
            break;
        case Curve::EXPONENTIAL:
            velocity = exp(gyroData); // omitting multiplier, since this (obviously...) grows really fast!
            break;
        case Curve::LOGARITHMIC:
            if (velocity != 0) velocity = sgn(velocity) * log(abs(velocity));
            break;
        case Curve::QUADRATIC:
            velocity = pow(velocity, 2);
            break;
    }

    stepper.setSpeed(velocity); 

    stepper.runSpeed();
}