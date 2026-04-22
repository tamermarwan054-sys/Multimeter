#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "config.h"
#include "adc.h"

void  autoZero();
float readVoltage();
float readCurrent();
float readResistance();

#endif