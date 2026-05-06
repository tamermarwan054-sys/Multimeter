#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "config.h"
#include "adc.h"

void  autoZero();
float readVoltage();
float readVoltageMean();
float readCurrent();
float readResistance();
float readResistanceMean();

#endif