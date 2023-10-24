#include <Wire.h>
#include <Adafruit_MCP4725.h>
int flag = 1;
Adafruit_MCP4725 dac_x;
Adafruit_MCP4725 dac_y;
const int poten_Pin1 = A0;
const int poten_Pin2 = A1;
const int switchPin1 = 11;
const int switchPin2 = 12;

void setup() {
  Serial.begin(115200);
  pinMode(switchPin2, INPUT);
  pinMode(switchPin1, INPUT);
  // For Adafruit MCP4725A1, the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0, the address is 0x60 or 0x61
  // For MCP4725A2, the address is 0x64 or 0x65
  dac_x.begin(0x61);
  dac_y.begin(0x60);

}
void loop() {
  int switchState1 = digitalRead(switchPin1);
  //Serial.println("Switch1: " + String(switchState1));
  int switchState2 = digitalRead(switchPin2);
  //Serial.println("Switch2: " + String(switchState2));
  if (switchState1 == 1) {
    pot_test();
  }
  if (switchState1 == 0) {
    serial_test();
  }
}
void serial_test() {
  if (flag == 1) {
    stopp();
    delay(500);
    flag = 0;
  }
  if (Serial.available()) {
    Serial.println("<<<<<<<<<<<<<<<SERIAL TEST BEGIN>>>>>>>>>>>>>>>>>>>>");
    // Read the serial input as a string
    String input = Serial.readStringUntil('\n');

    Serial.println("SERIAL INPUT : " + String(input) + " ");
    int in_val = input.toInt();
    if (in_val == 1) {
      Serial.println("forward");
      forward();
    }
    if (in_val == 2) {
      Serial.println("backward");
      backward();
    }
    if (in_val == 3) {
      Serial.println("right");
      rightward();
    }
    if (in_val == 4) {
      Serial.println("left");
      leftward();
    }
    if (in_val == 0) {
      Serial.println("stop");
      stopp();
    }
    // Set the DAC voltages using the mapped values

  }
}
void pot_test() {
  flag = 1;
  Serial.println("<<<<<<<<<<<<<<<POT TEST BEGIN>>>>>>>>>>>>>>>>>>>>");
  int val_x = analogRead(poten_Pin1);
  int val_y = analogRead(poten_Pin2);
  int map_x = map(val_x, 0, 1023, 400, 3550);
  int map_y = map(val_y, 0, 1023, 400, 3550);
  dac_x.setVoltage(map_x, false);
  dac_y.setVoltage(map_y, false);

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
