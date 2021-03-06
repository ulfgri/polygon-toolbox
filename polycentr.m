function [cg] = polycentr(pa)
%function [cg] = polycentr(pa)
%
% polycentr :  calculate the centroid(s) of one or more
%              plane, simple polygons.
%
% INPUT
% pa :  a cell array of length N containing polygons (nx2 matrices)
%
% OUTPUT
% cg :  Nx2 array with centers of gravity, one per row

% This software was developed at the National Institute of Standards and Technology
% by employees of the Federal Government in the course of their official duties.
% Pursuant to title 17 Section 105 of the United States Code this software is not
% subject to copyright protection and is in the public domain. This software is an
% experimental system. NIST assumes no responsibility whatsoever for its use by other
% parties, and makes no guarantees, expressed or implied, about its quality, reliability,
% or any other characteristic.
%
% Initial version, Ulf Griesmann, November 2016
