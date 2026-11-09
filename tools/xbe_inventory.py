#!/usr/bin/env python3
"""Read-only XBE inventory for Project Oogie Decomp.

Usage:
  xbe_inventory.py header    <default.xbe>
  xbe_inventory.py sections  <default.xbe> [out.csv]
  xbe_inventory.py functions <default.xbe> <functions.json> <out.csv> [summary.md]

Never writes to the XBE. Every field read is bounds-checked; malformed input
fails with XbeError instead of guessing. Raw (file) ranges and mapped
(virtual, possibly zero-filled) ranges are reported separately.

`functions.json` is the candidate function list from XboxRecomp's disassembler
(C:/ProjectOogie/build_out/disasm/functions.json). This tool re-reads every
candidate's bytes from the XBE itself, so the classification evidence does not
depend on the recomp's own labels.
"""
import csv, hashlib, json, struct, sys
from collections import Counter, defaultdict

XOR_ENTRY = {"retail": 0xA8FC57AB, "debug": 0x94859D4B}
XOR_THUNK = {"retail": 0x5B6D40B6, "debug": 0xEFB1F152}

# Sections whose names are the XDK/middleware library that owns them.
# Evidence: the library-version table (XDK 1.0.5849) plus the section names
# placed there by the XDK linker. Code in these sections is not game code.
LIB_SECTIONS = {
    "D3D": "XDK D3D8", "D3DX": "XDK D3DX8", "XGRPH": "XDK XGRAPHICS",
    "DSOUND": "XDK DSOUND", "XACTENG": "XDK XACT", "XPP": "XDK XPP (USB/input)",
    "WMADEC": "XDK WMA decoder", "DOLBY": "XDK Dolby",
}


class XbeError(Exception):
    pass


class Xbe:
    def __init__(self, path):
        with open(path, "rb") as f:
            self.data = f.read()
        self.path = path
        d = self.data
        if len(d) < 0x178 or d[:4] != b"XBEH":
            raise XbeError("not an XBE (missing XBEH magic or too short)")
        self.base = self.u32(0x104)
        self.size_headers = self.u32(0x108)
        self.size_image = self.u32(0x10C)
        self.timedate = self.u32(0x114)
        self.cert_addr = self.u32(0x118)
        self.num_sections = self.u32(0x11C)
        self.sect_hdr_addr = self.u32(0x120)
        raw_entry = self.u32(0x128)
        raw_thunk = self.u32(0x158)
        self.tls_addr = self.u32(0x12C)
        self.debug_path_addr = self.u32(0x14C)
        self.num_libs = self.u32(0x160)
        self.libs_addr = self.u32(0x164)
        if self.size_headers > len(d):
            raise XbeError("header size exceeds file size")
        # Decide retail vs debug by which XOR key puts the entry inside the image.
        self.kind = None
        for kind, key in XOR_ENTRY.items():
            ep = raw_entry ^ key
            if self.base <= ep < self.base + self.size_image:
                self.kind, self.entry = kind, ep
                break
        if self.kind is None:
            raise XbeError("entry point decodes outside the image with both keys")
        self.raw_entry, self.raw_thunk = raw_entry, raw_thunk
        self.thunk = raw_thunk ^ XOR_THUNK[self.kind]
        self.sections = self._sections()

    # -- bounds-checked readers (header addresses are virtual, base-relative)
    def u32(self, off):
        if off < 0 or off + 4 > len(self.data):
            raise XbeError(f"read past end at file offset {off:#x}")
        return struct.unpack_from("<I", self.data, off)[0]

    def hdr_off(self, va):
        off = va - self.base
        if not 0 <= off < self.size_headers:
            raise XbeError(f"header pointer {va:#x} outside header region")
        return off

    def cstr(self, va, limit=260):
        off = self.hdr_off(va)
        end = self.data.find(b"\0", off, off + limit)
        if end < 0:
            raise XbeError(f"unterminated string at {va:#x}")
        return self.data[off:end].decode("latin-1")

    def _sections(self):
        out = []
        off = self.hdr_off(self.sect_hdr_addr)
        if self.num_sections > 256:
            raise XbeError("implausible section count")
        for i in range(self.num_sections):
            o = off + i * 56
            if o + 56 > self.size_headers:
                raise XbeError("section header table truncated")
            flags, va, vsz, raw, rsz, name_va = struct.unpack_from("<6I", self.data, o)
            if raw + rsz > len(self.data):
                raise XbeError(f"section {i} raw range past end of file")
            if rsz > vsz:
                raise XbeError(f"section {i} raw size larger than virtual size")
            out.append(dict(index=i, name=self.cstr(name_va, 16), flags=flags,
                            va=va, vsize=vsz, raw=raw, rsize=rsz,
                            exec=bool(flags & 4), write=bool(flags & 1)))
        return out

    def libraries(self):
        out = []
        if self.num_libs == 0:
            return out
        off = self.hdr_off(self.libs_addr)
        for i in range(self.num_libs):
            o = off + 16 * i
            if o + 16 > self.size_headers:
                raise XbeError("library table truncated")
            name = self.data[o:o + 8].rstrip(b"\0").decode("latin-1")
            maj, mnr, bld, fl = struct.unpack_from("<4H", self.data, o + 8)
            out.append(f"{name} {maj}.{mnr}.{bld}")
        return out

    def num_thunks(self):
        """Entries in the kernel thunk table, up to its zero terminator."""
        n = 0
        while self.read_va_u32(self.thunk + 4 * n) != 0:
            n += 1
            if n > 400:
                raise XbeError("kernel thunk table has no terminator")
        return n

    def read_va_u32(self, va):
        return struct.unpack("<I", self.read_va(va, 4))[0]

    def section_of(self, va):
        for s in self.sections:
            if s["va"] <= va < s["va"] + s["vsize"]:
                return s
        return None

    def read_va(self, va, n):
        """Bytes at a virtual address. Fails if any byte is not file-backed."""
        s = self.section_of(va)
        if s is None:
            raise XbeError(f"{va:#x} is not in any section")
        rel = va - s["va"]
        if rel + n > s["rsize"]:
            raise XbeError(f"{va:#x}+{n} runs into zero-filled (non-file) range of {s['name']}")
        return self.data[s["raw"] + rel:s["raw"] + rel + n]


def cmd_header(x):
    print(f"file        {x.path}")
    print(f"size        {len(x.data)}")
    print(f"sha256      {hashlib.sha256(x.data).hexdigest()}")
    print(f"sha1        {hashlib.sha1(x.data).hexdigest()}")
    print(f"kind        {x.kind}")
    print(f"base        {x.base:#010x}  image size {x.size_image:#x}")
    print(f"entry       {x.entry:#010x}  (raw {x.raw_entry:#010x})")
    print(f"kthunk      {x.thunk:#010x}  (raw {x.raw_thunk:#010x})")
    print(f"kthunks     {x.num_thunks()}")
    print(f"tls         {x.tls_addr:#010x}")
    print(f"timedate    {x.timedate}")
    print(f"debug path  {x.cstr(x.debug_path_addr) if x.debug_path_addr else '-'}")
    print(f"sections    {len(x.sections)}")
    print("libraries   " + ", ".join(x.libraries()))


def cmd_sections(x, out=None):
    rows = [["index", "name", "va", "va_end", "vsize", "raw", "rsize", "zero_fill", "flags", "exec", "write"]]
    for s in x.sections:
        rows.append([s["index"], s["name"], f"{s['va']:#010x}", f"{s['va'] + s['vsize']:#010x}",
                     s["vsize"], f"{s['raw']:#x}", s["rsize"], s["vsize"] - s["rsize"],
                     f"{s['flags']:#x}", int(s["exec"]), int(s["write"])])
    w = csv.writer(open(out, "w", newline="") if out else sys.stdout)
    w.writerows(rows)


def kernel_refs(x, va, size):
    """Count `call/jmp dword ptr [thunk+4n]` and `mov reg,[thunk+4n]` encodings.
    The thunk table is 125 entries; game code normally reaches the kernel only
    through XAPI/CRT wrappers, so direct references are library evidence."""
    try:
        b = x.read_va(va, size)
    except XbeError:
        return -1
    lo, hi = x.thunk, x.thunk + 4 * x.num_thunks()
    n = 0
    for i in range(len(b) - 5):
        # ff 15 / ff 25 disp32, a1 disp32, 8b 0d/15/1d/35/3d disp32
        if b[i] == 0xFF and b[i + 1] in (0x15, 0x25):
            t = struct.unpack_from("<I", b, i + 2)[0]
        elif b[i] == 0xA1:
            t = struct.unpack_from("<I", b, i + 1)[0]
        elif b[i] == 0x8B and b[i + 1] in (0x0D, 0x15, 0x1D, 0x35, 0x3D):
            t = struct.unpack_from("<I", b, i + 2)[0]
        else:
            continue
        if lo <= t < hi and (t - lo) % 4 == 0:
            n += 1
    return n


def classify(x, funcs, crt_names):
    """Assign owner + confidence. Rules, in order (recorded in docs/inventory.md):
    1. Function in a library-named section -> that library, high.
    2. BINK* sections -> RAD Bink, high (section names + Bink strings).
    3. .text at/after LIB_TEXT_START -> XDK XAPI/LIBCMT, medium.
    4. .text before it -> game, medium (refined to low if it calls the kernel
       directly or matches a CRT signature, which marks it 'library?').
    """
    out = []
    for f in funcs:
        va, size, sec = f["va"], f["size"], f["section"]
        kr = kernel_refs(x, va, size) if size > 0 else 0
        crt = crt_names.get(va)
        if sec in LIB_SECTIONS:
            owner, conf, why = LIB_SECTIONS[sec], "high", "section name"
        elif sec.startswith("BINK"):
            owner, conf, why = "RAD Bink", "high", "section name"
        elif sec == ".text" and va >= LIB_TEXT_START:
            owner, conf, why = "XDK XAPI/LIBCMT (.text tail)", "medium", "after game/lib boundary"
        elif sec == ".text":
            if crt:
                owner, conf, why = "CRT? (signature)", "low", f"crt signature {crt} inside game range"
            elif kr > 0:
                # XDK headers map some Win32 calls (e.g. EnterCriticalSection ->
                # RtlEnterCriticalSection) straight to kernel imports, so game code
                # can reference the thunk table itself. Kept as game, lower confidence.
                owner, conf, why = "game", "low", f"{kr} direct kernel thunk refs (inlined XDK import)"
            else:
                owner, conf, why = "game", "medium", "before game/lib boundary"
        else:
            owner, conf, why = "unknown", "low", "unexpected section"
        out.append(dict(f, owner=owner, confidence=conf, kernel_refs=kr, evidence=why,
                        aligned16=int(va % 16 == 0), crt_name=crt or ""))
    return out


# First .text address attributed to XDK libraries. Evidence (see docs/inventory.md):
# * function starts switch from 16-byte aligned (game, compiled with padding)
#   to unaligned at 0x001BC6FD (first odd start after 0x001BC6D0);
# * known XAPI routines (DuplicateHandle 0x001BC71B, CreateFile site 0x001BCE35,
#   SuspendThread 0x001BD290, SwitchToThread 0x001BD332, CreateThread 0x001BD49C);
# * the entry point 0x001BEF07 (XAPI mainXapiStartup) lies past it.
# Overridden by find_boundary() output when run; this constant is the reviewed value.
LIB_TEXT_START = 0x001BC6D0


def find_boundary(funcs):
    """Report the first run of >=8 consecutive non-16-aligned .text starts."""
    t = sorted(f["va"] for f in funcs if f["section"] == ".text"
               and f["method"] in ("call_target", "prologue"))
    run = 0
    for i, va in enumerate(t):
        run = run + 1 if va % 16 else 0
        if run >= 8:
            return t[i - 7]
    return None


def cmd_functions(x, fjson, out_csv, summary=None):
    raw = json.load(open(fjson))
    funcs = []
    for f in raw:
        va = int(f["start"], 16)
        funcs.append(dict(va=va, size=int(f["size"]), section=f["section"],
                          method=f.get("detection_method", ""), ninsn=f.get("num_instructions", 0)))
    crt_path = fjson.replace("disasm/functions.json", "func_id/crt_functions.json")
    try:
        crt_names = {int(c["address"], 16): c["name"] for c in json.load(open(crt_path))}
    except OSError:
        crt_names = {}
    # Shared tails / aliases: candidates fully inside an earlier one are counted once for bytes.
    funcs.sort(key=lambda f: f["va"])
    rows = classify(x, funcs, crt_names)
    end = 0
    for r in rows:
        r["unique_bytes"] = max(0, r["va"] + r["size"] - max(r["va"], end))
        end = max(end, r["va"] + r["size"])
    with open(out_csv, "w", newline="") as fo:
        w = csv.writer(fo)
        w.writerow(["va", "size", "unique_bytes", "section", "owner", "confidence", "evidence",
                    "kernel_refs", "aligned16", "crt_name", "detect", "ninsn", "state"])
        for r in rows:
            w.writerow([f"{r['va']:#010x}", r["size"], r["unique_bytes"], r["section"], r["owner"],
                        r["confidence"], r["evidence"], r["kernel_refs"], r["aligned16"],
                        r["crt_name"], r["method"], r["ninsn"], "Unanalyzed"])
    cnt, byt = Counter(), Counter()
    group = lambda o: ("game" if o == "game" else "library" if o.startswith(("XDK", "RAD")) else "unknown/unclassified")
    for r in rows:
        cnt[(group(r["owner"]), r["owner"], r["confidence"])] += 1
        byt[(group(r["owner"]), r["owner"], r["confidence"])] += r["unique_bytes"]
    gt, gb = Counter(), Counter()
    for k in cnt:
        gt[k[0]] += cnt[k]; gb[k[0]] += byt[k]
    lines = [f"# Function inventory summary", "",
             f"XBE sha256 `{hashlib.sha256(x.data).hexdigest()}`; candidates from `{fjson}`.",
             f"Aligned-start boundary heuristic found: {find_boundary(funcs):#010x}; reviewed boundary used: {LIB_TEXT_START:#010x}.", "",
             "| Group | Owner | Confidence | Functions | Unique code bytes |", "|---|---|---|---|---|"]
    for k in sorted(cnt):
        lines.append(f"| {k[0]} | {k[1]} | {k[2]} | {cnt[k]} | {byt[k]} |")
    lines += ["", "| Group | Functions | Unique code bytes |", "|---|---|---|"]
    for g in sorted(gt):
        lines.append(f"| {g} | {gt[g]} | {gb[g]} |")
    lines.append(f"| total | {sum(gt.values())} | {sum(gb.values())} |")
    text = "\n".join(lines) + "\n"
    if summary:
        open(summary, "w").write(text)
    print(text)


def main(argv):
    if len(argv) < 3:
        print(__doc__); return 2
    x = Xbe(argv[2])
    if argv[1] == "header":
        cmd_header(x)
    elif argv[1] == "sections":
        cmd_sections(x, argv[3] if len(argv) > 3 else None)
    elif argv[1] == "functions" and len(argv) >= 5:
        cmd_functions(x, argv[3], argv[4], argv[5] if len(argv) > 5 else None)
    else:
        print(__doc__); return 2
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main(sys.argv))
    except XbeError as e:
        print(f"error: {e}", file=sys.stderr); sys.exit(1)
