#include "HX711.h"

#define DOUT  3
#define CLK   2

HX711 scale;

void setup() {
  Serial.begin(9600); // Send to Feather via UART
  scale.begin(DOUT, CLK);
  scale.set_scale();   // You can calibrate here later
  scale.tare();        // Reset scale to 0
}

void loop() {
  float weight = scale.get_units(5); // Average over 5 readings
  Serial.println(weight, 2);         // Send to Feather, 2 decimal places
  delay(1000);                       // Read every second
}
