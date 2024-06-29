#include <Arduino.h>
#include "pid.h"

#define TS 0.001
#define KP 0.08
#define TAU_I 0.01
#define TAU_D 0.2
#define ALPHA 0.4
#define LIM 10
#define EN_LIM false
#define CTRL_ERROR 1.0
#define LINE_FEED 0x0A
#define BUF_SIZE 128
#define LOOP_DELAY_MS 25
#define CMD_TEST_PID 0x54
#define CMD_PRINT_PID 0x50
bool cmd_available = false;
uint8_t bfr[BUF_SIZE];
uint8_t bfr_idx = 0;
PID ctrl;
void clear_buffer()
{
  for(int i = 0; i < BUF_SIZE; i++)
  {
    bfr[i] = 0;
  }
}
void print_cmd()
{
  for(int i = 0; i < bfr_idx; i++){
      Serial.print((char)bfr[i]);
  }
}
void check_cmd()
{
  if(cmd_available)
  {
    for(int i = 0; i < bfr_idx; i++){
      Serial.print((char)bfr[i]);
    }
    Serial.println();
    for(int i = 0; i < bfr_idx; i++){
      Serial.print(bfr[i]);
    }
    Serial.println();
    cmd_available = 0;
    bfr_idx = 0;
  }
}
void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  ctrl.begin(TS, KP, TAU_I, TAU_D, ALPHA, LIM, EN_LIM);
  clear_buffer();
  bfr_idx = 0;
  delay(500);
  Serial.println("Setup done");
}

void loop()
{
  if(cmd_available)
  {
    print_cmd();
    cmd_available = 0;
    bfr_idx = 0;
    if((bfr[0] == CMD_TEST_PID) && (bfr[1] == LINE_FEED))
    {
      Serial.println("PID test command received");
      ctrl.test(CTRL_ERROR);
    }
    if((bfr[0] == CMD_PRINT_PID) && (bfr[1] == LINE_FEED))
    {
      Serial.println("PID print command received");
      ctrl.print();
    }
  }
  //ctrl.test(CTRL_ERROR);
  delay(LOOP_DELAY_MS);
}

void serialEvent() {
  if(bfr_idx < BUF_SIZE)
  {
    while (Serial.available()) 
    {
    Serial.println(bfr_idx);
    uint8_t b = Serial.read();
    bfr[bfr_idx] = b;
    bfr_idx++;
    if(b == LINE_FEED)
    {
      Serial.println("Command done");
      cmd_available = 1;
    }
    }
  }
}