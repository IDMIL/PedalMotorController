#include "StepperPositionMenu.h"
#include <MotorInfo.h>

StepperPositionMenu::StepperPositionMenu(LiquidCrystal* lcd, MotorInfo* motor) :
    Menu(lcd, motor)
{
}

void StepperPositionMenu::init() {
    printMotorNum();
    lcd->print("Stepper Position:");
    lastPrint = String("");
}
void StepperPositionMenu::update() {
    clearLastPrint();
    
    if (16 - lastPrint.length() < 4)
        printMotorNum();

    String toPrint = String(motor->currentStep) + " / " + String(motor->maxSteps);

    lcd->setCursor(0, 1);
    lcd->print(toPrint);

    lastPrint = toPrint;
}