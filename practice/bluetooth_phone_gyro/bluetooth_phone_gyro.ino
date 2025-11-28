#include <SoftwareSerial.h>
#include <string.h>

#define RX_PIN 11
#define TX_PIN 10

#define BAUD_RATE 38400

SoftwareSerial BTSerial(TX_PIN, RX_PIN); // RX | TX

void setup() {
  Serial.begin(BAUD_RATE);
  BTSerial.begin(BAUD_RATE);
}

void loop() {
  Serial.print("Bytes available: ");
  Serial.println(BTSerial.available());

  String data;

  for (int i = 0; i < 13; i++) {
    char byte = BTSerial.read();
    data.concat(byte);
  }

  char asString[32];

  Serial.print("Data: ");
  Serial.println(asString);
}
