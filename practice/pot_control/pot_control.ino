#include <Stepper.h>

const int MAX_STEPS = 2048;
const int MAX_SPEED = 17; // max speed of motor is 17 rpm
const uint8_t POT_PIN = A0;

int pos = 0;

Stepper motor(MAX_STEPS, 8, 10, 9, 11);

void setup() {
  motor.setSpeed(MAX_SPEED);
  Serial.begin(9600);
}

void loop() {
  float pot = analogRead(POT_PIN);

  Serial.print("Pot: ");
  Serial.println(pot);

  int steps = ((pot / 501.) * MAX_STEPS) - pos;
  motor.step(steps);
  pos += steps;
}
