#include "adc.h"

float readADC(int pin, int samples) {
    long sum = 0;
    for (int i = 0; i < samples; i++) {
        sum += analogRead(pin);
        delayMicroseconds(150);
    }
    return sum / (float)samples;
}