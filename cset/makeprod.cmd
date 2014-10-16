@echo off
rem
rem makeprod.cmd
rem
    set src=..
    cd oprod
    nmake /f %src%\cset\makefile.mak %1 %2 %3 %4 %5 %6 %7 %8
    cd %src%
