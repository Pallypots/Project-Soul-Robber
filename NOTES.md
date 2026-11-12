# NOTES (read first; keep short)

Repo: C:\ProjectOogieDecomp (GitHub Pallypots/Project-Soul-Robber). XBE: C:\ProjectOogie\game\default.xbe (read only).

## Loop for one function
1. Pick: unrecorded rows of config\inventory\functions.csv (owner=game), not in config\not_functions.csv or any config\function_states*.csv.
2. `py -3 tools\xdis.py 0xVA` (honours config\size_overrides.csv).
3. Write C in src\game\<area>_N.c; prototypes from include\shared_decls.h; own header include\<area>.h.
4. `cmd /c tools\clto.bat build\obj_<area> src\game\<area>_N.c`
5. `py -3 tools\xcompare.py build\obj_<area>\<area>_N.obj Name 0xVA -d | tail -n 40` (waivers only apply in --all).
6. Record in config\function_states_<area>.csv (va,name,state,source,obj,waivers,notes) + symbols in config\symbols_<area>.csv.
7. Batch end: `py -3 tools\xcompare.py --all | tail -n 3`, `py -3 tools\progress.py`, commit + push.

## Rules that matter
- Hangs: `if (bad) for (;;) ;` (cl deletes `while (bad) ;`). Never re-call inside a hang.
- Check pushed call arguments by hand (checker does not compare them).
- No pointer<->int casts. Register args: normal params + `regargs: p1=EAX ...` in notes.
- Waivers only for idioms in docs\verification.md. Never waive call target/count, global, logic constant, hangs.
- Security-cookie functions (call 0x1C7D27): put them in a file whose name contains `_gs` (e.g. m1_gs1.c); clto_gs.bat/build_all compile those with /GS. Cookie symbols are mapped in config/symbols_m1.csv.
- Skip: XMM float args/results, thiscall with stack args.
- Fails after 3 attempts -> log below as hard, move on.

## Current area for my own work
Area prefix: `m1` (src\game\m1_*.c, include\m1.h, config\*_m1.csv, build\obj_m1).

## Log (one line per function)
0x72EE0 m1_FadeStart72EE0 PASS* (store merge)
0x53D70 m1_PathOp53D70 PASS (first /GS cookie function: *_gs*.c files compile with /GS)
0x53ED0 m1_LoadFmt53ED0 PASS
0x65A50 m1_LoadNum65A50 PASS
0x8DC40 m1_PathYca8DC40 PASS
0x8E8B0 m1_PathClp8E8B0 PASS
0x8ED70 m1_PathDfd8ED70 PASS
0x8EFB0 m1_PathLgt8EFB0 PASS
0x8F210 m1_PathBms8F210 PASS (0x89690 returns a string ptr)
0x85300 m1_LoadEnemyArg85300 PASS
0x861A0 m1_LoadLoadsetArg861A0 PASS
0x86E60 m1_LoadBgobjectArg86E60 PASS
0x86FA0 m1_LoadResidentArg86FA0 PASS
0x873D0 m1_LoadArrangeLin873D0 PASS
0x53DC0 m1_LoadRun53DC0 PASS
0xE0010 m1_LoadEventBmsE0010 PASS
0xE0070 m1_LoadTalkBmsE0070 PASS
0xE00D0 m1_LoadShopBmsE00D0 PASS (early returns stop cl folding the 6..8 range)
0xE0150 m1_LoadQuizBmsE0150 PASS
0xE05B0 m1_LoadEventLgcE05B0 PASS
0xE0700 m1_LoadRubberE0700 PASS
0xE0DD0 m1_LoadMbBmsE0DD0 PASS
0x1DBF0 m1_LoadPigA1DBF0 PASS
0x1DC70 m1_LoadPigB1DC70 PASS
0x5EE40 shock .shd loop: hard (cl drops the always-true i<0x100 check the original keeps)
0x36660 m1_LoadById36660 PASS
0x366F0 m1_LoadDemoEff366F0 PASS
0x40E90 m1_LoadStageFlip40E90 PASS
0x1A88D0 m1_SysCall1A88D0 PASS
0x1A9A30 m1_TitleMetaExists1A9A30 PASS
0x1A9B90 digest compare: hard (original inline memcmp is repe cmpsd; cl 19 expands it differently)
0x371A0 m1_LoadFigure371A0 PASS
0x8C3C0 m1_FindKind8C3C0 PASS
0x36860 skipped: loads arg2 into EBX and never uses it (not producible from C)
0x8E900 m1_LoadClpRes8E900 PASS (after checker rule: AND mask feeding a 16-bit store compares low 16 bits)
0x8F260 load .bms resource: hard (cl orders the three cookie exits differently; tried early return, rc variable, swapped branch)
0x1DB40 model .bmd/.pod loader: hard (cl folds kind 1..2 range into one unsigned compare; tried if/else, switch, nested ifs)
0x4F810 m1_SplitPath4F810 PASS
0x4F8E0 m1_FindStream4F8E0 PASS (int index loop -> signed jl like the original)
0x2E8C0 m1_DrawTextf2E8C0 PASS (checker: pushed float bits = float literal; fld1 = 1.0)
0x3E4B0 m1_DrawTagf3E4B0 PASS
- r6f 0x8E480/0x8EB10: +0x18 flag update now writes 16 bits (f18.s.w), as the original; exposed by the 16-bit mask rule
0x3E610 menu line: hard (old neg/sbb/and 0xB/add 0x20 select vs cl cmov 0x2B/0x20; a select rule clashed with setcc+lea forms, reverted)
0x84DD0 m1_LoadAddEnemy84DD0 PASS (inline memset = __stosd+__stosb)
0x85C50 item.arg loader: hard (pointer bias loop: cl biases the slot pointer differently; tried pointer and index forms)
