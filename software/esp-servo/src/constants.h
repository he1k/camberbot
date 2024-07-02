//###############################
//|          TESTING            |
//###############################
#define TEST_PID 1
#define TEST_FILT_MOTOR 1
//###############################
//|       COMMUNICATION         |
//###############################
#define BAUD_RATE 115200

//###############################
//|           TIMING            |
//###############################

#define PRE_SCALE 80       // Prescaler
#define APB_CLK_F 80e6     // APB (advanced peripheral bus) clock frequency
#define TS        0.00025  // Sampling time
#define TS_US     250
#define TS_US_TOL 10

//###############################
//|            GPIO             |
//###############################
#define ENC_A_PIN_MOTOR 19
#define ENC_B_PIN_MOTOR 18
#define ENC_A_PIN_WHEEL 17
#define ENC_B_PIN_WHEEL 16
#define PULSE_PIN 5
#define PWM_CH 0
#define PWM_PIN 4
#define DIR_PIN 21
#define LED 2
//###############################
//|            PID              |
//###############################
#define V_BAT 22.1
#define V_MAX V_BAT
#define KP 0.08
#define TAU_I 0.01
#define TAU_D 0.2
#define ALPHA 0.4
#define LIM V_MAX
#define EN_LIM true
#define A0_PID 1.0
#define A1_PID (TAU_I*(TS - 2.0*ALPHA*TAU_D) - 1.0*TAU_I*(TS + 2.0*ALPHA*TAU_D))/(TAU_I*(TS + 2.0*ALPHA*TAU_D))
#define A2_PID (-1.0*TAU_I*(TS - 2.0*ALPHA*TAU_D))/(TAU_I*(TS + 2.0*ALPHA*TAU_D))
#define B0_PID (0.5*KP*(TS + 2.0*TAU_D)*(TS + 2.0*TAU_I))/(TAU_I*(TS + 2.0*ALPHA*TAU_D))
#define B1_PID (0.5*KP*(TS - 2.0*TAU_D)*(TS + 2.0*TAU_I) + 0.5*KP*(TS + 2.0*TAU_D)*(TS - 2.0*TAU_I))/(TAU_I*(TS + 2.0*ALPHA*TAU_D))
#define B2_PID (0.5*KP*(TS - 2.0*TAU_D)*(TS - 2.0*TAU_I))/(TAU_I*(TS + 2.0*ALPHA*TAU_D))
//###############################
//|          FILTER             |
//###############################
#define FILT_TYPE 0
#if FILT_TYPE == 0 // Low pass filtered derivative (high pass filter with 1/tau DC gain)
  #define TAU_FILT 0.01
  #define A0_FILT 1
  #define A1_FILT (TS-2*TAU_FILT)/(2*TAU_FILT+TS)
  #define B0_FILT 2/(2*TAU_FILT+TS)
  #define B1_FILT -2/(2*TAU_FILT+TS)
#elif FILT_TYPE == 1 // High pass filter
  #define TAU_FILT 10 
  #define A0_FILT 1
  #define A1_FILT (TS-2*TAU_FILT)/(2*TAU_FILT+TS)
  #define B0_FILT 2*TAU_FILT/(2*TAU_FILT+TS)
  #define B1_FILT -2*TAU_FILT/(2*TAU_FILT+TS)
#elif FILT_TYPE == 2 // Low pass filter
  #define TAU_FILT 0.01
  #define A0_FILT 1
  #define A1_FILT (TS-2*TAU_FILT)/(TS+2*TAU_FILT)
  #define B0_FILT TS/(TS+2*TAU_FILT)
  #define B1_FILT TS/(TS+2*TAU_FILT)
#endif
//###############################
//|          ENCODER            |
//###############################
#define PPR_MOTOR 1024.0
#define CPR_MOTOR 4.0*PPR_MOTOR
#define PPR_WHEEL 5120.0
#define CPR_WHEEL 4.0*PPR_WHEEL
//###############################
//|             PWM             |
//###############################
#define PWM_F 70000
#define PWM_BITS 9
#define PWM_MAX (int)(pow(2,PWM_BITS)-1)
#define PWM_MIN 0