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
- When backing out an attempt, remove only symbol lines added in that attempt (check `git diff config/symbols_m1.csv`); a sed on a name can delete an older line.

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
0x142AF0 m1_EnemyHit142AF0 PASS
0x138140 m1_EnemyRecoil138140 PASS
0x13CF90 m1_EnemySeq13CF90 PASS
0x137170 enemy next attack: hard (cl builds the 3/5/1 attack choice from bit 7 arithmetic with one call)
0x126090 actor check: hard (orig tests bit 15 as test ah,ah/js and orders the calls differently; tried 3 forms)
0x11AC30 m1_EnemyAttack11AC30 PASS
0xCC430 m1_DefaultKeysCC430 PASS
0xE1E90 m1_FreeRigE1E90 PASS
0x540C0 m1_SaveShutdown540C0 PASS
0x18840 m1_SetCopy18840 PASS (regargs dst=EBX)
0xA4560 m1_SetOwnedAnimA4560 PASS
0xE7580 m1_CloseScreenE7580 PASS
0x37BC0 m1_ChanShutdown37BC0 PASS
0x3A020 m1_EmitBlock3A020 PASS
0xEA170 event dispatch: hard (orig repeats always-true word compares cmp ax,ax that cl folds)
0xA9EF0 m1_RestoreDefaultsA9EF0 PASS
0x191F0 m1_SamplePose191F0 PASS
0xEC670 m1_RemoveComp12EC670 PASS
0xCBA30 item fx/sound: hard (cl lays the create-effect block after the stop path; calls compared in address order; tried 3 layouts)
0xCC2A0 m1_JackFrameCC2A0 PASS
0xCB390 m1_GatherTargetCB390 PASS* (merged-bit-test waiver)
0xCB540 target selection sort: hard (orig walks order[] and reads key[] at -0x80; cl walks key[] and bumps the pointer mid-iteration)
0xCE4C0 m1_PartsLookCE4C0 PASS (own file to stop inlining)
0x107490 m1_BossTeardown107490 PASS
0xC6B90 m1_ValidateAimC6B90 PASS* (merged-bit-test waiver)
0xAAA90 m1_SeqStepAAA90 PASS
0xB6740 m1_DoorSeqB6740 PASS (shared door template)
0xB6840 m1_DoorSeqB6840 PASS (shared door template)
0xB6950 m1_DoorSeqB6950 PASS (shared door template)
0xBAB90 m1_DoorSeqBAB90 PASS (shared door template)
0xBA630 m1_SeqStepBA630 PASS
0xBA020 m1_SeqStepBA020 PASS
0xB7120 multi-step sequencer: hard (orig shares one 0xA4340 call between steps 14/16 via the jump table; cl splits it)
0x17D810 m1_SceneEnd17D810 PASS
0x4ED90 pad reset: hard (cl merges the sixteen 0x7F axis byte stores into four 0x7F7F7F7F dword stores)
0x17CDC0 m1_ResetRecs17CDC0 PASS
0xCC360 m1_RecheckTargetCC360 PASS* (merged-bit-test waiver)
0xCB490 m1_TargetKeysCB490 PASS
0x18A250 m1_ClearRecs18A250 PASS
0xCCC50 slot clear: hard (orig lea base+0x200 then walks; cl stores through the indexed address directly)
0xCED00 m1_BoneHold0CED00 PASS
0xCED50 m1_BoneRelease0CED50 PASS
0xCEDA0 m1_BoneHold1CEDA0 PASS
0xCEDF0 m1_BoneRelease1CEDF0 PASS
0xCAAD0 m1_FeedLevelCAAD0 PASS
0x109400 m1_ResetMotion109400 PASS
0xF9230 apply velocity: hard (orig keeps a self-copy of +0x6C that cl deletes)
0x102950 camera distance: hard (cl rewrites y*-0.015625*2 float constants)
0x1108A0 m1_HitStrong1108A0 PASS
0xCEC90 m1_BoneSetCEC90 PASS
0xCE880 m1_BoneEntsInitCE880 PASS
0xA3D40 m1_SyncPoseA3D40 PASS
0xA35B0 m1_WrapAngleA35B0 PASS
0x18D190 m1_SpinTurn18D190 PASS
0x18D090 m1_SpinStart18D090 PASS
0x18DFC0 m1_ResetRecs18DFC0 PASS
0x18DC90 m1_BurstDestroy18DC90 PASS
0x18DC00 m1_PlaceModel18DC00 PASS
0x18DED0 m1_SetupFollower18DED0 PASS
0x179060 m1_Setup179060 PASS (simple setup template)
0x17EBF0 m1_Setup17EBF0 PASS (simple setup template)
0x17EC80 m1_Setup17EC80 PASS (simple setup template)
0x17ED70 m1_Setup17ED70 PASS (simple setup template)
0x17EEA0 m1_Setup17EEA0 PASS (simple setup template)
0x183140 m1_Setup183140 PASS (simple setup template)
0x183290 m1_Setup183290 PASS (simple setup template)
0x183A80 m1_SetupPair183A80 PASS
0x183D30 m1_SetupFixed183D30 PASS
0x1852E0 m1_SetupHold1852E0 PASS
0x114300 m1_EnemyDefaults114300 PASS
0x17E310 m1_SetupScene17E310 PASS
0x183010 m1_SetupSingle183010 PASS
0x182630 m1_SetupLink182630 PASS
0x183200 m1_DrawStd183200 PASS
0x172480 world y of part: skipped (float result returned in XMM0, out of scope)
0xCE8F0/0xCE970 bone entry clears PASS
0xA1F50/0xA1FD0 raised position PASS* (stride waiver)
0xA3CC0 m1_SyncPoseA3CC0 PASS
0xCFF10 m1_PushStateCFF10 PASS
0xF4590 m1_StageRestartF4590 PASS
0xBF350 m1_JackStopBF350 PASS
0x1090F0 m1_HitReact1090F0 PASS
0x10C510 m1_ResetMotion10C510 PASS
0x10E350 m1_StopSpeed10E350 PASS
0xA8C90 m1_AnyNearA8C90 PASS
0xA8090 m1_WithinRadiusA8090 PASS (own file)
0xA8BF0 m1_HandsNearA8BF0 PASS
0xA88B0/0xA8990 voice slot starters: hard (orig keeps an always-false i<0 check after the free-slot search; cl drops it)
0x17D780 m1_SceneReset17D780 PASS
0x1A4190 matrix fill: skipped (float argument passed in XMM0)
0xEACC0 m1_RestoreViewEACC0 PASS
0xCBE20 m1_AimAtTargetCBE20 PASS
0x17FB10 m1_StepUpdate17FB10 PASS
0x11A660 enemy flinch: hard (rand() % 4001 signed modulo; cl uses a reciprocal multiply, only the unsigned form is a documented idiom)
0x10C590 m1_ResetMotion10C590 PASS
0x10ED90/0x10B910/0x10C630 motion resets PASS
0x10EC80 m1_StopSpeed10EC80 PASS
0x10AB90 m1_ResetMotion10AB90 PASS
0x109370 m1_HitReact109370 PASS
0x10C030/0x10E810/0x10E470 motion helpers PASS
0x10BCD0/0x10C460/0x10E100 motion helpers PASS
0x10E760 m1_DrainFuel10E760 PASS
0xF2400 reset motion: hard (0x1B..0x1D range check folded by cl)
0x111A20 enemy anim hit: hard (orig sub-chain switch 2/0x12 and block order differ from cl)
0x10E1B0/0x10E280 speed stops PASS
0x10E030 m1_StopSpeed10E030 PASS
0x10B250 m1_ResetMotion10B250 / 0x10D6B0 m1_StopSpeed10D6B0 PASS
0x10D5D0/0x10D790 speed stop + anim (M1_SPEED_STOP_ANIM) PASS
0x10EB90/0x10E510 speed stop variants PASS
0x10DDF0/0x10E600 speed stop music + hold records PASS
0x10ED00/0x10DF20 zero speed, 0x10EF70 launch vector PASS; 0x10FA20 sound start: hard (cl merges the two 0x36750 calls into flag?8:9 via sbb)
- Edit CSVs as bytes (mixed CRLF/LF); Python text mode rewrites every line ending.
0x1032A0 m1_ScrReset1032A0 / 0x1173F0 m1_Step1173F0 PASS (m1_48.c)
0x113E90 link init: hard (orig duplicates the 0x1B21D0 tail call per branch; cl merges it)
0x102310 m1_CamHold102310 / 0x1036E0 m1_CamRelease1036E0 PASS
0x1009E0 m1_CtlStep1009E0 PASS; 0x1060B0 player aim: hard (orig keeps two 0xCF330 tail calls; cl merges them)
0x101E50 m1_ScrTimers101E50 PASS (walk a float* to the timer, resource at [-4]; slot struct pointer made cl spill); 0x104630 m1_ScrWatch104630 PASS
0x10E3D0 m1_ZeroSpeed10E3D0 / 0x1008F0 m1_CtlStep1008F0 PASS
0x116590 m1_RigStep116590 PASS; 0x103A80: skip (0x1023A0 takes ecx + xmm1 float)
0x115CC0/0x1162E0 rig steps PASS (checker float-rule round-trip fix)
0x1130F0 m1_ChainShow1130F0 / 0x10DF90 m1_ZeroSpeed10DF90 / 0x10A0A0 m1_FadeOut10A0A0 PASS (byte offset loop var for the stride-0x108 store); 0x104070 deck shuffle: hard (orig uses div by 9; cl always uses a reciprocal multiply)
0x119900 m1_RigOnce119900 PASS; 0x13FD20 hit next-state: hard (cl tail-duplicates the 0x113040 call into the branches); 0x11F4F0: skip (eax + xmm0 register args)
0x11A950 m1_RigStep11A950 PASS; 0x125540: skip (register args eax/esi/ebx)
0x138FB0: skip (orig duplicates the 0x113040 tail call per branch, same class as 0x113E90); 0x120BF0: skip (0x11F0C0 takes eax)
0x11E700 gauge drain: hard (orig reuses the 1.0 register for the +0x7C store; ours stores the bit pattern and the 1.0 load is already matched, so the float rule cannot fold it); 0x11DF80: skip (0x11DD70 takes esi/edi)
0x12E720/0x1360B0 rig idle (M1_RIG_IDLE) PASS
0x13E390/0x13E770 rig steps with fade + command PASS
0x12C730 m1_RigSpin12C730 PASS; 0x118870: skip (0x1154D0 takes eax)
0x12F4C0 rig idle with random state: hard (cl folds rand&1 ? 0x32 : 0x31 into add; orig pushes per branch); 0x132080: skip (0x131310 takes edi)
0x135FE0 m1_RigIdle135FE0 PASS; 0x1373D0: skip (same random-pick class as 0x12F4C0)
0x13E8D0 m1_RigRoll13E8D0 / 0x14B510 m1_RigBlend14B510 PASS (float rule widened for register-reused constants)
0x11E700 (now passes with the widened float rule), 0x12F2E0, 0x12F850, 0x1399D0, 0x146940, 0x14F360, 0x12F380 PASS (m1_50.c); 0x11DB30: skip (0x11B1C0 takes eax)
0x12F420 m1_RigIdle12F420 / 0x146E50 m1_RigBlend146E50 PASS (m1_51.c: 0x156180 declared with float args)
0x1430B0 m1_RigNext1430B0 PASS (picking next with a ternary and guarding the side effect with next == 8 stops cl duplicating the 0x113040 tail call; worth trying on that hard class)
0x139EF0 m1_RigAim139EF0 PASS; 0x13FD20 retried with the ternary trick: still hard
0x121DA0 m1_RigStep121DA0 PASS (call written in both branches keeps the orig's duplicate)
0x1421C0 m1_RigCleanup1421C0 PASS; 0x138A10 knock-back: hard (orig keeps two 0xED780 calls; cl merges them in every layout tried)
0x188FD0: skip (null checks on global array elements; cl drops them); 0x18A280, 0x18E540: skip (register/xmm args)
0x172650 height offset: blocked (checker reads an indexed .rdata float table on the orig side as a float constant but as data on ours; orig also keeps a dead lea of the entry). Possible checker fix: treat declared data symbols in .rdata as data on both sides; 0x1701A0, 0x18ECD0: skip (register args)
0x1576A0 m1_RigStep1576A0 PASS; 0x18F8D0: skip (eax arg)
0x180A60 m1_GroupReset180A60 PASS (int index loop gives the signed compare); 0x169EA0: skip (0x169D30 takes edi)
0x167D00, 0x186470: skip (register args eax / edi+ebx)
0x1AA200 sem init: hard (orig biases the loop pointer to +0x1C, cl to +0x14); 0x1AD4B0 m1_ThreadClose1AD4B0 (call written in the loop and after it keeps the orig's two calls); 0x1A1D50 channel select: hard (cl folds i >= 9 && i > 0); 0x1B74E0: skip (x87 float chain)
0x1B93E0 voice list init: hard (orig biases the loop pointer by +0x50 and links via lea -0x50; bias rule does not fold it); 0x1BB710: skip (tail jmp); 0x1A2020: skip (aligned symbol address math); 0x1AEDF0, 0x1B34D0, 0x1A78A0, 0x1A78F0: skip (x87/xmm); 0x1B1D40: skip (register args)
0x1B8800 bank bind: hard (our cl picks cmove for the data-or-0 store; orig branches)
0x1B6A90 m1_CueLength1B6A90 PASS; 0x1A9CE0 save seal: hard (weighted-sum loop: cl unrolls by 2 or drops the n > 0 guard); 0x1BB780: skip (0x1BB660 register use unclear); 0x1B8870: skip (bitfield init)
0x193990: hard (biased +0x44 loop pointer); 0x19A040: hard (always-true pointer range checks cl drops)
0x4F680: hard (always-false i<0 && i>=0x21E check); 0xED520/0xED590: hard (orig folds the const table's first kind (2) into an immediate)
0xC9CE0 m1_ActionReady0C9CE0 PASS (merged bit-test waiver); 0xA9EB0: hard (cl folds the 0..7 range into one unsigned compare); 0x9FC60/0xA0030: interior fragments, added to not_functions.csv; 0xEE080, 0xF4280, 0x8FFE0: hard (const table fold + tail jmp / duplicated tail call / inline memcmp); 0xF23C0, 0xF24B0, 0xB4790: skip (register args)
0xCCC90 stick quadrant: hard (cl uses the byte-minus-0x7F range for unsigned compares); 0x53F70: hard (orig calls _aulldiv for ms*576000/1000, cl multiplies); 0x900A0: hard (inline memcmp); 0xC2A40, 0xE99A0: skip (register args)
0x5AB70: hard (cl folds kind 12..13 into one unsigned compare); 0xCD8D0, 0xCEEA0: skip (register args)
0x79EF0 fog apply: hard (cl merges the two 0x84910 calls); 0xCEF00, 0xD0480: skip (register args)
0xFCDD0 m1_HelperCam0FCDD0 PASS
0xD2CC0: hard (orig keeps an always-true null test on &o->fE04); 0xDFED0, 0x5ED30: skip (byte-pair packing / insert loops with biased pointers); 0x6CA50, 0x45C60, 0xCEE40, 0x38BF0: skip (register args)
0x409E0: hard (hang on 1..24 range, cl folds it); 0x75850: skip (0x75780 register args)
0xC7340, 0x72F30: skip (esi register arg / tail jmp with unsigned-to-float fixup)
0xCBEB0, 0xA82C0, 0x94360/0x943D0 (M1_GROW, double literal keeps the x87 fmul qword) PASS; 0xF1E80: skip (double store to the same field)
0xDD990: hard (orig builds the id's high byte with mov dh; cl shifts); 0xA9440, 0x497E0, 0x6DC00: skip (register args)
0x94680, 0xCF2C0, 0xF95B0, 0x904F0, 0xA30F0 PASS (m1_58.c); 0xD2C40: hard (always-true null test, like 0xD2CC0); 0x38AD0: skip (register args)
0xFC8F0/0xFCC20 helper speed: hard (cl merges the two 0x832D0 calls); 0xA7570 m1_MsgQueue0A7570 PASS
0x53760 m1_PoolsInit053760 PASS (index loop for the signed end test); 0xFC970: hard (merged 0x832D0 calls, as 0xFC8F0); 0xCF330: skip (x87 result of 0xBC040 into a field mid-sequence)
0xEFA60 m1_TurnAround0EFA60 PASS; 0xF3260: hard (0..15 range fold); 0xC9280: skip (register args)
0xFC660, 0xC4420, 0xF5380 PASS (m1_60.c); 0x5A2F0: skip (main loop, register args); 0x40950: hard (1..24 range hang); 0x1A710: skip (register args)
0xC7130 m1_Nearest0C7130 (merged bit-test waiver, three tests); 0xC46B0: hard (kind 0x25/0x26 folded into one compare); 0xEE6D0: hard (duplicated tail calls)
0x38E80 m1_CmdPush038E80 PASS; 0xCD970, 0x1C7B0: skip (multi-exit flag chain / duplicated tail stores, later)
0xEFAF0, 0xCBB70 PASS (m1_61.c); 0xEE1B0: hard (const table first kind folded, like 0xED520)
0xFFEA0, 0xC6E10, 0xE7990 PASS (m1_62.c)
0x34110, 0x541B0: skip (register args)
0x166B30/0x1721E0 effect models (M1_FX_MODEL) PASS
0x186B50, 0x18AB70 PASS (m1_63.c)
0x116630 PASS (m1_63.c)
0x1556D0 m1_Shoot1556D0 PASS
0x155780 m1_Phased155780 PASS (m1_64.c); 0x172F40: skip (xmm0/edi args)
0x176C60: skip (0x176930 takes eax)
0x116980, 0x1809B0 PASS (m1_64.c)
0x187380 PASS (m1_64.c); 0x185420 record count: hard (cl cmove on the first unrolled slot)
0x183F10, 0x1178F0: skip (register args / xmm result)
0x142330 m1_RigLaunch142330 PASS
0x119C80 PASS (m1_65.c, countdown loop kept); 0x12CF00: skip (0x11FCC0 register args)
0x175430/0x176510 leash checks PASS (m1_65.c)
0x1771E0 m1_Glow1771E0 PASS (m1_65.c)
0x118410 m1_Step118410 PASS (m1_65.c, case 0 falls into case 1)
0x12FCA0, 0x12FF80 PASS (m1_65.c)
0x137970 PASS (m1_66.c); 0x173440: skip (0x172C90 takes eax)
0x179820 m1_Sequence179820 PASS (m1_66.c)
0x147140 m1_FadeStep147140 PASS (ours 65 vs 47 insns: x87 temporaries); 0x188390: hard (random/flag pick folded, like 0x12F4C0)
0x186C40 PASS (m1_66.c); 0x138C10 wait step: hard (cl duplicates the 0x113040 tail call in every layout tried)
0x158430, 0x16B030 PASS (m1_67.c)
0x17C140 m1_Drop17C140 PASS (m1_67.c); 0x187EA0: hard (flag-pick push folded)
0x147090 m1_PhasedT147090 PASS (m1_67.c; !(0 >= t) gives the orig jb); 0x1786F0: skip (0x178470 register use unclear)
0x157080 m1_RigBlend157080 PASS (m1_67.c); 0x113CE0: skip (inline memset sizing, later)
0x1339A0, 0x133A50: skip (0x12E630 eax / 0x131310 ebx args)
0x170990, 0x139030 PASS (m1_68.c)
0x146DA0 m1_StandUp146DA0 PASS (m1_68.c)
0x1481E0 m1_RigSwing1481E0 PASS (m1_68.c)
0x178DF0 m1_Launch178DF0 PASS (m1_68.c); 0x16E570: skip (0x16C820 register arg)
0x17DCF0, 0x187280 PASS (m1_69.c)
0x166BD0 m1_FxModelFree166BD0 PASS (m1_69.c)
0x172280 m1_FxModelFree172280 PASS (M1_FX_FREE)
0x174EF0 m1_FxModelFree174EF0 PASS (M1_FX_FREE); 0x1757C0: skip (eax/ecx args)
0x174E50 m1_FxModel174E50 PASS
0x189B90 / 0x189C30 effect model load/free PASS (m1_70.c)
0x1127B0, 0x112890: hard (kind 3 or 4 test folded into one compare)
0x16FA40 m1_FxModels16FA40 PASS (m1_70.c)
0xE2540: skip (jump-table switch with cross-jumped tails)
0x145F70 m1_Upright145F70 PASS (m1_71.c)
0x156440 m1_DropToNode156440 PASS (m1_71.c); 0x1745D0: skip (esi arg)
0x17E5D0, 0x17E9B0: skip (eax args to 0x17E4D0 / 0x17E720)
0x135F20 m1_RigIdle135F20 PASS (m1_71.c); 0x138640: hard (random pick branches folded)
0x119F30 m1_RigCleanup119F30, 0x18EBF0 m1_Burst18EBF0 PASS (m1_72.c; !(x >= k) gives the orig jae)
0x1428D0 m1_RigPick1428D0 PASS (temp float avoids _ftol); 0x136710: skip (register args)
0x143570 m1_Glow143570 PASS (m1_72.c); 0x1788D0: skip (esi arg)
0x1391B0: hard (block order of the shared exit; three layouts tried); 0x127A30: skip (ebx args)
0x139270: hard (same block order as 0x1391B0); 0x141760: skip (table calls with sbb select)
0x13B620: hard (sbb select for next state); 0x173FE0: skip (register args)
0x1787A0, 0x181400 PASS (m1_73.c; if-chain avoids cl's jump table)
0x13B890: hard (cl converts the frame with _ftol, orig cvttss2si); 0x15A3D0: later (long)
- 0x185900 m1_RigFall185900 PASS (m1_74); needed sub_00145F70 symbol for the cross-file call.
- 0x10A230 m1_PartsReset10A230 PASS (m1_74), byte-offset loop pointer.
- 0x11FCC0 skip (ecx/eax register args).
- 0x13FF80, 0x115970, 0x115DB0 PASS (m1_74; M1_SWAY template for 0x1456E0 + command-1 sway setups).
- 0x115760, 0x115E70, 0x115F50, 0x12EDC0, 0x12EF90, 0x12F080, 0x12F550 PASS (m1_75; M1_SWAYQ: rig type, quaternion reset, pre and body are parameters). 0x115620 is the same family with an extra random sound and table copies, not tried yet.
- 0x115620 PASS (m1_75), sway point table 0x31A3B0 has 6 entries of 0x18.
- 0x13E6B0 PASS (m1_76, sibling of 0x13E770). 0x127470 skip (register-arg calls 0x11EDE0/0x11F2B0).
- 0x1416A0: hard (rand pick 0x1D/10 is setge/dec/and; cl always emits cmovge, even written as arithmetic).
- 0x17C1F0 PASS (m1_76).
- 0x13E4A0 PASS (m1_76). neg/sbb select: write (-(bit != 0) & k) + base; a ternary or bit*k+base gives lea/cmov. Retry 0x13B620 with this. 0x110540 skip (tail jmp with eax arg).
- 0x13BA30 PASS (m1_77). 0x13D3F0 skip (ebx register arg).
- 0x139FE0, 0x159B30 PASS (m1_77).
- 0x177AC0, 0x17DAB0 skip (register args).
- 0x159E30 PASS (m1_77).
- 0x13B620 now PASS (m1_77) with the (-(bit != 0) & 2) select; was hard.
- 0x16DED0 PASS (m1_77).
- 0x173570, 0x17A780 skip (register-arg calls 0x172C90/0x172E00, 0x17A2B0).
- 0x17E910, 0x17C530, 0x18A880 PASS (m1_78; 0x17C530 keeps the original double i>=6 check). 0x188740 skip (eax/ecx args).
- 0x18EB50, 0x1566D0 PASS (m1_78). 0x186800 skip (eax arg calls).
- 0x174B40, 0x17B1C0, 0x17CA70 PASS (m1_78). Index loop over a global array gives the signed jl pointer compare; a pointer loop gives jb.
- 0x17F050, 0x180AF0 PASS (m1_79, record-release family). 0x179190: hard (cl merges the +0x14/+0x16 halfword zero stores into one dword). 0x17E5D0 skip (eax arg call 0x17E4D0). 0x16D5E0, 0x170750 skip (register-arg calls).
- 0x166110 PASS (m1_79). 0x186600, 0x17CF40 skip (register args).
- 0x138DF0 PASS (m1_79; case 0 falls through to case 1). 0x166110 needed pointer+counter loop (index loop gave an end-pointer compare).
- 0x17B9A0, 0x188690 PASS (m1_80).
- 0x188DD0 PASS (m1_80).
- 0x155610 PASS (m1_80).
- 0x118070 PASS (m1_81). 0x11D980 skip (ecx/edx call 0x11B0D0).
- 0x14B1C0 PASS (m1_81). 0x176E00 skip (calls 0x176970 with esi arg).
- 0x18D680 PASS (m1_81).
- 0x116EA0, 0x11A3D0 PASS (m1_81).
- 0x138D20 PASS (m1_82, mask select again). 0x13B7C0: hard (_ftol for the start frame and cl turns the sign-flag +2 into sar/and).
- 0x103770 PASS (m1_82).
- 0x11A590: hard (_ftol for the random wait; orig cvttss2si).
- 0x1390E0: hard (cl does the whole wait/distance test in x87 with a double 15.0; orig uses SSE comiss for the wait). 0x159D60 not tried yet.
- 0x159D60 PASS (m1_83).
- 0x1811F0: hard (cl merges the two state-2 calls; orig keeps one per branch). 0x16FBC0 skip (esi arg call 0x16FB60).
- 0x18BA50 PASS (m1_83). 0x189020 skip for now (always-true null check on &table[i]).
- 0x17C010 PASS (m1_84; the orig w self-copy comes from a vec4 struct copy). 0x187810 skip (register-arg call 0x186470).
- 0x188D00: hard (cl unrolls the 3-row scale loop; orig keeps it).
- 0x112C00 PASS (m1_84).
- 0x17C6F0 PASS (m1_84).
- 0x11DC20 PASS (m1_84; second limit reads the partner component +0x274).
- 0x175CE0, 0x179910 PASS (m1_85).
- 0x17CC00 PASS (m1_85). 0x18B8F0 skip for now (x87 fild random angles).
- 0x12DDE0 PASS (m1_85).
- 0x184530 PASS (m1_85).
- 0x1357F0, 0x11B210 PASS (m1_86).
- 0x18C6B0: hard (orig checks 10 slots unrolled; cl re-rolls even hand-unrolled code into a loop).
- 0x139E10 PASS (m1_87). 0x118BC0 skip (fragment using esi/edi from its caller).
- 0x157730, 0x176070 PASS (m1_87).
- 0x13E9C0 PASS (m1_87). 0x1452D0 skip (register-arg call 0x143740).
- 0x17D6A0 PASS (m1_87). 0x172D20 skip (register args).
- 0x13B6E0: hard (_ftol for the random start frame, same as 0x13B7C0).
- 0x135170 PASS (m1_88, countdown loop of 3 kept).
- 0x144720 PASS (m1_88; state picked into one variable so cl keeps a single call). 0x16C480 skip (register args).
- 0x1700C0 skip (eax register arg).
- 0x175310, 0x17D5C0 PASS (m1_89). 0x1869A0 skip (eax-arg calls 0x186160/0x186470).
- 0x12F630 (m1_75), 0x165480, 0x156A30, 0x1395C0 (m1_90) PASS.
- 0x156C10 PASS (m1_91). 0x156B10, 0x156F90 (and likely 0x156770, 0x156CF0, 0x156E50, 0x157880, 0x157F80): hard, the doubled-rate sways multiply by 2.0 and cl turns x*2 into x+x. 0x181650 skip (eax call 0x181090).
- 0x184040 PASS (m1_91).
- 0x11D8A0 PASS (m1_91; wait defaulted to 0 first so cl shares the state-5 call).
- 0x178080 PASS (m1_92). 0x171070 skip (eax/edi call 0x170E40).
- 0x136B90 PASS (m1_92). 0x119690: hard (orig tests rig flag 0x8000 as test ah,ah/js on the loaded dword; cl emits an imm test whatever the form).
- 0x137090, 0x184160 PASS (m1_93; signed rig byte works when it is a byte load).
- 0x18B750 PASS (m1_93). 0x13F3E0: hard (cl tail-merges two of the five state calls).
- 0x136CD0 PASS (m1_94). 0x17B7A0: hard (x*2.0 becomes x+x in cl). 0x10A140 skip (esi/eax args).
- 0x17F2A0, 0x18C450 PASS (m1_95).
- 0x10ACA0 PASS (m1_95). 0x127C80 skip (register-arg calls 0x120820/0x11F2B0).
- 0x18AC10, 0x104B70 PASS (m1_96).
- 0x1806E0 skip (calls 0x17F990 with esi arg).
- 0x127FA0, 0x171580 skip (register-arg calls).
- 0x17BA50 PASS (m1_97). 0x185540: hard (8 unrolled record checks; cl re-rolls).
- 0x107220 skip (esi register arg).
- 0x104FC0: hard (block order and the char rand compare; three tries).
- 0x1371F0, 0x109B10 PASS (m1_97).
- 0x18E270 skip (eax/esi args).
- 0x11DA40 PASS (m1_97).
- 0x18F950 skip (edi register arg).
- 0x167E20 PASS (m1_98).
- 0x18BBB0 skip (esi register arg).
- 0x141AD0: hard (cl merges the duplicated state calls).
- 0x183C40 skip (esi register arg).
- 0x16B950 PASS (m1_98).
- 0x13CE50 skip (eax/edx call 0x139B10). 0x16A5C0 skip for now (x87 fild random turn).
- 0x180E00 skip (edi register arg). 0x11C030 skip (fragment using caller registers).
- 0x1419E0 skip (eax/edx call 0x140040).
- 0x182400 PASS (m1_99; cl unrolls this 4-record clear like the original).
- 0x17CCD0 PASS (m1_99; x*-2.0 stays a multiply). 0x1789E0 skip as hard (frameRate*2.0 becomes x+x).
- 0x1099D0 PASS (m1_99).
- 0x117AE0 skip (eax-arg call 0x114D10).
- 0x118640 skip (eax-arg call 0x114D10).
- 0x1327A0 skip (calls 0x131310 which reads ebx/edi).
- 0x14FE90 PASS (m1_100; if-chain keeps the cmp 2). 0x18B530 PASS (signed pointer compare loop with goto found).
- 0x1868A0, 0x146AA0 PASS (m1_100).
- 0x1451E0: hard (cl merges the two 0x113090 calls and splits the state call).
- 0x165560 PASS (m1_101).
- 0x17AE00 skip (esi register arg).
- 0x186D20 PASS (m1_101).
- 0x1677F0 PASS (m1_101).
- 0x181770 PASS (m1_101).
- 0x1255C0 skip (eax/esi call 0x11F640).
- 0x157E80 PASS (m1_102).
- 0x157480 PASS (m1_102).
- 0x132130 skip (eax-arg calls 0x12DC90/0x131310).
- 0x17FD80 PASS (m1_102).
- 0x154150 PASS (m1_102). 0x114930 not tried yet (long target pick).
- 0x13F040 PASS (m1_102).
- 0x16D940: hard (flag 0x8000 tested as test ah,ah/js on the dword, like 0x119690).
- 0x177400 PASS (m1_103).
- 0x15A550, 0x1480E0 skip (esi-arg call 0x15A270 family).
- 0x10B150, 0x157370 PASS (m1_103).
- 0x14A9F0, 0x158660 PASS (m1_103).
- 0x1141F0 PASS (m1_104).
- 0x101380 PASS (m1_104; field stores placed after the clear loop so cl keeps them).
- 0x170C70 skip (eax-arg call 0x16FCB0).
- 0x186500 PASS (m1_104).
- 0x157260 PASS (m1_104). 0x13F880, 0x141FD0 not tried (shared-block layouts).
- 0x157590 PASS (m1_105).
- 0x182C00: hard (merged duplicate state calls and the indexed .rdata time table folds to a constant in the checker).
- 0x182D20 skip as hard (same indexed time table as 0x182C00). 0x188120 skip (calls 0x186470 with register args).
- 0x179FE0 not tried yet (long matrix build).
- 0x140C20: hard (setge/dec/and random state pick, cl uses cmov). 0x173BC0 skip (eax/ecx call 0x173030).
- 0x112490 PASS (m1_105).
- 0x179EC0: hard (cl turns the 0x213/0x214 sound pick into arithmetic; orig branches).
- m1_106 PASS: 0x154250, 0x172A30, 0x139890, 0x1821B0, 0x141E80, 0x18C1B0, 0x157BC0, 0x1866A0. Skip (register args): 0x132300, 0x18F7B0, 0x10D3E0 (esi), 0x12AC20 (ebx). 0x180BC0 hard (_ftol).
- m1_107 PASS: 0x18F530, 0x166E20, 0x1050B0, 0x18B130, 0x140D30, 0x149890, 0x149C40. Skip (register args): 0x155D10 (edi), 0x16C560 (ebx), 0x10F130 (esi/edi). Hard (x87 compare): 0x18FF50, 0x105480; 0x103B20, 0x170AF0 also have fcom.
- 0x13CB80: hard (two neg/sbb/and state picks; cl turns whichever comes last into cmov).
- m1_108 PASS: 0x14BD00, 0x18E100, 0x17BD70, 0x100AD0, 0x17F860, 0x157130, 0x149510, 0x1327A0. Skip: 0x18A300 (calls 0x18A280 with eax/ecx/xmm0). Sway-tail family todo list: grep fam 0f2e051cfb25009ff6c444.
- 0x14E0A0, 0x14CDE0: hard (x*2.0 doubled sway rate, cl emits addss).
- 0x14F710, 0x1584E0: hard (int+1 via fild/_ftol). 0x14C6C0: hard (x*2.0).
- 0x148DD0, 0x148950, 0x14D2E0: hard (x*2.0).
- 0x157A30: hard (x*2.0).
- m1_109 PASS: 0x12F710, 0x186F00, 0x1184C0, 0x17D970, 0x152740. Trick: a constant compared at run time in the original (u = 1.0; if (u != -1)) needs volatile float.
- Skip (register args): 0x16A170 (0x169D30 edi), 0x12CC20 (0x11F640 eax/esi).
- 0x17FFB0: hard (cl folds idx 0..5 range check). 0x108BB0, 0x12AD40 skip (register args).
- 0x18C950: hard (cl cross-jumps the two 0x189DA0(o,h,2) calls into one).
- 0x1450A0: hard (cl tail-duplicates the 0x113040 call into 3 copies; tried defaulted state, nesting). 0x124280 skip (0x11F640 eax/esi).
- 0x13E250 skip (0x13D4B0 eax/ebx). 0x18C070 skip (0x18BB20 eax).
- m1_110 PASS: 0x14A220, 0x1876D0, 0x159500, 0x1538B0, 0x154080, 0x14E800, 0x1521E0, 0x158140. Launch family (sound 0x130) todo: 0x1599D0, 0x14EDB0, 0x151310, 0x158DA0, 0x1582A0, 0x159320 and larger.
- m1_111 PASS: 0x1599D0, 0x14EDB0, 0x151310, 0x158DA0, 0x1582A0, 0x159320.
- 0x11C4F0 skip (0x11B0D0/0x11B020/0x11B140 register args).
- 0x141570: hard (cl tail-duplicates the 0x113040 call, as 0x1450A0).
- 0x118F20 skip (0x1154D0 eax).
- 0x12B860 skip (0x120820 eax/esi, 0x11F2B0 ebx).
- m1_112 PASS: 0x177B80, 0x17A180, 0x110600, 0x1758B0, 0x177840.
- 0x12A0F0 skip (0x11F640 eax/esi). 0x100DB0 skip (0x18F650 takes eax). 0x116F70: likely hard (x87 multiply of the 0x1AD9D0 float return).
- 0x119B20 skip (0x114E90/0x115440 eax). 0x126D90 skip (0x11F640 eax/esi).
- 0x181EF0: hard (cl merges the two 0x1EEC0 tilt calls into one select and folds the +0x30 pointer stores).
- m1_113 PASS: 0x17FBE0, 0x1878E0.
- 0x169BA0 skip (ecx input). 0x110730 skip (0x10A140 register return).
- 0x111EB0 skip (esi/ebx inputs).
- m1_114 PASS: 0x145E10, 0x12F170, 0x17AA60, 0x16FF30, 0x115A30, 0x157CE0.
- 0x135550: hard (flag 0x8000 tested as test ah,ah/js, as 0x119690).
- 0x136140 skip (0x135730 eax/ebx). 0x133FC0 skip (0x12E630 eax). 0x120C80 skip (0x11F520 register).
- 0x12EA90 skip (0x12E390 eax/edi/ebx). 0x176A10 skip (0x176970/0x18C6B0 register calls).
- 0x1367D0 skip (0x135C60 eax/edi/ebx).
- 0x16EA50: hard (cl rewrites the event 0x20..0x24 counter loop to compare 0x25, and moves the 0x1D removal block). 0x181A40: skipped (default case reads an uninitialized value; x87 fst chain).
- 0x100700: hard (x87 sin/cos sums). 0x184F90: hard (count-down node loop; empty case reads stale loop slot).
- 0x107330: hard (x87 angle math). 0x12CD60 skip (0x11F640 eax/esi).
- 0x136270 skip (0x135AC0 eax, 0x135C60). 0x10D110 skip (esi input).
- 0x1100A0 skip (0x10A140 eax, xmm0 return).
- 0x1561F0: hard (x87 fucompi on 0x145DA0 results).
- m1_115 PASS: 0x1465C0, 0x179590, 0x168950, 0x1754E0, 0x156500.
- 0x131E40: hard (state 1..4 range check folded by cl).
- 0x136950: hard (as 0x131E40, state 1..4 range check).
- 0x137690 skip (0x135E10/0x1374E0 register calls). 0x1724E0: hard (dead lea of table 0x279B60 that cl drops).
- 0x17D3F0: hard (idx 0..5 range check folded).
- 0x1023A0 skip (xmm1/ecx inputs).
- 0x129DB0 skip (0x11F640 eax/esi). 0x134FA0 skip (0x12DEC0/0x12E590 register calls).
- m1_116 PASS: 0x1799E0, 0x1065C0, 0x114AE0, 0x1765C0, 0x1833F0.
- Trick (0x1799E0): volatile int16 fields stop cl merging adjacent halfword stores.
- 0x18BE50: hard (slot search unrolled by 5 in the original; cl re-rolls).
- 0x1892E0 skip (tail call 0x188C80 with eax).
- m1_117 PASS: 0x176150, 0x1741A0, 0x12DA60.
- 0x171820: hard (mode 0..2 check folded by cl).
- m1_118 PASS: 0x11E260, 0x137C70.
- 0x171270: hard (ranges 0..4 and 10..14 folded). 0x163C50: likely hard (duplicated inlined recover blocks cl tail-merges).
- 0x108CF0 skip (esi input).
- 0x163C50: hard (cl merges the 0x18/0x1B recover blocks that differ only in the state).
- 0x152340: hard (as 0x163C50, recover blocks 0xC/0xE differ only in state; cl merges).
- 0x16C0D0: hard (state 2..3 range folded).
- m1_119 PASS: 0x14CF50. m1_120 PASS: 0xF1E80, 0x5ED30.
- 0xD2CC0: hard (cl hoists the duplicate 0x171CD0 call out of the two branches). 0x409E0: hard (1..0x18 range check).
- 0xA9440 skip (0xA8510 ecx/edx). 0x497E0 skip (0x48B70 edi/ebx). 0x38AD0 skip (ecx/esi inputs).
- 0xDD990: hard (cl emits _ftol for the float-to-int casts; orig cvttss2si).
- 0xC1A90 skip (eax input). 0x7D7B0 skip (eax/ecx/edx inputs).
- m1_121 PASS: 0xD2C40, 0x7EF30, 0xE9100, 0xEC5A0, 0xCA580, 0xCF330, 0xE1FD0. Trick: inline memset via __stosd/__stosb with the size through a volatile copy. 0xFC970: hard (cl merges the two 0x832D0 clip calls). 0xF6F60: odd default reads arg1 as a count; skipped.
- 0xF3260: hard (idx 0..15 range). 0x40950: hard (1..0x18 range).
- 0xEE1B0: hard (cl cannot fold the first table kind 2 from rdata). 0xDE400: skipped (not-found path reads an uninitialised local).
- m1_122 PASS: 0xEE6D0, 0x1C7B0, 0xFC380. 0xC93D0: hard (cl biases the record loop pointer differently, +0 or +4 vs +8). 0xABB60: likely hard (_ftol). 0x38A10 skip (64-bit shifts).
- 0xC9790: hard (record loop pointer biased +8). 0x13850 skip (vec4 struct passed by value to a debug printer).
- 0x23330 skip (eax input). 0xE4050: skipped (count-down loop over entity rows).
- 0xC0BF0 skip (edi input). 0xC87B0: hard (record loop pointer biased +8).
- m1_123 PASS: 0xA92A0, 0xF4470, 0xFB310, 0x3C740, 0xF92C0, 0xA33E0.
- 0xE9830: hard (float-to-int index cvttss2si; cl uses _ftol). 0xC62A0: skipped (indexes a local table by a global).
- 0x13C00, 0x138F0, 0x13990: skip (push-buffer builders passing a vec4 struct by value).
- m1_124 PASS: 0x98090, 0xAAB60.
- 0x34390: likely hard (float-to-int, _ftol). 0x53E20 skip (inline strcmp/strcpy). 0x5E9B0, 0x3F5A0: skipped (byte-script loops).
- m1_124 add 0xA9090. m1_125 PASS: 0x36C90, 0xAA000, 0xBCBE0.
- 0x5ABD0: hard (kind 12..13 range folded).
- 0x3D6F0 skip (eax/ecx/edx inputs).
- m1_126 PASS: 0xC73B0, 0xC48A0, 0xCA600.
- 0xC9310: hard (record loop pointer biased +8). 0x6E960: skipped.
- 0xC4AB0: hard (cl merges the two 0x1ADBA0 calls into one with a selected source).
- m1_127 PASS: 0x71FE0, 0xF4940, 0xE85D0, 0xCF200.
- 0x89B50 skip (0x89460 register). 0xA9B80: skipped (local id tables indexed by +4).
- m1_128 PASS: 0x91550, 0x91490, 0x7FC60, 0xE8920.
- m1_129 PASS: 0x48620. 0xE4950: hard (orig addresses the slot part as (i*3+0x129)*8; cl folds to +0x948).
- 0xC7CC0: hard (record loop pointer biased +8).
- 0x49180 skip (0x48B70 eax/edi/ebx). 0x7D6E0 skip (eax/edx/ecx inputs).
- m1_130 PASS: 0xB6F60, 0xDE330.
- 0x81100, 0x811D0 skip (edx/edi/esi inputs). 0x68D50 skip (0x65E50 takes esi).
- m1_131 PASS: 0x58B40.
- 0xE4690: likely hard (slot address formed as (i*5+0x10E)*8). 0xA23E0, 0xC7460: skipped (count-down loops).
- m1_131 add 0x261A0.
- 0x260C0: likely hard (n clamp 1..4 folds). 0x5AA20: hard (12..13 range). 0xA24C0: hard (0x1B..0x1C range).
- m1_132 PASS: 0x3FAF0.
- 0x810F0 skip (edx input). 0x36180: skipped.
- m1_132 add 0x195F0, 0xE1270. Trick: for a pair loop biased +4, walk a pointer to the second field and index [-1].
- 0xAF920, 0xA57C0, 0x79370: skipped for now (long chains / range lists).
- m1_133 PASS: 0x25FD0.
- 0xC7A10 skip (edi/esi inputs). 0x3C2D0: hard (orig keeps a branch whose two sides make the same call; cl removes it).
- m1_133 add 0xA8A90, 0xEDCB0.
- 0x79CB0 skip (esi input). 0xC2420 skip (edi input). 0xC61B0: skipped (large frame, two-call select).
- 0xA95E0: skipped (equality chains 0xF4/0xF6/0xF8 likely turned into a bit test). 0x4EB50: skipped (push-buffer + neg/sbb select).
- m1_134 PASS: 0x82750, 0xF4730, 0xF4CA0.
- m1_135 PASS: 0x262A0, 0x263B0.
