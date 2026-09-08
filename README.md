# ESP32 ECG Heart-Rate Audio Monitor

## Project Overview

This project is an ESP32 microcontroller-based wearable system that acquires a single-lead ECG signal, calculates heart rate, displays system information on an OLED, and plays prerecorded audio based on the detected heart-rate zone.

The project combines embedded programming, digital communication protocols, biosignal acquisition, hardware integration, and real-time control logic.

## Intended System Behavior

- Below 100 BPM: no audio prompt
- 100–129 BPM for longer than 10 seconds: play a random Zone A prompt
- 130–160 BPM for longer than 10 seconds: play a random Zone B prompt
- Above 160 BPM for longer than 30 seconds: play a special prompt
- Display BPM, heart-rate zone, signal status, and audio status on an OLED

## Main Hardware

- ESP32-based Nano microcontroller board
- ProtoCentral MAX30003 ECG breakout
- 1.3-inch 128x64 OLED display
- DFPlayer Mini audio module
- MicroSD card
- Mono earpiece
- ECG electrodes
- Breadboard and jumper wires
- USB power bank

## Development Progress

- [x] Gather project components
- [x] Install and configure the development environment
- [x] Test code compilation and upload
- [x] Solder and inspect OLED header pins
- [x] Measure OLED supply voltage
- [x] Detect OLED at I2C address 0x3D
- [x] Reassign OLED I2C communication to A2/A3
- [x] Display Hello World on the OLED
- [x] Establish basic MAX30003 SPI communication
- [ ] Configure continuous ECG acquisition
- [ ] Obtain a stable ECG waveform
- [ ] Calculate heart rate
- [ ] Integrate the OLED and ECG board
- [ ] Test the audio module
- [ ] Implement heart-rate zone logic
- [ ] Build a portable prototype

## Development Phases

### Phase 1: Microcontroller Setup

Configured the ESP32-based microcontroller development environment and verified successful code compilation and uploading with a Blink test.

[View the complete Phase 1 documentation](docs/phase-1-setup.md)

### Phase 2: OLED Assembly and Display Test

Soldered the OLED header pins, verified the supply voltage, tested I2C communication, and detected the OLED at address `0x3D`. During troubleshooting, the I2C connection was reassigned from the original A4/A5 path to the working A2/A3 pins.

[View the complete Phase 2 documentation](docs/phase-2-oled-test.md)

### Phase 3: MAX30003 Communication Test

Connected the MAX30003 through SPI and confirmed basic communication by reading a device register.

## Current Status

The OLED has been tested successfully, and basic communication with the MAX30003 has been established. The next objective is to acquire and verify a stable ECG waveform.

## Safety and Limitations

This project is intended for education, experimentation, and engineering development only. It is not a certified medical device and must not be used for diagnosis or emergency decision-making.
