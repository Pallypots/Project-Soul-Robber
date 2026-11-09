@echo off
rem Compile recovered C to x86 COFF objects for xcompare (structural only).
rem Usage: tools\cl.bat src\game\file.c [more.c]   -> build\obj\file.obj
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86 >nul 2>nul
if not exist build\obj mkdir build\obj
cl /nologo /c /O2 /Oy /GS- /Gy /Zl /W3 /arch:SSE /Iinclude /Fobuild\obj\ %*
