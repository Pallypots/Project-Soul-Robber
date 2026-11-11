# Project Oogie Decomp: CLAUDE.md

True source decompilation of **The Nightmare Before Christmas: Oogie's Revenge** (original Xbox, TOSE/Capcom 2005, title ID `42560004`). Sister project of the playable static recompilation at `C:\ProjectOogie` (public as Pallypots/ProjectOogie). Adapted on 2026-11-09 from the owner's KND charter (`C:\Users\jimmy\Downloads\CLAUDE.md`); that file's general rules apply here wherever this one is silent.

At session start read this file, `docs/STATE.md`, `docs/PLAN.md`, the latest log in `logs/`, and `git status`. At session end update `docs/STATE.md` with what changed, commands and results, open hypotheses and the next task.

The owner is not a programmer. Explain results in plain English, no em dashes, lead the engineering, and ask only before irreversible or outward-facing actions.

## 1. Mission and scope
- Recover readable, maintainable C (C++ where the binary shows C++) for the game's own code, function by function, with original logic, types, data layouts and control flow. Original names, comments and formatting cannot be recovered; every name we give is marked inferred.
- **Not a recompilation.** XboxRecomp output, instruction-to-C translation, register simulators, guest-CPU interpreters, XBE loaders or emulator wrappers never count as recovered source. The recomp at `C:\ProjectOogie` is the playable version and our **test bench**, not our implementation.
- Reference input: the US retail Xbox `default.xbe` only (internal ID `OOGIE-XBOX-US-RETAIL`, below). Do not switch to the PS2 release or mix addresses between builds without the owner's decision.
- Two build purposes: **matching** (original-era compiler, byte comparison, currently BLOCKED, see `docs/toolchain.md`) and **native/portable** (modern compilers, behaviour tests). A native build is not expected to match Xbox bytes.

## 2. Reference build
| Field | Value |
|---|---|
| ID | `OOGIE-XBOX-US-RETAIL` |
| File | `C:\ProjectOogie\game\default.xbe` (read only, never copied into this repo) |
| Size / SHA-1 | 3,751,936 bytes / `667c5bd8abc4a551ef6b7cbab3bf3a45e7244605` |
| SHA-256 | `9a8319c7b1cb5ee29781bf641a0cf549c221fdc57effb8f72085608019f41548` |
| Kind | retail XOR keys; entry 0x001BEF07; kernel thunks 0x0025F8E0 (125) |
| XDK | 1.0.5849 (library table); debug path `...\xnightmare\Release_US\xnightmare.exe` |

Verify the SHA-1 before any analysis run (`tools/xbe_inventory.py header`).

## 3. Hard rules
- Never modify the XBE, the disc image, or anything in `C:\ProjectOogie` (files, branches, commits). Read only. Before launching the recomp for a test, check the owner is not already running the game.
- Never commit game files, XBE copies, disassembly, analysis databases, Ghidra projects or private traces (`.gitignore`). Function lists of addresses and sizes are fine.
- Never invent addresses, counts, compiler versions or results. Every claim in `docs/` is **Verified** (with the command or log) or **Hypothesis**.
- No leaked SDK, leaked symbols or leaked source, ever. Public availability is not provenance. Microsoft XDK files are not legitimately obtainable; do not fetch them.
- Decompiler output (Ghidra, the recomp's generated C) is a draft, never proof.
- No GitHub repo, commit to other repos, or push without the owner's OK. Local commits here only when asked.
- GPL/LGPL code (xemu, Cxbx-Reloaded, the rival GPL port) is behaviour reference only, never pasted.
- The matching-decomp skill is MIPS/ELF based. Do not use its checker, splat layout or MIPS recipes for x86 XBE work; build or qualify an x86 checker first (see `docs/verification.md`).

## 4. Function states (use exactly these)
| State | Meaning |
|---|---|
| Unanalyzed | No validated recovery |
| Analyzed | Boundaries and behaviour investigated |
| Draft source | Recovered C written, not validated |
| Structurally compared | Modern compiler output reviewed instruction by instruction against the original; documented differences only. Not a match. |
| Semantic-tested | Swapped into the recomp test bench (or host unit test) and passed stated behaviour tests |
| Relocation-aware match | Bytes match under documented relocation rules (needs original compiler: blocked) |
| Exact linked match | Rebuilt bytes match at original addresses (blocked) |
| Native-integrated | Runs in a native build without the recomp |

Each function record (`docs/functions/*.md`) carries: build ID, address, size, owner, source path, confidence, compiler and flags, verification command, result, evidence.

Progress counts game, library and unknown functions separately, functions and unique bytes separately, from `config/inventory/functions.csv`. Library code (XDK, Bink) is out of the decomp denominator; the port replaces it with PC services.

## 5. Layout
```
tools/        xbe_inventory.py (read-only XBE inventory)
config/inventory/  sections.csv, functions.csv (addresses, sizes, owner, confidence)
include/ src/game/ recovered source (names inferred)
tests/        synthetic parser tests, later host behaviour tests
docs/         STATE, PLAN, provenance, toolchain, inventory, verification, swap_plan, functions/
logs/         command output backing Verified claims
build/        local compiler output (ignored)
```

## 6. Commands
```
py -3 tools\xbe_inventory.py header    C:\ProjectOogie\game\default.xbe
py -3 tools\xbe_inventory.py sections  C:\ProjectOogie\game\default.xbe config\inventory\sections.csv
py -3 tools\xbe_inventory.py functions C:\ProjectOogie\game\default.xbe C:\ProjectOogie\build_out\disasm\functions.json config\inventory\functions.csv docs\inventory_summary.md
py -3 -m unittest discover -s tests -v
py -3 tools\build_all.py --check      (rebuild every recorded source into its object dir, then check every function)
py -3 tools\xcompare.py --all          (check every recorded function against existing objects)
py -3 tools\xcompare.py <obj> <name> <va> -d   (one function, side-by-side disassembly)
py -3 tests\negative_controls.py       (re-qualify the checker after changing it; must be 13/13)
py -3 tools\progress.py                (regenerate the README chart, docs/progress.md, docs/functions.md)
cmd /c tools\clto.bat <objdir> <files> (compile up to 4 sources into an object dir)
py -3 tools\xdis.py 0xVA               (original disassembly; honours config\size_overrides.csv)
py -3 tools\source_names.py            (original source-file names left in the XBE)
```
