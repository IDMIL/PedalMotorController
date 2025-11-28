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

static Timer t;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
