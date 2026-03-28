#include "StepperAngleMenu.h"

StepperAngleMenu::StepperAngleMenu(LiquidCrystal& lcd, MotorInfo& motor) :
    Menu(lcd, motor)
{
}

void StepperAngleMenu::init() {
    printMotorNum();
    lcd.print("Stepper Angle:");
}

void StepperAngleMenu::update() {
    lcd.setCursor(0, 1);
    lcd.print(String((double) motor.currentStep / (double) motor.maxSteps * 270.0f) + " / " + String(270));
}