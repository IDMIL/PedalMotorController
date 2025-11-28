#include <AccelStepper.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

// Custom library in ../libraries
// Install it by zipping the corresponding folder and going to Sketch > Include Library > Add .ZIP Library...
#include <SerialSensorArduino.h>

#define sgn(x) (x < 0 ? -1 : 1)

// HC-05 pre-configured to use 38400 baud
// See this video on how to set up and configure the HC-05:
// https://www.youtube.com/watch?v=ykgt4v7_4y4 
static const unsigned long BAUD_RATE = 38400;

static const int STEPS_PER_REVOLUTION = 200;
static AccelStepper stepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 3, 4, 5, 6);
static SerialSensorArduino bleSensor(9, 10, 11, BAUD_RATE);

// static Timer t;

void setup() {
  Serial.begin(BAUD_RATE);

  bleSensor.init();

  stepper.setMaxSpeed(1000);
  stepper.setSpeed(200);
  stepper.setCurrentPosition(0);

  // Serial.println("===EEPROM CHECK===");
  
  // Serial.print("Size: "); Serial.println(EEPROM.length());

  // // Uncomment this for the first time this program is uploaded!
  // // EEPROM.put(0, 0.0f);

  // float f = 0.;
  // EEPROM.get(0, f);
  // Serial.print("Latest float value: "); Serial.println(f);

  // Serial.println("===EEPROM CHECK===");
}

void loop() {
  Frame frame = bleSensor.readFrame();

  if (frame.valid) {
    float omega_x = frame.x;
    float omega_y = frame.y;
    float omega_z = frame.z;

    // steps/sec = (rad/sec) * (rev/rad) * (steps/rev)
    float velocity = omega_z / (2 * PI) * STEPS_PER_REVOLUTION;

    stepper.setSpeed(velocity);
    stepper.runSpeed();
  }
}
