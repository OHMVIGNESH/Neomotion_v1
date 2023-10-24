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

void loop(void) {
  if (Serial.available()) {
    // Read the serial input as a string
    String input = Serial.readStringUntil('\n');

    // Split the input string into two parts
    int commaPos = input.indexOf(',');
    if (commaPos != -1) {
      // Extract the two values from the input string
      String input1_str = input.substring(0, commaPos);
      String input2_str = input.substring(commaPos + 1);

      // Convert the extracted strings to float values
      float x = input1_str.toFloat();
      float y = input2_str.toFloat();



      Serial.print("x: ");
      Serial.println(x);
      Serial.print("y: ");
      Serial.println(y);

      // Set the DAC voltages using the mapped values
      dac_x.setVoltage(x, false);
      dac_y.setVoltage(y, false);
    }
  }
}
