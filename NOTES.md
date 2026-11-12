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
