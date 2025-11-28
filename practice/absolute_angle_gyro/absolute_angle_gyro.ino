#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Sensor.h>
#include <AccelStepper.h>

#define sgn(x) ((x < 0 ? -1 : 1))

class Timer {
  public:
    Timer();
    double poll();
  private:
    double last_poll_time;
};

Timer::Timer() {
  last_poll_time = micros() / 1000000.;
}

// Returns the time elapsed in seconds since the last call to poll
double Timer::poll() {
  double current_time = micros() / 1000000.;
  double dt = current_time - last_poll_time;
  last_poll_time = current_time;

  return dt;
}

class GyroAbsoluteAngle {
  public:
    GyroAbsoluteAngle(Adafruit_L3GD20_Unified* gyro);

    void update();

    float getXAngle() { return x_angle; }
    float getYAngle() { return y_angle; }
    float getZAngle() { return z_angle; }
  private:
    Adafruit_L3GD20_Unified* gyro;
    Timer t;

    float x_angle = 0.;
    float y_angle = 0.;
    float z_angle = 0.;
};

GyroAbsoluteAngle::GyroAbsoluteAngle(Adafruit_L3GD20_Unified* gyro) :
  gyro(gyro),
  t()
{
  // Nothing here
}

// Updates the angle values for the gyroscope; this should be run for every iteration in the loop!
void GyroAbsoluteAngle::update() {
  sensors_event_t event;
  gyro->getEvent(&event);

  double dt = t.poll();

  float x_omega = event.gyro.x;
  float y_omega = event.gyro.y;
  float z_omega = event.gyro.z;
  
  x_angle += (x_omega * dt);
  y_angle += (y_omega * dt);
  z_angle += (z_omega * dt);
}

static Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
static GyroAbsoluteAngle angleTracker = GyroAbsoluteAngle(&gyro);

static const int STEPS_PER_REVOLUTION = 2048;
static AccelStepper stepper(AccelStepper::FULL4WIRE, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);

  // (15 rev / min) * (2048 steps / 1 rev) * (1 min / 60 sec) = 512 steps / sec
  float speed_steps_per_sec = 512.;
  stepper.setMaxSpeed(speed_steps_per_sec);

  gyro.enableAutoRange(true);
  gyro.begin();
}

void loop() {
  angleTracker.update();
  float z_angle = angleTracker.getZAngle();

  Serial.print("Z angle: "); Serial.println(z_angle);

  // Steps to destination: (radians / (2pi radians) * steps_per_rev)
  stepper.moveTo(z_angle / (2 * PI) * STEPS_PER_REVOLUTION);
  stepper.runToPosition();
}
