function [xx, tt] = onecos( freq, cAmp, fs, dur, tstart )
% ONECOS function to generate one cosine
% usage:
% [xx, tt] = onecos(freq,camp,dur,tstart)
% xx = output for cosine at a single frequency
% tt = output for time vector showing location of cosine values in seconds
% freq = desired frequency
% cAmp = complex amplitude
% fs = sampling frequency (used to determine the spacing of the computed
% values from the sinusoid)
% dur = duration of the sinusoid in seconds
% tstart = start time of the sinusoid in seconds
tt = tstart:1/fs:(tstart + dur);
phi = angle(cAmp);
amp = abs(cAmp);
xx = amp*cos(2*pi*freq.*tt + phi);
plot(tt,xx);
end