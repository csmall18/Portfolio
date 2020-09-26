function xs = mySinusoid(amp, freq, pha, fs, tsta, tend)
% amp = amplitude
% freq = frequency in cycle per second
% pha = phase, time offset for the first peak
% fs = number of sample values per second
% tsta = starting time in sec
% tend = ending time in sec
tt = tsta : 1/fs : tend; % time indices for all the values
xs = amp * cos( freq*2*pi*tt + pha );
amp = 7;
freq = 100;
pha = pi/3;
fs = 8000;
tsta = 0;
tend = 3; %a 3-sec long signal
%<--- plot first three cycles of the generated sinusoid
ts = tsta:1/fs:tsta+3/freq;
Lt = length(ts);
plot( ts, xs(1:Lt), 'b-', ts, 2*xs(1:Lt), 'r--' ), grid on
title('TEST PLOT of TWO SINUSOIDS (scaling by 2)')
xlabel('TIME (sec)')
end
