@echo off
rem Compile all recovered C and run the structural checker on every recorded function.
call tools\cl.bat src\game\*.c >nul || exit /b 1
py -3 tools\xcompare.py --all %*
