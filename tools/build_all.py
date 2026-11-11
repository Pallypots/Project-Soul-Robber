#!/usr/bin/env python3
"""Rebuild every recorded source file into the object directory its
function_states rows name, then (optionally) run the structural checker.
Usage: py -3 tools/build_all.py [--check]
Needed after changing a shared header (include/oogie.h etc.)."""
import csv, glob, os, subprocess, sys
from collections import defaultdict

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
groups = defaultdict(set)
for p in glob.glob(os.path.join(ROOT, "config", "function_states*.csv")):
    for r in csv.DictReader(open(p)):
        if r.get("obj") and r.get("source"):
            groups[os.path.dirname(r["obj"])].add(r["source"])
errors = 0
for objdir, srcs in sorted(groups.items()):
    srcs = sorted(srcs)
    for i in range(0, len(srcs), 4):
        batch = [s.replace("/", "\\") for s in srcs[i:i + 4]]
        out = subprocess.run(["cmd", "/c", "tools\\clto.bat", objdir.replace("/", "\\")] + batch,
                             cwd=ROOT, capture_output=True, text=True).stdout
        if out.strip():
            errors += 1
            print(out.strip())
print(f"built {sum(len(s) for s in groups.values())} files in {len(groups)} object dirs, {errors} batches with messages")
if "--check" in sys.argv:
    sys.exit(subprocess.call([sys.executable, os.path.join(ROOT, "tools", "xcompare.py"), "--all"], cwd=ROOT))
