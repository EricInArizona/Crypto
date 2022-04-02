#!/bin/bash


cd /home/Eric/Crypto

# pwd

# chmod +x aprogram.sh


# The warning about -Wpadded means it's aligning a struct
# or object on a boundary, like an 8 byte boundary.  Which
# is normal and fine.

# Can't do -Wl,--stack in Linux.
# See SetStack.cpp for that.

# -H, --trace-includes
# Show header includes and nesting depth

# clang predefined macros all start with two underscores
# except for these two:
# linux
# unix 1

# List all clang predefined macros:
# clang++ -x c /dev/null -dM -E > Build.log


clang++ *.cpp /home/Eric/LinuxApi/*.cpp /home/Eric/CryptoBase/*.cpp -o  cryptoMain -Weverything -Wno-padded -Wno-c++98-compat-pedantic -ftrapv -Ofast 2> Build.log
