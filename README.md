# Seat-Occupancy-Detection-Hardware-Model-

HX711 + Load Cell + ESP32

📌 Project Overview

This project implements a real-time chair occupancy detection system using a load cell and the HX711 amplifier module.

Instead of measuring exact weight, the system uses raw sensor values and a threshold-based approach to determine:

✅ Chair Occupied
❌ Chair Empty

🚫 No calibration
🚫 No offset handling
✔ Simple & fast deployment

🧠 How It Works
Load cells detect force when someone sits.
HX711 converts analog signals into digital values.
ESP32 reads multiple samples for stability.
Average value is compared with a threshold.
If |Raw Value| > Threshold → OCCUPIED
Else → EMPTY
⚙️ Hardware Requirements
ESP32
HX711 Load Cell Amplifier
Load Cells (2 × 3-wire or equivalent)
Jumper wires
Chair (for mounting)
🔌 Pin Configuration
HX711	ESP32
DOUT	34
CLK	26
📦 Library Installation

Install the HX711 library:

Arduino IDE → Library Manager → Search "HX711" → Install

Recommended:

HX711 by Bogde
🧾 Code
#include "HX711.h"

#define DOUT 34
#define CLK  26

HX711 scale;

const long THRESHOLD = 5000;
const int SAMPLES = 10;

bool isOccupied = false;

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, CLK);
  delay(1000);
}

void loop() {
  if (!scale.is_ready()) {
    Serial.println("HX711 not ready!");
    delay(1000);
    return;
  }

  long rawValue = scale.read_average(SAMPLES);

  Serial.print("Raw Value: ");
  Serial.print(rawValue);

  if (rawValue > THRESHOLD || rawValue < -THRESHOLD) {
    if (!isOccupied) {
      Serial.println(" --> OCCUPIED");
      isOccupied = true;
    } else {
      Serial.println(" --> still occupied");
    }
  } else {
    if (isOccupied) {
      Serial.println(" --> EMPTY");
      isOccupied = false;
    } else {
      Serial.println(" --> still empty");
    }
  }

  delay(800);
}
📊 Sample Output
Raw Value: 11200 --> OCCUPIED
Raw Value: 11500 --> still occupied
Raw Value: 2100  --> EMPTY
Raw Value: 1800  --> still empty
🔧 Parameter Tuning
Threshold
const long THRESHOLD = 5000;
Increase → reduces false positives
Decrease → improves sensitivity
Sampling
const int SAMPLES = 10;
Higher → stable but slower
Lower → faster but noisy
⚠️ Troubleshooting
❌ HX711 not detected
Check VCC & GND
Verify pin connections (34, 26)
Ensure proper wiring of load cells
❌ Always 0 or no change
Load cells wired incorrectly
HX711 damaged
No pressure applied
❌ Unstable readings
Increase SAMPLES
Ensure firm mounting under chair
🚀 Future Improvements
📡 WiFi-based occupancy monitoring
💡 LED/Buzzer indicator
📊 Dashboard for seat analytics
🎯 Proper calibration for weight measurement
📁 Project Structure
chair-occupancy-detection/
│── chair_occupancy.ino
│── README.md
📸 (Optional Additions for GitHub)

You can enhance this repo by adding:

Wiring diagram (Fritzing)
Setup images
Demo video GIF
