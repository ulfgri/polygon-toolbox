%
% test the polyinters function

clear all

% a polygon that zigs and zags
zig = [0:2:20]';
zag = [1:2:21]';

xy = [[zig,ones(numel(zig),1)];[zag,-ones(numel(zag),1)]];
[s,idx] = sort(xy);
xya = xy(idx(:,1),:);

plot(xya(:,1),xya(:,2))
hold on

% and one that doesn't
xyb = [0,-0.5; 22,0.5];
plot(xyb(:,1),xyb(:,2), 'r-')

% calculate intersections
ints = polyinters(xya, xyb); % swapping xya and xyb should give
                             % same result
plot(ints(:,1),ints(:,2), 'g*')

