# First recovered functions

Build `OOGIE-XBOX-US-RETAIL`. Source `src/game/recovered_first.c`. Names inferred. Compiler for comparison: VS 2022 cl 19.44 x86 `/O2 /Oy /GS-` (not the original). Command: `build\cc.bat`; output `logs/modern_cl_structural.log`. Original bytes read with capstone through `tools/xbe_inventory.py` (`Xbe.read_va`).

| VA | Size | Name (inferred) | Owner | State | Notes |
|---|---|---|---|---|---|
| 0x00057E90 | 6 | Job_IsRunning | game, medium | Structurally compared | Original `mov eax,[0x3E3F7C]; ret`; ours `mov eax,[g_job+0x18]; ret` (0x3E3F64 + 0x18 = 0x3E3F7C). Identical shape. |
| 0x000414A0 | 68 | Grade_AddExclamations | game, medium | Structurally compared | Same order: add to [0x41318C], cdecl call 0x00025FD0(1, 0x78), clamp 0..999 with the same early `ret`. Differences: original loads the global into edx and stores it (`mov edx,[g]; add edx,eax; ... mov [g],edx`) and the store is scheduled after the pushes; ours uses `add [g],eax`; original `jge`, ours `jns` (equivalent after `test`). Purpose of 0x00025FD0 not analysed. |
| 0x001A7BA0 | 88 | Frame_Present | game, low (direct kernel refs) | Structurally compared | Same calls in the same order: 0x001A7940, RtlEnterCriticalSection([0x40B0E0]) via thunk slot 0 (ordinal 277), D3D Swap 0x001D6D20(0), RtlLeaveCriticalSection via slot 1 (ordinal 294), then the SwitchToThread / WaitForSingleObjectEx([0x40B0E4], 0, TRUE) loop, exiting unless the result is 0x102 or 0xC0. Callee-pops (stdcall) for Swap/SwitchToThread/WaitForSingleObjectEx/Rtl* Verified (no `add esp` after them); first attempt as cdecl produced `add esp` and was corrected. Differences: original `mov eax,[g]; push eax`, ours `push [g]`; padding `mov edi,edi` vs `nop`. |

None is byte-matched (blocked) or semantic-tested yet. Next: run the x86 structural checker once written, then swap 0x000414A0 into the recomp test bench (`docs/swap_plan.md`).
