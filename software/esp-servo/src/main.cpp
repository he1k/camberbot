#include <Arduino.h>
#include "constants.h"
#include <math.h>
#include <ESP32Encoder.h>
#include "timer0.h"
uint8_t isr_flag = 0;
uint8_t on = 0;
uint8_t error = 0;
volatile float ref_motor = 3.0;
volatile int64_t cnt_motor_prev = 0.0;
volatile int64_t cnt_wheel_prev = 0.0;
volatile float meas_motor = 0.0;
volatile float meas_wheel = 0.0;
ESP32Encoder enc_motor;
ESP32Encoder enc_wheel;
void update();
float pid_update(float e, bool rst);
float filt_motor_update(float u, bool rst);
void setup()
{
  Serial.begin(BAUD_RATE);
  uint64_t ticks = setup_timer(PRE_SCALE, TS, APB_CLK_F);
  enc_motor.attachFullQuad(ENC_A_PIN_MOTOR, ENC_B_PIN_MOTOR);
  enc_wheel.attachFullQuad(ENC_A_PIN_WHEEL, ENC_B_PIN_WHEEL);
  delay(500); // Wait a little bit before clearing encoder counts
  enc_motor.clearCount();
  enc_wheel.clearCount();
  pinMode(PULSE_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(PULSE_PIN, LOW);
  ledcSetup(PWM_CH, PWM_F, PWM_BITS);
  ledcAttachPin(PWM_PIN, PWM_CH);
  ledcWrite(PWM_CH,PWM_MIN);
  delay(2000);
  if(TEST_PID)
  {
    for(int i = 0; i < 10; i++)
    {
      float u = pid_update(1.0, false);
      Serial.print("(pid) u = "); Serial.println(u,10);
    }
    pid_update(1.0, true);
  }
  if(TEST_FILT_MOTOR)
  {
    for(int i = 0; i < 10; i++)
    {
      float y = filt_motor_update(1.0, false);
      Serial.print("(filt motor) y = "); Serial.println(y,10);
    }
    filt_motor_update(1.0, true);
  }
}

void loop()
{
  if(isr_flag)
  {
    if(!error)
    {
      update();
    }
    isr_flag = 0;
  }
}
void update()
{
  // Check for timing violations
  static uint64_t t_p = micros();
  //static float u_tm1 = 0, u_tm2 = 0, e_tm1 = 0, e_tm2 = 0;
  uint64_t t = micros();
  if((t-t_p) > (TS_US+TS_US_TOL))
  { // Timing error occured
    digitalWrite(PULSE_PIN, HIGH);
    digitalWrite(LED, HIGH);
    error = 1;
  }else
  { // No error, keep on going
    on = !on;
    digitalWrite(PULSE_PIN, on);
    // 1) Measurement
    int64_t cnt_motor = enc_motor.getCount();
    int64_t cnt_wheel = enc_wheel.getCount();
    meas_motor = (cnt_motor-cnt_motor_prev)/CPR_MOTOR*2*M_PI;
    meas_wheel = (cnt_wheel-cnt_wheel_prev)/CPR_MOTOR*2*M_PI;
    // 2) Calculate motor voltage
    float u = 0.0;
    // 3) Detect polarity and saturate control signal
    uint8_t dir = u < 1 ? 0 : 1;
    int bits = (int) fabs(u/V_MAX*PWM_MAX);
    if(bits > PWM_MAX)
    {
      bits = PWM_MAX;
    }
    // 4) Write output to motor driver
    digitalWrite(DIR_PIN, dir);
    ledcWrite(PWM_CH, bits);
  }
  t_p = t;
}

float pid_update(float e, bool rst){
  static float _u[2] = {0,0}; // State
  static float _e[2] = {0,0}; // State
  float u; // Output
  // Calculate u(t) using direct implementation
  u = 1.0/A0_PID*(B0_PID*e + B1_PID*_e[0] + B2_PID*_e[1] - A1_PID*_u[0] - A2_PID*_u[1]);
  if(EN_LIM)
  {
    if(u > LIM)
    {
      u = LIM;
    }else if(u < -LIM)
    {
      u = -LIM;
    }
  }
  // Update states
  if(rst)
  {
    _u[1] = 0;
    _u[0] = 0;
    _e[1] = 0;
    _e[0] = 0;
  }else
  {
    _u[1] = _u[0];
    _u[0] = u;
    _e[1] = _e[0];
    _e[0] = e;
  }
  return u;
}
float filt_motor_update(float u, bool rst){
  static float _u = 0; // State
  static float _y = 0; // State
  float y; // Output
  // Calculate y(t) using direct implementation
  y = 1.0/A0_FILT*(B0_FILT*u + B1_FILT*_u - A1_FILT*_y);
  // Update state
  if(rst)
  {
    _u = 0;
    _y = 0;
  }else
  {
    _u = u;
    _y = y;
  }
  return y;
}