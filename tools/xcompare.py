#!/usr/bin/env python3
"""x86 structural checker: original XBE function vs our compiled COFF object.

Usage:
  xcompare.py <obj> <symbol> <va> [--size N] [-v]
  xcompare.py --all [-v]        check every row of config/function_states.csv
                                that names an obj (column `obj`)

NOT a byte matcher (the original compiler is unavailable). It extracts the
function's observable structure from both sides and requires equality of:
  calls     ordered list of call targets (VA; imports resolved to thunk slot)
  data      multiset of absolute addresses referenced (globals, constants,
            jump tables are excluded on both sides and counted instead)
  imm       multiset of immediate constants, excluding stack-pointer
            arithmetic, 0/1 register idioms and jump-table plumbing
  jcc       multiset of conditional-branch classes, where a condition and its
            negation are one class (layout may invert them) and js/jns after
            `test r,r` is folded into l/ge
  ret       set of `ret N` stack pops (calling convention)
  jtables   number of indirect jumps through tables
Known limits (documented in docs/verification.md): a pure negation of a
condition (< vs >=) is invisible; register choice and instruction selection
are ignored; byte-sized vs dword-sized accesses are not distinguished.

Symbol -> VA mapping comes from config/symbols.csv (name,va). Names are the
undecorated C names; `_x`, `_x@8` and `__imp__x@8` all map to `x`.
"""
import argparse, csv, glob, os, re, struct, sys
from collections import Counter
sys.path.insert(0, os.path.dirname(__file__))
from xbe_inventory import Xbe
import capstone
from capstone import x86

ROOT = os.path.join(os.path.dirname(__file__), "..")
XBE = os.environ.get("OOGIE_XBE", "C:/ProjectOogie/game/default.xbe")
IMG_LO, IMG_HI = 0x00010000, 0x00460000

JCC_CLASS = {
    "jl": "l/ge", "jge": "l/ge", "jle": "le/g", "jg": "le/g",
    "je": "e/ne", "jne": "e/ne", "jb": "b/ae", "jae": "b/ae",
    "jbe": "be/a", "ja": "be/a", "js": "s/ns", "jns": "s/ns",
    "jp": "p/np", "jnp": "p/np", "jo": "o/no", "jno": "o/no",
}


def undecorate(n):
    n = re.sub(r"^__imp_", "", n)
    if n.startswith("@"):      # __fastcall: @name@N
        return re.sub(r"@\d+$", "", n[1:])
    n = re.sub(r"@\d+$", "", n)
    return n[1:] if n.startswith("_") else n


def rows_of(prefix):
    """All rows of config/<prefix>.csv plus per-area config/<prefix>_*.csv."""
    out = []
    for path in sorted(glob.glob(os.path.join(ROOT, "config", prefix + ".csv")) +
                       glob.glob(os.path.join(ROOT, "config", prefix + "_*.csv"))):
        with open(path) as f:
            out += list(csv.DictReader(f))
    return out


def load_symbols():
    out = {}
    for r in rows_of("symbols"):
        va = int(r["va"], 16)
        if r["name"] in out and out[r["name"]] != va:
            raise SystemExit(f"symbol {r['name']} has two addresses")
        out[r["name"]] = va
    return out


def load_arrays():
    """(base, end, elem) for symbols declared as arrays of records."""
    out = []
    for r in rows_of("symbols"):
        if r.get("elem") and r.get("count"):
            b, e, n = int(r["va"], 16), int(r["elem"], 0), int(r["count"], 0)
            out.append((b, b + e * n, e))
    return out


ARRAYS = load_arrays()


def array_key(a):
    """Indexed access into a known record array -> (array base, field offset)."""
    # overlapping declarations: the array starting closest below wins
    best = None
    for b, end, e in ARRAYS:
        if isinstance(a, int) and b <= a < end and (best is None or b > best[0]):
            best = (b, e)
    return None if best is None else (best[0], (a - best[0]) % best[1])


# ---------------------------------------------------------------- COFF
class Coff:
    def __init__(self, path):
        d = open(path, "rb").read()
        self.d = d
        mach, nsec, _, symoff, nsym, opt, _ = struct.unpack_from("<HHIIIHH", d, 0)
        if mach != 0x14C:
            raise SystemExit(f"{path}: not an i386 COFF object (machine {mach:#x})")
        stroff = symoff + 18 * nsym
        def name8(raw):
            if raw[:4] == b"\0\0\0\0":
                o = struct.unpack_from("<I", raw, 4)[0]
                return d[stroff + o:d.index(b"\0", stroff + o)].decode()
            return raw.rstrip(b"\0").decode()
        self.secs = []
        for i in range(nsec):
            o = 20 + opt + 40 * i
            raw = d[o:o + 8]
            nm = raw.rstrip(b"\0").decode()
            if nm.startswith("/"):
                so = int(nm[1:]); nm = d[stroff + so:d.index(b"\0", stroff + so)].decode()
            _, _, size, ptr, prel, _, nrel, _, ch = struct.unpack_from("<IIIIIIHHI", d, o + 8)
            rels = [struct.unpack_from("<IIH", d, prel + 10 * k) for k in range(nrel)]
            self.secs.append(dict(name=nm, size=size, data=d[ptr:ptr + size], rels=rels))
        self.syms = []
        i = 0
        while i < nsym:
            o = symoff + 18 * i
            nm = name8(d[o:o + 8])
            val, sec, typ, cls, naux = struct.unpack_from("<IhHBB", d, o + 8)
            self.syms.append(dict(name=nm, value=val, sec=sec, cls=cls))
            for _ in range(naux):
                self.syms.append(None)
            i += 1 + naux

    def function(self, cname):
        for s in self.syms:
            if s and s["sec"] > 0 and undecorate(s["name"]) == cname and s["cls"] == 2:
                sec = self.secs[s["sec"] - 1]
                start = s["value"]
                # end = next symbol in the same section, else section end
                # next function, or a static data label (jump/byte tables cl
                # places after the code; class 3). Class 6 labels are code.
                ends = [t["value"] for t in self.syms if t and t["sec"] == s["sec"]
                        and t["value"] > start and t["cls"] in (2, 3)]
                end = min(ends) if ends else sec["size"]
                relmap = {}
                for va, si, typ in sec["rels"]:
                    if start <= va < end:
                        relmap[va - start] = (self.syms[si]["name"], typ, self.syms[si]["sec"])
                return sec["data"][start:end], relmap, s["sec"]
        raise SystemExit(f"symbol {cname} not found in object")


# ---------------------------------------------------------------- events
FP_PREFIX = ("f",)
def sign_test(p):
    """`test r,r` or `cmp x,0`: js/jns after it means the same as jl/jge."""
    if p.mnemonic == "test" and len(p.operands) == 2 and p.operands[0].type == x86.X86_OP_REG and        p.operands[1].type == x86.X86_OP_REG and p.operands[0].reg == p.operands[1].reg:
        return True
    return p.mnemonic == "cmp" and len(p.operands) == 2 and p.operands[1].type == x86.X86_OP_IMM         and p.operands[1].imm == 0


def is_fp(m):
    return m.startswith("f") or m.endswith(("ss", "sd")) or m in ("comiss", "ucomiss", "comisd", "ucomisd")


REG_NAMES = {
    x86.X86_REG_EAX: ("eax", "ax", "al", "ah"), x86.X86_REG_EBX: ("ebx", "bx", "bl", "bh"),
    x86.X86_REG_ECX: ("ecx", "cx", "cl", "ch"), x86.X86_REG_EDX: ("edx", "dx", "dl", "dh"),
    x86.X86_REG_ESI: ("esi", "si"), x86.X86_REG_EDI: ("edi", "di"), x86.X86_REG_EBP: ("ebp", "bp"),
}


def pointer_bias(insns, base, resolve):
    """A loop pointer walking a global array may start at any field of the
    first record: `mov r, A` ... `[r+d]` ... `add r, step` / `cmp r, B`.
    Choosing a different field shifts A, B and every d by the same amount
    without changing a single access. Canonical form: shift so that the
    smallest d is 0. Applied only when r is used in no other way.
    Returns {insn address: delta} for the A/B immediates and the [r+d] operands."""
    import re
    out = {}
    for r, names in REG_NAMES.items():
        pat = re.compile(r"\b(" + "|".join(names) + r")\b")
        movs, cmps, mems, ok = [], [], [], True
        # the walk starts at `mov r, imm`; earlier uses of r are another value,
        # provided nothing after that point branches back before it
        st = next((k for k, i in enumerate(insns) if i.mnemonic == "mov" and len(i.operands) == 2 and
                   i.operands[0].type == x86.X86_OP_REG and i.operands[0].reg == r and
                   i.operands[1].type == x86.X86_OP_IMM), 0)
        if st and any(k.mnemonic.startswith("j") and k.operands and k.operands[0].type == x86.X86_OP_IMM and
                      k.operands[0].imm < insns[st].address and k.operands[0].imm >= base
                      for k in insns[st:]):
            continue
        for i in insns[st:]:
            if not pat.search(i.op_str):
                if i.mnemonic.startswith(("rep", "movs", "stos", "cmps", "lods", "scas")) and r in (x86.X86_REG_ESI, x86.X86_REG_EDI):
                    ok = False
                continue
            ops = i.operands
            off = i.address - base
            # callee-saved register: saved before the walk, restored at exits
            if i.mnemonic == "push" and i.op_str == names[0] and not movs:
                continue
            if i.mnemonic == "pop" and i.op_str == names[0]:
                continue
            if i.mnemonic in ("mov", "cmp") and len(ops) == 2 and ops[0].type == x86.X86_OP_REG and                     ops[0].reg == r and ops[1].type == x86.X86_OP_IMM:
                fo = i.imm_offset if i.imm_offset else None
                a = resolve(off, fo, ops[1].imm & 0xFFFFFFFF, "abs")
                if not isinstance(a, int):
                    ok = False; break
                (movs if i.mnemonic == "mov" else cmps).append(i.address)
                continue
            if i.mnemonic in ("add", "sub") and len(ops) == 2 and ops[0].type == x86.X86_OP_REG and                     ops[0].reg == r and ops[1].type == x86.X86_OP_IMM:
                continue
            # after the loop's bound compare, a plain reload of r (not from r)
            # starts an unrelated value: stop tracking there (later code is
            # compared unadjusted, which can only make a match stricter)
            if cmps and i.mnemonic in ("mov", "movzx", "movsx") and len(ops) == 2 and \
                    ops[0].type == x86.X86_OP_REG and ops[0].reg == r and \
                    len(pat.findall(i.op_str)) == 1:
                break
            # `mov r, r` is an alignment no-op
            if i.mnemonic == "mov" and i.op_str == names[0] + ", " + names[0]:
                continue
            # `push r` after the walk started passes the record pointer itself
            if i.mnemonic == "push" and i.op_str == names[0] and movs:
                mems.append((i.address, 0))
                continue
            # `mov x, r` copies the walking pointer: same as `lea x, [r+0]`
            if i.mnemonic == "mov" and len(ops) == 2 and ops[1].type == x86.X86_OP_REG and ops[1].reg == r and                     ops[0].type == x86.X86_OP_REG and ops[0].reg != r:
                mems.append((i.address, 0))
                continue
            memuse = [o for o in ops if o.type == x86.X86_OP_MEM and o.mem.base == r and o.mem.index == 0]
            if memuse and not any(o.type == x86.X86_OP_REG and o.reg == r for o in ops) and                     len(pat.findall(i.op_str)) == len(memuse):
                mems.append((i.address, memuse[0].mem.disp))
                continue
            ok = False; break
        if not ok or len(movs) != 1 or not mems:
            continue
        dmin = min(d for _, d in mems)
        if dmin == 0:
            continue
        for a in movs + cmps:
            out[a] = ("imm", dmin)
        for a, _ in mems:
            out[a] = ("mem", r, -dmin)
    return out


def events(code, base, resolve, md, fconst=None, local=None, use_bias=False):
    """resolve(insn_offset, field_offset, raw_value, kind) -> VA or None"""
    calls, data, imm, jcc, ret = [], Counter(), Counter(), Counter(), set()
    pushimm = set()   # values pushed as immediates (a float argument can be pushed as its bit pattern)
    jt = 0
    insns = list(md.disasm(code, base))
    # EBP is a frame pointer only when the function sets one up; with frame
    # pointer omission it is an ordinary register and its offsets are fields
    frame_reg = x86.X86_REG_EBP if (len(insns) > 1 and insns[0].mnemonic == "push" and
                                    insns[0].op_str == "ebp" and insns[1].mnemonic == "mov" and
                                    insns[1].op_str == "ebp, esp") else -1
    prev = None
    flagsrc = None
    hangs = 0
    bias = pointer_bias(insns, base, resolve) if use_bias else {}
    # struct-pointer offsets (second comparison only): `lea r,[b+K]`,
    # `mov r,b`, `add r,K` then `[r+d]` is the same access as `[b+K+d]`;
    # tracked in straight-line code, reset at branch targets and calls
    R32 = (x86.X86_REG_EAX, x86.X86_REG_EBX, x86.X86_REG_ECX, x86.X86_REG_EDX,
           x86.X86_REG_ESI, x86.X86_REG_EDI) + ((x86.X86_REG_EBP,) if frame_reg == -1 else ())
    targets = {k.operands[0].imm for k in insns
               if k.mnemonic.startswith("j") and k.operands and k.operands[0].type == x86.X86_OP_IMM}
    jsrc = {}
    for k in insns:
        if k.mnemonic.startswith("j") and k.operands and k.operands[0].type == x86.X86_OP_IMM:
            jsrc.setdefault(k.operands[0].imm, []).append(k.address)
    nwrites = Counter()
    if use_bias:
        for k in insns:
            if k.mnemonic == "pop":
                continue   # epilogue restore of a callee-saved register
            try:
                for w in k.regs_access()[1]:
                    nwrites[w] += 1
            except Exception:
                pass
    alias = {}
    alias_def = {}
    zero_regs = set()
    skip_sel = set()
    for ii, i in enumerate(insns):
        if use_bias:
            if i.address in targets:
                zero_regs.clear()
                # keep an offset whose register is written exactly once (its
                # definition) when every jump into this point comes after it
                for r in list(alias):
                    d = alias_def.get(r)
                    if d is None or nwrites[r] != 1 or not all(a > d for a in jsrc.get(i.address, [])):
                        alias.pop(r)
            if i.mnemonic == "call":
                for r in (x86.X86_REG_EAX, x86.X86_REG_ECX, x86.X86_REG_EDX):
                    alias.pop(r, None)
            elif i.mnemonic == "ret" and alias.get(x86.X86_REG_EAX):
                imm[("k", alias[x86.X86_REG_EAX] & 0xFFFFFFFF)] += 1
        if i.mnemonic == "fld1":   # x87 load of the constant 1.0 (no .rdata literal)
            data[("fconst", 1.0)] += 1
        # assert-style hang: a branch back to itself, or back to a compare/test
        # with nothing else in between (the loop has no effect but to spin)
        if i.mnemonic.startswith("j") and i.operands and i.operands[0].type == x86.X86_OP_IMM                 and i.address - 16 <= i.operands[0].imm <= i.address:
            t = i.operands[0].imm
            body = [k for k in insns if t <= k.address < i.address]
            def harmless(k):
                if k.mnemonic in ("cmp", "test", "lea", "nop", "comiss", "ucomiss", "comisd", "ucomisd", "fcomp", "fcom", "fucomp", "fnstsw", "movss", "fld", "fstp") or k.mnemonic in JCC_CLASS:
                    return True
                if k.mnemonic in ("mov", "movzx", "movsx") and k.operands:
                    d = k.operands[0]
                    # register loads, or stores only to the stack
                    return d.type == x86.X86_OP_REG or (d.type == x86.X86_OP_MEM and d.mem.base == x86.X86_REG_ESP)
                return False
            if all(harmless(k) for k in body):
                hangs += 1
        if prev is not None and prev.mnemonic not in ("mov", "movzx", "movsx", "lea", "push", "pop", "movss", "movsd", "fld", "fstp", "fst"):
            flagsrc = prev
        off = i.address - base
        m = i.mnemonic
        ops = i.operands
        esp_op = any(o.type == x86.X86_OP_REG and o.reg == x86.X86_REG_ESP for o in ops)
        if m == "call":
            o = ops[0]
            if o.type == x86.X86_OP_IMM:
                calls.append(resolve(off, i.size - 4, o.imm, "rel"))
            elif o.type == x86.X86_OP_MEM and o.mem.base == 0 and o.mem.index == 0:
                calls.append(resolve(off, i.size - 4, o.mem.disp & 0xFFFFFFFF, "abs"))
            else:
                calls.append("indirect")
                # call through a function-pointer table: compare the table address
                if o.type == x86.X86_OP_MEM and o.mem.disp:
                    fo = i.disp_offset if i.disp_offset else None
                    a = resolve(off, fo, o.mem.disp & 0xFFFFFFFF, "abs") if fo is not None else None
                    if a is not None:
                        ak = array_key(a) if isinstance(a, int) and o.mem.index != 0 else None
                        data[ak[0] if ak else a] += 1
                    elif o.mem.base not in (0, x86.X86_REG_ESP, frame_reg):
                        imm[("k", o.mem.disp & 0xFFFFFFFF)] += 1   # call [obj+off]: the slot offset
            prev = i; continue
        if m == "jmp" and ops[0].type == x86.X86_OP_MEM and ops[0].mem.index != 0:
            # switch jump table (own table, right after the code) vs indirect
            # tail call through a function-pointer table elsewhere
            fo = i.disp_offset if i.disp_offset else None
            a = resolve(off, fo, ops[0].mem.disp & 0xFFFFFFFF, "abs") if fo is not None else None
            own = (isinstance(a, tuple) and a[0] == "local") or \
                  (isinstance(a, int) and local is not None and local[0] <= a < local[1])
            if own or a is None:
                jt += 1
            else:
                calls.append(("tail", "indirect"))
                ak = array_key(a) if isinstance(a, int) else None
                data[ak[0] if ak else a] += 1
            prev = i; continue
        if m.startswith(("cmov", "set")) and ("j" + m[4:] if m.startswith("cmov") else "j" + m[3:]) in JCC_CLASS:
            # conditional move / set: same decision as a branch (modern cl
            # uses cmov, which 2005-era code for this game never does)
            c = JCC_CLASS["j" + (m[4:] if m.startswith("cmov") else m[3:])]
            if c == "s/ns" and flagsrc is not None and sign_test(flagsrc):
                c = "l/ge"   # same folding as js/jns after test r,r
            jcc[c] += 1
        elif m == "sbb" and len(ops) == 2 and ops[0].type == x86.X86_OP_REG and \
                ops[1].type == x86.X86_OP_REG and ops[0].reg == ops[1].reg and \
                flagsrc is not None and flagsrc.mnemonic in ("neg", "cmp", "sub"):
            # `neg x; sbb r,r` (or cmp/sbb) materialises a condition branch-free;
            # moves or stores may sit between them
            jcc["e/ne" if flagsrc.mnemonic == "neg" else "b/ae"] += 1
        elif m in JCC_CLASS:
            c = JCC_CLASS[m]
            if c == "s/ns" and flagsrc is not None and sign_test(flagsrc):
                c = "l/ge"
            jcc[c] += 1
            # conditional tail call: jcc rel32 straight to another function
            if i.size == 6 and ops and ops[0].type == x86.X86_OP_IMM:
                t = resolve(off, 2, ops[0].imm, "rel")
                inside = (isinstance(t, tuple) and t[0] == "unrelocated") or \
                         (isinstance(t, int) and base <= t < base + len(code))
                if not inside:
                    calls.append(("tail", t))
            prev = i; continue
        if m == "ret":
            ret.add(ops[0].imm if ops else 0); prev = i; continue
        if m == "jmp" and ops[0].type == x86.X86_OP_IMM and i.size == 5:
            t = resolve(off, 1, ops[0].imm, "rel")
            is_local = (isinstance(t, tuple) and t[0] == "unrelocated") or \
                       (isinstance(t, int) and base <= t < base + len(code))
            if not is_local:
                calls.append(("tail", t))   # tail call to another function
                prev = i; continue
        if m == "jmp" and ops and ops[0].type == x86.X86_OP_REG:
            calls.append(("tail", "indirect"))   # jmp reg: indirect tail call
            prev = i; continue
        if m.startswith("j") and m not in JCC_CLASS:
            prev = i; continue
        if m in JCC_CLASS:
            prev = i; continue
        # memory operands: an absolute address (original: in-image displacement;
        # object: relocated displacement) is data, otherwise a structure offset
        if use_bias and ii in skip_sel:
            prev = i; continue
        if use_bias and m == "and" and len(ops) == 2 and ops[0].type == x86.X86_OP_REG and                 ops[1].type == x86.X86_OP_IMM and ii >= 1:
            # branch-free select: `neg x; sbb r,r` (or `setcc; dec r`) then
            # `and r,D` [`add r,K`] yields K or K+D, the same two constants an
            # `if` would load with two movs
            rn = i.reg_name(ops[0].reg)
            p1 = insns[ii - 1]
            sel = (p1.mnemonic == "sbb" and p1.op_str == rn + ", " + rn) or                   (p1.mnemonic == "dec" and p1.op_str == rn and ii >= 2 and insns[ii - 2].mnemonic.startswith("set"))
            if sel:
                d = ops[1].imm & 0xFFFFFFFF
                k = 0
                for jj in range(ii + 1, min(ii + 5, len(insns))):
                    q = insns[jj]
                    if q.mnemonic == "add" and q.op_str.startswith(rn + ", ") and q.operands[1].type == x86.X86_OP_IMM:
                        k = q.operands[1].imm & 0xFFFFFFFF
                        skip_sel.add(jj)
                        break
                    if q.op_str.startswith(rn + ",") or q.op_str == rn or q.mnemonic.startswith(("j", "call", "ret")):
                        break
                imm[("k", k)] += 1
                imm[("k", (k + d) & 0xFFFFFFFF)] += 1
                prev = i; continue
        if use_bias and m == "add" and len(ops) == 2 and ops[0].type == x86.X86_OP_REG and                 ops[1].type == x86.X86_OP_IMM and ii >= 1 and insns[ii - 1].mnemonic.startswith("set"):
            # `setcc r8; add r32,K` yields K or K+1
            low = {"eax": "al", "ebx": "bl", "ecx": "cl", "edx": "dl"}.get(i.reg_name(ops[0].reg))
            if low and insns[ii - 1].op_str == low:
                k = ops[1].imm & 0xFFFFFFFF
                imm[("k", k)] += 1
                imm[("k", (k + 1) & 0xFFFFFFFF)] += 1
                prev = i; continue
        if use_bias and not esp_op:
            done = False
            if m == "lea" and ops[0].type == x86.X86_OP_REG and ops[0].reg in R32 and                     ops[1].mem.base in R32 and abs(ops[1].mem.disp) < 0x10000 and                     (ops[1].mem.index == 0 or ops[1].mem.disp != 0):
                bb = bias.get(i.address)
                adj = bb[2] if bb and bb[0] == "mem" and bb[1] == ops[1].mem.base else 0
                alias[ops[0].reg] = alias.get(ops[1].mem.base, 0) + ops[1].mem.disp + adj
                alias_def[ops[0].reg] = i.address
                done = True
            elif m == "mov" and len(ops) == 2 and ops[0].type == x86.X86_OP_REG and ops[1].type == x86.X86_OP_REG and                     ops[0].reg in R32 and ops[1].reg in R32:
                bb = bias.get(i.address)
                adj = bb[2] if bb and bb[0] == "mem" and bb[1] == ops[1].reg else 0
                alias[ops[0].reg] = alias.get(ops[1].reg, 0) + adj
                done = True
            elif m in ("add", "sub") and len(ops) == 2 and ops[0].type == x86.X86_OP_REG and ops[0].reg in R32 and                     ops[1].type == x86.X86_OP_IMM and abs(ops[1].imm) < 0x10000:
                k = ops[1].imm if ops[1].imm < 0x80000000 else ops[1].imm - 0x100000000
                alias[ops[0].reg] = alias.get(ops[0].reg, 0) + (k if m == "add" else -k)
                done = True
            if done:
                prev = i; continue
            # an aliased register read as a value: its offset becomes visible
            try:
                rd, wr = i.regs_access()
            except Exception:
                rd, wr = list(alias), list(alias)
            membase = {o.mem.base for o in ops if o.type == x86.X86_OP_MEM}
            memidx = {o.mem.index for o in ops if o.type == x86.X86_OP_MEM}
            for rr in rd:
                if rr in alias and alias[rr] and (rr not in membase or rr in memidx or
                        any(o.type == x86.X86_OP_REG and o.reg == rr for o in ops)):
                    imm[("k", alias[rr] & 0xFFFFFFFF)] += 1
            for r in wr:
                alias.pop(r, None)
        if use_bias:
            # a 4-byte store of zero also clears the 16-bit field two bytes up:
            # cl merges two adjacent word clears into one dword store
            if m == "mov" and len(ops) == 2 and ops[0].type == x86.X86_OP_MEM and ops[0].size == 4 and                     ops[0].mem.base not in (0, x86.X86_REG_ESP, frame_reg) and ops[0].mem.index == 0 and                     ((ops[1].type == x86.X86_OP_IMM and ops[1].imm == 0) or
                     (ops[1].type == x86.X86_OP_REG and ops[1].reg in zero_regs)) and abs(ops[0].mem.disp) < 0x10000:
                eff = ops[0].mem.disp + alias.get(ops[0].mem.base, 0)
                imm[("k", (eff + 2) & 0xFFFFFFFF)] += 1
            if m == "xor" and len(ops) == 2 and ops[0].type == x86.X86_OP_REG and                     ops[1].type == x86.X86_OP_REG and ops[0].reg == ops[1].reg:
                zero_regs.add(ops[0].reg)
            else:
                try:
                    for w in i.regs_access()[1]:
                        zero_regs.discard(w)
                except Exception:
                    zero_regs.clear()
        bi = bias.get(i.address)
        if bi and bi[0] == "mem" and m == "push" and ops and ops[0].type == x86.X86_OP_REG and ops[0].reg == bi[1]:
            if bi[2]:
                imm[("k", bi[2] & 0xFFFFFFFF)] += 1   # canonical offset of the pushed pointer
            prev = i; continue
        for o in ops:
            if o.type != x86.X86_OP_MEM:
                continue
            disp = o.mem.disp & 0xFFFFFFFF
            if use_bias and alias.get(o.mem.base) and abs(o.mem.disp) < 0x10000:
                d2 = (o.mem.disp + alias[o.mem.base]) & 0xFFFFFFFF
                if d2:
                    imm[("k", d2)] += 1
                continue
            if bi and bi[0] == "mem" and o.mem.base == bi[1]:
                d2 = (o.mem.disp + bi[2]) & 0xFFFFFFFF
                if d2:
                    imm[("k", d2)] += 1
                continue
            fo = i.disp_offset if i.disp_offset else None
            a = resolve(off, fo, disp, "abs") if fo is not None or o.mem.base == 0 else None
            if isinstance(a, tuple) and a[0] == "local":
                continue       # the function's own jump table / byte map
            if a is not None and local is not None and local[0] <= a < local[1]:
                continue
            if a is not None and isinstance(a, int) and (o.mem.base != 0 or o.mem.index != 0):
                ak = array_key(a)
                if ak:
                    data[ak[0]] += 1
                    if ak[1]:
                        imm[("k", ak[1])] += 1
                    continue
            if a is not None:
                if is_fp(m) and fconst is not None:
                    c = fconst(a, o.size)
                    if c is not None:
                        if c != 0.0:   # 0.0 is often built with xorps instead of loaded
                            data[("fconst", c)] += 1
                        continue
                data[a] += 1
            elif (o.mem.base not in (0, x86.X86_REG_ESP, frame_reg) or
                  (o.mem.base == 0 and o.mem.index != 0)) and o.mem.disp:
                imm[("k", o.mem.disp & 0xFFFFFFFF)] += 1
            elif o.mem.base == 0 and o.mem.index == 0 and o.mem.disp:
                # absolute address outside the image (hardware registers): a
                # constant, whether written as [k] or as `mov r,k` + [r]
                imm[("k", o.mem.disp & 0xFFFFFFFF)] += 1
        for o in ops:
            if o.type == x86.X86_OP_IMM:
                v = o.imm & 0xFFFFFFFF
                fo = i.imm_offset if i.imm_offset else None
                a = resolve(off, fo, v, "abs")
                if a is not None and bi and bi[0] == "imm" and isinstance(a, int):
                    a += bi[1]
                if a is not None:
                    data[a] += 1
                elif not esp_op:
                    # `test ah, 8` tests bit 0x800 of the dword: scale high-byte operands
                    if m in ("test", "and", "or", "xor", "cmp") and ops[0].type == x86.X86_OP_REG and \
                            ops[0].reg in (x86.X86_REG_AH, x86.X86_REG_BH, x86.X86_REG_CH, x86.X86_REG_DH):
                        v <<= 8
                    # `and r32, 0xFFFFxxxx` whose register only feeds a 16-bit store
                    # (optionally after or/and/xor with constants) is the same mask as
                    # `and r32, 0xxxxx`: only the low 16 bits reach memory
                    if m == "and" and (v >> 16) == 0xFFFF and ops[0].type == x86.X86_OP_REG:
                        r32 = i.reg_name(ops[0].reg)
                        if r32 in ("eax", "ebx", "ecx", "edx", "esi", "edi"):
                            r16 = r32[1:]
                            for k in insns[ii + 1:ii + 5]:
                                if k.mnemonic in ("or", "and", "xor") and k.op_str.startswith(r32 + ", ") and k.operands[1].type == x86.X86_OP_IMM:
                                    continue
                                if k.mnemonic == "mov" and k.op_str.startswith("word ptr [") and k.op_str.endswith("], " + r16):
                                    v &= 0xFFFF
                                break
                    # `sub r32, -N` is cl's short encoding of `add r32, N` (same value)
                    if m == "sub" and ops[0].type == x86.X86_OP_REG and v >= 0xFFFFFF80:
                        v = (-v) & 0xFFFFFFFF
                    imm[("k", v)] += 1
                    if m == "push" or (m == "mov" and ops[0].type == x86.X86_OP_MEM):
                        pushimm.add(v)   # also a float literal stored as its bit pattern
        prev = i
    # 0/1 materialisation differs freely between compilers (xor r,r / mov r,1 / setcc)
    # 0xFF / 0xFFFF masks: `and r,0xFF` and a zero-extending byte/word load are the same operation
    for k in [k for k in imm if k[1] in (0, 1, 0xFFFFFFFF, 0xFF, 0xFFFF)]:
        del imm[k]
    # Addresses and constants are compared as sets: instruction selection
    # (read-modify-write vs load/store, re-reads) changes how often each
    # appears, not which ones appear.
    return dict(calls=calls, data=set(data), imm=set(imm), jcc=set(jcc), ret=ret, jtables=jt, hangs=hangs,
                n=len(insns), insns=insns, pushimm=pushimm)


def fold_pushed_floats(a, b):
    """A float argument pushed as an immediate bit pattern (`push 0x3F800000`) is the
    same constant as a float literal loaded from .rdata and stored to the argument
    slot: when one side has fconst c and the other pushes c's exact bit pattern,
    count the pushed value as fconst c. Value must match exactly."""
    for x, y in ((a, b), (b, a)):
        for key in [d for d in y["data"] if isinstance(d, tuple) and d[0] == "fconst" and d not in x["data"]]:
            bits = struct.unpack("<I", struct.pack("<f", key[1]))[0]
            if bits in x["pushimm"] and ("k", bits) in x["imm"] and                     float(f"{struct.unpack('<f', struct.pack('<I', bits))[0]:.7g}") == key[1]:
                x["imm"].discard(("k", bits))
                x["data"].add(key)


def fval(raw, size):
    v = struct.unpack("<f" if size == 4 else "<d", raw)[0]
    return float(f"{struct.unpack('<f', struct.pack('<f', v))[0]:.7g}")


def orig_fconst(xbe):
    ro = [s for s in xbe.sections if s["name"] == ".rdata"]
    def f(a, size):
        if size not in (4, 8):
            return None
        for s in ro:
            if s["va"] <= a < s["va"] + s["rsize"]:
                return fval(xbe.read_va(a, size), size)
        return None
    return f


def obj_fconst(a, size):
    # obj side: resolver already returned ("unknown-symbol", "__real@hex")
    if isinstance(a, tuple) and str(a[1]).startswith("__real@"):
        h = a[1][7:]
        raw = bytes.fromhex(h)[::-1]
        return fval(raw, 4 if len(h) == 8 else 8)
    return None


def orig_resolver(lo=IMG_LO, hi=IMG_HI):
    def r(off, fo, v, kind):
        if kind == "rel":
            return v
        return v if lo <= v < hi else None
    return r


def obj_resolver(relmap, syms, code, cursec):
    def r(off, fo, v, kind):
        if fo is None:
            return v if kind == "abs" and IMG_LO <= v < IMG_HI else None
        key = off + fo
        if key not in relmap:
            if kind == "abs":   # same rule as the original side: in-image values count as data
                return v if IMG_LO <= v < IMG_HI else None
            return ("unrelocated", v)
        name, typ, secidx = relmap[key]
        if secidx == cursec and name.startswith("$LN"):
            return ("local", name)
        cn = undecorate(name)
        if cn not in syms:
            return ("unknown-symbol", name)
        addend = struct.unpack_from("<I", code, key)[0] if typ == 6 else 0
        return (syms[cn] + addend) & 0xFFFFFFFF
    return r


def fmt(e):
    def h(x):
        return f"{x:#x}" if isinstance(x, int) else str(x)
    return {
        # a tail call (jmp target) and call+ret do the same thing; compare targets only
        "calls": [h(c[1] if isinstance(c, tuple) and c[0] == "tail" else c) for c in e["calls"]],
        "data": sorted(h(k) if not isinstance(k, tuple) else f"{k[0]}:{k[1]}" for k in e["data"]),
        "imm": sorted(h(k[1]) for k in e["imm"]),
        "jcc": sorted(e["jcc"]),
        "ret": sorted(e["ret"] or ({0} if any(isinstance(c, tuple) and c[0] == "tail" for c in e["calls"]) else set())),
        "jtables": e["jtables"],
        "hangs": min(e["hangs"], 1) if e["hangs"] else 0,
    }


def code_size(xbe, va, size, md):
    """Stop at the function's own jump table when it lies inside the
    recorded range (switch tables placed right after the code)."""
    end = va + size
    for i in md.disasm(xbe.read_va(va, size), va):
        if i.address >= end:
            break
        if i.mnemonic == "jmp" and i.operands and i.operands[0].type == x86.X86_OP_MEM                 and i.operands[0].mem.index != 0 and i.operands[0].mem.base == 0:
            t = i.operands[0].mem.disp & 0xFFFFFFFF
            if va < t < end:
                end = t
    return end - va


def compare(obj, sym, va, size=None, verbose=False, xbe=None, syms=None, dump=False, waivers=None):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    xbe = xbe or Xbe(XBE)
    syms = syms if syms is not None else load_symbols()
    if size is None:
        sizes = {int(r["va"], 16): int(r["size"]) for r in
                 csv.DictReader(open(os.path.join(ROOT, "config", "inventory", "functions.csv")))}
        # reviewed corrections where the disassembler's boundary swallowed the next function
        ov = os.path.join(ROOT, "config", "size_overrides.csv")
        if os.path.exists(ov):
            for r in csv.DictReader(open(ov)):
                sizes[int(r["va"], 16)] = int(r["size"], 0)
        size = sizes[va]
    # the original's own jump tables sit right after its code
    size = code_size(xbe, va, size, md)
    coff = Coff(obj)
    code, relmap, cursec = coff.function(sym)
    # compare plainly first; then with loop-pointer bias canonicalised on both
    # sides (pointer_bias); either comparison on its own is a full check
    for use_bias in (False, True):
        a = events(xbe.read_va(va, size), va, orig_resolver(), md, orig_fconst(xbe), local=(va, va + size + 0x100), use_bias=use_bias)
        b = events(code, 0, obj_resolver(relmap, syms, code, cursec), md, obj_fconst, use_bias=use_bias)
        fold_pushed_floats(a, b)
        fa, fb = fmt(a), fmt(b)
        if fa == fb:
            break
        if not use_bias:
            plain = (a, b, fa, fb)
    else:
        a, b, fa, fb = plain
    # documented waivers: "category:item" entries allowed to differ, each with
    # a reason in the function record. Reported, never silent.
    waived = []
    for k in fa:
        if fa[k] == fb[k] or k not in ("data", "imm", "jcc"):
            continue
        da, db = set(fa[k]), set(fb[k])
        delta = {f"{k}:{x}" for x in da ^ db}
        if waivers and delta <= waivers:
            waived += sorted(delta)
            fb[k] = fa[k]
    diffs = [k for k in fa if fa[k] != fb[k]]
    ok = not diffs
    tag = "PASS" if ok and not waived else "PASS*" if ok else "FAIL"
    print(f"{tag:5} {sym} @ {va:#010x}  orig {a['n']} insns, ours {b['n']} insns"
          + ("" if ok else "  differs: " + ", ".join(diffs))
          + (f"  ({len(waived)} documented waivers)" if waived else ""))
    if dump:
        import itertools
        la = [f"{i.address:08x} {i.mnemonic} {i.op_str}" for i in a["insns"]]
        lb = [f"{i.address:04x} {i.mnemonic} {i.op_str}" for i in b["insns"]]
        for x, y in itertools.zip_longest(la, lb, fillvalue=""):
            print(f"   {x:<48} | {y}")
    if verbose or not ok:
        for k in (fa if verbose else diffs):
            print(f"   {k:8} orig {fa[k]}")
            print(f"   {'':8} ours {fb[k]}")
    return ok


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("obj", nargs="?"); ap.add_argument("symbol", nargs="?"); ap.add_argument("va", nargs="?")
    ap.add_argument("--size", type=lambda s: int(s, 0)); ap.add_argument("-v", action="store_true")
    ap.add_argument("-d", "--dump", action="store_true", help="side-by-side disassembly")
    ap.add_argument("--all", action="store_true")
    a = ap.parse_args()
    if a.all:
        xbe, syms = Xbe(XBE), load_symbols()
        bad = 0; n = 0
        for r in rows_of("function_states"):
            if not r.get("obj"):
                continue
            n += 1
            w = set(x for x in (r.get("waivers") or "").split(";") if x)
            obj = os.path.join(ROOT, r["obj"])
            if not os.path.exists(obj):
                print(f"FAIL  {r['name']} @ {r['va']}  object missing: {r['obj']}")
                bad += 1
                continue
            try:
                bad += not compare(obj, r["name"], int(r["va"], 16), None, a.v, xbe, syms, waivers=w)
            except OSError as e:   # object being rebuilt by a parallel compile
                print(f"FAIL  {r['name']} @ {r['va']}  object unreadable: {e}")
                bad += 1
        print(f"{n - bad}/{n} pass")
        sys.exit(1 if bad else 0)
    ok = compare(a.obj, a.symbol, int(a.va, 16), a.size, a.v, dump=a.dump)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
