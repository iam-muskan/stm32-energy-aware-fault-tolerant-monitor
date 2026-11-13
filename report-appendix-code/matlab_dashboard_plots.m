clear;
clc;
close all;
%% 1. Time data (milliseconds)
time_ms = [ ...

1006 2019 3025 4034 5042 6049 7056 8064 ...
9071 10080 11088 12098 13107 14115 15124 ...
16133 17141 18150 19159 20167 21177 22185];
t = time_ms / 1000; % Time in seconds
%% 2. Sensor readings
Temp_C = [ ...
28.2 28.4 28.4 28.0 28.8 29.0 27.9 28.2 ...
28.4 28.5 28.5 28.4 28.5 28.4 28.7 ...
28.6 28.3 28.7 28.9 29.2 29.6 29.9];
Humidity = [ ...
66.4 65.6 66.2 66.4 66.2 66.2 66.6 66.6 ...
66.6 66.4 67.0 67.0 67.0 67.0 66.6 ...
65.8 65.2 64.2 63.6 64.4 63.8 63.0];
MQ135_1 = [ ...
604 597 586 571 579 588 593 591 ...
850 850 850 850 851 851 885 ...
886 889 889 872 854 866 871];
%no value is NaN
MQ135_2 = [ ...
NaN NaN NaN NaN NaN NaN NaN NaN ...
NaN 604 820 NaN 604 834 NaN ...
NaN NaN NaN NaN NaN NaN NaN];
PM25 = [ ...
20.0 20.5 20.5 21.0 20.0 21.5 19.5 19.0 ...
18.5 18.5 20.0 19.5 20.0 21.5 21.0 ...
22.5 24.0 24.5 25.5 26.0 27.5 25.5];
EHI = [ ...
70.8 70.8 71.4 71.9 71.8 66.2 71.4 71.2 ...
62.0 62.0 61.6 61.7 61.3 60.9 59.3 ...
59.7 58.4 58.1 58.7 59.3 58.5 58.8];
%% 3. Plot 1: Temperature vs Time
figure('Name','Temperature vs Time');
plot(t, Temp_C, '-o', 'LineWidth', 1.5);
grid on;
xlabel('Time (s)');
ylabel('Temperature (°C)');
title('Temperature vs Time');
%% 4. Plot 2: Humidity vs Time
figure('Name','Humidity vs Time');
plot(t, Humidity, '-o', 'LineWidth', 1.5);

grid on;
xlabel('Time (s)');
ylabel('Humidity (%)');
title('Humidity vs Time');
%% 5. Plot 3: MQ135(1) vs Time
figure('Name','MQ135(1) vs Time');
plot(t, MQ135_1, '-o', 'LineWidth', 1.5);
grid on;
xlabel('Time (s)');
ylabel('MQ135(1) Reading');
title('MQ135(1) vs Time');
%% 6. Plot 4: MQ135(2) vs Time
figure('Name','MQ135(2) vs Time');
plot(t, MQ135_2, '-s', 'LineWidth', 1.5);
grid on;
xlabel('Time (s)');
ylabel('MQ135(2) Reading');
title('MQ135(2) vs Time');
% NaN values create gaps
%% 7. Plot 5: PM2.5 vs Time
figure('Name','PM2.5 vs Time');
plot(t, PM25, '-o', 'LineWidth', 1.5);
grid on;
xlabel('Time (s)');
ylabel('PM2.5 Reading (displayed units)');
title('PM2.5 vs Time');
%% 8. Plot 6: EHI vs Time
figure('Name','EHI vs Time');
plot(t, EHI, '-o', 'LineWidth', 1.5);
grid on;
xlabel('Time (s)');
ylabel('Environmental Hazard Index (EHI)');
title('EHI vs Time');
%% 9. Saving all six plots
figures = findall(0, 'Type', 'figure');
for k = 1:numel(figures)
    fig = figures(k);
    filename = sprintf('SensorPlot_%d.png', k);
    exportgraphics(fig, filename, 'Resolution', 300);
end

fprintf('Six separate plots generated.\n');
fprintf('Time interval: %.3f to %.3f seconds\n', t(1), t(end));
