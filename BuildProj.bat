@echo off

rem 1> is standard out and 2> is standard error.

cd \Eric\Main\Crypto

rem -Weverything
rem Enable all diagnostics.

rem Command line reference:
rem https://clang.llvm.org/docs/ClangCommandLineReference.html

C:\LLVM\bin\clang++ @CommandLine.txt -o main.exe -Wall -O1 2> Build.log
