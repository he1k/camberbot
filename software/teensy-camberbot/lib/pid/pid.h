#ifndef PID_H
#define PID_H
#define OUT_OF_BOUNDS 9999.1337
#define TS_DEF 0.001
#define KP_DEF 1.75
#define TAU_I_DEF 0.01
#define TAU_D_DEF 0.1
#define ALPHA_DEF 0.4
class PID
{
    private:
        float Ts;
        float Kp;
        float tau_i;
        float tau_d;
        float alpha;
        float a[3];
        float b[3];
        float u[3];
        float e[3];
    public:
        PID();
        void begin(float Ts, float Kp, float tau_i, float tau_d, float alpha);
        float update(float r, float e);
        double getTs();
        double getKp();
        double getTaui();
        double getTaud();
        double getA(int idx);
        double getB(int idx);
        bool test(float Ts = TS_DEF, float Kp = KP_DEF, float tau_i = TAU_I_DEF, float tau_d = TAU_D_DEF, float alpha = ALPHA_DEF);
};
#endif