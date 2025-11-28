#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

// Default SerialSensor frame for gyroscopic data, plus a bool for validity
struct Frame {
    bool valid;

    byte id;
    float x;
    float y;
    float z;
};

const Frame INVALID_FRAME = {
    false,
    0,
    0.0,
    0.0,
    0.0
};

class SerialSensorArduino {
    public:
        SerialSensorArduino(int enable_pin = 9, int tx_pin = 10, int rx_pin = 11, unsigned long baud_rate = 38400);
        void init();
        Frame readFrame();

    private:
        float getFloatFromBytes(byte arr[], int idx);

        int enable_pin;
        int tx_pin;
        int rx_pin;
        unsigned long baud_rate;

        SoftwareSerial ble_serial;
};  