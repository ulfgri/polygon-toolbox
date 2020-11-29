%
% Test the polyinters function
%

clear all

% first polygon
pa = [2,0; 0,2; -2,0; 0,-2; 2,0]; % diamond

% second polygon
pb = [-3,1.5; 1,1.5; 1,-3];

[xy,si] = polyinters(pa,pb)

