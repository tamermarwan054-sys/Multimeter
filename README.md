# Arduino Digital Multimeter

A DIY digital multimeter built on Arduino that measures voltage, current, and resistance, displayed on a 16x2 I2C LCD screen.

## Features

- Voltage measurement with noise stability check
- Current measurement in mA with EMA filter for smooth readings
- Resistance measurement with auto-ranging in Ω / kΩ / MΩ
- Auto-zero calibration on startup to eliminate offset errors
- Single button to cycle between measurement modes
- Serial monitor output for real-time data logging

## Hardware

| Component | Details |
|---|---|
| Microcontroller | Arduino Nano / Uno |
| Display | 16x2 LCD with I2C backpack (address 0x27) |
| Shunt Resistor | 55.9Ω for current sensing |
| Voltage Divider | 11x ratio (R1=100kΩ, R2=10kΩ) |
| Known Resistor | 10kΩ for resistance mode |

## Pin Connections

| Pin | Function |
|---|---|
| A0 | Voltage measurement |
| A1 | Current measurement |
| A2 | Resistance measurement |
| D2 | Mode selection button |
| A4 / A5 | I2C SDA / SCL for LCD |

## File Structure
src/
├── main.cpp        # Setup and main loop
├── config.h        # Pin definitions and tunable constants
├── adc.h           # ADC function declaration
├── adc.cpp         # ADC averaging with oversampling
├── sensors.h       # Sensor function declarations
├── sensors.cpp     # Voltage, current, resistance + auto-zero
├── display.h       # Display function declarations
└── display.cpp     # LCD and serial output formatting

## Dependencies

- [LiquidCrystal_I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) by Marco Schwartz

Install via `platformio.ini`:
```ini
lib_deps = marcoschwartz/LiquidCrystal_I2C@^1.1.4
```

## Build Instructions

This project is built with [PlatformIO](https://platformio.org/).

1. Install [VS Code](https://code.visualstudio.com/) and the [PlatformIO IDE extension](https://platformio.org/install/ide?install=vscode)
2. Clone this repository
3. Open the project folder in VS Code
4. PlatformIO will automatically install dependencies
5. Click the **✓ Build** button in the bottom toolbar

## Calibration

All tunable values are in `config.h`:

| Constant | Description |
|---|---|
| `CAL_V` | Voltage calibration multiplier |
| `CAL_I` | Current calibration multiplier |
| `SHUNT_RESISTOR` | Your actual measured shunt resistance in Ω |
| `DIVIDER_RATIO` | Your actual voltage divider ratio |
| `VREF` | Arduino reference voltage (default 5.0V) |

## How It Works

The device has 3 modes cycled by pressing the button:

- **Voltage mode** — reads A0 through a resistor divider, takes two averaged samples and compares them for stability. Floating or disconnected pins return 0V.
- **Current mode** — reads voltage across a shunt resistor on A1, applies an exponential moving average filter (α=0.80) for stable readings.
- **Resistance mode** — uses a voltage divider with a known 10kΩ resistor on A2, calculates unknown resistance and auto-ranges the unit displayed.

## License

MIT License — free to use, modify, and distribute.