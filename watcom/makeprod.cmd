@echo off
rem
rem makeprod.cmd
rem
    set WATCLOS2=%WATCOM%\lib386\os2;%WATCOM%\lib386
    set WATCINCS=%WATCOM%\h;%WATCOM%\H\OS2;%TOOLKIT%\C\OS2H
    set WATCBINS=%WATCOM%\binp;%WATCOM%\binb
    set src=..
    cd oprod
    wmake /h /f %src%\watcom\makefile.mak ver=prod MAKEDLL=1 %1 %2 %3 %4 %5 %6 %7 %8
    cd %src%
