# Energy-Aware Adaptive Fault-Tolerant Environmental Monitor (STM32 Blue Pill)

Code from our Embedded Systems minor specialization project at Manipal Institute of Technology: an energy-aware, fault-tolerant environmental monitoring system on an STM32 Blue Pill. It reads temperature, humidity, gas and dust inputs, validates readings, votes across gas sensor readings, switches behaviour by battery level, runs a built-in self-test (BIST) and prints one JSON status line per second over serial.

Team: Harsh Gupta, Muskan Toshniwal, Rahul Vardhan. Guide: Dr. Rahul Ratnakumar, School of Electrical Engineering, MIT Manipal.

## What is in this repo

### wokwi/ - the online simulation
Downloaded unchanged from https://wokwi.com/projects/480248611738601473 ("Environmental Monitor - BIST").
- stm32-analog.ino - main program: gas decision with a five-reading vote, battery-aware mode, BIST, DHT22 validity checks, JSON output.
- diagram.json - Wokwi wiring diagram.
- libraries.txt - libraries used: DHT sensor library, Adafruit Unified Sensor.
- mq135.chip.c, mq135.chip.json - custom simulated MQ135 gas sensor.
- gp2y1010.chip.c, gp2y1010.chip.json - custom simulated GP2Y1010 dust sensor.
- battery.chip.c, battery.chip.json - custom simulated battery level input.
- wokwi-project.txt - the note Wokwi adds to a downloaded project.
The MQ135, dust and battery inputs are simulated parts, and the custom chip files only work inside Wokwi.

### report-appendix-code/ - code from the project report
Copied from the appendices of the project report (Appendices A to E). The C++ programs are software simulation models: they do not represent the real BIST circuit or the exact behaviour of the STM32.
- simulation1_environmental_classification.cpp - Appendix A: classifies six samples as NORMAL, ABNORMAL or INVALID_DATA.
- simulation2_software_bist.cpp - Appendix B: software BIST over eight test inputs.
- simulation3_fault_injection.cpp - Appendix C: five fault-injection test cases.
- simulation4_five_stage_pipeline.cpp - Appendix D: a simplified five-stage pipeline trace of the alarm logic.
- matlab_dashboard_plots.m - Appendix E: MATLAB script that plots values transcribed by hand from a dashboard screenshot (temperature, humidity, MQ135 readings, PM2.5, EHI).

## Notes on the code
- The files in report-appendix-code/ were extracted from the report PDF, so line breaks and blank lines at page breaks may differ from the original source files. The code itself is as printed in the report.
- The Wokwi version is the simulation. The version for the physical Blue Pill hardware was written in the Arduino IDE and is not included here.
