#include "sensors.h"

extern bool checkButton();
extern int  mode;

static float zeroOffsetV = 0.0f;
static float zeroOffsetI = 0.0f;

void autoZero() {
    analogReference(DEFAULT);
    delay(50);

    // voltage autozero disabled — midrail handles offset
    zeroOffsetV = 0.0f;

    analogRead(CURR_PIN);
    delay(10);
    float avgI  = readADC(CURR_PIN, 1000);
    zeroOffsetI = (avgI * VREF) / ADC_MAX;
    if (zeroOffsetI > 0.1f) zeroOffsetI = 0.0f;
}

float readVoltage() {
    float adc1 = readADC(VOLT_PIN, 50);
    delay(5);
    float adc2 = readADC(VOLT_PIN, 50);

    float v1 = (adc1 / ADC_MAX) * VREF * DIVIDER_RATIO * CAL_V;
    float v2 = (adc2 / ADC_MAX) * VREF * DIVIDER_RATIO * CAL_V;

    if (abs(v1 - v2) > 0.3f) return 0.0f;

    float v = (v1 + v2) / 2.0f;

    // subtract midrail bias
    v = v - (V_MIDRAIL * DIVIDER_RATIO * CAL_V);

    // separate slopes for positive and negative
    if (v >= 0.0f) {
        v = (V_SLOPE_POS * v) + V_OFFSET;
    } else {
        v = (V_SLOPE_NEG * v) + V_OFFSET;
    }

    // dead-band
    if (abs(v) < V_DEADBAND) v = 0.0f;

    return v;
}

float readVoltageMean() {
    float sum = 0.0f;
    for (int i = 0; i < MEAN_V; i++) {
        if (checkButton()) return 0.0f;
        sum += readVoltage();
        delay(10);
    }
    return sum / (float)MEAN_V;
}

float readCurrent() {
    float adc    = readADC(CURR_PIN, SAMPLES_I);
    float vShunt = ((adc * VREF) / ADC_MAX) - zeroOffsetI;

    if (vShunt < 0.002f) vShunt = 0.0f;

    float amps = (vShunt / SHUNT_RESISTOR) * CAL_I;
    return (amps < 0.0f) ? 0.0f : amps;
}

float readResistance() {
    float adc  = readADC(RES_PIN, SAMPLES_R);
    float vOut = (adc / ADC_MAX) * VREF;

    if (vOut >= 4.9f) return -1.0f;
    if (vOut <= 0.1f) return  0.0f;

    return (vOut * R_KNOWN) / (VREF - vOut);
}

float readResistanceMean() {
    float sum        = 0.0f;
    int   validCount = 0;

    for (int i = 0; i < MEAN_R; i++) {
        if (checkButton()) return -1.0f;
        float r = readResistance();
        if (r >= 0.0f) {
            sum += r;
            validCount++;
        }
        delay(10);
    }

    return (validCount == 0) ? -1.0f : sum / (float)validCount;
}