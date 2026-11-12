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
0x33710 fx reset: hard (orig clears via lea base+0x1C then offsets 0..0x3C; cl folds to 0x1C..0x58)
0x37AF0/0x37B20 slot loops: hard (pointer bias: orig walks +0x20 field pointer with -0x20 base)
0x49A40 mark pair bit: hard (pointer bias +4 into 0x2C7E40 and signed i%32 with unsigned loop bound)
0x4BE20 grade 0..4: hard (signed pointer bound jle 0x4133EC; cl uses unsigned end and folds ==0x62)
0x77190 channel reset: hard (2-iteration loop fully unrolled by cl)
0x47A80 cue slot: hard (cl folds two range checks; a checker range-fold rule broke 31 switch/waiver cases and was reverted)
0x54CC0 m1_StampTime54CC0 PASS (passing the record to the ESI-regarg callee keeps the base pointer)
0x586E0 m1_JobFrame586E0 PASS
0x54D50 yes/no input: hard (cl tail-merges the confirm-yes and confirm-no sound calls; orig has 3 call sites)
0x56740 m1_ApplySave56740 PASS
0x53CA0 record queue step: hard (n*0x44 built as shl/add leaves an extra shift count 4; stride waiver allows only the stride)
0x52840 m1_InitLocks52840 PASS
0x48590 m1_SoundReset48590 PASS
0xC6920 m1_SetupBufsC6920 PASS
0xC7B00 m1_SetupBufsC7B00 PASS
0xC72C0 m1_SetupBufsC72C0 PASS
0xD9050 m1_LoadAtrD9050 PASS
0x194B40 thunk PASS
0x1A13D0 thunk PASS
0x19C5D0/0x1A85C0/0x19D8B0 thunks PASS
0x3DD20/0x19B690/0x1A7B90 thunks PASS
0x1DF10 link part: hard (cookie exits: cl merges the two exits; same class as 0x8F260)
0xF8D30/0x102FA0/0x1A7C00/0xFD8F0 stubs+thunk PASS
0x1A88B0 m1_Check1A88B0 PASS (nested ifs, not &&)
0xDD880 m1_TextSelectDD880 PASS
0xCD830 slot total add: hard (pointer bias: orig keeps base+0x200 then +4; cl folds 0x204)
0x16ADA0 mode 7/9 call: hard (cl tail-merges the two calls)
0x180970 pair notify loop: hard (orig signed pointer bound jl with -4 bias)
0x1A24D0 vector iterator: hard (orig dec/js then dec/jne count loop; tried while, for, do-while)
0x1A64F0 render-lock release: hard (cl tail-merges the two Leave calls)
0x3EA40 m1_SetClamped3EA40 PASS (volatile state field keeps the 2-then-3 store)
0xA23A0 m1_OffsetParts_A23A0 PASS (checker: sub r,-N = add r,N)
0x194EB0 m1_DestroyDone194EB0 PASS (checker: loop pointer bias canonicalised)
0x180970 m1_NotifyPairs180970 PASS (was hard; bias rule)
0x180930 m1_WakePairs180930 PASS
0x181CE0 link fire: hard (exit after found: cl recomputes the entry from the index, orig keeps the walking pointer; tried index, pointer)
0xED9A0 m1_TakeSlotED9A0 PASS (goto found + hang; bias rule stops at reload)
0xCC030 m1_ApplyActiveCC030 PASS
0x185370 m1_DropHolds185370 PASS
0x169730 flag mark x16: hard (manual unroll matches, but cl merges the &1 and &0x1000 tests into one &0x1001 compare)
0xA46D0 m1_PauseAllA46D0 PASS
0xA8B80 m1_StopVoicesA8B80 PASS
0x169790 flag mark 0x400: hard (same as 0x169730)
0xDE100 group/key lookup: hard (orig outer pointer sits on items and reads the next id at +0x200; tried index and pointer forms)
0xA8150 m1_StopKindsA8150 PASS
0x19A830 one-slot play start: hard (index must be 0 after the hang check, so cl constant-folds it; orig keeps the index math)
0xA4970 m1_FlagOwnedA4970 PASS (manual 4x unroll)
0xCCCE0 stick quadrant: hard (cl turns the sign tests into unsigned/table math; also struct-pointer bias +0x20C)
0x12D670 m1_ActorRelease12D670 PASS
0xEDB10 filter find-first: hard (cl folds the 0..2 range check into one unsigned compare)
0x5A760 part by index: hard (orig dec/dec switch with default block first; cl uses cmp 2 and lays default last; tried switch, if, gotos)
0x1ADE10 m1_MatFromRows1ADE10 PASS (checker: struct-pointer offset tracking)
0xC6CD0 fire owned x3: hard (cl merges &1 and &0x10000000 into one mask test)
0x33710 m1_FxReset33710 PASS (was hard; struct-pointer offset tracking)
0xC44E0 m1_ClearWordsC44E0 PASS
0x114650 m1_ActorRelease114650 PASS
0xA3690 m1_SampleA3690 PASS (unsigned cast for _ftol2; assumes >= 0)
0xCC840 m1_ReactButtonsCC840 PASS
0xAC9D0 m1_SeqStepAC9D0 PASS
0xADB60 m1_SeqStepADB60 PASS
0xAC8A0 m1_SeqStepAC8A0 PASS
0xAC930 m1_SeqStepAC930 PASS
0x47950 m1_AllIdle47950 PASS
0xA9A30 stat bump: hard (cl builds 0x4F/0x50 as 0x4F+setne, losing the 0x50 constant; same select class as 0x3E610)
0x169730/0x169790 m1_MarkOn PASS* (merged-bit-test waiver; were hard)
0xC6CD0 m1_FireOwnedC6CD0 PASS* (merged-bit-test waiver)
0x37AF0 m1_ChanUpdate37AF0 PASS (was hard; bias rule without a pointer bound compare)
0x37B20 channel apply: hard (orig dec/dec kind switch and pointer passed as lea; cl cmp 2 and passes the walking pointer)
0x398D0 map value: hard (orig has exactly two 0x396E0 call sites; cl gives one or three)
0x128240 m1_AfterAnim128240 PASS (checker: branch-free select = two constants)
0xA9A30 m1_StatBumpA9A30 PASS (was hard; setcc+add select rule)
0x3E610 m1_DrawMenuLinef3E610 PASS (was hard; select rule with lookahead)
0xCD830 m1_AddSlotTotalCD830 PASS (was hard; offset tracking through indexed lea)
0xCDAB0 m1_FindEntryCDAB0 PASS (regargs m=EAX key=ESI; bias rule starts at the pointer load)
0xCF000 m1_UpdateEntriesCF000 PASS (regarg callees)
0xA93F0 m1_VoiceStartA93F0 PASS (regarg callee)
0x188360 run mode 2/1: hard (cl computes the mode as (flag&1)+1 with one call; orig branches to two calls)
0x54770 m1_BuildSave54770 PASS (regargs s=EAX)
0x531C0 m1_FindSound531C0 PASS
0x34050 effect name: hard (cl merges the type-1 and default snprintf calls; orig has three call sites)
0xCDB00/0xCDB50/0xCDBA0 bone save/restore/clear PASS (regargs)
0xCEF60/0xCEFB0 entry set pickers PASS (regarg callees)
0xCEAE0/0xCEBB0 entry pickers: hard (orig keeps an always-false i<0 check after the free-slot search; cl drops it)
0xA0FD0 m1_CountHandledA0FD0 PASS* (merged-bit-test waiver)
0xF3630 m1_EnsureResF3630 PASS
0x107760/0xEEF40 hit reaction 4/5: hard (cl merges the two 0x36750 calls)
0xA5730 m1_SetupA5730 PASS
0xCAB30 m1_FeedLimitsCAB30 PASS
0xBC5F0 ring clear: hard (cl knows count >= 3 and drops the loop-entry check the original keeps)
0x181DA0 m1_ResetLinks181DA0 PASS
0x181D40 m1_LinksReady181D40 PASS
0xA4670 m1_StopOwnedSoundsA4670 PASS (bias rule: mov copy of the walking pointer)
0xCC8C0 m1_ReactButtonsCC8C0 PASS (regargs o=ESI buttons=EAX)
0xA36E0 m1_StartSlotEffectA36E0 PASS
0xCDA00 m1_RunHandlerCDA00 PASS
0xCDA50 m1_InputStepCDA50 PASS (own file so cl does not inline)
0xCD860 m1_SlotTickCD860 PASS (offset kept across a branch target when its register is written once)
- 0xCC4D0/0xCD930 were already recorded by area r6e; my duplicates removed. Check function_states before picking by hand.
0xA56C0 m1_ClearJackFlagsA56C0 PASS
0x125DE0 m1_AfterAnim125DE0 PASS
0x5AB00 chain anim restart: hard (cl folds the 12..13 range and duplicates the restart call; a range checker rule was tried and reverted: it hid the wrong-array-field control)
0xA4DE0 m1_ReleaseEntryA4DE0 PASS
0xA3810 entry reset: hard (cl fully unrolls the 4-step loop the original keeps rolled); checker gained: float literal stored as bit pattern = fconst
0xB6300 m1_SeqStepB6300 PASS (regargs)
0xCCD60 m1_PadKeyCCD60 PASS
0xB4010 sequencer variant: hard (two 0xA4410 calls with 1/0; cl merges them)
0x39660 m1_FadeColour39660 PASS (quad table declared as 2 x 0x1450 array)
0x79910 record copy by id: hard (cl merges the direct-slot call with the final call)
0xA4B80 m1_ResetAllA4B80 PASS
0xA3780 m1_LookupKeyA3780 PASS* (stride waiver)
0xEB3A0 give/anim: hard (cl merges the two 0xD0200 call sites)
0xE1E00 m1_SetupRigE1E00 PASS
0x189960 m1_StageReset189960 PASS (bias rule: pushed walking pointer)
0x37B20 m1_ChanApply37B20 PASS (was hard; bias rule skips mov r,r no-ops and handles pushed pointers)
0x17E410 m1_SetupActor17E410 PASS
0xF6D80 m1_ResetInputF6D80 PASS (checker: dword zero store also clears the word 2 bytes up)
