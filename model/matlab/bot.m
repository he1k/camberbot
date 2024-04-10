clear all; close all; clc
L = 0.6;
m = 0.3;
I = 1/3*m*L^2;
g = 9.82;
mdl = 'bot_m';
SIM_TIME = 10;
STEP_SIZE = 1e-3;
t = 0:STEP_SIZE:SIM_TIME;
theta0 = deg2rad(15);
dtheta0 = 0;
sim(mdl);
figure;
plot(t,rad2deg(theta),'r');
xlabel('time(s)');
ylabel('angle (deg)');
