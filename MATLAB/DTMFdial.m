function xx = DTMFdial(keyNames,fs)
% DTMFDIAL Create a signal vector of tones that will dial
% a DTMF (Touch Tone) telephone system.
%
% usage: xx = DTMFdial(keyNames,fs)
% keyNames = vector of CHARACTERS containing valid key names
% fs = sampling frequency (1/Ts)
% xx = signal vector that is the concatenation of DTMF tones.
%
keyNames = '159D*286A';
TTkeys = ['1','2','3','A';'4','5','6','B';'7','8','9','C';'*','0','#','D'];
keys = [];
TTcolTones = [1209,1336,1477,1633]; %-- in Hz
TTrowTones = [697,770,852,941];
Ts = 0.3e-3;
fs = 1/Ts;
numKeys = length(keyNames);
tt = 0:1/fs:0.3;
durDualTone = 0.18; %-- in seconds
LenDualTone = durDualTone*fs;
durSilence = 0.048;
LenSilence = durSilence*fs;
xx = zeros(1,round(numKeys*(durDualTone + durSilence)/Ts)); %- initialize xx
%to be long enough to hold the entire output
%sil = [];
%z = zeros(1,LenSilence);
for kk=1:numKeys
[jrow,jcol] = find(keyNames(kk) == TTkeys);
keys = [keys,TTkeys(jrow,jcol)];
%fprintf('keys are %s\n',keys(kk));
rowFreq = TTrowTones(jrow);
colFreq = TTcolTones(jcol);
%fprintf('rowFreq is %d and colFreq is %d\n',rowFreq, colFreq);
DTMFsig = cos(2*pi*rowFreq*tt+rand(1)) + cos(2*pi*colFreq*tt+rand(1));
n1 = 1 + (kk - 1)*(LenDualTone + LenSilence);
n2 = n1+length(DTMFsig)-1;
xx(n1:n2) = DTMFsig;
%plotspec(DTMFsig,fs,128); grid on
%soundsc(xx,fs);
plotspec(xx,fs,128);
grid on
end