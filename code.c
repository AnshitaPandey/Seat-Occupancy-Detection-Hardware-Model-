#include "HX711.h"

#define DOUT 34   // HX711 Data pin
#define CLK  26   // HX711 Clock pin

HX711 scale;

// ---- SETTINGS ----
const long THRESHOLD = 5000;   // Adjust after testing
const int SAMPLES = 10;        // Averaging for stability

// ---- VARIABLES ----
bool isOccupied = false;

void setup() {
  Serial.begin(115200);
  Serial.println("=== Chair Occupancy Detection System ===");
  Serial.println("No offset / No calibration mode");
  
  scale.begin(DOUT, CLK);
  delay(1000);
}

void loop() {
  if (!scale.is_ready()) {
    Serial.println("HX711 not ready. Check wiring!");
    delay(1000);
    return;
  }

  // Take stable reading
  long rawValue = scale.read_average(SAMPLES);

  Serial.print("Raw Value: ");
  Serial.print(rawValue);

  // ---- OCCUPANCY LOGIC ----
  if (rawValue > THRESHOLD || rawValue < -THRESHOLD) {
    
    if (!isOccupied) {
      Serial.println("  --> Chair OCCUPIED");
      isOccupied = true;
    } else {
      Serial.println("  --> (still occupied)");
    }

  } else {

    if (isOccupied) {
      Serial.println("  --> Chair EMPTY");
      isOccupied = false;
    } else {
      Serial.println("  --> (still empty)");
    }
  }

  delay(800);
}
