## Basilsik Motor Controller Software

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
