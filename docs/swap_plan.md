# Testing recovered functions inside the working recomp

Plan only. `C:\ProjectOogie` is not edited by this project; each swap is proposed to the owner and done on a branch there with their OK.

## How the recomp lets us replace a function (Verified by reading the code, 2026-11-09)
- `port/src/recomp_manual.c` has `recomp_lookup_manual(uint32_t xbox_va)`: it returns a replacement for a guest address; used by indirect calls (RECOMP_ICALL) and calls through the dispatch table.
- It also supports entry hooks (`sub_X_enter`) and full overrides (`sub_X`), per that project's CLAUDE.md.
- Replacement functions run in the recomp's register model: arguments at `MEM32(g_esp + 4)`, `g_esp + 8`..., return value in `g_eax`; stdcall functions also pop their arguments (`g_esp += 4 + 4*n` including the return address, as `oogie_ke_stall` does). Guest memory is reached through `g_xbox_mem_offset`.
- **Hypothesis to check first:** whether direct calls inside generated C go through the dispatch table or call `sub_X` directly. If direct, the swap must be a full override of `sub_X` (generator excludes it), not only a lookup entry.

## Adapter shape
Recovered source stays clean (no `g_esp`). A thin, separate adapter file per swapped function translates:
```c
/* adapter, lives in the recomp branch, not in src/game */
static void swap_000414A0(void) {            /* cdecl, 1 arg */
    int amount = (int)MEM32(g_esp + 4);
    Grade_AddExclamations(amount);           /* recovered C */
}
```
Recovered globals become accessors onto guest memory (`g_chapterExclamations` -> `*(int32_t*)(0x0041318C + offset)`), generated from a single address table so the same source builds natively later with real globals. Calls from recovered code to unrecovered functions go back through the recomp (`recomp_call(0x00025FD0, 1, 0x78)`), never through our own guesses.

## Test protocol per function
1. Pick a function on a path the owner's walkthrough exercises (Easy difficulty).
2. Baseline run with the generated C, swap run with recovered C, same input route; compare logged values (memscan snapshots of the globals it writes, screenshots).
3. Add an A/B switch (environment variable) so the owner can turn the swap off.
4. Record result in `docs/functions/*.md` and promote to "Semantic-tested" only on a pass.

First candidates: 0x000414A0 (exclamation points, observable in the pause menu), 0x00057E90 (job running, Now Loading screen), 0x001A7BA0 (frame present, every frame).
