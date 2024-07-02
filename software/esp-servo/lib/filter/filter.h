#ifndef FILTER_H
#define FILTER_H
#include <Arduino.h>
typedef struct filter{
    float b0, b1, a1; // Coefficients
    float f1, f2;
}
#endif

// float lpfilt(float u, float tau, float Ts){
//   float b1 = Ts;
//   float b0 = Ts;
//   float a1 = Ts+2*tau;
//   float a0 = Ts-2*tau;
//   static float x = u, xp = u, y = 0, yp = 0;
//   x = u;
//   y = 1/a1*(b1*x+b0*xp-a0*yp);
//   //0.21296791443850267379679144385027*x - 0.23703208556149732620320855614973*xp + yp;
//   yp = y;
//   xp = x;
//   return y;
// }



// f(i) = e(i) -(a_1*f(i-1)+a_2*f(i-2))
// u(i) = b_0*f(i)+b_1*f(i-1)+b_2*f(i-2)