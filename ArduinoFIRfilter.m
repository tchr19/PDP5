%audioIn = dsp.AudioFileReader('dog.wav');
%audioOut = audioDeviceWriter('SampleRate',audioIn.SampleRate);
%audioIn.Filename = "dog.wav";,
elevations = -45 + 5.625*(0:49);
load hrir_final.mat
%%
az = arduinoObj.UserData.Data(end,1);
el = arduinoObj.UserData.Data(end,2);

f = figure(1);
a = axes('Parent',f);

f2 = figure(2);
a2 = axes('Parent',f2);

for i = 1:length(el)
    for j = 1:length(az)

        left = squeeze(hrir_l(az(j), el(i), :));
        right = squeeze(hrir_r(az(j), el(i), :));
        D = (1-sum(left))/length(left);
        left = left + D;

        D = (1-sum(right))/length(right);
        right = right + D;




        filtLP_l = dsp.FIRFilter(left');    
        filtLP_r = dsp.FIRFilter(right');

        plot(a,[left right])
        drawnow
        while ~isDone(audioIn)
            audio = audioIn();    % Read audio source file
            l = filtLP_l(audio(:,1)); 
            r = filtLP_r(audio(:,1));  % Filter the data
            w = [l(:), r(:)];
            %audioOut(w)
            audioOut(w);              % Play the filtered data
        end
        plot(a2,w);
        audioIn = dsp.AudioFileReader('dog.wav');
            
    end
end

release(audioOut);
release(audioIn);
%reset(audioIn);