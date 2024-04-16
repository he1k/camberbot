clc; clear all;
N_gbox = 134;            % Gear box ratio
J_rotor = 164e-6;        % Rotor inertia
R = 0.21;                % Winding restistance
I = 60e-6;               % Winding inductance
Kt = 31.82e-3;           % Torque constant
Ke = 3.33*1e-3/(2*pi/60);% Back EMF constant
n0 = 5400/60;            % No load rotor speed - Rotations per second
n0*1/N_gbox              % No load speed of output shaft
N_belt = 3;
d = 0.15;
o = pi*0.20;
n0*1/N_gbox*N_belt
n0*1/N_gbox*N_belt*o
PPR = 5120;
CPR = 4*PPR;
res_mm = o/CPR*1e3

