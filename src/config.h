#ifndef CONFIG_H
#define CONFIG_H

#define VOLT_PIN        A0
#define CURR_PIN        A1
#define RES_PIN         A2
#define BUTTON_PIN      2

#define VREF            5.0f
#define ADC_MAX         1023.0f
#define DIVIDER_RATIO   11.0f
#define SHUNT_RESISTOR  55.9f
#define R_KNOWN         10000.0f
#define CAL_V           1.0f
#define CAL_I           1.0f

#define SAMPLES_V       100
#define SAMPLES_I       500
#define SAMPLES_R       100

#define ALPHA           0.80f

#endif