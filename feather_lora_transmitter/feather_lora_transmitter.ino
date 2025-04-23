#include <SPI.h>
#include <RH_RF95.h>

// LoRa pins for Adafruit Feather M0
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(9600);    // USB Serial for debugging
  Serial1.begin(9600);   // UART from UNO R4 (pin 0 RX1)

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  if (!rf95.init()) {
    Serial.println("LoRa init failed");
    while (1);
  }

  rf95.setFrequency(915.0);         // Adjust if you're not in North America
  rf95.setTxPower(13, false);       // Safe default power level
}

void loop() {
  if (Serial1.available()) {
    String weight = Serial1.readStringUntil('\n'); // Read from UNO
    Serial.print("Weight received: ");
    Serial.println(weight);

    rf95.send((uint8_t*)weight.c_str(), weight.length());
    rf95.waitPacketSent();

    Serial.println("LoRa message sent");
  }
}
