@echo off
rem Usage: tools\clto.bat <outdir> file.c ...   (same flags as cl.bat)
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86 >nul 2>nul
set OUT=%1
shift
if not exist %OUT% mkdir %OUT%
cl /nologo /c /O2 /Oy /GS- /Gy /Zl /W3 /arch:SSE /Iinclude /Fo%OUT%\ %1 %2 %3 %4 >nul
