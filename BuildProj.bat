@echo off

rem 1> is standard out and 2> is standard error.

cd \Eric\Main\Bitcoin\Cpp

rem -Weverything
rem Enable all diagnostics.

C:\LLVM\bin\clang++ main.cpp FileUtil.cpp MainApp.cpp -o main.exe -Wall -O1 2> Build.log
