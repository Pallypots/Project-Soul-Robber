# Toolchain investigation

## Evidence (Verified, `logs/header.log`)
- Library table: XAPILIB, D3D8, D3DX8, XGRAPHC, DSOUND, XACTENG, XBOXKRNL, LIBCMT, LIBCPMT, all **1.0.5849**.
- Build timestamp 2005-07-25 (header timedate 1122258004). Debug path `c:\Project\nightmareXbox\xbox\project\xnightmare\xnightmare\Release_US\xnightmare.exe`: a Visual Studio project (`Release_US` configuration) producing a PE that imagebld turned into the XBE.
- LIBCPMT present: C++ standard library linked, so at least part of the game is C++ (also thiscall functions and vtables).
- Code generation seen in the first recovered functions: cdecl for game functions, stdcall for XAPI/D3D/kernel calls, kernel calls through the import thunk table (`call [0x25F8E0]`), frame-pointer omission, `mov edi,edi` loop-alignment padding, `int3` padding between functions, 16-byte function alignment, SSE scalar float (`cvtsi2ss` at 0x00025FF0, `subss` at 0x00148128) alongside x87 helpers (`_ftol`, `_ftol2`).

## Hypothesis: original compiler
XDK 5849 (mid-2005) shipped with Visual C++ .NET 2003 (cl 13.10) as its compiler. The `_ftol2` helper and SSE scalar code fit VC 7.1 with `/arch:SSE`-like Xbox settings. Not yet confirmed: there is no PE rich header in an XBE, and we have not found a compiler string.

## Matching status: BLOCKED
- The Xbox-specific compiler and libraries come only with the Microsoft XDK, which was never publicly sold and is not legitimately obtainable now. We will not use leaked copies.
- Visual C++ .NET 2003 retail (cl 13.10) was a commercial product. If the owner legitimately owns a copy (old MSDN/retail media), it is a candidate for **x86 code-generation experiments** only; whether it reproduces the XDK compiler's output is unknown. Asking the owner is a material decision, not urgent.
- Until then: **no byte-match claims**. Recovery is semantic: draft source, structural comparison with a modern compiler, then behaviour tests in the recomp test bench.

## What works now
- VS 2022 Build Tools, cl 19.44 x86 (`build\cc.bat`): compiles recovered C as 32-bit and dumps it with `dumpbin /disasm`. Used for **structural comparison** (same calls, branches, constants, calling conventions; register choice and padding may differ). First result: `logs/modern_cl_structural.log`.
- No Ghidra install found on this machine (not under Program Files). Planned in `docs/PLAN.md` week 1; the recomp's capstone disassembly covers us meanwhile.
- No ninja on PATH. CMake is installed.

## Checker plan (x86, not the MIPS skill checker)
A structural checker `tools/xcompare.py` (next task): disassemble original range from the XBE and our COFF `.obj` with capstone, resolve our relocations to symbols, map symbols to original addresses via a table in the function record, and compare opcode sequence, immediates, branch shapes and call/data targets. Wrong constant, reversed condition, wrong call target, wrong global and missing function must fail (negative controls) before any verdict is trusted. Register allocation differences are reported, not hidden. Output state: "Structurally compared", never "match".
