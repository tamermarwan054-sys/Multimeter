#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"
#include "adc.h"
#include "sensors.h"
#include "display.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

static int   mode            = 0;
static bool  lastButtonState = LOW;
static float filteredCurrent = 0.0f;

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
    bool currentButton = digitalRead(BUTTON_PIN);
    if (currentButton == HIGH && lastButtonState == LOW) {
        mode = (mode + 1) % 3;
        lcd.clear();
        delay(200);
    }
    lastButtonState = currentButton;

    switch (mode) {
        case 0:
            displayVoltage(lcd, readVoltage());
            break;

        case 1: {
            float raw = readCurrent();
            filteredCurrent = (ALPHA * raw) + ((1.0f - ALPHA) * filteredCurrent);
            displayCurrent(lcd, filteredCurrent * 1000.0f);
            break;
        }

        case 2:
            displayResistance(lcd, readResistance());
            break;
    }

    delay(150);
}