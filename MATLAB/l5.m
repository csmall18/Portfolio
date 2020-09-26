%psi(t) = 2*pi*mu*t^2+2*pi*f0*t+phi
fSamp = 4000; %-Number of time samples per second
dt = 1/fSamp;
tStart = 0;
tStop = 5;
tt = tStart:dt:tStop;
mu = 600;
fzero = 400;
phi = 2*pi*rand; %-- random phase
psi = 2*pi*mu*tt.^2+2*pi*fzero*tt+phi; %<=================== FILL IN THE CODE HERE
%
cc = real( 7.7*exp(j*psi) );
% soundsc( cc, fSamp ); %-- uncomment to hear the sound
plotspec( cc+j*1e-12, fSamp, 256 ), colorbar, grid on %-- with negative frequencies
soundsc(cc,fSamp)