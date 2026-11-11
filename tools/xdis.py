#!/usr/bin/env python3
"""Print the original disassembly of functions from the reference XBE.
Usage: py -3 tools/xdis.py <va> [<va> ...]     (size taken from functions.csv)
       py -3 tools/xdis.py <va>:<size>
Output is for local study only; do not commit dumps (see .gitignore)."""
import csv, os, sys
sys.path.insert(0, os.path.dirname(__file__))
from xbe_inventory import Xbe
import capstone

ROOT = os.path.join(os.path.dirname(__file__), "..")
XBE = os.environ.get("OOGIE_XBE", "C:/ProjectOogie/game/default.xbe")


def sizes():
    out = {int(r["va"], 16): int(r["size"]) for r in
           csv.DictReader(open(os.path.join(ROOT, "config", "inventory", "functions.csv")))}
    ov = os.path.join(ROOT, "config", "size_overrides.csv")
    if os.path.exists(ov):
        for r in csv.DictReader(open(ov)):
            out[int(r["va"], 16)] = int(r["size"], 0)
    return out


def main():
    x = Xbe(XBE)
    sz = sizes()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    for a in sys.argv[1:]:
        va, _, n = a.partition(":")
        va = int(va, 16)
        n = int(n, 0) if n else sz[va]
        print(f"; ---- {va:#010x} size {n}")
        for i in md.disasm(x.read_va(va, n), va):
            print(f"{i.address:08x}  {i.bytes.hex():<20} {i.mnemonic} {i.op_str}")
        print()


if __name__ == "__main__":
    main()
