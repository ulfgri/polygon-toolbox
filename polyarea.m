function [ar] = polyarea(pa)
%function [ar] = polyarea(pa)
%
% polyarea :  calculate the area(s) of one or more
%             plane, simple polygons.
%
% INPUT
% pa :  a cell array of polygons (nx2 matrices). 
%
% OUTPUT
% ar :  array of polygon areas with same shape as 'pa'.
%       The area is positive for polygons with positive 
%       orientation, and negative for polygons with negative
%       orientation.

% This software was developed at the National Institute of Standards and Technology
% by employees of the Federal Government in the course of their official duties.
% Pursuant to title 17 Section 105 of the United States Code this software is not
% subject to copyright protection and is in the public domain. This software is an
% experimental system. NIST assumes no responsibility whatsoever for its use by other
% parties, and makes no guarantees, expressed or implied, about its quality, reliability,
% or any other characteristic.
%
% Initial version, Ulf Griesmann, November 2016
