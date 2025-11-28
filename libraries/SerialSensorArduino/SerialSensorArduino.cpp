#include "SerialSensorArduino.h"

SerialSensorArduino::SerialSensorArduino(int enable_pin, int tx_pin, int rx_pin, unsigned long baud_rate) :
    enable_pin(enable_pin),
    tx_pin(tx_pin),
    rx_pin(rx_pin),
    baud_rate(baud_rate),
    ble_serial(tx_pin, rx_pin)
{
    // Nothing here
}

void SerialSensorArduino::init() {
    // Starting data transfer
    ble_serial.begin(baud_rate);
}

// Returns a SerialSensor frame by reading from its serial connection. If not enough data is
// available yet, returns an invalid frame (valid bool = 0).
Frame SerialSensorArduino::readFrame() {
    if (ble_serial.available() >= 13) {
        byte frame_bytes[13];

        for (int i = 0; i < 13; i++)
            frame_bytes[i] = ble_serial.read();

        Frame frame;

        frame.valid = true;
        frame.id = frame_bytes[0];

        memcpy(&frame.x, &frame_bytes[1], 4);
        memcpy(&frame.y, &frame_bytes[5], 4);
        memcpy(&frame.z, &frame_bytes[9], 4);

        return frame;
    }

    // Return an invalid frame if there's no data available
    return INVALID_FRAME;
}