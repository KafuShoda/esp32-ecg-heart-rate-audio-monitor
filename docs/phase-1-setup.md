# Phase 1: ESP32 Microcontroller Setup

## Objective

The objective of Phase 1 was to prepare the ESP32-based microcontroller development environment and confirm that programs could be compiled and uploaded successfully.

## Project Goal

The long-term goal is to develop a wearable embedded system that:

1. Acquires a single-lead ECG signal
2. Detects heartbeats and calculates BPM
3. Determines the current heart-rate zone
4. Displays information on an OLED
5. Plays prerecorded audio prompts based on the heart-rate zone

## Development Equipment

- ESP32-based Nano microcontroller board
- USB-C data cable
- Windows computer
- Arduino IDE
- Breadboard
- Jumper wires

## Development Environment Setup

The Arduino IDE was installed as the development environment. The required ESP32 board support package was then installed through the IDE's Boards Manager.

The ESP32-based Nano board was selected under the board settings, and the appropriate serial port was selected after connecting the microcontroller to the computer through USB.

## Initial Upload Test

A basic Blink program was compiled and uploaded to the microcontroller.

The purpose of this test was to confirm:

- The microcontroller received power
- The computer recognized the board
- The selected USB cable supported data transfer
- The correct board package was installed
- The correct serial port was selected
- The program compiled successfully
- The program uploaded successfully
- The microcontroller executed the uploaded instructions

## Troubleshooting

The first USB-C cable used for the project did not establish a successful programming connection. The upload produced a device-detection error.

The cable was replaced with a USB-C cable capable of transferring data. After changing the cable, the program uploaded successfully.

This demonstrated that a USB cable may provide power without necessarily supporting reliable data transfer.

## Result

Phase 1 was completed successfully. The development environment was configured, communication with the ESP32-based microcontroller was established, and a test program was uploaded and executed.

## Skills Practiced

- Microcontroller setup
- Embedded development environment configuration
- Code compilation
- Firmware uploading
- Serial-port selection
- Hardware troubleshooting
- USB power-versus-data diagnosis

## Next Phase

The next phase tests an OLED display independently through the I2C communication protocol.
