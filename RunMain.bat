@echo off
rem echo This is RunMain.bat.


cd \Eric\Main\Crypto
del ExeOut.txt
rem \Eric\Main\Crypto\main.exe > ExeOut.txt
\Eric\Main\Crypto\main.exe

echo The error level is:
echo %ERRORLEVEL% 

rem IF %ERRORLEVEL% NEQ 0 ( 
rem   DO_Something 
rem )

