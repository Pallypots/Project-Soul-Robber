# State (updated 2026-11-09, session 2)

## Milestones
| Milestone | Status |
|---|---|
| M0 Identity | **Passed** for the XBE (SHA-1/SHA-256, header, 31 sections: `logs/header.log`, `config/inventory/sections.csv`). |
| M1 Trustworthy tools | **Passed for structural checking**: `tools/xcompare.py` with 13 negative controls (`logs/negative_controls.log`, 13/13). Byte matching still **blocked** (no legitimate original compiler). |
| M2 Reference reconstruction | Blocked with byte matching. |
| M3 Verified subsystem | **Partial**: chapter grading, player stats/souls, chapter clock recovered and structurally compared; no behaviour tests yet. |

## Recovered so far
43 game functions, all **Structurally compared** (`logs/check_all.log`, 43/43; 6 with documented compiler-idiom waivers). None Semantic-tested yet. List: `docs/functions.md`.

| Area | Source | Functions |
|---|---|---|
| Chapter grading and unlocks | `src/game/grade.c` | 5 |
| Player stats, souls, damage | `src/game/stats.c` | 14 |
| Player object | `src/game/player_obj.c` | 12 |
| Chapter and play clocks, session, video rate | `src/game/clock.c`, `video.c` | 10 |
| Loader job, frame present | `src/game/system.c` | 2 |

## Findings this session (Verified by disassembly unless marked)
- The game uses whole-program-optimised calling conventions in places: 0x00040C10 takes its argument in EAX (no stack argument). Expect more custom conventions; the recomp adapter must handle them per function.
- 0x00040C10 hangs on purpose for an out-of-range chapter (`cmp/jl` back to itself): an assert-style trap (purpose Hypothesis).
- The chapter clock is 300 ticks per second; with video rate mode 0 (0x003E2544) times are scaled by 1.001001 / 0.999, which fits 59.94 Hz NTSC timing (Hypothesis). Relevant to the high-frame-rate work.
- 0x00420C20 (stats + 0xD60) is a flags word, not a stat slot; bit 1 runs a 720-unit timer at stats + 0xD94.
- Jack's hit routine 0x000CF950 confirmed: damage tally, cheat bit 0 keeps 1 health, death call 0x000CEF00.
- The 2005 compiler never emits `cmov`; modern cl does. Logged as a checker normalisation.
- **Risk (Verified in several callers, e.g. 0x00040E90 uses EDX, 0x000CF000 passes ESI/EDI/EAX):** register-argument conventions from whole-program optimisation are common. Plain C cannot express them, and the checker does not see argument registers, so these functions stay "Structurally compared" until behaviour tests. The recomp swap adapters must read those registers (g_eax, g_edx...) per function.

## Next concrete tasks
1. Keep recovering by call graph outward from grading/stats (callers of 0x000CF950, 0x000D1F40, 0x00041480), and the `.stm` archive loader.
2. First recomp swap test (0x000414A0, exclamation points), per `docs/swap_plan.md`, in a branch of `C:\ProjectOogie` with the owner's OK.

## Repo
https://github.com/Pallypots/Project-Soul-Robber. Update the README chart with `py -3 tools/progress.py` after changing `config/function_states.csv`.

## Original source layout (Verified, `docs/source_files.md`, 2026-11-09)
The XBE still contains 19 of the developers' own source paths (debug allocator and assert arguments), e.g. `\Project\nightmareXbox\app\char_unit.c`, `effman.c`, `figure.c`, `pkdatload.c`, `resman.c`, `scene.c`, `seseq.c`, `tex_ex.c`, `world.c`, `y_camera.c`, `y_character.c`, `demo\demo*.c`, `jack\jkmngsub.c`. Functions that pass a path are known to come from that file; neighbours by address probably do too (Hypothesis). Use these names for `src/` organisation once areas are merged: e.g. 0x000D00B0 is in `jack\jkmngsub.c`, so the player stats/object code near 0x000CF000-0x000D2000 is probably that file; 0x00053760/0x000539C0 are `resman.c` (the slot heaps).
- Hypothesis (from script opcodes in 0x000DB2B0-0x000DBE90): the script handlers pass `&g_stats` (0x0041FEC0) to the PlayerObj_* helpers, so the "player stats" block and the PlayerObj type are probably one object (Jack's character data at 0x0041FEC0). To merge the two struct types once confirmed.
- Known declaration problems in `include/oogie.h` (to fix in a consolidation pass): `sub_000F5D40` is a two-argument vector copy (dst, src), declared with one; `sub_00036750` is called with two arguments by 0x000F4280; areas use aliases at the same addresses meanwhile. 0x000F3D10 is the generic actor state change (ctx, actor, newState) with exit/enter handler tables at +0x7C/+0x74.
