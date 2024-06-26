#include <Arduino.h>
#include "pid.h"

#define TS 0.001
#define KP 1.75
#define TAU_I 0.01
#define TAU_D 0.2
#define ALPHA 0.4
PID ctrl;
void setup(){
  Serial.begin(115200);
  ctrl.begin(TS, KP, TAU_I, TAU_D, ALPHA);
}

void loop(){

}