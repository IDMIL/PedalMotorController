#include <Stepper.h>

const uint8_t X_PIN = A0;
const uint8_t Y_PIN = A1;

const int MAX_STEPS = 2048;

Stepper motor(MAX_STEPS, 11, 9, 10, 8);

int sign(float x) {
  if (x == 0) return 1;
  else return x / fabs(x);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float x_val = analogRead(X_PIN) - 512;
  float y_val = analogRead(Y_PIN) - 512;

  float mag = sqrt(pow(x_val, 2) + pow(y_val, 2));
  float dir = atan2(y_val, x_val);

  float speed = (mag / (512. * sqrt(2))) * 16.;
  float direction = sign(dir);

  if (speed > 1) {
    motor.setSpeed(speed);
    motor.step(direction * MAX_STEPS / 100.);
  }

  Serial.print("Speed: ");
  Serial.println(speed);

  Serial.print("Direction: ");
  Serial.println((direction < 0 ? "counterclockwise" : "clockwise"));
}
