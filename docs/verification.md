# Verification

Byte matching is blocked (no legitimate original compiler, see `toolchain.md`). Until that changes, a function is promoted to **Structurally compared** only by `tools/xcompare.py`, and to **Semantic-tested** only by a behaviour test in the recomp test bench (`swap_plan.md`).

## The structural checker (`tools/xcompare.py`)
Our C is compiled by VS 2022 `cl` 19.44 for x86 (`/O2 /Oy /GS- /Gy /Zl /arch:SSE`, see `tools/cl.bat`). The checker disassembles the original function from the XBE and our function from the COFF object, resolves our relocations through `config/symbols.csv`, and requires these to be equal:

| Category | What is compared |
|---|---|
| calls | Ordered call targets, including tail calls (`jmp` to another function). Imports resolve to their kernel thunk slot. |
| data | Set of absolute addresses touched (globals, `.rdata`). Float constants in `.rdata` compare by value (ours are cl's `__real@` literals). Indexed access into a record array listed in `symbols.csv` (`elem`, `count`) compares as array + field offset. The function's own jump tables are skipped on both sides. |
| imm | Set of constants: immediates and structure offsets in one class (compilers pick `lea r,[r+k]` or `add r,k` freely). 0, 1 and -1 are ignored. Stack-pointer arithmetic is ignored; EBP offsets are ignored only in functions that set up an EBP frame (otherwise EBP is an ordinary register under /Oy and its offsets are fields). |
| jcc | Set of decision kinds. A condition and its negation are one kind (block layout can invert them). `cmov`, `setcc`, `neg;sbb` and `cmp;sbb` count as decisions. `js/jns` right after `test r,r` count as `l/ge`. |
| ret | `ret N` values (calling convention: callee-pops vs caller-pops). |
| jtables | Number of jump-table dispatches. |

Also normalised (each found by recovery work and re-qualified with the negative controls; reviewed function-size corrections live in `config/size_overrides.csv` with a reason each; the original range also stops at the function's own jump table when it sits inside the recorded size; absolute addresses outside the image (hardware registers) count as constants): high-byte register tests (`test ah,8` = bit 0x800); `js/jns` after `test r,r` or `cmp x,0` = `l/ge`; `call [obj+off]` records the slot offset; calls through a function-pointer table compare the table address; jumps through a table outside the function are indirect tail calls, not switches; conditional tail calls (`jcc` to another function) count as calls; a tail call and call+ret to the same target are equal (targets and order still compared); 0.0 float constants are ignored (built with xorps); 0xFF and 0xFFFF masks are ignored like 0/1 (`and 0xFF` equals a zero-extending load); `__fastcall` names undecorate; cl's `__ftol2_sse` float-to-int helper is the same CRT routine as the original's `_ftol2` (0x001C7D38) and is aliased to it in config/symbols.csv.

Register choice, instruction selection, ordering of independent instructions and counts of repeated accesses are deliberately not compared.

## Negative controls (`tests/negative_controls.py`, log `logs/negative_controls.log`)
Each control plants one bug in a copy of real recovered source and must FAIL: wrong constant, reversed condition, wrong call target, wrong tail-call target, wrong global, wrong float constant, wrong field, wrong struct offset, wrong array field, extra call (calling convention/stack), missing function. Result on 2026-11-09: 13/13 behaved as expected.

## Known blind spots (also tested, expected to PASS)
- A pure negation (`<` vs `>=`) is invisible, because layout may invert a branch.
- Swapping two fields that are both used elsewhere in the same function is invisible (sets, not positions).
- Byte vs dword access width is not distinguished.
- The number and order of arguments passed to a call are not compared (call targets are; stack slots are not), so swapped or missing arguments can pass. Recovery helpers must read each callee's entry code; behaviour tests must cover argument order.
- A fixed slot of a known record array read directly on one side and through an index register on the other side compares as different data (array mapping applies only to indexed accesses). Such functions are left out, not waived.
These are why Structurally compared is below Semantic-tested: behaviour tests catch them.

## Waivers
A function may list exact `category:item` differences in the `waivers` column of `config/function_states.csv`, with the reason in `notes`. Only those items may differ; the run prints `PASS*` and the waiver count. Waivers are for compiler idioms that the 2005 compiler and cl 19.44 express differently (division by a power of two, bounds checks, 1/-1 selection), never for logic.

## Commands
```
tools\check_all.bat                  compile src/game/*.c and check every recorded function (log: logs/check_all.log)
py -3 tools\xcompare.py <obj> <name> <va> -d     one function, side-by-side disassembly
py -3 tests\negative_controls.py     re-qualify the checker after any change to it
```

## Register-argument functions (policy from 2026-11-09)
Much of the game was compiled with whole-program optimisation, which passes some arguments in registers (EAX, EDX, ESI, EDI, EBX...) instead of on the stack. Plain C cannot express that, and it does not need to: the recovered source is portable C in which callers and callees agree on normal C parameters. Such functions may be recovered when:
- every register input is mapped to a named C parameter, and the record's `notes` column states the mapping exactly, e.g. `regargs: p1=EAX p2=ESI` (inputs read before being written) and, for callers of such functions, which C argument goes in which register;
- the checker passes as usual (it compares calls, data, constants and decisions; it does not compare which register or stack slot an argument arrives in, which is why the mapping must be written down);
- the state stays "Structurally compared". The register mapping is only proven by a behaviour test in the recomp test bench (the swap adapter reads g_eax/g_edx/... per the note).
