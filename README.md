# Arduino Digital Multimeter

A DIY digital multimeter built on Arduino that measures **voltage (±)**, **current**, and **resistance** — displayed on a 16×2 I2C LCD screen.

---

## ✨ Features

- ➕➖ Bidirectional voltage measurement — reads both positive and negative voltages using a mid-rail bias circuit
- 📊 Mean filter on voltage and resistance (20-sample average) for stable readings
- 🌊 EMA filter (α = 0.80) on current for smooth mA display
- 🎯 Auto-zero calibration on startup to eliminate current offset errors
- 🔘 Responsive single button to cycle between modes — checks button mid-sampling so it never misses a press
- 🖥️ Serial monitor output for real-time data logging
- ⏱️ Non-blocking display updates using millis() — button always responsive

---

## 🛠️ Hardware

| Component | Details |
|---|---|
| Microcontroller | Arduino Nano / Uno |
| Display | 16×2 LCD with I2C backpack (address 0x27) |
| Shunt Resistor | 55.9 Ω for current sensing |
| Voltage Divider | 11× ratio (R1 = 100 kΩ, R2 = 10 kΩ) |
| Mid-rail Bias | 2× 10 kΩ resistors from 5V → GND (midpoint → bottom of divider) |
| Known Resistor | 10 kΩ reference for resistance mode |

---

## 📌 Pin Connections

| Pin | Function |
|---|---|
| A0 | Voltage measurement |
| A1 | Current measurement |
| A2 | Resistance measurement |
| D2 | Mode selection button |
| A4 / A5 | I2C SDA / SCL for LCD |

---

## 📁 File Structure
src/
├── main.cpp         # Setup, main loop, button handling
├── config.h         # All pin definitions and tunable constants
├── adc.h / .cpp     # ADC averaging with oversampling
├── sensors.h / .cpp # Voltage, current, resistance + mean filters
└── display.h / .cpp # LCD and serial output formatting

---

## ⚙️ How It Works

**Voltage Mode** — reads A0 through an 11× resistor divider. A mid-rail bias shifts the ADC input up ~2.5V enabling negative voltage detection. Takes two averaged samples, checks stability, applies separate calibration slopes for positive and negative paths, and averages 20 readings for a stable display.

**Current Mode** — reads voltage across a 55.9 Ω shunt resistor on A1. Applies EMA filter (α = 0.80) for smooth mA readings. Updates continuously in real time.

**Resistance Mode** — uses a voltage divider with a known 9.65 kΩ reference on A2. Calculates unknown resistance, auto-ranges display (Ω / kΩ / MΩ), averages 20 readings, shows OL when open or too high.

---

## 🔧 Calibration

All tunable values live in `config.h`:

| Constant | Description |
|---|---|
| `CAL_V` | Voltage ADC multiplier — 0.867 hardware / 1.0 Tinkercad |
| `CAL_I` | Current ADC multiplier — 0.901 hardware / 1.0 Tinkercad |
| `V_MIDRAIL` | Measured voltage at mid-rail point (measure with multimeter) |
| `V_SLOPE_POS` | Calibration slope for positive voltages |
| `V_SLOPE_NEG` | Calibration slope for negative voltages |
| `V_OFFSET` | Voltage offset — 0.004 hardware / 0.0 Tinkercad |
| `V_DEADBAND` | Threshold around zero to suppress floating noise |
| `R_KNOWN` | Actual measured reference resistance in Ω |
| `SHUNT_RESISTOR` | Actual measured shunt resistance in Ω |

---

## 📏 Measured Accuracy

| Device | Average Error |
|---|---|
| Voltmeter | ~2.74% |
| Ohmmeter | ~2.91% |
| Ammeter | ~3.66% |

---

## 📦 Dependencies

- [LiquidCrystal_I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) by Marco Schwartz

```ini
lib_deps = marcoschwartz/LiquidCrystal_I2C@^1.1.4
```

---

## 🚀 Build Instructions

1. Install VS Code and the PlatformIO IDE extension
2. Clone this repository
3. Open the project folder in VS Code
4. PlatformIO will automatically install dependencies
5. Click ✓ Build in the bottom toolbar

---

## 📄 License

MIT License — free to use, modify, and distribute.