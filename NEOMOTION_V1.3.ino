#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#include <Adafruit_MCP4725.h>
int flag = 1;
Adafruit_MCP4725 dac_x;
Adafruit_MCP4725 dac_y;
int poten_Pin1 = A1;
int poten_Pin2 = A0;
int switchPin1 = 9;
int switchPin2 = 10;
int relay = 4;
int auto_led = 12;
int pot_led = 11;
int val_x ;
  float val_y ;
  float map_x;
  float map_y ;
  float x_v;
  float y_v ;
  float x_ros_dac;
  float y_ros_dac;
  float x_ros_volt;
  float y_ros_volt;
String disp_ros;
void intortext() {
  display.clearDisplay();

  display.setTextSize(5);             // Normal 1:1 pixel scale
  display.setCursor(20,0);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
  display.println("MAX");
  display.display();
}

void mode_joystick() {
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setCursor(0,0);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
  display.print("MODE:JOYSTICK CONTROL");

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setCursor(0,10);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
  display.print("CONTROL FORM WHEELCHAIR JOYSTICK");
  
  display.display();
}

void mode_pot() {

  display.clearDisplay();
   display.setTextSize(1);  
  display.setCursor(0,0);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("MODE: POT CONTROL");
 
 display.setTextSize(1);  
  display.setCursor(0,8);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("Xpot:");
  display.setTextSize(1);  
  display.setCursor(0,16);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("Xdac:");
  display.setTextSize(1);  
  display.setCursor(0,24);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("X_Vt:");
 display.setTextSize(1);  
  display.setCursor(63,8);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("Ypot:");
  display.setTextSize(1);  
  display.setCursor(63,16);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("Ydac:");
  display.setTextSize(1);  
  display.setCursor(63,24);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("Y_Vt:");

display.setTextSize(1);  
  display.setCursor(30,8);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print(int(val_x));
  display.setTextSize(1);  
  display.setCursor(30,16);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print(int(map_x));
  display.setTextSize(1);  
  display.setCursor(30,24);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print(x_v);
 
display.setTextSize(1);  
  display.setCursor(95,8);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print(int(val_y));
  display.setTextSize(1);  
  display.setCursor(95,16);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print(int(map_y));
  display.setTextSize(1);  
  display.setCursor(95,24);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print(y_v);
  display.display();
}
void mode_ros() {
  display.clearDisplay();
   display.setTextSize(1);  
  display.setCursor(0,0);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("MODE: ROS CONTROL");
 
 display.setTextSize(1);  
  display.setCursor(0,8);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
  display.print("Dirt_cmd:");
  display.setTextSize(1);  
  display.setCursor(60,8);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print(disp_ros);



  display.setCursor(0,16);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("Xdac:");
  display.setTextSize(1);  
  display.setCursor(0,24);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("X_Vt:");
 
  display.setTextSize(1);  
  display.setCursor(63,16);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("Ydac:");
  display.setTextSize(1);  
  display.setCursor(63,24);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print("Y_Vt:");

  display.setTextSize(1);  
  display.setCursor(30,16);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print(int(x_ros_dac));
  display.setTextSize(1);  
  display.setCursor(30,24);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print(x_ros_volt);
 

  display.setTextSize(1);  
  display.setCursor(95,16);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print(int(y_ros_dac));
  display.setTextSize(1);  
  display.setCursor(95,24);             // Start at top-left corner
  display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
 display.print(y_ros_volt);
  display.display();

 
  display.display();
}

void setup() {

  Serial.begin(115200);
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  pinMode(pot_led, OUTPUT);
  pinMode(auto_led, OUTPUT);
  pinMode(switchPin2, INPUT);
  pinMode(switchPin1, INPUT);
  // For Adafruit MCP4725A1, the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0, the address is 0x60 or 0x61
  // For MCP4725A2, the address is 0x64 or 0x65
  dac_x.begin(0x61);
  dac_y.begin(0x60);
  intortext();
  delay(1000);

}
void serial_test() {
  if (flag == 1) {
    stopp();
    delay(500);
    flag = 0;
  }
  if (Serial.available()) {
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
  val_x = analogRead(poten_Pin1);
  val_y = analogRead(poten_Pin2);
 map_x = map(val_x, 0, 1023, 400, 3550);
 map_y = map(val_y, 0, 1023, 400, 3550);
x_v = (map_x*5)/4095;
y_v = (map_y*5)/4095;
  dac_x.setVoltage(map_x, false);
  dac_y.setVoltage(map_y, false);

}
void forward() {
  dac_x.setVoltage(3550, false);
  dac_y.setVoltage(1900, false);
  disp_ros = "FORWARD";
  x_ros_dac = 3550;
  y_ros_dac = 1900;
  x_ros_volt = (x_ros_dac*5)/4095;
  y_ros_volt = (y_ros_dac*5)/4095;
}
void backward() {
  dac_x.setVoltage(100, false);
  dac_y.setVoltage(1900, false);
    disp_ros = "BACKWARD";
      x_ros_dac = 100;
  y_ros_dac = 1900;
  x_ros_volt = (x_ros_dac*5)/4095;
  y_ros_volt = (y_ros_dac*5)/4095;
}
void rightward() {
  dac_x.setVoltage(1900, false);
  dac_y.setVoltage(400, false);
  disp_ros = "RIGHT";
    x_ros_dac = 1900;
  y_ros_dac = 400;
  x_ros_volt = (x_ros_dac*5)/4095;
  y_ros_volt = (y_ros_dac*5)/4095;
}
void leftward() {
  dac_x.setVoltage(1900, false);
  dac_y.setVoltage(3550, false);
   disp_ros = "LEFT";
     x_ros_dac = 1900;
  y_ros_dac = 3550;
  x_ros_volt = (x_ros_dac*5)/4095;
  y_ros_volt = (y_ros_dac*5)/4095;
}
void stopp() {
  dac_x.setVoltage(1900, false);
  dac_y.setVoltage(1900, false);
  disp_ros = "STOP";
    x_ros_dac = 1900;
  y_ros_dac = 1900;
  x_ros_volt = (x_ros_dac*5)/4095;
  y_ros_volt = (y_ros_dac*5)/4095;
}
void loop() {
  
  int switchState1 = digitalRead(switchPin1);
  int switchState2 = digitalRead(switchPin2);
  
   if (switchState1 == 0) {
    digitalWrite(relay,LOW);
    digitalWrite(pot_led,LOW);
    digitalWrite(auto_led,LOW);
    mode_joystick();
  }
  
  
  if (switchState1 == 1) {
    digitalWrite(relay,HIGH);
    
    if(switchState2 == 0){
    digitalWrite(pot_led,HIGH);
    digitalWrite(auto_led,LOW);
    mode_pot();
    pot_test();
    }
    
    if(switchState2 == 1){
    digitalWrite(pot_led,LOW);
    digitalWrite(auto_led,HIGH);
    serial_test();
    mode_ros(); 
}  
 }
  }
   
 
