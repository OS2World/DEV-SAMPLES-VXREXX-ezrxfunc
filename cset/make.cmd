@echo off
rem
rem make.cmd
rem
    set src=..
    cd o
    nmake /f %src%\cset\makefile.mak DEBUG=1 %1 %2 %3 %4 %5 %6 %7 %8
    cd %src%
