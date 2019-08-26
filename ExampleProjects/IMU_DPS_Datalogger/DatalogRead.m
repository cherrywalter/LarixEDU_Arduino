%prepare workspace
close all;
clear all;
clc

%array to store converted values into
IMU_Data = [];

%Open File and convert it so it is possible to use the data in matlab
Datafile = fopen('F:\IMU.TXT');
MeasurementData = textscan(Datafile,'%s');
MeasurementData = MeasurementData{1,1};
DataSize = size(MeasurementData);

%iterate through rows of data
for counter = 1:DataSize(1,1)
    CurrentData = MeasurementData(counter,1);
    CurrentData = CurrentData{1,1};
    cellSize = size(CurrentData);
    
    %number to store floats into after splitted up strings
    currentNumber = '';
    
    %set variable for current data row
    IMUDataRow = 1;
    
    %iterate through every line and get string split up into numbers
    for charNumber = 1:cellSize(1,2)
        if CurrentData(1,charNumber) == ';'
            IMU_Data(counter, IMUDataRow) = str2double(currentNumber);
            currentNumber = '';
            IMUDataRow = IMUDataRow + 1;
        elseif charNumber == cellSize(1,2)
            currentNumber = strcat(currentNumber,CurrentData(1,charNumber));
            IMU_Data(counter, IMUDataRow) = str2double(currentNumber);
        else
            currentNumber = strcat(currentNumber,CurrentData(1,charNumber));
        end
    end

end

%Get all vectors from the MeasurementData
time = IMU_Data(1:end,1);
temperature_dps = IMU_Data(1:end,2);
pressure_dps = IMU_Data(1:end,3);
Accel_X = IMU_Data(1:end,4);
Accel_Y = IMU_Data(1:end,5); 
Accel_Z = IMU_Data(1:end,6);
Gyro_X = IMU_Data(1:end,7);
Gyro_Y = IMU_Data(1:end,8);
Gyro_Z = IMU_Data(1:end,9);
Mag_X = IMU_Data(1:end,10);
Mag_X = IMU_Data(1:end,11);
Mag_Z = IMU_Data(1:end,12);
temperature_imu = IMU_Data(1:end,13);

time_offset = 0;

%Make Seconds from Miliseconds
%Plot starts at first Measurement (should be 0) -> Subtract the first time
%from all times.
for i=1:1:numel(time)
    if i==1
        time_offset = time(i);
    end
    time(i) = (time(i) - time_offset)/1000; %get Seconds
end

%Plot as example for temperature of DPS and IMU
figure(1);
title('Temperature IMU und DPS')
plot(time, temperature_dps)
grid on
xlabel('Time in s')
ylabel('Temperature in Grad Celsius')
hold on;
plot(time, temperature_imu)

legend('Temperature DPS','Temperature IMU')