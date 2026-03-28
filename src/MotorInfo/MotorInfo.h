#pragma once

#include "SerialSensorGyro.h"

#include <AccelStepper.h>

/**
 * MotorInfo: A class for encapsulating PMC motor behavior & state
 * @author Ian Doherty
 */
class MotorInfo {
    public:
        enum class Axis {
            X = 0,
            Y = 1,
            Z = 2
        };

        enum class Curve {
            LINEAR = 0,
            EXPONENTIAL = 1,
            LOGARITHMIC = 2,
            QUADRATIC = 3
        };

        MotorInfo(int motorNum, AccelStepper& stepper, long maxSteps, SerialSensorGyro& ssg);
        
        /**
         * Moves the motor based on the object's state.
         */
        void move();

        int motorNum;

        AccelStepper& stepper;
        long currentStep = 0;
        long maxSteps;

        long multiplier = 1;
        Axis axis = Axis::X;
        Curve curve = Curve::LINEAR;

        SerialSensorGyro& ssg;
}