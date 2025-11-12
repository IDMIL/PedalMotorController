#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Sensor.h>
#include <AccelStepper.h>

static Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

static const int STEPS_PER_REVOLUTION = 2048;
static AccelStepper stepper(AccelStepper::FULL4WIRE, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);

  stepper.setMaxSpeed(1000);

  gyro.enableAutoRange(true);
  gyro.begin();
}

void loop() {
  sensors_event_t event;
  gyro.getEvent(&event);

  float z_angular_velocity = event.gyro.z;

  // steps/sec = (rad/sec) * (rev/rad) * (steps/rev)
  float speed = z_angular_velocity / (2 * PI) * STEPS_PER_REVOLUTION;

  Serial.print("Speed (steps/sec): "); Serial.println(speed);

  stepper.setSpeed(speed);
  stepper.runSpeed();
}
