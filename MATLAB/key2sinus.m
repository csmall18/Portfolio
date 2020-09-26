function [xx,tt] = key2sinus(keynum, amp, phase, fsamp, dur )
% KEY2SINUS Produce a sinusoidal waveform corresponding to a
% given piano key number
%
% usage: xx = key2sinus(keynum, amp, phase, fsamp, dur )
%
% xx = the output sinusoidal waveform
% tt = vector of sampling times
% keynum = the piano keyboard number of the desired note
% amp, phase = sinusoid params
% fsamp = sampling frequency, e.g., 8000, 11025 or 22050 Hz
% dur = the duration (in seconds) of the output note
% Example Values:
amp = 5;
phase = pi/2;
fsamp = 8000;
dur = 3;
tt = 0:(1/fsamp):dur;
freqKey = 440*2^((keynum - 49)/12); %<=============== fill in this line
Xphasor = amp*exp(j*phase); %<=============== fill in this line
xx = real( Xphasor*exp(j*2*pi*freqKey*tt) );
plotspec(xx,fsamp,1024); colorbar
end

function [] = cMajorScale()
keynums = [40,42,44,45,47,49,51,52];
amp = 5;
phase = pi/2;
fsamp = 8000;
for i = 1:length(keynums)
    keynum = keynums(i);
    [x,t] = key2sinus(keynum, amp, phase, fsamp,0.4 );
    soundsc(x,fsamp)
    pause(0.1)
end
end