# State (updated 2026-11-09, session 1)

## Milestones
| Milestone | Status |
|---|---|
| M0 Identity | **Passed** for the XBE: SHA-1/SHA-256 checked, header and 31 sections mapped (`logs/header.log`, `config/inventory/sections.csv`). Disc image hash comes from the recomp's records (Redump SHA-1 b39ba1e3...), not re-checked here. |
| M1 Trustworthy tools | **Partial**: inventory tool with 9 synthetic tests incl. 6 negative controls (`logs/tests.log`, all pass). x86 structural checker not written yet. Byte matching blocked (no legitimate original compiler). |
| M2+ | Not started |

## What exists
- `tools/xbe_inventory.py`: read-only XBE header/section/function inventory, bounds-checked, retail/debug XOR detection, kernel thunk table length, raw vs zero-filled ranges.
- `config/inventory/functions.csv`: 10,500 candidates; **7,735 game** (1.66 MB), **2,762 library** (0.48 MB), 3 unknown. Method: `docs/inventory.md`.
- 3 recovered functions, state "Structurally compared" (not matched, not behaviour-tested): `docs/functions/first.md`.
- Toolchain findings and matching blocker: `docs/toolchain.md`. Recomp swap plan: `docs/swap_plan.md`.

## Progress (game code only)
| State | Functions | Unique bytes |
|---|---|---|
| Structurally compared | 3 | 162 |
| Semantic-tested or better | 0 | 0 |
| Unanalyzed | 7,732 | ~1.66 MB |

## Open hypotheses
- Game/library cut in `.text` at 0x001BC6D0 (within a few hundred bytes).
- Original compiler is VC 7.1 (XDK 5849 era).
- Whether recomp direct calls go through `recomp_lookup_manual`.

## Next concrete task
Write `tools/xcompare.py` (x86 structural checker, COFF obj vs XBE range, symbol-to-address table) with negative controls, and run it on the three functions.

## Repo
`C:\ProjectOogieDecomp`, public at https://github.com/Pallypots/Project-Soul-Robber (repo made by the owner 2026-11-09). Update the README chart with `py -3 tools/progress.py` after changing `config/function_states.csv`.
