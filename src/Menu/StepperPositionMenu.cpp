#include "StepperPositionMenu.h"

StepperPositionMenu::StepperPositionMenu(LiquidCrystal& lcd, MotorInfo& motor) :
    Menu(lcd, motor)
{
}

void StepperPositionMenu::init() {
    printMotorNum();
    lcd.print("Stepper Position:");
}
void StepperPositionMenu::update() {
    lcd.setCursor(0, 1);
    lcd.print(String(motor.currentStep) + " / " + String(motor.maxSteps));
}