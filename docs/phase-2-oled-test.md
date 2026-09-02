# Phase 2: OLED Header Assembly and Display Test

## Objective

The objective of Phase 2 was to prepare the OLED module for breadboard use, connect it to the ESP32-based microcontroller through I2C, identify its address, and verify that it could display text successfully.

## Hardware and Tools Used

- ESP32-based Nano microcontroller board
- Adafruit 1.3-inch 128x64 OLED display
- Male header pins
- Soldering iron
- Solder
- Soldering stand and tip-cleaning material
- Breadboard
- Jumper wires
- USB-C data cable
- Computer running Arduino IDE

## OLED Header-Pin Soldering

The OLED required header pins before it could be installed securely on the breadboard. Male header pins were positioned through the OLED breakout board and soldered into place.

The assembly process included:

1. Positioning the header pins through the OLED breakout board
2. Keeping the header straight and aligned
3. Stabilizing the OLED and header during soldering
4. Heating each header-pin and PCB-pad connection
5. Applying solder to form an electrical and mechanical connection
6. Allowing each joint to cool without moving the pin
7. Inspecting the completed solder joints
8. Checking for unintended solder bridges between adjacent pins
9. Confirming that the header fit securely into the breadboard

The OLED was disconnected from power during soldering.

## Solder-Joint Inspection

The completed assembly was visually inspected for:

- Secure solder surrounding each header pin
- Straight and aligned header pins
- Separation between neighboring solder joints
- Absence of visible solder bridges
- Absence of loose pins
- Secure installation on the breadboard

Successful operation of the OLED provided additional functional evidence that its power and communication connections were working.

## Communication Protocol

The OLED communicates with the microcontroller using I2C.

I2C uses two primary signal lines:

- SDA carries data between the devices
- SCL provides the communication clock

The OLED and microcontroller must also share power and ground connections.

## Wiring

| OLED pin | Microcontroller connection |
|---|---|
| VIN | 3.3V |
| GND | GND |
| SDA | SDA/A4 |
| SCL | SCL/A5 |

The physical pin labels and breadboard connections were inspected before USB power was connected.

## Required Libraries

The following libraries were installed through the Arduino IDE Library Manager:

- Adafruit GFX Library
- Adafruit SH110X

These libraries provide the functions needed to initialize the OLED and display text or graphics.

## I2C Address Test

An I2C scanner program was uploaded to the microcontroller. The scanner searched the I2C bus for connected devices.

The OLED was detected at:

`0x3D`

This confirmed that the microcontroller could communicate with the OLED over the I2C bus.

## Hello World Test

After identifying the correct I2C address, a separate display-test program was uploaded.

The program:

1. Initialized the OLED at address `0x3D`
2. Cleared the display buffer
3. Selected the text size and color
4. Wrote `Hello World` to the display buffer
5. Sent the buffer to the OLED

The message appeared successfully on the display.

## Result

Phase 2 was completed successfully. Header pins were soldered onto the OLED breakout board, and the completed joints were visually inspected before the module was installed on the breadboard.

The OLED was then detected at I2C address `0x3D` and successfully displayed `Hello World`.

This confirmed:

- Successful header-pin assembly
- Secure breadboard installation
- OLED power and ground connections
- SDA and SCL connections
- Correct I2C address
- Required software-library configuration
- Successful microcontroller-to-display communication

## Skills Practiced

- Through-hole header-pin soldering
- Solder-joint inspection
- Header alignment
- Breadboard assembly
- I2C communication
- I2C address scanning
- Embedded display programming
- Library installation
- Incremental hardware testing
- Hardware troubleshooting

## Limitations

The solder joints were evaluated through visual inspection and successful operation of the OLED. This test confirmed that the module operated correctly in the current prototype, but it was not a formal manufacturing or reliability qualification.

## Next Phase

The next phase tests SPI communication between the ESP32-based microcontroller and the MAX30003 ECG breakout board.

## Safety Notice

The OLED was disconnected from power during soldering and physical wiring changes. This project is intended for education and engineering experimentation and is not a certified medical device.
