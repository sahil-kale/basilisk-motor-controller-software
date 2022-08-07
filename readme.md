## Basilsik Motor Controller Software

![image](https://user-images.githubusercontent.com/32375512/183306439-b15b1c74-507d-4077-88cd-3f728b1d4264.png)

# Description
Software for brushed motor controller

# How to build unit tests:
Ensure cpputest is installed on machine

cd High_Level_Code/test
make

Code is stored in G030_varient due to different MCU models supported on same hardware.

# Errata
LED is weird to bringup - this shuold be updated to a different LED. Preferably standard 0603. Will be cheaper too
Needs more bulk capacitance
