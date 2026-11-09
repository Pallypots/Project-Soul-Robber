@echo off
rem Compile all recovered C (plus structure layout checks) and run the
rem structural checker on every recorded function.
call tools\cl.bat src\game\*.c tests\layout_check.c >nul || (echo COMPILE OR LAYOUT CHECK FAILED & exit /b 1)
py -3 tools\xcompare.py --all %*