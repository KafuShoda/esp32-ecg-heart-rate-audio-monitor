#include <SPI.h>
#include <protocentral_max30003.h>

const int MAX30003_CS_PIN = D10;

MAX30003 max30003(MAX30003_CS_PIN);

unsigned long lastReportTime = 0;
unsigned long lastSampleTime = 0;
unsigned long samplesThisSecond = 0;
unsigned long totalSamples = 0;
unsigned long dropoutSeconds = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(MAX30003_CS_PIN, OUTPUT);
  digitalWrite(MAX30003_CS_PIN, HIGH);

  SPI.begin();

  Serial.println();
  Serial.println("MAX30003 10-minute continuity test");
  Serial.println("---------------------------------");

  if (!max30003.readDeviceID()) {
    Serial.println("ERROR: MAX30003 not detected.");
    Serial.println("Check power, ground, and SPI wiring.");

    while (true) {
      delay(1000);
    }
  }

  Serial.println("MAX30003 detected.");
  Serial.println("Starting raw-sample monitoring.");
  Serial.println("Do not press reset during the test.");
  Serial.println();

  max30003.begin();
  delay(200);

  lastReportTime = millis();
  lastSampleTime = millis();
}

void loop() {
  int32_t ecgSample;

  if (max30003.readEcgSample(ecgSample)) {
    samplesThisSecond++;
    totalSamples++;
    lastSampleTime = millis();
  }

  unsigned long currentTime = millis();

  if (currentTime - lastReportTime >= 1000) {
    unsigned long uptimeSeconds = currentTime / 1000;
    unsigned long sampleAge = currentTime - lastSampleTime;

    Serial.print("Time: ");
    Serial.print(uptimeSeconds);
    Serial.print(" s");

    Serial.print(" | Samples: ");
    Serial.print(samplesThisSecond);

    Serial.print(" | Total: ");
    Serial.print(totalSamples);

    Serial.print(" | Last sample age: ");
    Serial.print(sampleAge);
    Serial.print(" ms");

    if (samplesThisSecond > 0) {
      Serial.println(" | Status: STREAMING");
    } else {
      dropoutSeconds++;

      Serial.print(" | Status: NO SAMPLES");
      Serial.print(" | Dropout seconds: ");
      Serial.println(dropoutSeconds);
    }

    samplesThisSecond = 0;
    lastReportTime = currentTime;
  }

  delay(8);
}
