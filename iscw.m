function cw = iscw(pin)
%function cw = iscw(pin)
%
% iscw :  returns a vector with a flag for each
%         polgon. The flag is 1 if the polygon has 
%         clockwise orientation, 0 otherwise.
%
% pin :   Nx2 array of polygon vertices or cell array of polygons.
% cw   :  array with flags indicating the orientation of the
%         polygons.

% This software was developed at the National Institute of Standards and Technology
% by employees of the Federal Government in the course of their official duties.
% Pursuant to title 17 Section 105 of the United States Code this software is not
% subject to copyright protection and is in the public domain. This software is an
% experimental system. NIST assumes no responsibility whatsoever for its use by other
% parties, and makes no guarantees, expressed or implied, about its quality, reliability,
% or any other characteristic.
%
% Initial version, Ulf Griesmann, NIST, November 2012

    % check argument
    if ~iscell(pin), pin = {pin}; end

    % call mex function
    cw = iscwmex(pin);

end
