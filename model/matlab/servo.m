clear all;
clc;
close all;
run("parameters.m"); % Load parameters
Ts = 1e-3;
Kp = 1.75;
tau_i = 0.01;
tau_d = 0.2;
alpha = 0.4;
s = tf('s');
Kp = 1
G = (1)