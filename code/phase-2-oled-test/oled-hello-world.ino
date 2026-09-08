#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3D
#define OLED_RESET -1

const int OLED_SDA_PIN = A2;
const int OLED_SCL_PIN = A3;

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Start I2C on the working alternate pins
  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
  Wire.setClock(100000);

  // The final false prevents the library from restarting
  // I2C on the default A4/A5 pins.
  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS,
        true,
        false
      )) {
    Serial.println("OLED initialization failed.");

    while (true) {
      delay(100);
    }
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Hello");
  display.println("World");
  display.display();

  Serial.println("Hello World displayed successfully.");
}

void loop() {
}
