@echo off

rem 1> is standard out and 2> is standard error.

cd \Eric\Main\Crypto

rem @CommandLine.txt
rem Use -v to see how it gets called.
rem Using -v shows that Clang is using
rem Visual Studio tools:
rem \Community\\VC\\Tools\\MSVC\
rem and \\Windows Kits\\10\\include\\
rem Visual C++ C Runtime (CRT)
rem Universal C Runtime

rem C:\LLVM\bin\clang++ --help

rem -MAP goes to main.map.

rem -Weverything
rem -Wall

rem Don't use old style casting.
rem -Wno-old-style-cast

rem -Ofast

rem Check MainApp.cpp to see where the exeout
rem file it going to.

C:\LLVM\bin\clang++ *.cpp \Eric\Main\CryptoBase\*.cpp \Eric\Main\LinuxApi\*.cpp -o main.exe -Weverything -Wno-c++98-compat-pedantic -ftrapv -Ofast -Wl,-MAP -Wl,-STACK:100000000 2> Build.log

rem https://docs.microsoft.com/en-us/cpp/build/reference/stack-stack-allocations?view=msvc-160
rem Tell the linker to use this max stack size.
rem -Wl,-STACK:10000000
rem -Wl,"-stack_size 0x100000"
rem On Windows, clang calls link.exe.
rem "For ARM, x86 and x64 machines, the default
rem stack size is 1 MB."

rem -Wl,<arg>
rem Pass the comma separated arguments in
rem <arg> to the linker
