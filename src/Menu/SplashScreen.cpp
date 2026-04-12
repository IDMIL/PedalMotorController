#include "SplashScreen.h"

SplashScreen::SplashScreen(LiquidCrystal* lcd, String ssid, unsigned port) :
    Menu(lcd, nullptr),
    ssid(ssid),
    port(port)
{
}

void SplashScreen::init() {
    lcd->setCursor(0, 0);
    lcd->print("PMC AP Created");
    lcd->setCursor(0, 1);
    lcd->print(WiFi.localIP().toString() + ":" + String(port));
    lcd->setCursor(0, 0);
}

void SplashScreen::update() {
    // nothing
}