#include <SPI.h>
#include <protocentral_max30003.h>

const int MAX30003_CS_PIN = D10;

MAX30003 max30003(MAX30003_CS_PIN);

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(MAX30003_CS_PIN, OUTPUT);
  digitalWrite(MAX30003_CS_PIN, HIGH);

  SPI.begin();

  if (max30003.readDeviceID()) {
    Serial.println("MAX30003 detected.");
  } else {
    Serial.println("ERROR: MAX30003 not detected.");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("Initializing ECG acquisition...");
  max30003.begin();
  Serial.println("ECG acquisition started.");
}

void loop() {
  static int sampleCounter = 0;
  int32_t ecgSample = 0;

  if (max30003.readEcgSample(ecgSample)) {
    sampleCounter++;

    // Display only every fourth sample
    if (sampleCounter >= 2) {
      Serial.println(ecgSample);
      sampleCounter = 0;
    }
  }

  delay(8);
}
