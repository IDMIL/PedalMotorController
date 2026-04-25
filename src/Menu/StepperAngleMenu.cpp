#include "StepperAngleMenu.h"
#include <MotorInfo.h>

StepperAngleMenu::StepperAngleMenu(LiquidCrystal* lcd, MotorInfo* motor) :
    Menu(lcd, motor)
{
}

void StepperAngleMenu::init() {
    printMotorNum();
    lcd->print("Stepper Angle:");
    lastPrint = String("");
}

void StepperAngleMenu::update() {
    clearLastPrint();
    
    if (16 - lastPrint.length() < 4)
        printMotorNum();
    
    String toPrint = String((double) motor->currentStep / (double) motor->maxSteps * 270.0f) + " / " + String(270);

    lcd->setCursor(0, 1);
    lcd->print(toPrint);

    lastPrint = toPrint;
}