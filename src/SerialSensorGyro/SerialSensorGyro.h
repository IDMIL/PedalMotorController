#pragma once

#include <WiFi.h>

/**
 * SerialSensorGyro: A class that reads gyroscopic data over a UDP connection with the SerialSensor
 * app
 * @author Ian Doherty
 */
class SerialSensorGyro {
    public:
        SerialSensorGyro(WiFiUDP* udp);

        float getX();
        float getY();
        float getZ();

    private:
        union ByteFloat {
            byte b[4];
            float f;
        };

        struct SerialSensorGyroFrame {
            byte id;
            float x;
            float y;
            float z;
        };

        void readFrame();

        ByteFloat bf;
        SerialSensorGyroFrame currentFrame;
        WiFiUDP* udp;
};