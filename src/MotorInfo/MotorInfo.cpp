#include "MotorInfo.h"

#define sgn(x) (x < 0 ? -1 : 1)

MotorInfo::MotorInfo(int motorNum, AccelStepper stepper, long maxSteps, SerialSensorGyro& ssg) :
    motorNum(motorNum),
    stepper(stepper),
    maxSteps(maxSteps),
    ssg(ssg)
{
}

void MotorInfo::run() {
    float gyroData = 0.0f;

    switch (axis) {
        case MotorInfo::Axis::X:
            gyroData = ssg.getX();
            break;
        case MotorInfo::Axis::Y:
            gyroData = ssg.getY();
            break;
        case MotorInfo::Axis::Z:
            gyroData = ssg.getZ();
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