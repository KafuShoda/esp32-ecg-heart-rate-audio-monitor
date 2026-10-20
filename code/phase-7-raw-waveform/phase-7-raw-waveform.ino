#include <SPI.h>
#include <protocentral_max30003.h>

// MAX30003 chip-select connection
const int MAX30003_CS_PIN = D10;

// Average four raw samples into each displayed point.
// 4 produces roughly 31 plotted points per second.
const int DISPLAY_BLOCK_SIZE = 4;

MAX30003 max30003(MAX30003_CS_PIN);

int64_t sampleSum = 0;
int samplesInBlock = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(MAX30003_CS_PIN, OUTPUT);
  digitalWrite(MAX30003_CS_PIN, HIGH);

  SPI.begin();

  // Confirm communication with the MAX30003.
  if (!max30003.readDeviceID()) {
    Serial.println("MAX30003 not detected");

    while (true) {
      delay(1000);
    }
  }

  // Configure ECG acquisition.
  max30003.begin();
  delay(200);
}

void loop() {
  int32_t ecgSample;

  // Read a new raw ECG sample when one is available.
  if (max30003.readEcgSample(ecgSample)) {
    sampleSum += ecgSample;
    samplesInBlock++;

    // Plot the average after collecting four samples.
    if (samplesInBlock >= DISPLAY_BLOCK_SIZE) {
      int32_t averagedSample =
        (int32_t)(sampleSum / DISPLAY_BLOCK_SIZE);

      Serial.println(averagedSample);

      sampleSum = 0;
      samplesInBlock = 0;
    }
  }

  // Continue reading the sensor at approximately 125 samples/second.
  delay(8);
}
