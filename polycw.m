function po = polycw(pin, ori);
%function po = polycw(pin, ori);
%
% polycw :  change all polygons with CCW orientation to 
%           polygons with CW orientation or vice versa.
%
% INPUT
% pin : Nx2 matrix of polygon vertices or a cell array of polygons.
% ori : (Optional) a string describing the orientation of the output
%       polygons. Either 'cw' or 'ccw'. Default is 'ccw' (positive).
%
% OUTPUT
% po :  A cell array containing the output polygon(s).

% This software was developed at the National Institute of Standards and Technology
% by employees of the Federal Government in the course of their official duties.
% Pursuant to title 17 Section 105 of the United States Code this software is not
% subject to copyright protection and is in the public domain. This software is an
% experimental system. NIST assumes no responsibility whatsoever for its use by other
% parties, and makes no guarantees, expressed or implied, about its quality, reliability,
% or any other characteristic.
%
% Initial version, Ulf Griesmann, NIST, November 2012

    % check arguments
    if nargin < 2, ori = 'ccw'; end
    if ~iscell(pin), pin = {pin}; end

    % determine orientation of input
    switch lower(ori)
        
      case 'cw'
          already_good = iscw(pin);
          
      case 'ccw'
          already_good = ~iscw(pin);
          
      otherwise
          error('unknown polygon orientation argument.');
    end

    % re-orient the ones with CCW orientation
    po = pin;
    for k = find(~already_good)
        po{k} = po{k}(end:-1:1,:);
    end

end
