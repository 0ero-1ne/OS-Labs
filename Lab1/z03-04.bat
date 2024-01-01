@echo off
echo -- строка параметров: %*
echo -- параметр 1: %1
echo -- параметр 2: %2
echo -- параметр 3: %3

set /A res1=%1 + %2
set /A res2=%1 * %2
set /A res3=%3 / %2
set /A res4=%2 - %1
set /A res5=(%2 - %1)*(%1 - %2)

echo -- %1 + %2 = %res1%
echo -- %1 * %2 = %res2%
echo -- %3 / %2 = %res3%
echo -- %2 - %1 = %res4%
echo -- (%2 - %1)*(%1 - %2) = %res5%