# Phase 4 Images — Raw ECG Acquisition

This folder contains photographs and screenshots documenting raw ECG signal acquisition with the MAX30003 and ESP32-based microcontroller.

## Images

### Complete Prototype

`phase-4-complete-system.jpeg`

Complete breadboard prototype showing the ESP32-based microcontroller, MAX30003 ECG breakout, OLED display, three-lead electrode cable, and disposable electrodes. During this phase, the MAX30003 was tested independently while the OLED remained physically connected for later integration.

### MAX30003 Wiring

`phase-4-max30003-wiring.jpeg`

Close-up photograph documenting the MAX30003 power, ground, SPI, chip-select, and interrupt connections.

### Electrode Cable

`phase-4-electrode-cable.jpeg`

The three-lead electrode cable used for ECG acquisition. The cable includes red and yellow signal leads and a green reference lead.

### Raw ECG Waveform

`phase-4-raw-ecg-waveform.png`

Screenshot of raw ECG-like samples displayed in Arduino Serial Plotter. The repeating sharp complexes demonstrate successful acquisition of a biological electrical signal.

### Electrode Placement

`phase-4-electrode-placement.jpeg`

Photograph showing the three-electrode placements used during testing. Below left and right sides of collarbone and lower left abdomen.

## Result

The MAX30003 successfully acquired a repeating ECG-like waveform through the three-electrode cable. The signal was transmitted to the microcontroller over SPI and displayed using Serial Plotter.

Occasional changes in peak height were attributed to display decimation, electrode contact, movement, breathing, and environmental electrical noise.

## Safety and Limitations

Body-connected testing was performed using a laptop operating from its internal battery with the charger disconnected. The system is an educational and experimental prototype, not a certified medical device, and its output is not intended for diagnosis.
