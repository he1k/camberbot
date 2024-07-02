clear all;
clc;
close all;
run("parameters.m"); % Load parameters
Ts = 0.25e-3;
Kp = 0.08;
tau_i = 0.01;
tau_d = 0.2;
alpha = 0.4;
% First check PID implementation
disp('PID compare values');
s = tf('s');
G = Kp*((1+tau_i*s)/(tau_i*s))*((1+tau_d*s)/(1+tau_d*alpha*s));
H = c2d(G,Ts,'tustin');
[y,t] = step(H);
y(1:10)
% Then check filter implementation
disp('Filter compare values');
tau = 0.01;
G = 1/(tau*s+1);
H = c2d(G,Ts,'tustin');
[y,t] = step(H);
y(1:10)
% b = zeros(3,1);
% a = zeros(3,1);
% b(1) =  0.5*Kp*(Ts + 2.0*tau_d)*(Ts + 2.0*tau_i);
% b(2) = 0.5*Kp*(Ts - 2.0*tau_d)*(Ts + 2.0*tau_i) + 0.5*Kp*(Ts + 2.0*tau_d)*(Ts - 2.0*tau_i);
% b(3) = 0.5*Kp*(Ts - 2.0*tau_d)*(Ts - 2.0*tau_i);
% a(1) = tau_i*(Ts + 2.0*alpha*tau_d);
% a(2) = tau_i*(Ts - 2.0*alpha*tau_d) - 1.0*tau_i*(Ts + 2.0*alpha*tau_d);
% a(3) = -1.0*tau_i*(Ts - 2.0*alpha*tau_d);
% b;
% a;
% z = tf('z',Ts);
% H2 = (b(1)+b(2)*z^(-1)+b(3)*z^(-2))/(a(1)+a(2)*z^(-1)+a(3)*z^(-2));
% [y2,t2] = step(H2);
% y(1:10)