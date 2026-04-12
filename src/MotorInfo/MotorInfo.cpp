#include "MotorInfo.h"

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

    long currentPosition = stepper.currentPosition();
    float velocity = gyroData * multiplier;
    long nextStep = currentPosition + sgn(velocity);

    if (nextStep < 0 || nextStep > maxSteps)
      stepper.setSpeed(0);
    else
      stepper.setSpeed(velocity); 

    stepper.runSpeed();
}