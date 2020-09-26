%How to use: 
%When this is run, type in your name and click OK.
[V1,fs] = audioread('first.wav');
[row,col] = size(V1);
V1 = reshape(V1,[1,row*col]);
[V2,fs2] = audioread('second.wav');
[row2,col2] = size(V2);
V2 = reshape(V2,[1,row2*col2]);
[V3,fs3] = audioread('third.wav');
[row3,col3] = size(V3);
V3 = reshape(V3,[1,row3*col3]);
% Program to do text to speech.
% Get user's sentence
userPrompt = 'What is your name?';
titleBar = 'We are the Rats';
defaultString = 'Name';
caUserInput = inputdlg(userPrompt, titleBar, 1, {defaultString});
if isempty(caUserInput)
	return;
end % Bail out if they clicked Cancel.
caUserInput = char(caUserInput); % Convert from cell to string.
NET.addAssembly('System.Speech');
obj = System.Speech.Synthesis.SpeechSynthesizer;
obj.Volume = 100;
soundsc(V1(1:end/2+1),fs); %first verse
pause(7.75);
Speak(obj, caUserInput);
soundsc(V2(1:end/2+1),fs2); %second verse
pause(3.5);
Speak(obj, caUserInput);
soundsc(V3(1:end/2+1),fs3);
fprintf('Happy Birthday, %s!',caUserInput);