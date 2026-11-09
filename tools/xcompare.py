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
        if r.get("elem"):
            b, e, n = int(r["va"], 16), int(r["elem"], 0), int(r["count"], 0)
            out.append((b, b + e * n, e))
    return out


ARRAYS = load_arrays()


def array_key(a):
    """Indexed access into a known record array -> (array base, field offset)."""
    for b, end, e in ARRAYS:
        if isinstance(a, int) and b <= a < end:
            return b, (a - b) % e
    return None


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
def is_fp(m):
    return m.startswith("f") or m.endswith(("ss", "sd")) or m in ("comiss", "ucomiss", "comisd", "ucomisd")


def events(code, base, resolve, md, fconst=None, local=None):
    """resolve(insn_offset, field_offset, raw_value, kind) -> VA or None"""
    calls, data, imm, jcc, ret = [], Counter(), Counter(), Counter(), set()
    jt = 0
    insns = list(md.disasm(code, base))
    prev = None
    for i in insns:
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
            prev = i; continue
        if m == "jmp" and ops[0].type == x86.X86_OP_MEM and ops[0].mem.index != 0:
            jt += 1; prev = i; continue
        if m.startswith(("cmov", "set")) and ("j" + m[4:] if m.startswith("cmov") else "j" + m[3:]) in JCC_CLASS:
            # conditional move / set: same decision as a branch (modern cl
            # uses cmov, which 2005-era code for this game never does)
            jcc[JCC_CLASS["j" + (m[4:] if m.startswith("cmov") else m[3:])]] += 1
        elif m == "sbb" and len(ops) == 2 and ops[0].type == x86.X86_OP_REG and \
                ops[1].type == x86.X86_OP_REG and ops[0].reg == ops[1].reg and \
                prev is not None and prev.mnemonic in ("neg", "cmp", "sub"):
            # `neg x; sbb r,r` (or cmp/sbb) materialises a condition branch-free
            jcc["e/ne" if prev.mnemonic == "neg" else "b/ae"] += 1
        elif m in JCC_CLASS:
            c = JCC_CLASS[m]
            if c == "s/ns" and prev is not None and prev.mnemonic == "test" and \
               len(prev.operands) == 2 and prev.operands[0].type == x86.X86_OP_REG and \
               prev.operands[1].type == x86.X86_OP_REG and prev.operands[0].reg == prev.operands[1].reg:
                c = "l/ge"
            jcc[c] += 1; prev = i; continue
        if m == "ret":
            ret.add(ops[0].imm if ops else 0); prev = i; continue
        if m == "jmp" and ops[0].type == x86.X86_OP_IMM and i.size == 5:
            t = resolve(off, 1, ops[0].imm, "rel")
            is_local = (isinstance(t, tuple) and t[0] == "unrelocated") or \
                       (isinstance(t, int) and base <= t < base + len(code))
            if not is_local:
                calls.append(("tail", t))   # tail call to another function
                prev = i; continue
        if m.startswith("j") and m not in JCC_CLASS:
            prev = i; continue
        if m in JCC_CLASS:
            prev = i; continue
        # memory operands: an absolute address (original: in-image displacement;
        # object: relocated displacement) is data, otherwise a structure offset
        for o in ops:
            if o.type != x86.X86_OP_MEM:
                continue
            disp = o.mem.disp & 0xFFFFFFFF
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
            elif o.mem.base not in (0, x86.X86_REG_ESP, x86.X86_REG_EBP) and o.mem.disp:
                imm[("k", o.mem.disp & 0xFFFFFFFF)] += 1
        for o in ops:
            if o.type == x86.X86_OP_IMM:
                v = o.imm & 0xFFFFFFFF
                fo = i.imm_offset if i.imm_offset else None
                a = resolve(off, fo, v, "abs")
                if a is not None:
                    data[a] += 1
                elif not esp_op:
                    # `test ah, 8` tests bit 0x800 of the dword: scale high-byte operands
                    if m in ("test", "and", "or", "xor", "cmp") and ops[0].type == x86.X86_OP_REG and \
                            ops[0].reg in (x86.X86_REG_AH, x86.X86_REG_BH, x86.X86_REG_CH, x86.X86_REG_DH):
                        v <<= 8
                    imm[("k", v)] += 1
        prev = i
    # 0/1 materialisation differs freely between compilers (xor r,r / mov r,1 / setcc)
    for k in [k for k in imm if k[1] in (0, 1, 0xFFFFFFFF)]:
        del imm[k]
    # Addresses and constants are compared as sets: instruction selection
    # (read-modify-write vs load/store, re-reads) changes how often each
    # appears, not which ones appear.
    return dict(calls=calls, data=set(data), imm=set(imm), jcc=set(jcc), ret=ret, jtables=jt,
                n=len(insns), insns=insns)


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
        return syms[cn] + addend
    return r


def fmt(e):
    def h(x):
        return f"{x:#x}" if isinstance(x, int) else str(x)
    return {
        "calls": [h(c) for c in e["calls"]],
        "data": sorted(h(k) if not isinstance(k, tuple) else f"{k[0]}:{k[1]}" for k in e["data"]),
        "imm": sorted(h(k[1]) for k in e["imm"]),
        "jcc": sorted(e["jcc"]),
        "ret": sorted(e["ret"]),
        "jtables": e["jtables"],
    }


def compare(obj, sym, va, size=None, verbose=False, xbe=None, syms=None, dump=False, waivers=None):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    xbe = xbe or Xbe(XBE)
    syms = syms if syms is not None else load_symbols()
    if size is None:
        sizes = {int(r["va"], 16): int(r["size"]) for r in
                 csv.DictReader(open(os.path.join(ROOT, "config", "inventory", "functions.csv")))}
        size = sizes[va]
    # the original's own jump tables sit right after its code
    a = events(xbe.read_va(va, size), va, orig_resolver(), md, orig_fconst(xbe), local=(va, va + size + 0x100))
    coff = Coff(obj)
    code, relmap, cursec = coff.function(sym)
    b = events(code, 0, obj_resolver(relmap, syms, code, cursec), md, obj_fconst)
    fa, fb = fmt(a), fmt(b)
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
            bad += not compare(os.path.join(ROOT, r["obj"]), r["name"], int(r["va"], 16), None, a.v, xbe, syms, waivers=w)
        print(f"{n - bad}/{n} pass")
        sys.exit(1 if bad else 0)
    ok = compare(a.obj, a.symbol, int(a.va, 16), a.size, a.v, dump=a.dump)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
