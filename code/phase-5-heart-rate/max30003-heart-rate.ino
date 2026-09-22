#include <SPI.h>
#include <protocentral_max30003.h>

const int MAX30003_CS_PIN = D10;

MAX30003 max30003(MAX30003_CS_PIN);

unsigned long lastDisplayTime = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(MAX30003_CS_PIN, OUTPUT);
  digitalWrite(MAX30003_CS_PIN, HIGH);

  SPI.begin();

  Serial.println("MAX30003 heart-rate test");

  if (max30003.readDeviceID()) {
    Serial.println("MAX30003 detected.");
  } else {
    Serial.println("ERROR: MAX30003 not detected.");

    while (true) {
      delay(1000);
    }
  }

  max30003.begin();

  Serial.println("Heart-rate detection started.");
  Serial.println("Remain still while the signal settles.");
}

void loop() {
  max30003.updateHeartRate();

  if (millis() - lastDisplayTime >= 1000) {
    lastDisplayTime = millis();

    float bpm = max30003.heartRate();
    unsigned long rrMilliseconds = max30003.rrInterval();

    Serial.print("BPM: ");
    Serial.print(bpm, 1);

    Serial.print(" | R-R interval: ");
    Serial.print(rrMilliseconds);

    Serial.println(" ms");
  }

  delay(10);
}
