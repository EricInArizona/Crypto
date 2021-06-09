@echo off

rem 1> is standard out and 2> is standard error.

cd \Eric\Main\Crypto

rem -Weverything
rem Enable all diagnostics.

rem Command line reference:
rem https://clang.llvm.org/docs/ClangCommandLineReference.html

rem @CommandLine.txt
rem Use -v to see how it gets called.
rem Using -v shows that Clang is using
rem Visual Studio tools:
rem \Community\\VC\\Tools\\MSVC\
rem and \\Windows Kits\\10\\include\\
rem Visual C++ C Runtime (CRT)
rem Universal C Runtime

rem C:\LLVM\bin\clang++ --help
rem C:\LLVM\bin\clang++ main.cpp MainApp.cpp Base10Number.cpp FileUtil.cpp Base10Number.cpp -o main.exe -Wall -O1 2> Build.log

rem -MAP goes to main.map.
C:\LLVM\bin\clang++ *.cpp -o main.exe -Wall -O1 -Wl,-MAP -Wl,-STACK:10000000 2> Build.log

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

