% An early version, the trig equations can be made more efficent in future.
clear all, close all, clc

% Joint Centre Positions:
      load('JointCentres.mat');
      
% Segment Lengths:
sL1 = 200;
sL2 = 500;
sL3 = 600;
sL4 = 150;


%% Some way of calculating theta1
% Needed to know how the remainder of the arm is aligned relative to the
% y/z plane.

if mirror == 0
    theta1 = atand((JointCentre4(1)-JointCentre1(1))/(JointCentre4(2)-JointCentre1(2)));
else
    theta1 = -1*((atand((JointCentre4(1)-JointCentre1(1))/(JointCentre4(2)-JointCentre1(2)))/abs(atand((JointCentre4(1)-JointCentre1(1))/(JointCentre4(2)-JointCentre1(2)))))*180-atand((JointCentre4(1)-JointCentre1(1))/(JointCentre4(2)-JointCentre1(2))));
end

% Will potentially need to include some code that recognises when theta1 has exceeded
% either 180 or -180 degrees, and reverses the sign and begins counting
% down towards 0. (Same with 0 degrees).

%% aligned-Y segments

if theta1 == 0 || theta1 == 180
    if mirror == 0
        aYs2 = JointCentre2(2)-JointCentre1(2);
        aYs3 = JointCentre3(2)-JointCentre2(2);
        aYs4 = JointCentre4(2)-JointCentre3(2);
    else
        aYs2 = -1*(JointCentre2(2)-JointCentre1(2));
        aYs3 = -1*(JointCentre3(2)-JointCentre2(2));
        aYs4 = -1*(JointCentre4(2)-JointCentre3(2));
    end
else
    aYs2 = (JointCentre2(1)-JointCentre1(1))/sind(theta1);
    aYs3 = (JointCentre3(1)-JointCentre2(1))/sind(theta1);
    aYs4 = (JointCentre4(1)-JointCentre3(1))/sind(theta1); 
end
% The y-axis component of each segment when aligned to the y/z plane (as
% when theta1 = 0).



%% theta 2:
%
if JointCentre2(3) > JointCentre1(3) && abs(aYs2) < sL2  % 5&6
    theta2 = -1*asind(aYs2/sL2);
elseif JointCentre2(3) < JointCentre1(3) && aYs2 > 0  % 8
    theta2 = -180-(-1*asind(aYs2/sL2));
elseif JointCentre2(3) < JointCentre1(3) && aYs2 < 0  % 7
    theta2 = 180-(-1*asind(aYs2/sL2));
elseif JointCentre2(3) == JointCentre1(3)  % 2&3
    if aYs2 > 0
        theta2 = -90;
    elseif aYs2 < 0
        theta2 = 90;
    end
elseif aYs2 == 0  % 1
    theta2 = 0;
end
% theta2 cannot be = +/-180 due to physical constraints.    



%% theta3
%
if JointCentre3(3) > JointCentre2(3) && abs(aYs3) < sL3  % 5&6
    theta3 = (-1*asind(aYs3/sL3))-theta2;
elseif JointCentre3(3) < JointCentre2(3) && aYs3 > 0  % 8
    theta3 = -180-(-1*asind(aYs3/sL3))-theta2;
elseif JointCentre3(3) < JointCentre2(3) && aYs3 < 0  % 7
    theta3 = 180-(-1*asind(aYs3/sL3))-theta2;
elseif JointCentre3(3) == JointCentre2(3)  % 2&3
    if aYs3 > 0
        theta3 = -90-theta2;
    elseif aYs3 < 0
        theta3 = 90-theta2;
    end
elseif aYs3 == 0
    if JointCentre3(3) > JointCentre2(3)  % 1
        theta3 = -1*theta2;
    elseif JointCentre3(3) < JointCentre2(3)  % 4
        theta3 = (theta2/abs(theta2))*180-theta2;  
        % either 1 or -1 * 180, - theta2 (accounts for both +&- rotations).
    end
end

    

%% theta 4
%
if JointCentre4(3) > JointCentre3(3) && abs(aYs4) < sL4  % 5&6
    theta4 = (-1*asind(aYs4/sL4))-theta2-theta3;
elseif JointCentre4(3) < JointCentre3(3) && aYs4 > 0  % 8
    theta4 = -180-(-1*asind(aYs4/sL4))-theta2-theta3;
elseif JointCentre4(3) < JointCentre3(3) && aYs4 < 0  % 7
    theta4 = 180-(-1*asind(aYs4/sL4))-theta2-theta3;
elseif JointCentre4(3) == JointCentre3(3)  % 2&3
    if aYs4 > 0
        theta4 = -90-theta2-theta3;
    elseif aYs4 < 0
        theta4 = 90-theta2-theta3;
    end
elseif aYs4 == 0
    if JointCentre4(3) > JointCentre3(3)  % 1
        theta4 = -1*(theta2+theta3);
    elseif JointCentre4(3) < JointCentre3(3)  % 4
        theta4 = ((theta2+theta3)/abs(theta2+theta3))*180-theta2-theta3;
        % (either 1 or -1) * 180, - theta2 (accounts for both +&- rotations).
    end
end


Test = [theta1, theta2, theta3, theta4]   


    
