#!/usr/bin/env python3
"""Generate the decompilation progress chart (docs/progress.svg) and a
markdown table (docs/progress.md) from config/inventory/functions.csv and
config/function_states.csv. Counts game code only in the main bar; library
code (XDK, Bink) is shown separately and is not part of the decomp target.

Usage: py -3 tools/progress.py
"""
import csv, os
from collections import Counter

ROOT = os.path.join(os.path.dirname(__file__), "..")
P = lambda *a: os.path.join(ROOT, *a)

# Order = best to worst. Colours: green family = verified, amber = draft, grey = none.
STATES = [
    ("Exact linked match",      "#1a7f37"),
    ("Relocation-aware match",  "#2da44e"),
    ("Native-integrated",       "#0969da"),
    ("Semantic-tested",         "#54aeff"),
    ("Structurally compared",   "#bf8700"),
    ("Draft source",            "#d4a72c"),
    ("Analyzed",                "#8250df"),
    ("Unanalyzed",              "#d0d7de"),
]
COLOR = dict(STATES)


def load():
    states = {}
    with open(P("config", "function_states.csv")) as f:
        for r in csv.DictReader(f):
            if r["state"] not in COLOR:
                raise SystemExit(f"unknown state {r['state']!r} for {r['va']}")
            states[int(r["va"], 16)] = r["state"]
    rows = list(csv.DictReader(open(P("config", "inventory", "functions.csv"))))
    known = {int(r["va"], 16) for r in rows}
    missing = set(states) - known
    if missing:
        raise SystemExit("states for addresses not in inventory: " + ", ".join(hex(m) for m in missing))
    return rows, states


def group(owner):
    return "game" if owner == "game" else "library" if owner.startswith(("XDK", "RAD")) else "unknown"


def main():
    rows, states = load()
    fn, by = Counter(), Counter()
    tot_fn, tot_by, lib_fn, lib_by, unk_fn = 0, 0, 0, 0, 0
    for r in rows:
        g = group(r["owner"])
        b = int(r["unique_bytes"])
        if g == "library":
            lib_fn += 1; lib_by += b; continue
        if g == "unknown":
            unk_fn += 1; continue
        s = states.get(int(r["va"], 16), "Unanalyzed")
        fn[s] += 1; by[s] += b; tot_fn += 1; tot_by += b

    W, H, X0, BAR = 760, 250, 20, 720
    out = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}" font-family="Segoe UI,Helvetica,Arial,sans-serif">',
           f'<rect width="{W}" height="{H}" rx="8" fill="#ffffff" stroke="#d0d7de"/>',
           f'<text x="{X0}" y="30" font-size="17" font-weight="600" fill="#1f2328">Project Soul Robber: game code decompiled</text>']

    def bar(y, counts, total, label):
        out.append(f'<text x="{X0}" y="{y - 6}" font-size="12" fill="#57606a">{label}</text>')
        out.append(f'<rect x="{X0}" y="{y}" width="{BAR}" height="22" rx="4" fill="{COLOR["Unanalyzed"]}"/>')
        x = X0
        for name, col in STATES[:-1]:
            if counts[name]:
                w = max(2.0, BAR * counts[name] / total)
                out.append(f'<rect x="{x:.1f}" y="{y}" width="{w:.1f}" height="22" fill="{col}"><title>{name}: {counts[name]}</title></rect>')
                x += w
    done_by = tot_by - by["Unanalyzed"] - by["Analyzed"]
    done_fn = tot_fn - fn["Unanalyzed"] - fn["Analyzed"]
    bar(66, by, tot_by, f"By code size: {done_by:,} of {tot_by:,} bytes have recovered source ({100 * done_by / tot_by:.3f}%)")
    bar(118, fn, tot_fn, f"By function: {done_fn:,} of {tot_fn:,} functions ({100 * done_fn / tot_fn:.2f}%)")
    # legend
    lx, ly = X0, 166
    for i, (name, col) in enumerate(STATES):
        cx = lx + (i % 4) * 182
        cy = ly + (i // 4) * 22
        out.append(f'<rect x="{cx}" y="{cy}" width="12" height="12" rx="2" fill="{col}"/>')
        out.append(f'<text x="{cx + 17}" y="{cy + 10.5}" font-size="11.5" fill="#1f2328">{name} ({fn[name]})</text>')
    out.append(f'<text x="{X0}" y="{H - 14}" font-size="10.5" fill="#57606a">Library code ({lib_fn:,} functions, {lib_by:,} bytes: XDK, Bink) is not counted. Byte matching is blocked; see docs/toolchain.md.</text>')
    out.append("</svg>")
    open(P("docs", "progress.svg"), "w", encoding="utf-8").write("\n".join(out) + "\n")

    write_map(rows, states)

    md = ["| State | Functions | Unique bytes |", "|---|---|---|"]
    for name, _ in STATES:
        md.append(f"| {name} | {fn[name]:,} | {by[name]:,} |")
    md.append(f"| **Game total** | **{tot_fn:,}** | **{tot_by:,}** |")
    md.append(f"| Library (not counted) | {lib_fn:,} | {lib_by:,} |")
    md.append(f"| Unknown owner | {unk_fn:,} | |")
    open(P("docs", "progress.md"), "w", encoding="utf-8").write("\n".join(md) + "\n")
    print("\n".join(md))


def write_map(rows, states):
    """docs/progress_map.svg: one square per game function, in address order
    (left to right, top to bottom), coloured by state. Runs of equal colour in
    a row are drawn as one rectangle to keep the file small."""
    game = [r for r in rows if group(r["owner"]) == "game"]
    cols, cell, gap, x0, y0 = 120, 6, 1, 20, 50
    step = cell + gap
    nrows = (len(game) + cols - 1) // cols
    W = x0 * 2 + cols * step
    H = y0 + nrows * step + 40
    out = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}" font-family="Segoe UI,Helvetica,Arial,sans-serif">',
           f'<rect width="{W}" height="{H}" rx="8" fill="#ffffff" stroke="#d0d7de"/>',
           f'<text x="{x0}" y="30" font-size="17" font-weight="600" fill="#1f2328">Game code map: one square per function ({len(game):,})</text>']
    cols_of = [COLOR[states.get(int(r["va"], 16), "Unanalyzed")] for r in game]
    for row in range(nrows):
        seg = cols_of[row * cols:(row + 1) * cols]
        i = 0
        while i < len(seg):
            j = i
            while j < len(seg) and seg[j] == seg[i]:
                j += 1
            w = (j - i) * step - gap
            out.append(f'<rect x="{x0 + i * step}" y="{y0 + row * step}" width="{w}" height="{cell}" fill="{seg[i]}"/>')
            i = j
    first, last = game[0]["va"], game[-1]["va"]
    out.append(f'<text x="{x0}" y="{H - 16}" font-size="10.5" fill="#57606a">Address order {first} (top left) to {last} (bottom right). Colours as in the progress bar. Library code not shown.</text>')
    out.append("</svg>")
    open(P("docs", "progress_map.svg"), "w", encoding="utf-8").write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
