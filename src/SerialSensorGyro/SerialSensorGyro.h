#pragma once

#include <WiFi.h>

class SerialSensorGyro {
    public:
        SerialSensorGyro(WiFiUDP udp);
        ~SerialSensorGyro();

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
        WiFiUDP& udp;
};