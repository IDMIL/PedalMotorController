// Arduino Standard Libs
// #include <KVStore.h>
// #include <kvstore_global_api.h>
#include <LiquidCrystal.h>
#include <WiFi.h>

// Custom Libraries
#include <Joystick.h>
#include <MotorInfo.h>

#include <Menu.h>
#include <AxisSelectMenu.h>
#include <CurveSelectMenu.h>
#include <MultiplierSelectMenu.h>
#include <SplashScreen.h>
#include <StepperAngleMenu.h>
#include <StepperPositionMenu.h>

// External Libraries
#include <AccelStepper.h>
#include <arduino-timer.h>

// Constants
const unsigned long BAUD_RATE = 38400;
const long STEPS_PER_REVOLUTION = 2048;
const long MAX_STEPS = (float) STEPS_PER_REVOLUTION * (270.0 / 360.0);
const unsigned UDP_PORT = 8888;
const String SSID = "PedalMotorController";

// Globals
LiquidCrystal lcd(1, 2, 3, 4, 5, 6);
WiFiUDP udp;
SerialSensorGyro ssg(&udp);
Joystick joystick(7, A0, A1);
auto joystickCooldownTimer = timer_create_default();

SplashScreen splashScreen(&lcd, SSID, UDP_PORT);

MotorInfo motors[4] = {
    MotorInfo(
        0, 
        AccelStepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 22, 24, 23, 25), 
        MAX_STEPS, 
        &ssg, &lcd, &joystick
    ),
    MotorInfo(
        1, 
        AccelStepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 26, 28, 27, 29), 
        MAX_STEPS, 
        &ssg, &lcd, &joystick
    ),
    MotorInfo(
        2, 
        AccelStepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 30, 32, 31, 33), 
        MAX_STEPS, 
        &ssg, &lcd, &joystick
    ),
    MotorInfo(
        3, 
        AccelStepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 34, 36, 35, 37), 
        MAX_STEPS, 
        &ssg, &lcd, &joystick
    )
};

int currentMotor = 0;
int currentMenu = 0;
bool firstTime = true;

bool joystickCooldownDone = true;

bool endJoystickCooldown(void*) {
    joystickCooldownDone = true;
    return true;
}

void setup() {
    // Serial
    Serial.begin(BAUD_RATE);
    while (!Serial);

    Serial.println("PedalMotorController");
    Serial.println("Booting...\n");

    // Motors
    for (int i = 0; i < 4; i++) {
        motors[i].stepper.setMaxSpeed(1000);
        motors[i].stepper.setSpeed(1);
    }

    // LCD
    lcd.begin(16, 2);
    lcd.clear();

    // Timer
    joystickCooldownTimer.every(500, endJoystickCooldown); // half second cooldown

    // Networking
    WiFi.beginAP(SSID.c_str(), SSID.c_str());
    udp.begin(UDP_PORT);

    // Debug Info
    Serial.print("PMC: SSID: "); Serial.println(SSID);
    Serial.print("PMC: UDP port: "); Serial.println(UDP_PORT);
    Serial.print("PMC: Local IP address: "); Serial.println(WiFi.localIP());
    Serial.print("\n");

    splashScreen.init();
}

void loop() {
    if (udp.parsePacket()) {
        // Always run the motors while there's data
        for (MotorInfo& motor : motors)
            motor.run();

        Menu* visibleMenu = motors[currentMotor].menus[currentMenu];

        // Initializing the first menu
        if (firstTime) {
            lcd.clear();
            visibleMenu->init();
            firstTime = false;
        }

        // Always run 
        visibleMenu->update();

        if (!visibleMenu->isSelected()) {
            bool menuChanged = false;

            if (joystickCooldownDone) {
                Joystick::Action action = joystick.getCurrentAction();
                Serial.println(Joystick::actionToString(action).c_str());

                // 4 motors, 5 menus each
                // Right -> go to next motor
                // Left -> go to previous motor
                // Down -> go to next menu
                // Up -> go to previous menu
                switch (action) {
                    case Joystick::Action::W:
                        if (currentMotor == 0)
                            currentMotor = 3;
                        else
                            currentMotor = (currentMotor - 1) % 4;
                        menuChanged = true;
                        break;
                    case Joystick::Action::E:
                        currentMotor = (currentMotor + 1) % 4;
                        menuChanged = true;
                        break;
                    case Joystick::Action::S:
                        if (currentMenu == 0)
                            currentMenu = 4;
                        else
                            currentMenu = (currentMenu - 1) % 5;
                        menuChanged = true;
                        break;
                    case Joystick::Action::N:
                        currentMenu = (currentMenu + 1) % 5;
                        menuChanged = true;
                        break;
                    default:
                        break;
                }

                if (menuChanged) {
                    lcd.clear();
                    motors[currentMotor].menus[currentMenu]->init();
                    joystickCooldownDone = false;
                }
            }
            else
                joystickCooldownTimer.tick();
        }
    }
}
