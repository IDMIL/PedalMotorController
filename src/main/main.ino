// Arduino Standard Libs
#include "KVStore.h"
#include "kvstore_global_api.h"
#include <LiquidCrystal.h>
#include <WiFi.h>

// Custom/External Libraries
#include <AccelStepper.h>

// Constants
const unsigned long BAUD_RATE = 38400;
const long STEPS_PER_REVOLUTION = 2048;
const long MAX_STEPS = (float) STEPS_PER_REVOLUTION * (270.0 / 360.0);
const unsigned UDP_PORT = 8888;
const String SSID = "PedalMotorController";
const String KVSTORE_KEY = "POSITION";

// Other Globals
LiquidCrystal lcd(1, 2, 3, 4, 5, 6);
WiFiUDP udp;
SerialSensorGyro ssg(udp);

MotorInfo motors[4] = {
  MotorInfo(0, AccelStepper stepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 23, 27, 25, 29), MAX_STEPS, ssg),
  MotorInfo(1, AccelStepper stepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 23, 27, 25, 29), MAX_STEPS, ssg),
  MotorInfo(2, AccelStepper stepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 23, 27, 25, 29), MAX_STEPS, ssg),
  MotorInfo(3, AccelStepper stepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 23, 27, 25, 29), MAX_STEPS, ssg),
};

Menu motorMenus[4][5] = {
  {StepperPositionMenu(lcd, motors[0]), StepperAngleMenu(lcd, motors[0]), AxisSelectMenu(lcd, motors[0]), MultiplierSelectMenu(lcd, motors[0]), CurveSelectMenu(lcd, motors[0])},
  {StepperPositionMenu(lcd, motors[1]), StepperAngleMenu(lcd, motors[1]), AxisSelectMenu(lcd, motors[1]), MultiplierSelectMenu(lcd, motors[1]), CurveSelectMenu(lcd, motors[1])},
  {StepperPositionMenu(lcd, motors[2]), StepperAngleMenu(lcd, motors[2]), AxisSelectMenu(lcd, motors[2]), MultiplierSelectMenu(lcd, motors[2]), CurveSelectMenu(lcd, motors[2])},
  {StepperPositionMenu(lcd, motors[3]), StepperAngleMenu(lcd, motors[3]), AxisSelectMenu(lcd, motors[3]), MultiplierSelectMenu(lcd, motors[3]), CurveSelectMenu(lcd, motors[3])}
};

void setup() {
  // Serial
  Serial.begin(BAUD_RATE);
  while (!Serial);

  Serial.println("PedalMotorController");
  Serial.println("Booting...\n");

  // Motors
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(1);

  // KVStore
  Serial.println("===KVSTORE CHECK===");

  // kv_reset("/kv/"); // comment this out after the first execution!

  long pos;
  kv_get(KVSTORE_KEY.c_str(), &pos, sizeof(long), NULL);
  Serial.print("Last Saved Position: "); Serial.println(pos);

  stepper.setCurrentPosition(pos);

  Serial.println("===KVSTORE CHECK===\n");

  // LCD
  lcd.begin(16, 2);
  lcd.clear();

  // Networking
  WiFi.beginAP(SSID.c_str(), SSID.c_str());
  udp.begin(UDP_PORT);

  // Debug Info
  Serial.print("PMC: SSID: "); Serial.println(SSID);
  Serial.print("PMC: UDP port: "); Serial.println(UDP_PORT);
  Serial.print("PMC: Local IP address: "); Serial.println(WiFi.localIP());
  Serial.print("\n");
}

void loop() {
  unsigned last_print_data_length = 0;

  if (udp.parsePacket()) {
    long current_pos = stepper.currentPosition();
    kv_set(KVSTORE_KEY.c_str(), &current_pos, sizeof(long), NULL);
  }
}
