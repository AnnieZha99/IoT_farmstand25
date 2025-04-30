#include "HX711.h"

// Pins for HX711
#define DOUT  3
#define CLK   2

HX711 scale;

// Uncomment the next line to run calibration mode
#define CALIBRATION_MODE

// Replace this with your calibrated scale factor once done
float scaleFactor = 2280.0;

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT, CLK);

#ifdef CALIBRATION_MODE
  Serial.println("Calibration mode...");
  Serial.println("Remove all weight. Taring...");
  delay(2000);
  scale.set_scale();
  scale.tare();
  Serial.println("Now place a known weight on the scale.");
  Serial.println("Waiting 5 seconds...");
  delay(5000);
  
  long reading = scale.get_units(10);
  Serial.print("Raw average reading: ");
  Serial.println(reading);
  Serial.println("Divide this value by the known weight in kg to get your scale factor.");
  Serial.println("Then update 'scaleFactor' in the code and disable CALIBRATION_MODE.");
#else
  scale.set_scale(scaleFactor); // set your calibrated scale factor
  scale.tare();                 // reset the scale to 0
#endif
}

void loop() {
#ifdef CALIBRATION_MODE
  Serial.print("Raw reading: ");
  Serial.println(scale.get_units(5));
  delay(1000);
#else
  float weight = scale.get_units(5);
  Serial.print("Measured weight: ");
  Serial.print(weight, 2);
  Serial.println(" kg");
  delay(1000);
#endif
}
