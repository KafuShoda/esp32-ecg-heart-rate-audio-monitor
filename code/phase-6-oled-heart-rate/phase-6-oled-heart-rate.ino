#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <protocentral_max30003.h>

// OLED configuration
const int OLED_SDA_PIN = A2;
const int OLED_SCL_PIN = A3;
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET_PIN = -1;
const int OLED_ADDRESS = 0x3D;

// MAX30003 configuration
const int MAX30003_CS_PIN = D10;

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET_PIN
);

MAX30003 max30003(MAX30003_CS_PIN);

unsigned long lastDisplayUpdate = 0;

void showMessage(const char* line1, const char* line2) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 12);
  display.println(line1);

  display.setCursor(0, 32);
  display.println(line2);

  display.display();
}

void showHeartRate(float bpm, unsigned long rrMilliseconds) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Title
  display.setTextSize(1);
  display.setCursor(34, 0);
  display.println("HEART RATE");

  // Large BPM value
  display.setTextSize(2);
  display.setCursor(18, 17);
  display.print(bpm, 0);
  display.println(" BPM");

  // R-R interval
  display.setTextSize(1);
  display.setCursor(0, 42);
  display.print("R-R: ");
  display.print(rrMilliseconds);
  display.println(" ms");

  // Signal status
  display.setCursor(0, 54);
  display.println("Status: BPM estimate");

  display.display();
}

void showAcquiringScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(34, 0);
  display.println("HEART RATE");

  display.setTextSize(2);
  display.setCursor(29, 20);
  display.println("-- BPM");

  display.setTextSize(1);
  display.setCursor(31, 51);
  display.println("Acquiring...");

  display.display();
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  // Start the OLED on the known working I2C pins
  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("ERROR: OLED was not detected.");

    while (true) {
      delay(1000);
    }
  }

  showMessage("OLED detected.", "Checking ECG...");
  Serial.println("OLED detected.");

  // Start SPI and prepare the MAX30003 chip-select pin
  pinMode(MAX30003_CS_PIN, OUTPUT);
  digitalWrite(MAX30003_CS_PIN, HIGH);
  SPI.begin();

  if (!max30003.readDeviceID()) {
    Serial.println("ERROR: MAX30003 was not detected.");
    showMessage("ECG ERROR", "Check SPI wiring");

    while (true) {
      delay(1000);
    }
  }

  Serial.println("MAX30003 detected.");

  // Use the same initialization method that worked in Phase 5
  max30003.begin();

  showAcquiringScreen();

  Serial.println("Heart-rate detection started.");
  Serial.println("Waiting for a plausible BPM estimate...");
}

void loop() {
  // This must run repeatedly so heartbeats can be processed.
  max30003.updateHeartRate();

  // Refresh the OLED and Serial Monitor once per second.
  if (millis() - lastDisplayUpdate >= 1000) {
    lastDisplayUpdate = millis();

    float bpm = max30003.heartRate();
    unsigned long rrMilliseconds = max30003.rrInterval();

    // Reject zero and obviously invalid initial values.
    bool plausibleReading =
      bpm >= 30.0 &&
      bpm <= 220.0 &&
      rrMilliseconds >= 250 &&
      rrMilliseconds <= 2000;

    if (plausibleReading) {
      showHeartRate(bpm, rrMilliseconds);

      Serial.print("BPM: ");
      Serial.print(bpm, 1);
      Serial.print(" | R-R interval: ");
      Serial.print(rrMilliseconds);
      Serial.println(" ms");
    } else {
      showAcquiringScreen();

      Serial.print("No plausible reading yet. BPM: ");
      Serial.print(bpm, 1);
      Serial.print(" | R-R interval: ");
      Serial.print(rrMilliseconds);
      Serial.println(" ms");
    }
  }

  delay(10);
}
