@echo off & setlocal enabledelayedexpansion
set value=%2
set last=%value:~-1%
if "!last!"=="\" (
 set left=%value:~0,-1% 
 move %1 !left!
 )
move %1 !value!
:end