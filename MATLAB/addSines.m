function [xx,tt]= addSines (freqs, cAmps, fs, dur, tstart)
%ADDSINES Synthesize a signal from sum of sinusoids
% usage:
% [xx,tt]= addSines (freqs, camps, fs, dur, tstart)
% xx = output for cosine at a single frequency
% tt = output for time vector showing location of cosine values in seconds
% freqs = vector of desired frequencies (non-negative)
% cAmps = vector of complex amplitudes
% fs = sampling frequency (used to determine the spacing of the computed values from the sinusoid)
% dur = total duration of the signal in seconds
% tstart = start time in seconds
%
% Note: freqs and camps must be the same length
% cAmps(1) corresponds to frequency freqs(1),
% cAmps(2) corresponds to frequency freqs(2), etc.
% The tt vector should be generated with a small time increment defined by the
% sampling rate, fs.
%
% Make use of the earlier function you created: onecos.m
for x = 1:length(freqs)
[xx, tt] = onecos(freqs(x),cAmps(x),fs,dur,tstart);
if x == 1 % initialize yt
    yt = zeros(1,length(xx));
end
yt = yt + xx;
end
%per = 1/gcd(freqs);
%fprintf('Period is %d', per);
plot(tt,yt);