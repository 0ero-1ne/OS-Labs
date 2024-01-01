@echo off
echo -- строка параметров: %*
echo -- режим: %1
echo -- имя файла: %2

if "%*" equ "" goto help
if "%2" equ "" echo ---+ не задано имя файла & goto exit

if /i "%1" equ "создать" goto create
if /i "%1" equ "удалить" goto delete
if /i "%1" neq "удалить" goto error_mode else if /i "%1" neq "удалить" goto error_mode

:help
echo ---+ z03-06 режим файл
echo ---++ режим = {создать, удалить}
echo ---++ файл = имя файла
goto exit

:error_mode
echo ---+ режим задан не корректно
goto exit

:create
if not exist %2 (echo. > %2 & echo ---+ файл %2 создан) else (echo ---+ файл %2 уже есть)
goto exit

:delete
if not exist %2 (echo ---+ файл %2 не найден) else (del %2 & echo ---+ файл %2 удален)
goto exit

:exit