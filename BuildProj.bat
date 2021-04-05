@echo off

rem 1> is standard out and 2> is standard error.

cd \Eric\Main\Crypto

rem -Weverything
rem Enable all diagnostics.

rem Command line reference:
rem https://clang.llvm.org/docs/ClangCommandLineReference.html

rem @CommandLine.txt
rem Use -v to see how it gets called.
rem C:\LLVM\bin\clang++ main.cpp MainApp.cpp Base10Number.cpp FileUtil.cpp Base10Number.cpp -o main.exe -Wall -O1 2> Build.log
C:\LLVM\bin\clang++ *.cpp -o main.exe -Wall -O1 2> Build.log
