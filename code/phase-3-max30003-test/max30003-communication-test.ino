#include <SPI.h>

const int MAX30003_CS = D10;

// Read one 24-bit MAX30003 register
uint32_t readMAX30003Register(uint8_t address) {
  uint32_t value = 0;

  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  digitalWrite(MAX30003_CS, LOW);

  // Register address plus read command
  SPI.transfer((address << 1) | 0x01);

  value |= ((uint32_t)SPI.transfer(0x00) << 16);
  value |= ((uint32_t)SPI.transfer(0x00) << 8);
  value |= SPI.transfer(0x00);

  digitalWrite(MAX30003_CS, HIGH);

  SPI.endTransaction();

  return value;
}

void setup() {
  Serial.begin(115200);

  delay(2000);

  pinMode(MAX30003_CS, OUTPUT);
  digitalWrite(MAX30003_CS, HIGH);

  SPI.begin();

  Serial.println();
  Serial.println("MAX30003 communication test");
  Serial.println("----------------------------");

  // MAX30003 INFO register address
  uint32_t infoRegister = readMAX30003Register(0x0F);

  Serial.print("INFO register: 0x");
  Serial.println(infoRegister, HEX);

  if (infoRegister != 0x000000 &&
      infoRegister != 0xFFFFFF) {
    Serial.println("SUCCESS! MAX30003 detected.");
  } else {
    Serial.println("ERROR: MAX30003 not detected.");
    Serial.println("Check power, ground, SPI wires, and CS.");
  }
}

void loop() {
  delay(1000);
}
