function [pulse,azerr,elerr] = getNearestUCDpulse(azimuth,elevation,h3D)
% [pulse,azerr,elerr] = getNearestUCDpulse(azimuth,elevation,h3D)
%  
% retrieves the impulse response from h3D that is closest to the 
% specified azimuth and elevation (in degrees)

if nargin < 1,
    fprint('Format: [pulse, azerr, elerr] = getNearestUCDpulse(azimuth, elevation,h3D)\n')
    return;
end;

azimuth = pvaldeg(azimuth);
if (azimuth <-90) | (azimuth > 90),
    error('INvalid azimuth')
end;
elevation = pvaldeg(elevation);

elmax = 50;
elindices = 1:elmax;
elevations = -45 + 5.625*(elindices-1);
el = round((elevation+45)/5.625 + 1);
el = max(el,1);
el = min(el,elmax);
elerr = pvaldeg(elevation - elevations(el));

azimuths = [-80 -65 -55 -45:5:45 55 65 80];
[azerr, az] = min(abs(pvaldeg(abs(azimuths - azimuth))));

pulse = squeeze(h3D(az,el,:));
end

