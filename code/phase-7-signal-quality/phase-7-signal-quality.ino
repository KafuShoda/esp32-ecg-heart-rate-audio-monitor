#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <protocentral_max30003.h>

// --------------------------------------------------
// OLED configuration
// --------------------------------------------------

const int OLED_SDA_PIN = A2;
const int OLED_SCL_PIN = A3;

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET_PIN = -1;
const int OLED_ADDRESS = 0x3D;

// --------------------------------------------------
// MAX30003 configuration
// --------------------------------------------------

const int MAX30003_CS_PIN = D10;

// --------------------------------------------------
// Signal-quality settings
// --------------------------------------------------

// These are broad experimental limits, not medical limits.
const float MIN_BPM = 30.0;
const float MAX_BPM = 220.0;

const unsigned long MIN_RR_MS = 250;
const unsigned long MAX_RR_MS = 2000;

// Allowed difference between reported BPM and 60000 / R-R.
const float MAX_BPM_RR_DIFFERENCE = 3.0;

// Reject a one-second change larger than this amount.
const float MAX_INSTANT_BPM_CHANGE = 20.0;

// Require this many consecutive acceptable one-second reports.
const unsigned int REQUIRED_STABLE_SECONDS = 30;

// Number of values used by the median filter.
const int FILTER_SIZE = 5;

const unsigned long REPORT_INTERVAL_MS = 1000;

// --------------------------------------------------
// Objects and program state
// --------------------------------------------------

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET_PIN
);

MAX30003 max30003(MAX30003_CS_PIN);

enum SignalState {
  ACQUIRING,
  VALID_SIGNAL,
  POOR_SIGNAL
};

SignalState signalState = ACQUIRING;

unsigned long lastReportTime = 0;
unsigned int stableSeconds = 0;

float bpmBuffer[FILTER_SIZE];
unsigned long rrBuffer[FILTER_SIZE];

int bufferCount = 0;
int bufferIndex = 0;

// --------------------------------------------------
// Buffer and filtering functions
// --------------------------------------------------

void clearCandidateBuffer() {
  bufferCount = 0;
  bufferIndex = 0;
}

void addCandidate(float bpm, unsigned long rrMilliseconds) {
  bpmBuffer[bufferIndex] = bpm;
  rrBuffer[bufferIndex] = rrMilliseconds;

  bufferIndex = (bufferIndex + 1) % FILTER_SIZE;

  if (bufferCount < FILTER_SIZE) {
    bufferCount++;
  }
}

float medianBpm() {
  if (bufferCount == 0) {
    return 0.0;
  }

  float temporary[FILTER_SIZE];

  for (int i = 0; i < bufferCount; i++) {
    temporary[i] = bpmBuffer[i];
  }

  for (int i = 1; i < bufferCount; i++) {
    float value = temporary[i];
    int j = i - 1;

    while (j >= 0 && temporary[j] > value) {
      temporary[j + 1] = temporary[j];
      j--;
    }

    temporary[j + 1] = value;
  }

  return temporary[bufferCount / 2];
}

unsigned long medianRr() {
  if (bufferCount == 0) {
    return 0;
  }

  unsigned long temporary[FILTER_SIZE];

  for (int i = 0; i < bufferCount; i++) {
    temporary[i] = rrBuffer[i];
  }

  for (int i = 1; i < bufferCount; i++) {
    unsigned long value = temporary[i];
    int j = i - 1;

    while (j >= 0 && temporary[j] > value) {
      temporary[j + 1] = temporary[j];
      j--;
    }

    temporary[j + 1] = value;
  }

  return temporary[bufferCount / 2];
}

// --------------------------------------------------
// OLED functions
// --------------------------------------------------

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

void showAcquiringScreen(unsigned int secondsCompleted) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(34, 0);
  display.println("HEART RATE");

  display.setTextSize(2);
  display.setCursor(29, 17);
  display.println("-- BPM");

  display.setTextSize(1);
  display.setCursor(0, 43);
  display.println("Acquiring...");

  display.setCursor(0, 54);
  display.print("Stable: ");
  display.print(secondsCompleted);
  display.print("/");
  display.print(REQUIRED_STABLE_SECONDS);
  display.println(" s");

  display.display();
}

void showPoorSignalScreen(const char* reason) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(34, 0);
  display.println("HEART RATE");

  display.setTextSize(2);
  display.setCursor(12, 18);
  display.println("-- BPM");

  display.setTextSize(1);
  display.setCursor(0, 42);
  display.println("POOR SIGNAL");

  display.setCursor(0, 54);
  display.println(reason);

  display.display();
}

void showValidScreen(
  float filteredBpm,
  unsigned long filteredRr
) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(34, 0);
  display.println("HEART RATE");

  display.setTextSize(2);
  display.setCursor(18, 17);
  display.print(filteredBpm, 0);
  display.println(" BPM");

  display.setTextSize(1);
  display.setCursor(0, 42);
  display.print("R-R: ");
  display.print(filteredRr);
  display.println(" ms");

  display.setCursor(0, 54);
  display.println("Status: VALID");

  display.display();
}

// --------------------------------------------------
// State functions
// --------------------------------------------------

void enterPoorSignal(const char* reason) {
  signalState = POOR_SIGNAL;
  stableSeconds = 0;
  clearCandidateBuffer();

  showPoorSignalScreen(reason);

  Serial.print("State: POOR_SIGNAL");
  Serial.print(" | Reason: ");
  Serial.println(reason);
}

void processCandidate(
  float bpm,
  unsigned long rrMilliseconds
) {
  // Check broad numerical limits.
  bool bpmInRange =
    bpm >= MIN_BPM &&
    bpm <= MAX_BPM;

  bool rrInRange =
    rrMilliseconds >= MIN_RR_MS &&
    rrMilliseconds <= MAX_RR_MS;

  if (!bpmInRange || !rrInRange) {
    enterPoorSignal("Invalid BPM/R-R");
    return;
  }

  // Check mathematical consistency.
  float expectedBpm =
    60000.0 / (float)rrMilliseconds;

  float bpmRrDifference =
    fabs(bpm - expectedBpm);

  if (bpmRrDifference > MAX_BPM_RR_DIFFERENCE) {
    enterPoorSignal("BPM/R-R mismatch");
    return;
  }

  // Compare the new candidate with the recent median.
  if (bufferCount > 0) {
    float recentMedian = medianBpm();
    float change = fabs(bpm - recentMedian);

    if (change > MAX_INSTANT_BPM_CHANGE) {
      enterPoorSignal("Abrupt BPM jump");
      return;
    }
  }

  // The candidate passed the available checks.
  if (signalState == POOR_SIGNAL) {
    signalState = ACQUIRING;
    stableSeconds = 0;
    clearCandidateBuffer();
  }

  addCandidate(bpm, rrMilliseconds);

  float filteredBpm = medianBpm();
  unsigned long filteredRr = medianRr();

  if (signalState == ACQUIRING) {
    stableSeconds++;

    if (stableSeconds >= REQUIRED_STABLE_SECONDS) {
      stableSeconds = REQUIRED_STABLE_SECONDS;
      signalState = VALID_SIGNAL;
    }
  }

  if (signalState == VALID_SIGNAL) {
    showValidScreen(filteredBpm, filteredRr);

    Serial.print("State: VALID");
    Serial.print(" | Raw BPM: ");
    Serial.print(bpm, 1);
    Serial.print(" | Filtered BPM: ");
    Serial.print(filteredBpm, 1);
    Serial.print(" | Filtered R-R: ");
    Serial.print(filteredRr);
    Serial.println(" ms");
  } else {
    showAcquiringScreen(stableSeconds);

    Serial.print("State: ACQUIRING");
    Serial.print(" | Candidate BPM: ");
    Serial.print(bpm, 1);
    Serial.print(" | R-R: ");
    Serial.print(rrMilliseconds);
    Serial.print(" ms");
    Serial.print(" | Stable: ");
    Serial.print(stableSeconds);
    Serial.print("/");
    Serial.print(REQUIRED_STABLE_SECONDS);
    Serial.println(" s");
  }
}

// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("ERROR: OLED was not detected.");

    while (true) {
      delay(1000);
    }
  }

  showMessage("OLED detected.", "Checking ECG...");
  Serial.println("OLED detected.");

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
  Serial.println("Signal-quality protection started.");
  Serial.println("Hardware lead-off API not enabled.");
  Serial.println("Audio output disabled.");

  max30003.begin();

  signalState = ACQUIRING;
  stableSeconds = 0;
  clearCandidateBuffer();

  showAcquiringScreen(0);

  lastReportTime = millis();
}

// --------------------------------------------------
// Main loop
// --------------------------------------------------

void loop() {
  // Continue updating the MAX30003 heart-rate detector.
  max30003.updateHeartRate();

  // Evaluate the latest result once per second.
  if (millis() - lastReportTime >= REPORT_INTERVAL_MS) {
    lastReportTime = millis();

    float bpm = max30003.heartRate();
    unsigned long rrMilliseconds =
      max30003.rrInterval();

    processCandidate(bpm, rrMilliseconds);
  }

  delay(10);
}
