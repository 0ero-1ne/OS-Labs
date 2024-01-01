@echo off
echo -- Текущий пользователь: %USERNAME%
set year=%date:~10,4%
set month=%date:~4,2%
set day=%date:~7,2%
echo -- Текущие дата и время: %day%.%month%.%year%, %TIME%
echo -- Имя компьютера: %COMPUTERNAME%
 