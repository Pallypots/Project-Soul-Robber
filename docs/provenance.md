# Provenance

Independent reverse engineering of the owner's own disc. No leaked source, symbols or SDK files are used. Not a formal clean-room process.

## Reused from C:\ProjectOogie (read only, nothing copied into git unless stated)
| Item | How used | Copied here? |
|---|---|---|
| `game/default.xbe` (SHA-1 667c5bd8...) | Read in place by `tools/xbe_inventory.py`. Owner extracted it from their disc with `tools/xiso_tool.py`. | No |
| `tools/xiso_tool.py` (Project Oogie, MIT) | Not needed yet (XBE already extracted). Use it in place for any further disc reads. | No |
| `docs/REVERSE_ENGINEERING.md` | Starting map of known functions/globals (job record 0x3E3F64, grading block 0x413180, render lock 0x40B0E0, Swap 0x1D6D20, XAPI routines). Each fact used is re-checked against the XBE bytes. | No (referenced) |
| `build_out/disasm/functions.json` (XboxRecomp v0.14.0 disassembler, 10,500 candidates) | Candidate function boundaries for the inventory. Bytes and evidence are re-read from the XBE by our tool. | No (generated, ignored) |
| `build_out/func_id/crt_functions.json` | 10 CRT signature hits, shown as evidence only. | No |
| `build_out/func_id/identified_functions.json` | Not used: its 17,497 entries include vtable-scan aliases, and its "game_*" categories are keyword guesses. | No |

## Tools
| Tool | Version | Source |
|---|---|---|
| Python | 3.12.10 | python.org install |
| capstone | 5.0.7 | pip |
| MSVC (modern, structural only) | VS 2022 Build Tools, cl 19.44 (MSVC 14.44.35207), x86 | Microsoft, owner's install |
| CMake | installed, `C:\Program Files\CMake` | |

## Third-party references
- XboxDev wiki XBE layout (field offsets, XOR keys), cross-checked: the decoded entry 0x001BEF07 and thunk 0x0025F8E0 equal the values the recomp's parser logged.
- The KND charter (`C:\Users\jimmy\Downloads\CLAUDE.md`), owner's document, adapted into `CLAUDE.md`.
- matching-decomp skill: principles only; its MIPS checker is not used.
