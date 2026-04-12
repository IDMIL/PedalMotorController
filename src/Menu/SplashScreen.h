#pragma once

#include "Menu.h"
#include <WiFi.h>

class SplashScreen : public Menu {
    public:
        SplashScreen(LiquidCrystal* lcd, String ssid, unsigned port);

        void init() override;
        void update() override;
        bool isSelected() override { return false; }

    private:
        String ssid;
        unsigned port;
};