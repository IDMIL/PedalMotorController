#include <SoftwareSerial.h>

const int ENABLE_PIN = 7;
const int TX_PIN = 5;
const int RX_PIN = 6;

const unsigned long BAUD_RATE = 38400;

SoftwareSerial bleSerial(TX_PIN, RX_PIN);

void setup() {
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, HIGH);

  Serial.begin(BAUD_RATE);
  Serial.println("Enter AT Commands");
  
  bleSerial.begin(BAUD_RATE);
}

void loop() {
  if (Serial.available())
    bleSerial.write(Serial.read());

  if (bleSerial.available())
    Serial.write(bleSerial.read());
}
