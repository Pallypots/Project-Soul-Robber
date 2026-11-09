#!/usr/bin/env python3
"""Generate the decompilation progress chart (docs/progress.svg) and a
markdown table (docs/progress.md) from config/inventory/functions.csv and
config/function_states.csv. Counts game code only in the main bar; library
code (XDK, Bink) is shown separately and is not part of the decomp target.

Usage: py -3 tools/progress.py
"""
import csv, glob, os
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
    ("Unanalyzed",              "#30363d"),
]
COLOR = dict(STATES)
# Dark theme (GitHub dark palette)
BG, BORDER, TEXT, MUTED, LIBSQ = "#0d1117", "#30363d", "#e6edf3", "#8b949e", "#161b22"


def state_rows():
    out = []
    for path in sorted(glob.glob(P("config", "function_states.csv")) + glob.glob(P("config", "function_states_*.csv"))):
        out += list(csv.DictReader(open(path)))
    return out


def load():
    states = {}
    if True:
        for r in state_rows():
            if r["state"] not in COLOR:
                raise SystemExit(f"unknown state {r['state']!r} for {r['va']}")
            va = int(r["va"], 16)
            if va in states:
                raise SystemExit(f"function {r['va']} recorded twice")
            states[va] = r["state"]
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
           f'<rect width="{W}" height="{H}" rx="8" fill="{BG}" stroke="{BORDER}"/>',
           f'<text x="{X0}" y="30" font-size="17" font-weight="600" fill="{TEXT}">Project Soul Robber: game code decompiled</text>']

    def bar(y, counts, total, label):
        out.append(f'<text x="{X0}" y="{y - 6}" font-size="12" fill="{MUTED}">{label}</text>')
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
        out.append(f'<text x="{cx + 17}" y="{cy + 10.5}" font-size="11.5" fill="{TEXT}">{name} ({fn[name]})</text>')
    out.append(f'<text x="{X0}" y="{H - 14}" font-size="10.5" fill="{MUTED}">Library code ({lib_fn:,} functions, {lib_by:,} bytes: XDK, Bink) is not counted. Byte matching is blocked; see docs/toolchain.md.</text>')
    out.append("</svg>")
    open(P("docs", "progress.svg"), "w", encoding="utf-8").write("\n".join(out) + "\n")

    write_map(rows, states)
    write_function_list()

    md = ["| State | Functions | Unique bytes |", "|---|---|---|"]
    for name, _ in STATES:
        md.append(f"| {name} | {fn[name]:,} | {by[name]:,} |")
    md.append(f"| **Game total** | **{tot_fn:,}** | **{tot_by:,}** |")
    md.append(f"| Library (not counted) | {lib_fn:,} | {lib_by:,} |")
    md.append(f"| Unknown owner | {unk_fn:,} | |")
    open(P("docs", "progress.md"), "w", encoding="utf-8").write("\n".join(md) + "\n")
    print("\n".join(md))


def write_function_list():
    """docs/functions.md: every recovered function with state and waivers."""
    rs = state_rows()
    rs.sort(key=lambda r: int(r["va"], 16))
    md = ["# Recovered functions", "",
          "Generated by `tools/progress.py` from `config/function_states.csv`. Names are inferred.", "",
          "| VA | Name | State | Source | Waivers | Notes |", "|---|---|---|---|---|---|"]
    for r in rs:
        w = (r.get("waivers") or "").replace(";", ", ")
        md.append(f"| {r['va']} | {r['name']} | {r['state']} | [{r['source']}](../{r['source']}) | {w} | {r.get('notes') or ''} |")
    open(P("docs", "functions.md"), "w", encoding="utf-8").write("\n".join(md) + "\n")


def write_map(rows, states):
    """docs/progress_map.svg: each square is 2,048 bytes of .text and library
    sections, in address order. Game squares are grey until source is recovered
    in them: the colour is the best state present, and the brightness grows
    with the share of the square's bytes recovered (a faint square = a little).
    Library squares are drawn darker and are not counted."""
    SQ = 2048
    spans = []   # (va, size, kind, state)
    for r in rows:
        g = group(r["owner"])
        if g == "unknown":
            continue
        va = int(r["va"], 16)
        spans.append((va, int(r["unique_bytes"]), g, states.get(va, "Unanalyzed")))
    spans.sort()
    lo = spans[0][0] // SQ * SQ
    hi = max(v + n for v, n, _, _ in spans)
    nsq = (hi - lo + SQ - 1) // SQ
    game_b = [0] * nsq; lib_b = [0] * nsq; done_b = [0] * nsq; best = [None] * nsq
    rank = {name: i for i, (name, _) in enumerate(STATES)}
    for va, n, g, st in spans:
        a = va
        while a < va + n:
            k = (a - lo) // SQ
            take = min(va + n, lo + (k + 1) * SQ) - a
            if g == "library":
                lib_b[k] += take
            else:
                game_b[k] += take
                if st not in ("Unanalyzed", "Analyzed"):
                    done_b[k] += take
                    if best[k] is None or rank[st] < rank[best[k]]:
                        best[k] = st
            a += take
    cols, cell, gap, x0, y0 = 48, 14, 4, 24, 96
    step = cell + gap
    used = [k for k in range(nsq) if game_b[k] or lib_b[k]]   # skip data gaps between sections
    nrows = (len(used) + cols - 1) // cols
    W = x0 * 2 + cols * step - gap
    H = y0 + nrows * step + 70
    tot_game = sum(game_b); tot_done = sum(done_b)
    out = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}" font-family="Segoe UI,Helvetica,Arial,sans-serif">',
           f'<rect width="{W}" height="{H}" rx="8" fill="{BG}" stroke="{BORDER}"/>',
           f'<text x="{x0}" y="42" font-size="24" font-weight="700" fill="{TEXT}">Decompiled: {100 * tot_done / tot_game:.2f}% of the game&#8217;s code</text>',
           f'<text x="{x0}" y="66" font-size="13" fill="{MUTED}">{tot_done:,} of {tot_game:,} game code bytes. Each square is 2,048 bytes of the executable&#8217;s code, in address order. Lit: source recovered. Grey: not yet.</text>']
    for pos, k in enumerate(used):
        x = x0 + (pos % cols) * step; y = y0 + (pos // cols) * step
        if game_b[k] >= lib_b[k]:
            if best[k]:
                op = 0.35 + 0.65 * done_b[k] / game_b[k]
                out.append(f'<rect x="{x}" y="{y}" width="{cell}" height="{cell}" rx="3" fill="{COLOR["Unanalyzed"]}"/>')
                out.append(f'<rect x="{x}" y="{y}" width="{cell}" height="{cell}" rx="3" fill="{COLOR[best[k]]}" fill-opacity="{op:.2f}"><title>{lo + k * SQ:#010x}: {done_b[k]} of {game_b[k]} bytes {best[k]}</title></rect>')
            else:
                out.append(f'<rect x="{x}" y="{y}" width="{cell}" height="{cell}" rx="3" fill="{COLOR["Unanalyzed"]}"/>')
        else:
            out.append(f'<rect x="{x}" y="{y}" width="{cell}" height="{cell}" rx="3" fill="{LIBSQ}" stroke="{BORDER}" stroke-width="0.5"/>')
    ly = y0 + nrows * step + 18
    legend = [(n, COLOR[n]) for n, _ in STATES if n not in ("Analyzed", "Unanalyzed")] + [("Not decompiled yet", COLOR["Unanalyzed"]), ("XDK, C runtime, Bink (not counted)", LIBSQ)]
    for i, (name, col) in enumerate(legend):
        cx = x0 + (i % 4) * ((W - 2 * x0) // 4); cy = ly + (i // 4) * 22
        out.append(f'<rect x="{cx}" y="{cy}" width="13" height="13" rx="3" fill="{col}" stroke="{BORDER}" stroke-width="0.5"/>')
        out.append(f'<text x="{cx + 19}" y="{cy + 11}" font-size="12" fill="{TEXT}">{name}</text>')
    out.append("</svg>")
    open(P("docs", "progress_map.svg"), "w", encoding="utf-8").write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
