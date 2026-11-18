#!/usr/bin/env python3
"""List undecompiled game functions, smallest first, with what (if anything) blocks each one.
Usage: py -3 tools/next_candidates.py [--max-size N] [--limit N] [--all-flags]
By default it shows only functions with no hard blocker. Flags:
  REG:eax,..  register inputs (in scope: name them as C params, write `regargs:` in notes)
  THIS        ECX input + callee-pops (thiscall): write as __fastcall(this, int unusedEdx, ...)
  GS          security cookie: put it in a *_gs*.c file
  CALLREG     calls a callee that reads registers; its header prototype must say which (e.g. /* b=EDI */)
  NOPROTO     calls something with no name in config/symbols*.csv yet
Hard blockers (hidden unless --all-flags): EH (C++ exception frame), XMMARG (float passed in XMM),
X87T (inline fsin/fcos/fpatan/fsqrt), NOTED (already logged as hard in NOTES.md)."""
import argparse, csv, glob, os, re, sys
sys.path.insert(0, os.path.dirname(__file__))
from xbe_inventory import Xbe
import capstone

ROOT = os.path.normpath(os.path.join(os.path.dirname(__file__), ".."))
CFG = os.path.join(ROOT, "config")
XBE = os.environ.get("OOGIE_XBE", "C:/ProjectOogie/game/default.xbe")
REGS = ["eax", "ecx", "edx", "ebx", "esi", "edi", "ebp"]
SETTERS = ("mov", "lea", "movzx", "movsx", "pop")
X87T = ("fsin", "fcos", "fsincos", "fpatan", "fptan", "fsqrt", "f2xm1", "fyl2x", "fscale")


def done_set():
    s = set()
    for f in glob.glob(os.path.join(CFG, "function_states*.csv")) + [os.path.join(CFG, "not_functions.csv")]:
        for r in csv.DictReader(open(f, encoding="utf-8", errors="replace")):
            try: s.add(int(r["va"], 16))
            except Exception: pass
    return s


def hard_set():
    s = set()
    for line in open(os.path.join(ROOT, "NOTES.md"), encoding="utf-8", errors="replace"):
        if "hard" in line.lower():
            for m in re.findall(r"0x([0-9A-Fa-f]{4,8})", line):
                s.add(int(m, 16))
    return s


def named_set():
    s = set()
    for f in glob.glob(os.path.join(CFG, "symbols*.csv")):
        for r in csv.reader(open(f, encoding="utf-8", errors="replace")):
            if len(r) >= 2:
                try: s.add(int(r[1], 16))
                except Exception: pass
    return s


def reg_inputs(ins):
    """Registers read before written, from the entry up to the first call/ret/jmp."""
    written, used = set(), set()
    for i in ins[:24]:
        m = i.mnemonic
        if m == "push" and i.op_str in REGS:   # saved for later, not an input
            written.add(i.op_str); continue
        d, _, s = i.op_str.partition(",")
        d, s = d.strip(), s.strip()
        selfzero = m in ("xor", "sub") and d == s
        for rg in REGS:
            if rg in written: continue
            if re.search(r"\b%s\b" % rg, s) or ("[" in d and re.search(r"\b%s\b" % rg, d)) \
               or (m not in SETTERS and not selfzero and re.search(r"\b%s\b" % rg, d)):
                used.add(rg)
        if d in REGS and (m in SETTERS or selfzero): written.add(d)
        if m == "call": written |= {"eax", "ecx", "edx"}
        if m in ("call", "ret", "jmp"): break
    return used


def xmm_arg(ins):
    w = set()
    for i in ins[:40]:
        d, _, s = i.op_str.partition(",")
        d, s = d.strip(), s.strip()
        if i.mnemonic in ("xorps", "pxor") and d == s:
            w.add(d); continue
        for r in re.findall(r"xmm\d", s):
            if r not in w: return True
        dm = re.findall(r"xmm\d", d)
        if dm:
            if i.mnemonic.startswith(("comis", "ucomis")) or i.mnemonic in ("addss", "subss", "mulss", "divss", "maxss", "minss", "andps", "orps"):
                if dm[0] not in w: return True
            w.add(dm[0])
        if i.mnemonic in ("call", "ret", "jmp"): break
    return False


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--max-size", type=int, default=400)
    ap.add_argument("--limit", type=int, default=40)
    ap.add_argument("--all-flags", action="store_true")
    a = ap.parse_args()
    x = Xbe(XBE)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    done, hard, named = done_set(), hard_set(), named_set()
    regcache = {}

    def callee_regs(t):
        if t not in regcache:
            try: regcache[t] = reg_inputs(list(md.disasm(x.read_va(t, 96), t)))
            except Exception: regcache[t] = set()
        return regcache[t]

    rows = []
    for r in csv.DictReader(open(os.path.join(CFG, "inventory", "functions.csv"), encoding="utf-8")):
        if r["owner"] != "game": continue
        va, sz = int(r["va"], 16), int(r["size"])
        if va in done or va % 16 or sz > a.max_size: continue
        ins = list(md.disasm(x.read_va(va, sz), va))
        text = " ; ".join(i.mnemonic + " " + i.op_str for i in ins)
        flags, hardf = [], []
        regs = reg_inputs(ins)
        retn = any(i.mnemonic == "ret" and i.op_str for i in ins)
        if "fs:[0]" in text: hardf.append("EH")
        if xmm_arg(ins): hardf.append("XMMARG")
        if any(i.mnemonic in X87T for i in ins): hardf.append("X87T")
        if va in hard: hardf.append("NOTED")
        if regs == {"ecx"} and retn: flags.append("THIS")
        elif regs: flags.append("REG:" + ",".join(sorted(regs)))
        if "0x379d8c" in text: flags.append("GS")
        targets = [int(i.op_str, 16) for i in ins if i.mnemonic in ("call", "jmp") and i.op_str.startswith("0x")]
        targets = [t for t in targets if not (va <= t < va + sz)]
        if any(callee_regs(t) - {"ecx"} for t in targets): flags.append("CALLREG")
        if any(t not in named for t in targets): flags.append("NOPROTO")
        if hardf and not a.all_flags: continue
        rows.append((sz, va, len(ins), flags + hardf))
    rows.sort()
    for sz, va, n, f in rows[:a.limit]:
        print("0x%06X size %4d insns %3d  %s" % (va, sz, n, " ".join(f)))
    print("shown %d of %d" % (min(a.limit, len(rows)), len(rows)))


if __name__ == "__main__":
    main()
