#include <AccelStepper.h>

static AccelStepper stepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 3, 4, 5, 6);

const float NEMA17_MAX_RPM = 200.0;
const int STEPS_PER_REVOLUTION = 200;
const float NEMA17_MAX_STEP_SPEED = NEMA17_MAX_RPM * STEPS_PER_REVOLUTION / 60.;

void setup() {
  stepper.setMaxSpeed(1500);
  stepper.setSpeed(750);
}

void loop() {
  // stepper.move(STEPS_PER_REVOLUTION / 100); // moving 1/100th of a revolution
  stepper.runSpeed();
}
