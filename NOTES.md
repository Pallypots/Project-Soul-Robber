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
