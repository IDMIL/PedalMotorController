#include "Arduino.h"
#include "Timer.h"

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