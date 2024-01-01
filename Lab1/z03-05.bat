@echo off
echo -- строка параметров: %*
echo -- параметр 1: %1
echo -- параметр 2: %2
echo -- параметр 3: %3

set res=0

if %3==+ set /A res=%1 + %2
if %3==- set /A res=%1 - %2
if %3==* set /A res=%1 * %2
if %3==/ set /A res=%1 / %2
if %3==% set /A res=%1 % %2

echo результат: %res%