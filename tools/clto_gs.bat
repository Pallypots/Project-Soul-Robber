@echo off
rem Usage: tools\clto.bat <outdir> file.c ...   (same flags as cl.bat)
rem Old .obj files for the given sources are deleted first, so a failed
rem compile can never leave a stale object behind; errors are shown.
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86 >nul 2>nul
set OUT=%1
shift
if not exist %OUT% mkdir %OUT%
for %%F in (%1 %2 %3 %4) do if exist "%OUT%\%%~nF.obj" del "%OUT%\%%~nF.obj"
cl /nologo /c /O2 /Oy /GS /Gy /Zl /W3 /arch:SSE /Iinclude /Fo%OUT%\ %1 %2 %3 %4 | findstr /i /c:"error" /c:"warning C4013"
exit /b 0