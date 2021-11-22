clear all, close all, clc

% Joint angles (degrees) - theta2,3,4 measured against an extrapolation of the proceeding segment. Negative = Anticlockwise.  
theta1 =  30 ;
theta2 = -60 ;
theta3 = -80 ;
theta4 = +30 ;
theta5 =   0 ;

if theta1 > 90 || theta1 < -90
    mirror = 1;
else
    mirror = 0;
end

% Segment lengths
sL1 = 200 ;
sL2 = 500 ;
sL3 = 600 ;
sL4 = 150 ;

% Centre of arm-base = origin
origin = [0, 0, 0];

%% Joint Centre calculations:
JointCentre1 = origin + [0, 0, sL1];
JointCentre2 = JointCentre1 + [-1*sind(theta2)*sL2*sind(theta1), -1*sind(theta2)*sL2*cosd(theta1), cosd(theta2)*sL2];
JointCentre3 = JointCentre2 + [-1*sind(theta2+theta3)*sL3*sind(theta1), -1*sind(theta2+theta3)*sL3*cosd(theta1), cosd(theta2+theta3)*sL3];
JointCentre4 = JointCentre3 + [-1*sind(theta2+theta3+theta4)*sL4*sind(theta1), -1*sind(theta2+theta3+theta4)*sL4*cosd(theta1), cosd(theta2+theta3+theta4)*sL4];


%% Basic plot of Joint Centres:

y = [origin(1,2), JointCentre1(1,2), JointCentre2(1,2), JointCentre3(1,2), JointCentre4(1,2)];
z = [origin(1,3), JointCentre1(1,3), JointCentre2(1,3), JointCentre3(1,3), JointCentre4(1,3)];


hold on
plot(y, z , '-xr', 'LineWidth', 2)
plot(y, z , 'x', 'color', 'k')
hold off
xlim([-200 1400])
ylim([-200 1400])


save('JointCentres', 'origin', 'JointCentre1', 'JointCentre2', 'JointCentre3', 'JointCentre4', 'mirror')

