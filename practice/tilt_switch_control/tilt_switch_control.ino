#include <Stepper.h>

const int MAX_STEPS = 2048;
const uint8_t TILT_PIN = 2;

Stepper motor(MAX_STEPS, 11, 9, 10, 8);

int sign(float x) {
  if (x == 0) return 1;
  else return x / fabs(x);
}

void setup() {
  digitalWrite(TILT_PIN, HIGH);
  Serial.begin(9600);
}

void loop() {
  float tilt = digitalRead(TILT_PIN);
  Serial.print("Tilt: ");
  Serial.println(tilt);

  // if (speed > 1) {
  //   motor.setSpeed(speed);
  //   motor.step(MAX_STEPS / 100.);
  // }
}
