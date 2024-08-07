clc; clear all;
N_gbox = 134;            % Gear box ratio
J_rotor = 164e-6;        % Rotor inertia
R = 0.21;                % Winding restistance
I = 60e-6;               % Winding inductance
Kt = 31.82e-3;           % Torque constant
Ke = 3.33*1e-3/(2*pi/60);% Back EMF constant
n0 = 5400/60;            % No load rotor speed (rot/s)
n1 = 22.2/18*n0;         % No load rotor speed - Assuming complete linearity
                         % adjusting for 22.2 V
d = 0.38;                % Wheel diameter (m)
o = pi*d;                % Wheel circumference (m)
n0*1/N_gbox*o            % Linear velocity using only gearbox (m/s)
%%
N_belt = 4;
d = 0.36;
o = pi*d;
n1*1/N_gbox*N_belt
v_lin = n0*1/N_gbox*N_belt*o
CPR_pos = 4*5120
CPR_vel = 4*1024*134
PPR = 5120;
CPR = 4*PPR;
res_mm = o/CPR*1e3

