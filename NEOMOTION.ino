int x_analog_in = A0;
int y_analog_in = A1;
int Auto_manu_sw = 12;
int Manu_select_sw = 11;
int Auto_manu_relay = 4;
int Auto_manu_led = 7;
int Manu_select_led = 10;
int Encoder_Leftmotor = 2;
int Encoder_Rightmotor = 3;
int Auto_manu_sw_val, Manu_select_sw_val;
int Pot_x = A0;
int Pot_y = A1;
int Pot_x_val;
int Pot_y_val;
// SERIAL ENABLE
#define DEBUG true
#define Serial if(DEBUG)Serial

// DELAY
unsigned long previousMillis = 0;
const unsigned long interval = 2000;
void setup() {
  Serial.begin(115200);
  pinMode(Auto_manu_sw, INPUT);
  pinMode(Manu_select_sw, INPUT);
  pinMode(Pot_x, INPUT);
  pinMode(Pot_y, INPUT);
  pinMode(Auto_manu_relay, OUTPUT);
  pinMode(Manu_select_led, OUTPUT);
  pinMode(Auto_manu_led, OUTPUT);

  Serial.println("<<<<<< BOOTING SYSTEM >>>>>>");
  Serial.println("------------START-----------");
  delay(5000);
}

void loop() {
  Auto_manu_sw_val = digitalRead(Auto_manu_sw);
  Manu_select_sw_val = digitalRead(Manu_select_sw);
  Auto_mauval();
  Manuval_pot_mode();  
  Serial.println("Auto_manu_sw_val :" + String(Auto_manu_sw_val) + ", Manu_select_sw_val : " + String(Manu_select_sw_val));

}
void Manuval_pot_mode() {
  Pot_x_val = analogRead(Pot_x);
  Pot_y_val = analogRead(Pot_y);
  Serial.println();
  int x_map = map(Pot_x_val,0,1023,0,4095);
  int y_map = map(Pot_y_val,0,1023,0,4095);
  Serial.println("Pot_x_val :" + String(Pot_x_val) + ", Pot_y_val : " + String(Pot_y_val) +" ,x_map :" + String(x_map) + ", y_map : " + String(y_map));


}

void Auto_mauval() {
  if (Manu_select_sw_val == 0 && Auto_manu_sw_val == 0) {
    digitalWrite(Manu_select_led, LOW);
    digitalWrite(Auto_manu_relay, LOW);
    digitalWrite(Auto_manu_led, LOW);
    Serial.println("<<<<<<<<<<<<<<< Contorl change to MANUVAL_MODE by JOYSTICK >>>>>>>>>>>>");
  }
  if (Manu_select_sw_val == 0 && Auto_manu_sw_val == 1 ) {
    digitalWrite(Auto_manu_relay, HIGH);
    digitalWrite(Manu_select_led, LOW);
    digitalWrite(Auto_manu_led, HIGH);
    Serial.println("<<<<<<<<<<<<<<< Contorl change to AUTO_MODE >>>>>>>>>>>>");
  }
  if (Manu_select_sw_val == 1 && Auto_manu_sw_val == 0 ) {
    digitalWrite(Auto_manu_relay, LOW);
    digitalWrite(Manu_select_led, LOW);
    digitalWrite(Auto_manu_led, LOW);
    Serial.println("<<<<<<<<<<<<<<< Contorl change to MANUVAL by JOYSTICK >>>>>>>>>>>>");
  }

  if (Manu_select_sw_val == 1 && Auto_manu_sw_val == 1 ) {
    digitalWrite(Auto_manu_relay, HIGH);
    digitalWrite(Manu_select_led, HIGH);
    digitalWrite(Auto_manu_led, LOW);

    Serial.println("<<<<<<<<<<<<<<< Contorl change to MANUVAL -> USE POT X,Y >>>>>>>>>>>>");
  }

}
