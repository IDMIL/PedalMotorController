#include <WiFi.h>

const unsigned BAUD_RATE = 38400;
const unsigned UDP_PORT = 8888;
const char* SSID = "PedalMotorController";

WiFiUDP udp;

struct SerialSensorGyroFrame {
  byte id;
  float x;
  float y;
  float z;
};

union ByteFloat {
  byte b[4];
  float f;
};

void readFrame(SerialSensorGyroFrame& frame) {
  byte data[13];
  udp.read(data, sizeof(SerialSensorGyroFrame));

  frame.id = data[0];

  ByteFloat bf;

  memcpy(bf.b, &data[1], sizeof(float));
  frame.x = bf.f;

  memcpy(bf.b, &data[5], sizeof(float));
  frame.y = bf.f;

  memcpy(bf.b, &data[9], sizeof(float));
  frame.z = bf.f;
}

void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial);

  WiFi.beginAP(SSID, SSID); // password = ssid
  udp.begin(UDP_PORT);

  Serial.print("PMC: SSID: ");
  Serial.println(SSID);
  Serial.print("PMC: UDP port: ");
  Serial.println(UDP_PORT);
  Serial.print("PMC: Local IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  SerialSensorGyroFrame frame;

  if (udp.parsePacket()) {
    readFrame(frame);

    Serial.print("PMC: frame = {");
    Serial.print(frame.id); Serial.print(",\t");
    Serial.print(frame.x); Serial.print(",\t");
    Serial.print(frame.y); Serial.print(",\t");
    Serial.print(frame.z); Serial.println("}");
  }
}
