# Plan: first month (from 2026-11-09)

Goal for the month: a trusted x86 checking loop, the recomp test bench proven on real swaps, and one small subsystem (chapter grading/stats) recovered and behaviour-tested.

## Week 1: tools
- `tools/xcompare.py`: structural checker (COFF `.obj` from cl vs original XBE range). Negative controls: wrong constant, reversed branch, wrong call target, wrong global, missing function must all fail. Rerun on the 3 recovered functions.
- Address table `config/symbols.csv` (inferred name, VA, type, confidence) shared by headers, checker and recomp adapters.
- Install Ghidra + XboxDev ghidra-xbe (official GitHub releases), import the XBE, cross-check entry, sections, thunks and 10 random functions against our inventory. Scripted export of xrefs for call-graph ordering.
- Own RTTI/vtable pass to find C++ classes; separate LIBCPMT inside the game range.

## Week 2: test bench
- In a branch of `C:\ProjectOogie` (with the owner's OK): adapter file, A/B environment switch, check whether direct calls hit `recomp_lookup_manual` (see `docs/swap_plan.md`).
- First swap: 0x000414A0 exclamation points. Verify with memscan on Chapter 1, Easy. Then 0x00057E90 and 0x001A7BA0.
- Host unit-test harness in `tests/` (CMake, VS 2022) for pure functions.

## Week 3-4: first subsystem, chapter grading and Jack's stats
Start from the call graph around addresses already mapped by the recomp work: grading block 0x413180 (sub_00041480, 0x000414A0, sub_000414F0, sub_00040C10), stats object 0x41FEC0 (sub_000CF790, sub_000CF810, sub_000CF910, sub_000CF950, sub_000D1F40), chapter clock (sub_0019C030, sub_0019C0B0). Leaves first, then callers. Type the stats object and grading block in `include/`. Each function: draft, structural compare, swap test, record.
- Target (estimate, to be measured): 20-40 functions semantic-tested. Throughput measured and recorded, no completion date promised.

## Ongoing
- Keep `docs/STATE.md` counts generated from `functions.csv`.
- Decision for the owner when relevant: do they legitimately own Visual C++ .NET 2003 for matching experiments? (No action otherwise.)
- Later subsystems by call graph: file/.stm archive loading, job/loader, scheduler, main loop, actors, then gameplay.
