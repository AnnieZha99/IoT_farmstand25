#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(9600);      // USB debug
  Serial1.begin(9600);     // RX1 reads from UNO's TX

  // Reset LoRa module
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  if (!rf95.init()) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  rf95.setFrequency(915.0);     // Set your region frequency
  rf95.setTxPower(13, false);   // Safe power
}

void loop() {
  if (Serial1.available()) {
    String value = Serial1.readStringUntil('\n');
    Serial.print("Received raw: ");
    Serial.println(value);

    rf95.send((uint8_t*)value.c_str(), value.length());
    rf95.waitPacketSent();
    Serial.println("Sent over LoRa");
  }
}
