#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac_x;
Adafruit_MCP4725 dac_y;

void setup(void) {
  Serial.begin(115200);

  // For Adafruit MCP4725A1, the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0, the address is 0x60 or 0x61
  // For MCP4725A2, the address is 0x64 or 0x65
  dac_x.begin(0x61);
  dac_y.begin(0x60);
}
void forward() {
  dac_x.setVoltage(3550, false);
  dac_y.setVoltage(1900, false);
}
void backward() {
  dac_x.setVoltage(100, false);
  dac_y.setVoltage(1900, false);
}
void rightward() {
  dac_x.setVoltage(1900, false);
  dac_y.setVoltage(400, false);
}
void leftward() {
  dac_x.setVoltage(1900, false);
  dac_y.setVoltage(3550, false);
}
void stopp() {
  dac_x.setVoltage(1900, false);
  dac_y.setVoltage(1900, false);
}
void loop(void) {
  if (Serial.available()) {
    // Read the serial input as a string
    String input = Serial.readStringUntil('\n');

    Serial.print("in: " + String(input));
    int in_val = input.toInt();
    if (in_val == 1) {
        Serial.print("forward");
      forward();
    }
    if (in_val == 2) {
         Serial.print("backward");
      backward(); 
    }
    if (in_val == 3) {
         Serial.print("right");
      rightward();
    }
    if (in_val == 4) {
         Serial.print("left");
      leftward();
    }
    if (in_val == 0) {
         Serial.print("stop");
      stopp();
    }
    // Set the DAC voltages using the mapped values

  }
}
