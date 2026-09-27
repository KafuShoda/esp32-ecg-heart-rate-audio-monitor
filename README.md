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
- [x] Configure continuous ECG acquisition
- [x] Obtain a repeating ECG waveform
- [x] Calculate heart rate and R-R interval
- [x] Compare heart-rate readings with a fingertip pulse oximeter
- [x] Integrate the OLED and MAX30003
- [x] Display live BPM and R-R interval on the OLED
- [x] Add an OLED acquiring state
- [ ] Add signal-quality and electrode-disconnection handling
- [ ] Test the DFPlayer Mini audio module
- [ ] Test earbud output and safe volume
- [ ] Implement heart-rate zone logic and timers
- [ ] Add randomized audio prompts
- [ ] Integrate the complete breadboard system
- [ ] Perform failure-condition testing
- [ ] Perform battery-powered testing
- [ ] Build a portable perfboard prototype
- [ ] Design an optional custom PCB

## Development Phases

### Phase 1: Microcontroller Setup

Configured the ESP32-based microcontroller development environment and verified successful code compilation and uploading with a Blink test.

[View the complete Phase 1 documentation](docs/phase-1-setup.md)

### Phase 2: OLED Assembly and Display Test

Soldered the OLED header pins, verified the supply voltage, tested I2C communication, and detected the OLED at address `0x3D`. During troubleshooting, the I2C connection was reassigned from the original A4/A5 path to the working A2/A3 pins.

[View the complete Phase 2 documentation](docs/phase-2-oled-test.md)

### Phase 3: MAX30003 SPI Communication Test

Connected the ProtoCentral MAX30003 ECG breakout v3 through SPI and successfully read its INFO register, confirming basic digital communication with the ESP32-based microcontroller.

[View the complete Phase 3 documentation](docs/phase-3-max30003-test.md)

### Phase 4: Raw ECG Acquisition

Configured the MAX30003 for continuous ECG acquisition and connected a three-electrode sensor cable. Raw ECG samples were displayed in Serial Plotter, producing a repeating waveform with identifiable heartbeat-related peaks. This phase confirmed that the system could acquire a body-connected biosignal rather than only communicate with the sensor digitally.

[View the complete Phase 4 documentation](docs/phase-4-raw-ecg.md)

### Phase 5: Heart-Rate and R-R Interval Measurement

Used the MAX30003 heartbeat data to measure R-R intervals and calculate heart rate in beats per minute. Live BPM and R-R values were displayed in Serial Monitor and informally compared with the pulse-rate reading from a Zacurate Pro Series 500DL fingertip pulse oximeter.

[View the complete Phase 5 documentation](docs/phase-5-heart-rate.md)

### Phase 6: OLED Heart-Rate Integration

Integrated the MAX30003 heart-rate measurements with the OLED. The display shows live BPM, R-R interval, and an acquiring state while the system waits for an estimate. The OLED is refreshed once per second while heartbeat processing continues in the main program loop.

[View the complete Phase 6 documentation](docs/phase-6-oled-heart-rate.md)

## Current Status

The ESP32-based microcontroller successfully communicates with the MAX30003 ECG sensor through SPI and with the OLED through I2C. The system can acquire raw ECG samples, display a repeating waveform, calculate BPM and R-R intervals, and show the resulting estimates on both Serial Monitor and the OLED.

The OLED displays an acquiring screen before a plausible BPM estimate becomes available and refreshes approximately once per second without interrupting heartbeat processing.

Disconnected electrodes can still collect electrical noise that may be mistaken for heartbeats. The next phase will add signal-quality checks, electrode-disconnection handling, and protection against unreliable readings triggering future audio prompts.

This remains an experimental engineering prototype and is not a medical device.

## Safety and Limitations

This project is intended for education, experimentation, and engineering development only. It is not a certified medical device and must not be used for diagnosis or emergency decision-making.
