serialportlist("available")


arduinoObj = serialport("COM3",9600)
configureTerminator(arduinoObj,"CR/LF");
flush(arduinoObj);
arduinoObj.UserData = struct("Data",[])

configureCallback(arduinoObj,"terminator",@readEncoderData);

%src = arduinoObj;

function readEncoderData(src, ~)
    % Read the ASCII data from the serialport object.
    data = readline(src)
    newStr = split(data,",")
    %new2 = split(newStr(2),":")
    % Convert the string data to numeric type and save it in the UserData
    % property of the serialport object.
    newStr2 = str2double(newStr);
    src.UserData.Data(end+1, :) = newStr2';

    % Update the Count value of the serialport object.
    %src.UserData.Count = src.UserData.Count + 1;

    % If 1001 data points have been collected from the Arduino, switch off the
    % callbacks and plot the data.
    
    %if src.UserData.Count > 1001
        %configureCallback(src, "off");
        %data
        %plot(src.UserData.Data(2:end));
    %end
end

