function [ints,nseg] = polyinters(pa,pb)
%function [ints,nseg] = polyinters(pa,pb)
%
% Calculates the line intersections of two plane, simple polygons.
% The polygons can be closed or open.
%
% INPUT
% pa,pb :  polygons (nx2 matrices)
%
% OUTPUT
% ints :   kx2 matrix with k polygon intersections, one per row. 
%          Returns an empty matrix when no intersections are found.
% nseg :   kx2  with segment numbers on which the 
%          intersections occur. nseg(:,1) are the intersection
%          segments for pa, nseg(:,2) the segments for pb. For a
%          polygon with N vertices, segments are numbered from 1,
%          which connects vertices 1 and 2, to N-1.

% This software was developed at the National Institute of Standards and Technology
% by employees of the Federal Government in the course of their official duties.
% Pursuant to title 17 Section 105 of the United States Code this software is not
% subject to copyright protection and is in the public domain. This software is an
% experimental system. NIST assumes no responsibility whatsoever for its use by other
% parties, and makes no guarantees, expressed or implied, about its quality, reliability,
% or any other characteristic.
%
% Initial version, Ulf Griesmann, November 2016
% Returns segment numbers, Ulf Griesmann, July 2019
