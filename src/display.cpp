#include "display.h"

void displayVoltage(LiquidCrystal_I2C &lcd, float voltage) {
    lcd.setCursor(0, 0);
    lcd.print("Voltage:        ");
    lcd.setCursor(0, 1);
    lcd.print(voltage, 2);
    lcd.print(" V          ");

    Serial.print("[V] ");
    Serial.print(voltage, 2);
    Serial.println(" V");
}

void displayCurrent(LiquidCrystal_I2C &lcd, float mA) {
    lcd.setCursor(0, 0);
    lcd.print("Current:        ");
    lcd.setCursor(0, 1);
    if (mA < 0.1f) {
        lcd.print("0.00 mA         ");
    } else {
        lcd.print(mA, 2);
        lcd.print(" mA         ");
    }

    Serial.print("[I] ");
    Serial.print(mA, 2);
    Serial.println(" mA");
}

void displayResistance(LiquidCrystal_I2C &lcd, float resistance) {
    lcd.setCursor(0, 0);
    lcd.print("Resistance:     ");
    lcd.setCursor(0, 1);

    if (resistance < 0) {
        lcd.print("OL              ");
    } else {
        lcd.print(resistance / 1000.0f, 3);
        lcd.print(" kOhm       ");
    }

    Serial.print("[R] ");
    if      (resistance < 0)      Serial.println("OL");
    else if (resistance < 1000) { Serial.print(resistance, 1);        Serial.println(" Ω");  }
    else if (resistance < 1e6)  { Serial.print(resistance / 1000, 2); Serial.println(" kΩ"); }
    else                        { Serial.print(resistance / 1e6, 2);  Serial.println(" MΩ"); }
}