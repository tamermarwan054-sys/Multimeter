#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"
#include "adc.h"
#include "sensors.h"
#include "display.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

int   mode            = 0;
bool  lastButtonState = LOW;
float filteredCurrent = 0.0f;

unsigned long lastUpdateTime = 0;

bool checkButton() {
    bool currentButton = digitalRead(BUTTON_PIN);
    if (currentButton == HIGH && lastButtonState == LOW) {
        lastButtonState = currentButton;
        mode++;
        if (mode > 2) mode = 0;
        lcd.clear();
        lastUpdateTime = 0;
        return true;
    }
    lastButtonState = currentButton;
    return false;
}

void setup() {
    Serial.begin(9600);
    Wire.begin();

    analogReference(DEFAULT);
    delay(50);

    lcd.init();
    lcd.backlight();
    pinMode(BUTTON_PIN, INPUT);

    lcd.setCursor(3, 0);
    lcd.print("Multimeter");
    lcd.setCursor(0, 1);
    lcd.print("   V    I    R  ");
    delay(2000);
    lcd.clear();

    autoZero();
}

void loop() {
    checkButton();

    if (mode == 0) {
        if (millis() - lastUpdateTime >= UPDATE_INTERVAL) {
            float voltage = readVoltageMean();
            if (mode == 0) {
                displayVoltage(lcd, voltage);
            }
            lastUpdateTime = millis();
        }
    }

    else if (mode == 1) {
        float raw = readCurrent();
        filteredCurrent = (ALPHA * raw) + ((1.0f - ALPHA) * filteredCurrent);
        displayCurrent(lcd, filteredCurrent * 1000.0f);
    }

    else if (mode == 2) {
        if (millis() - lastUpdateTime >= UPDATE_INTERVAL) {
            float resistance = readResistanceMean();
            if (mode == 2) {
                displayResistance(lcd, resistance);
            }
            lastUpdateTime = millis();
        }
    }

    delay(10);
}