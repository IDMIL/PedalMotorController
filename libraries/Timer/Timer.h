#pragma once

class Timer {
  public:
    Timer();
    double poll();
    
  private:
    double last_poll_time;
};