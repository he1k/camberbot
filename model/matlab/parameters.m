% Battery
bw = 42e-3;  % Battery width
bl = 140e-3; % Battery length
bh = 38e-3;  % Battery height
bm = 0.460;  % Battery mass
ncells = 6;
mAh = 3200e-3;
VBat = ncells*3.7;
% Motor
N_gbox = 134;            % Gear box ratio
J_rotor = 164e-6;        % Rotor inertia
R = 0.21;                % Winding restistance
I = 60e-6;               % Winding inductance
Kt = 31.82e-3;           % Torque constant
Ke = 3.33*1e-3/(2*pi/60);% Back EMF constant