function angle = pvaldeg(angle)
% angle = pvaldeg(angle)
%
% Maps angle (in degrees) into the range [-90, 270)

if nargin < 1,
    fprint('Format: angle = pvaldeg(angle)\n');
    return;
end;

dtr = pi/180;
angle = atan2(sin(angle*dtr),cos(angle*dtr))/dtr;
if angle < -90,
    angle = angle + 360;
end;
end

