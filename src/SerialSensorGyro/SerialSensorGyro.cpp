#include "SerialSensorGyro.h"

SerialSensorGyro::SerialSensorGyro(WiFiUDP& udp) {
    this.udp = udp;
}

SerialSensorGyro::~SerialSensorGyro() {
    delete this.bf;
    delete this.currentFrame;
}

void SerialSensorGyro::readFrame() {
    byte data[13];
    udp.read(data, 13);

    currentFrame.id = data[0];

    memcpy(bf.b, &data[1], sizeof(float));
    currentFrame.x = bf.f;

    memcpy(bf.b, &data[5], sizeof(float));
    currentFrame.y = bf.f;

    memcpy(bf.b, &data[9], sizeof(float));
    currentFrame.z = bf.f;
}

float SerialSensorGyro::getX() {
    readFrame();
    return currentFrame.x;
}

float SerialSensorGyro::getY() {
    readFrame();
    return currentFrame.y;
}

float SerialSensorGyro::getZ() {
    readFrame();
    return currentFrame.z;
}