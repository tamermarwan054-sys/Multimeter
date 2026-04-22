#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

void displayVoltage(LiquidCrystal_I2C &lcd, float voltage);
void displayCurrent(LiquidCrystal_I2C &lcd, float mA);
void displayResistance(LiquidCrystal_I2C &lcd, float resistance);

#endif