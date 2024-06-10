#include <Arduino.h>
#define T_BLINK 0.75
#define N_LED 4
#define T_ON (T_BLINK/N_LED)
#define N_RST_LEFT 0
#define N_RST_RIGHT 1
#define CLK 2
uint8_t blink_flag = 0;
uint8_t left = 0;
IntervalTimer tim;
void set_pins(int left, int right);
void set_clk();
void setup(){
  Serial.begin(9600);
  pinMode(N_RST_LEFT,  OUTPUT);
  pinMode(N_RST_RIGHT, OUTPUT);
  pinMode(CLK,       OUTPUT);
  set_pins(0,0);
  tim.begin(set_clk, T_ON/4.0*1e6);
}

void loop(){
  set_pins(1,0);
  delay(5000);
  set_pins(0,0);
  delay(50);
  set_pins(0,1);
  delay(5000);
  set_pins(0,0);
  delay(50);
  set_pins(1,1);
  delay(5000);
  set_pins(0,0);
  delay(50);
  set_pins(0,0);
  delay(100);
  Serial.print("T_BLINK: "); Serial.print("\t"); Serial.println(T_BLINK);
  Serial.print("N_LED  : "); Serial.print("\t"); Serial.println(N_LED);
  Serial.print("T_ON   : "); Serial.print("\t"); Serial.println(T_ON);
  delay(1000);
}

void set_pins(int left, int right){
  digitalWrite(N_RST_LEFT,  left);
  digitalWrite(N_RST_RIGHT, right);
}

void set_clk(){
  static uint8_t on = 0;
  digitalWrite(CLK, on);
  on = !on;
}