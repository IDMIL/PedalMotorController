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
#include <MutliplierSelectMenu.h>
#include <StepperAngleMenu.h>
#include <StepperPositionMenu.h>

// External Libraries
#include <AccelStepper.h>

// Constants
const unsigned long BAUD_RATE = 38400;
const long STEPS_PER_REVOLUTION = 2048;
const long MAX_STEPS = (float) STEPS_PER_REVOLUTION * (270.0 / 360.0);
const unsigned UDP_PORT = 8888;
const String SSID = "PedalMotorController";

// Globals
LiquidCrystal lcd(1, 2, 3, 4, 5, 6);
WiFiUDP udp;
SerialSensorGyro ssg(udp);
Joystick joystick(7, A0, A1);

MotorInfo motors[4] = {
    MotorInfo(
        0, 
        AccelStepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 23, 27, 25, 29), 
        MAX_STEPS, 
        ssg
    ),
    MotorInfo(
        1, 
        AccelStepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 23, 27, 25, 29), 
        MAX_STEPS, 
        ssg
    ),
    MotorInfo(
        2, 
        AccelStepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 23, 27, 25, 29), 
        MAX_STEPS, 
        ssg
    ),
    MotorInfo(
        3, 
        AccelStepper(AccelStepper::MotorInterfaceType::FULL4WIRE, 23, 27, 25, 29), 
        MAX_STEPS, 
        ssg
    )
};

Menu motorMenus[4][5] = {
    {
        StepperPositionMenu(lcd, motors[0]), 
        StepperAngleMenu(lcd, motors[0]), 
        AxisSelectMenu(lcd, motors[0], joystick), 
        MultiplierSelectMenu(lcd, motors[0], joystick), 
        CurveSelectMenu(lcd, motors[0], joystick)
    },
    {
        StepperPositionMenu(lcd, motors[1]), 
        StepperAngleMenu(lcd, motors[1]), 
        AxisSelectMenu(lcd, motors[1], joystick), 
        MultiplierSelectMenu(lcd, motors[1], joystick), 
        CurveSelectMenu(lcd, motors[1], joystick)
    },
    {
        StepperPositionMenu(lcd, motors[2]), 
        StepperAngleMenu(lcd, motors[2]), 
        AxisSelectMenu(lcd, motors[2], joystick), 
        MultiplierSelectMenu(lcd, motors[2], joystick), 
        CurveSelectMenu(lcd, motors[2], joystick)
    },
    {
        StepperPositionMenu(lcd, motors[3]), 
        StepperAngleMenu(lcd, motors[3]), 
        AxisSelectMenu(lcd, motors[3], joystick), 
        MultiplierSelectMenu(lcd, motors[3], joystick), 
        CurveSelectMenu(lcd, motors[3], joystick)
    }
};

int currentMotor = 0;
int currentMenu = 0;

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
    if (udp.parsePacket()) {
        // Always run the motors while there's data
        for (MotorInfo& motor : motors)
            motor.run();

        // Always run 
        Menu& visibleMenu = motorMenus[currentMotor][currentMenu];
        visibleMenu.update();

        // Handling changing menus
        if (!visibleMenu.isSelected()) {
            bool menuChanged = false;

            switch (joystick.getCurrentAction()) {
                case Joystick::Action::W:
                    currentMotor = (currentMotor - 1) % 4;
                    menuChanged = true;
                    break;
                case Joystick::Action::E:
                    currentMotor = (currentMotor + 1) % 4;
                    menuChanged = true;
                    break;
                case Joystick::Action::N:
                    currentMenu = (currentMenu - 1) % 5;
                    menuChanged = true;
                    break;
                case Joystick::Action::S:
                    currentMenu = (currentMenu + 1) % 5;
                    menuChanged = true;
                    break;
                default:
                    break;
            }

            if (menuChanged) {
                lcd.clear();
                motorMenus[currentMotor][currentMenu].init();
            }
        }
    }
}
