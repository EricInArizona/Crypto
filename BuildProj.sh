#!/bin/bash


cd /home/Eric/Crypto

pwd


# The warning about -Wpadded means it's aligning a struct
# or object on a boundary, like an 8 byte boundary.  Which
# is normal and fine.

# Can't do -Wl,--stack in Linux.
# See SetStack.cpp for that.

clang++ *.cpp /home/Eric/LinuxApi/*.cpp -o  cryptoMain -Weverything -Wno-padded -Wno-c++98-compat-pedantic -Ofast -Wl,-MAP -L/home/Eric/LinuxApi 2> Build.log
