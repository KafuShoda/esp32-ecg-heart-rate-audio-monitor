#include <Wire.h>

const int OLED_SDA_PIN = A2;
const int OLED_SCL_PIN = A3;

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println();
  Serial.println("OLED I2C Scanner");
  Serial.println("SDA/Data = A2");
  Serial.println("SCL/Clock = A3");

  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
  Wire.setClock(100000);
}

void loop() {
  int devicesFound = 0;

  Serial.println();
  Serial.println("Scanning for I2C devices...");

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte result = Wire.endTransmission();

    if (result == 0) {
      Serial.print("I2C device found at address 0x");

      if (address < 16) {
        Serial.print("0");
      }

      Serial.println(address, HEX);
      devicesFound++;
    }
  }

  if (devicesFound == 0) {
    Serial.println("No I2C devices found.");
  } else {
    Serial.println("Scan complete.");
  }

  delay(5000);
}
