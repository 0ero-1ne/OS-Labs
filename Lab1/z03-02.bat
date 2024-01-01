@echo off
echo -- имя этого bat-файла: %~n0
echo -- путь bat-файл: %~f0
for /f "skip=5 tokens=1,2 delims= " %%a in (' dir /T:C /A:-D %~nx0 ') do (
  echo -- этот bat-файл создан: %%a %%b
  exit /b 0
)