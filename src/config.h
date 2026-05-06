#ifndef CONFIG_H
#define CONFIG_H

// -------- Pins --------
#define VOLT_PIN        A0
#define CURR_PIN        A1
#define RES_PIN         A2
#define BUTTON_PIN      2

// -------- ADC --------
#define VREF            5.0f
#define ADC_MAX         1023.0f

// -------- Voltage Divider --------
#define DIVIDER_RATIO   11.0f

// -------- Current Shunt --------
#define SHUNT_RESISTOR  55.9f

// -------- Resistance Reference --------
#define R_KNOWN         9650.0f

// -------- Calibration --------
// 🔁 Swap to 1.0 for Tinkercad
#define CAL_V           0.867f
#define CAL_I           0.901f

// -------- Midrail --------
#define V_MIDRAIL       2.535f

// -------- Two-point Voltage Calibration --------
// 🔁 Swap slopes to 1.0 and offset to 0.0 for Tinkercad
#define V_SLOPE_POS     1.150f
#define V_SLOPE_NEG     1.018f
#define V_OFFSET        0.004f

// -------- Dead-band --------
#define V_DEADBAND      0.35f

// -------- Oversampling --------
#define SAMPLES_V       200
#define SAMPLES_I       500
#define SAMPLES_R       100

// -------- Mean Filter --------
#define MEAN_V          20
#define MEAN_R          20

// -------- EMA Filter --------
#define ALPHA           0.80f

// -------- Display Update Interval --------
#define UPDATE_INTERVAL 1000UL

#endif